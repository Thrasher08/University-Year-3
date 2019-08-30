#include "Renderer.h"
#include "../../Common/TextureWriter.h"
#include "../../Common/Maths.h"
#include "../../Common/Matrix3.h"
using namespace NCL;
using namespace Rendering;
using namespace CSC3223;

Renderer::Renderer(Window& w) : OGLRenderer(w)
{
	defaultShader	= new OGLShader("rasterisationVert.glsl", "rasterisationFrag.glsl");
	projMatrix		= Matrix4::Orthographic(-1.0f, 1.0f, (float)currentWidth, 0.0f, 0.0f, (float)currentHeight);
}

Renderer::~Renderer()
{
	delete defaultShader;
}

void Renderer::RenderFrame() {
	OGLShader* activeShader = nullptr;

	int modelLocation	= 0; 

	for (const RenderObject* object : renderObjects) {
		OGLShader* objectShader = (OGLShader*)object->GetShader();
		if (!object->GetMesh()) {
			continue;
		}
		if (objectShader == nullptr) {
			objectShader = defaultShader;
		}
		if (objectShader != activeShader) {
			activeShader = objectShader;
			BindShader(activeShader);
			int projLocation	= glGetUniformLocation(activeShader->GetProgramID(), "projMatrix");
			int viewLocation	= glGetUniformLocation(activeShader->GetProgramID(), "viewMatrix");
			modelLocation		= glGetUniformLocation(activeShader->GetProgramID(), "modelMatrix");	
			
			glUniformMatrix4fv(projLocation, 1, false, (float*)&projMatrix);
			glUniformMatrix4fv(viewLocation, 1, false, (float*)&viewMatrix);
			ApplyLightToShader(activeLight, activeShader);

			Matrix3 rotation = Matrix3(viewMatrix);
			Vector3 invCamPos = viewMatrix.GetPositionVector();

			Vector3 camPos = rotation * -invCamPos;

			glUniform3fv(glGetUniformLocation(activeShader->GetProgramID(), "cameraPos"), 1, (float*)&camPos);

			int timeLocation = glGetUniformLocation(activeShader -> GetProgramID(), "time");

			if (timeLocation >= 0) {
				float totalTime = frameTimer.GetTotalTime();
				glUniform1f(timeLocation, totalTime);
			}

		}

		Matrix4 mat = object->GetTransform();
		glUniformMatrix4fv(modelLocation, 1, false, (float*)&mat);

		BindTextureToShader(object->GetBaseTexture(), "mainTex", 0);
		BindTextureToShader(object -> GetSecondTexture(), "secondTex", 1);
		BindMesh(object->GetMesh());
		DrawBoundMesh();
	}
}

void Renderer::OnWindowResize(int w, int h)	{
	OGLRenderer::OnWindowResize(w, h);
	projMatrix = Matrix4::Orthographic(-1.0f, 1.0f, (float)currentWidth, 0.0f, 0.0f, (float)currentHeight);
}

void Renderer::EnableDepthBuffer(bool state) {
	if (state) {
		glEnable(GL_DEPTH_TEST);	}	else {		glDisable(GL_DEPTH_TEST);	}}void Renderer::WriteDepthBuffer(const string & filepath) const {
	float * data = new float[currentWidth * currentHeight];	glReadPixels(0, 0, currentWidth, currentHeight, GL_DEPTH_COMPONENT, GL_FLOAT, data);	char * pixels = new char[currentWidth * currentHeight * 3];	char * pixelPointer = pixels;	for (int y = 0; y < currentHeight; ++y) {		for (int x = 0; x < currentWidth; ++x) {			float depthValue = data[(y * currentWidth) + x];			float mult = 1.0f / 0.333f;			float redAmount = Maths::Clamp(depthValue, 0.0f, 0.333f) * mult;			float greenAmount = (Maths::Clamp(depthValue, 0.333f, 0.666f) - 0.333f) * mult;			float blueAmount = (Maths::Clamp(depthValue, 0.666f, 1.0f) - 0.666f) * mult;			unsigned char redByte = (char)(redAmount * 255);			unsigned char greenByte = (char)(greenAmount * 255);			unsigned char blueByte = (char)(blueAmount * 255);			*pixelPointer++ = (char)(redAmount * 255);			*pixelPointer++ = (char)(greenAmount * 255);			*pixelPointer++ = (char)(blueAmount * 255);								}	}	TextureWriter::WritePNG(filepath, pixels, currentWidth, currentHeight, 3);	delete pixels;	delete data;}void Renderer::SetBlendToLinear() {	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);}void Renderer::SetBlendToAdditive() {	glBlendFunc(GL_ONE, GL_ONE);}void Renderer::SetBlendToInvert() {	glBlendFunc(GL_ONE_MINUS_SRC_COLOR, GL_ONE_MINUS_DST_COLOR);}void Renderer::SetLightProperties(Vector3 position, Vector3 colour, float radius) {	activeLight.position = position;	activeLight.colour = colour;	activeLight.radius = radius;}void Renderer::ApplyLightToShader(const Light &l, const OGLShader * s) {	glUniform3fv(glGetUniformLocation(s->GetProgramID(), "lightColour"), 1, (float *)& l.colour);	glUniform3fv(glGetUniformLocation(s->GetProgramID(), "lightPos"), 1, (float *)& l.position);	glUniform1f(glGetUniformLocation(s->GetProgramID(), "lightRadius"),   l.radius);}