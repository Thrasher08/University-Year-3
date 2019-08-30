#include "../../Common/Window.h"
#include "../../Common/TextureLoader.h"
#include "../../Common/Vector3.h"
#include "../../Common/Vector4.h"
#include "../../Common/MeshGeometry.h"
#include "../../Common/Maths.h"

#include "../../Plugins/OpenGLRendering/OGLRenderer.h"
#include "../../Plugins/OpenGLRendering/OGLMesh.h"
#include "../../Plugins/OpenGLRendering/OGLShader.h"
#include "../../Plugins/OpenGLRendering/OGLTexture.h"

#include "Renderer.h"

using namespace NCL;
using namespace CSC3223;

float shrinkValue;
float burnValue;
float fadeValue;

//Tesselation
RenderObject* shrinkCube(Renderer &renderer) {
	OGLShader * shrinkShader = new OGLShader("Shrink.glsl", "RasterisationFrag.glsl");

	OGLMesh * cubeMesh = new OGLMesh("cube.msh");
	cubeMesh->SetPrimitiveType(GeometryPrimitive::Triangles);
	cubeMesh->UploadToGPU();

	RenderObject * cubeObject = new RenderObject(cubeMesh);
	cubeObject->SetShader(shrinkShader);

	TextureBase * tex = OGLTexture::RGBATextureFromFilename("crate.PNG");
	cubeObject->SetBaseTexture(tex);

	shrinkValue = 1.0f;

	renderer.AddRenderObject(cubeObject);

	renderer.SetLightProperties(Vector3(0, 25, 0), Vector3(1.0f, 0.3f, 0.2f), 200.0f);

	return cubeObject;
}

RenderObject* burnCube(Renderer &renderer) {
	OGLShader * shrinkShader = new OGLShader("Vert.glsl", "Burn.glsl");

	OGLMesh * cubeMesh = new OGLMesh("cube.msh");
	cubeMesh->SetPrimitiveType(GeometryPrimitive::Triangles);
	cubeMesh->UploadToGPU();

	RenderObject * cubeObject = new RenderObject(cubeMesh);
	cubeObject->SetShader(shrinkShader);

	TextureBase * tex = OGLTexture::RGBATextureFromFilename("crate.PNG");
	cubeObject->SetBaseTexture(tex);
	cubeObject->SetSecondTexture(OGLTexture::RGBATextureFromFilename("burned.JPG"));

	burnValue = 0.0f;

	renderer.AddRenderObject(cubeObject);

	renderer.SetLightProperties(Vector3(0, 25, 0), Vector3(1.0f, 0.3f, 0.2f), 200.0f);

	return cubeObject;
}

RenderObject* fadeCube(Renderer &renderer) {
	OGLShader * shrinkShader = new OGLShader("Vert.glsl", "Fade.glsl");

	OGLMesh * cubeMesh = new OGLMesh("cube.msh");
	cubeMesh->SetPrimitiveType(GeometryPrimitive::Triangles);
	cubeMesh->UploadToGPU();

	RenderObject * cubeObject = new RenderObject(cubeMesh);
	cubeObject->SetShader(shrinkShader);

	TextureBase * tex = OGLTexture::RGBATextureFromFilename("crate2.PNG");
	cubeObject->SetBaseTexture(tex);

	fadeValue = 1.0f;

	renderer.AddRenderObject(cubeObject);

	renderer.SetLightProperties(Vector3(0, 25, 0), Vector3(1.0f, 0.3f, 0.2f), 200.0f);

	return cubeObject;
}

RenderObject* displaceCube(Renderer &renderer) {
	OGLShader * shrinkShader = new OGLShader("Shrink.glsl", "");

	OGLMesh * cubeMesh = new OGLMesh("cube.msh");
	cubeMesh->SetPrimitiveType(GeometryPrimitive::Triangles);
	cubeMesh->UploadToGPU();

	RenderObject * cubeObject = new RenderObject(cubeMesh);
	cubeObject->SetShader(shrinkShader);

	TextureBase * tex = OGLTexture::RGBATextureFromFilename("perlin_noise.PNG");
	cubeObject->SetBaseTexture(tex);

	renderer.AddRenderObject(cubeObject);

	renderer.SetLightProperties(Vector3(0, 25, 0), Vector3(1.0f, 0.3f, 0.2f), 200.0f);

	return cubeObject;
}

RenderObject* laserCube(Renderer &renderer) {
	OGLShader * shrinkShader = new OGLShader("Shrink.glsl", "");

	OGLMesh * cubeMesh = new OGLMesh("cube.msh");
	cubeMesh->SetPrimitiveType(GeometryPrimitive::Triangles);
	cubeMesh->UploadToGPU();

	RenderObject * cubeObject = new RenderObject(cubeMesh);
	cubeObject->SetShader(shrinkShader);

	TextureBase * tex = OGLTexture::RGBATextureFromFilename("perlin_noise.PNG");
	cubeObject->SetBaseTexture(tex);

	renderer.AddRenderObject(cubeObject);

	renderer.SetLightProperties(Vector3(0, 25, 0), Vector3(1.0f, 0.3f, 0.2f), 200.0f);

	return cubeObject;
}

RenderObject* blackholeCube(Renderer &renderer) {
	OGLShader * shrinkShader = new OGLShader("Shrink.glsl", "");

	OGLMesh * cubeMesh = new OGLMesh("cube.msh");
	cubeMesh->SetPrimitiveType(GeometryPrimitive::Triangles);
	cubeMesh->UploadToGPU();

	RenderObject * cubeObject = new RenderObject(cubeMesh);
	cubeObject->SetShader(shrinkShader);

	TextureBase * tex = OGLTexture::RGBATextureFromFilename("perlin_noise.PNG");
	cubeObject->SetBaseTexture(tex);

	renderer.AddRenderObject(cubeObject);

	renderer.SetLightProperties(Vector3(0, 25, 0), Vector3(1.0f, 0.3f, 0.2f), 200.0f);

	return cubeObject;
}

int main() {
	Window*w = Window::CreateGameWindow("CSC3223 Coursework 2!");

	if (!w->HasInitialised()) {
		return -1;
	}

	Renderer*	renderer = new Renderer(*w);
	RenderObject* sCube = shrinkCube(*renderer);
	RenderObject* bCube = burnCube(*renderer);
	RenderObject* fCube = fadeCube(*renderer);
	Vector3 viewPosition(0, 0, 0);	float aspect = w->GetScreenAspect();	Matrix4 proj = Matrix4::Perspective(1.0f, 100.0f, aspect, 45.0f);	renderer->SetProjectionMatrix(Matrix4::Perspective(1, 100, w->GetScreenAspect(), 45.0f));

	float rotation = 0.0f;
	//float shrinkValue = 1.0f;

	bool shrink = false;
	bool burn = false;
	bool fade = false;

	renderer->SetApplyShrink(shrinkValue);
	renderer->SetApplyFade(fadeValue);

	while (w->UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)) {
		float time = w->GetTimer()->GetTimeDelta();

		rotation += time * 0.1f;

		sCube->SetTransform(Matrix4::Translation(Vector3(-25, 0, -70)) * Matrix4::Rotation(rotation, Vector3(1, 1, 1)) * Matrix4::Scale(Vector3(6, 6, 6)));
		bCube->SetTransform(Matrix4::Translation(Vector3(0, 0, -70)) * Matrix4::Rotation(rotation, Vector3(1, 1, 1)) * Matrix4::Scale(Vector3(6, 6, 6)));
		fCube->SetTransform(Matrix4::Translation(Vector3(25, 0, -70)) * Matrix4::Rotation(rotation, Vector3(1, 1, 1)) * Matrix4::Scale(Vector3(6, 6, 6)));

		renderer->Update(time);

		renderer->DrawString("OpenGL Rendering!", Vector2(10, 10));

		renderer->EnableDepthBuffer(true);
		renderer->EnableBlending(true);
		renderer->SetBlendToLinear();
		renderer->Render();

		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_PRIOR)) {
			w->ShowConsole(true);
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_NEXT)) {
			w->ShowConsole(false);
		}

		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_HOME)) {
			w->SetFullScreen(true);
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_END)) {
			w->SetFullScreen(false);
		}

		if (Window::GetKeyboard()->KeyDown(KEYBOARD_A)) {			viewPosition.x += 1.0f;		}		if (Window::GetKeyboard()->KeyDown(KEYBOARD_D)) {			viewPosition.x -= 1.0f;		}		if (Window::GetKeyboard()->KeyDown(KEYBOARD_SHIFT)) {			viewPosition.y -= 1.0f;		}		if (Window::GetKeyboard()->KeyDown(KEYBOARD_SPACE)) {			viewPosition.y += 1.0f;		}		if (Window::GetKeyboard()->KeyDown(KEYBOARD_W)) {			viewPosition.z += 1.0f;		}		if (Window::GetKeyboard()->KeyDown(KEYBOARD_S)) {			viewPosition.z -= 1.0f;		}		if (Window::GetKeyboard()->KeyDown(KEYBOARD_F11)) {			renderer->WriteDepthBuffer("Depth.png");		}		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_NUMPAD1)) {			shrink = true;		}		if (shrink == true) {			shrinkValue += 1.0f;			renderer->SetApplyShrink(shrinkValue);		}		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_NUMPAD2)) {			burn = true;		}		if (burn == true) {			burnValue += 0.01f;			renderer->SetApplyBurn(burnValue);		}		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_NUMPAD3)) {			fade = true;		}		if (fade == true) {			fadeValue -= 0.01f;			renderer->SetApplyFade(fadeValue);		}		renderer->SetViewMatrix(Matrix4::Translation(viewPosition));
		w->SetTitle(std::to_string(time));
	}

	delete renderer;

	Window::DestroyGameWindow();
}