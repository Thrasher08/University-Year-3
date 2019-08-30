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
#include "RasterMesh.h"
#include "Renderer.h"

using namespace NCL;
using namespace CSC3223;

int const numStars = 3000;		//Number of stars displayed
int shipX = 0;
int shipY = 0;
int shipZ = 0;
bool depth = true;
bool alpha = true;
bool displayCredits = false;

OGLMesh* stars[numStars];

void Stars(Renderer& renderer) {
	
	//Stars
	float x;
	float y;
	float z;

	for (int i = 0; i <= numStars; i++) {

		//Generate stars randomly on the X, Y and Z within these ranges
		float x = -10 + static_cast <float> (rand()) / static_cast <float> (RAND_MAX / (20));
		float y = -10 + static_cast <float> (rand()) / static_cast <float> (RAND_MAX / (20));
		float z = -10 + static_cast <float> (rand()) / static_cast <float> (RAND_MAX / (20));

		stars[i] = new OGLMesh();
		stars[i]->SetVertexPositions({ Vector3(x, y, z) });		//Sets position based on random co-ordinates
		stars[i]->SetVertexColours({ Vector4(1 ,1 ,1 ,1) });	//Sets star colour to white
		stars[i]->SetPrimitiveType(GeometryPrimitive::Points);
		stars[i]->UploadToGPU();

	}
}

//Draws and scales the number of stars
void StarsDraw(Renderer& renderer) {

	Matrix4 starScale = Matrix4::Scale(Vector3(5,5,5));
	for (int i = 0; i <= numStars; i++) {
		renderer.AddRenderObject(new RenderObject(stars[i],starScale));
	}
}

void Planet(Renderer& renderer, int degree, TextureBase *newTex) {
	
	//Planet
	OGLMesh* planet = new OGLMesh();
	
	planet->SetVertexPositions({

		//Top Pyramid
		Vector3(105, 105, 5), Vector3(100, 100, 0), Vector3(110, 100, 0),							//Back
		Vector3(105, 105, 5), Vector3(110, 100, 10),												//Right
		Vector3(105, 105, 5), Vector3(100, 100, 10),												//Front


		//Body
		Vector3(100, 100, 0), Vector3(100, 90, 0), Vector3(110, 100, 0), Vector3(110, 90, 0),		//Back
		Vector3(110, 100, 10), Vector3(110, 90, 10),												//Right
		Vector3(100, 100, 10), Vector3(100, 90, 10),												//Front
		Vector3(100, 100, 0), Vector3(100, 90, 0),													//Left


		//Bottom Pyramid
		Vector3(105, 85, 5), Vector3(100, 90, 0), Vector3(110, 90, 0),
		Vector3(105, 85, 5), Vector3(110, 90, 10),
		Vector3(105, 85, 5), Vector3(100, 90, 10),
		Vector3(105, 85, 5), Vector3(100, 90, 0)

	});

	planet->SetPrimitiveType(GeometryPrimitive::TriangleStrip);

	planet->SetVertexColours({ 

		Vector4(1, 1, 1, 0), Vector4(1, 1, 1, 0), Vector4(1, 1, 1, 0),
		Vector4(1, 1, 1, 0), Vector4(1, 1, 1, 0),
		Vector4(1, 1, 1, 0), Vector4(1, 1, 1, 0),

		Vector4(1, 1, 1, 0), Vector4(1, 1, 1, 0), Vector4(1, 1, 1, 0), Vector4(1, 1, 1, 0),
		Vector4(1, 1, 1, 0), Vector4(1, 1, 1, 0),
		Vector4(1, 1, 1, 0), Vector4(1, 1, 1, 0),
		Vector4(1, 1, 1, 0), Vector4(1, 1, 1, 0),

		Vector4(1, 1, 1, 0), Vector4(1, 1, 1, 0), Vector4(1, 1, 1, 0),
		Vector4(1, 1, 1, 0), Vector4(1, 1, 1, 0),
		Vector4(1, 1, 1, 0), Vector4(1, 1, 1, 0),
		Vector4(1, 1, 1, 0), Vector4(1, 1, 1, 0),
	});					   

	planet->SetVertexTextureCoords({ 
		Vector2(0.124, 1), Vector2(0, 0.75), Vector2(0.25, 0.75),
		Vector2(0.50, 0.75), Vector2(0.75, 0.75),
		Vector2(1, 0.75), Vector2(1 , 0.75),

		Vector2(0, 0.75), Vector2(0, 0.25), Vector2(0.25 , 0.75), Vector2(0.25 , 0.25),
		Vector2(0.50, 0.75), Vector2(0.50 , 0.25),
		Vector2(0.75, 0.75), Vector2(0.75 , 0.25),
		Vector2(1, 0.75), Vector2(1 , 0.25),

		Vector2(0.124, 0), Vector2(0 ,0.25), Vector2(0.25 ,0.25),
		Vector2(0.5, 0.5), Vector2(0.5 ,0.25),
		Vector2(0.75, 0.25), Vector2(0.75 ,0.25),
		Vector2(1, 0.25), Vector2(1 ,0.25)
	});

	Matrix4 planetRotate = Matrix4::Translation(Vector3(0, 0, 0)) *  Matrix4::Rotation(degree, Vector3(0, 1, 0)) * Matrix4::Translation(-planet->GetPositionData()[0]);	//Rotates and moves the planet to the right position
	planet->UploadToGPU();
	RenderObject* renObj = new RenderObject(planet, planetRotate);
	
	renObj->SetBaseTexture(newTex);
	renderer.AddRenderObject(renObj);
}

void Spaceship(Renderer& renderer) {
	
	//Spaceship
	OGLMesh* ship = new OGLMesh();
	OGLMesh* wing1 = new OGLMesh();		//Left Wing
	OGLMesh* wing2 = new OGLMesh();		//Right Wing

	ship->SetVertexPositions({ Vector3(2, 2, 15), Vector3(4, 2, 15), Vector3(3, 4, 15), });
	wing1->SetVertexPositions({ Vector3(2, 2, 15), Vector3(1, 1, 15), Vector3(2, 5, 16) });
	wing2->SetVertexPositions({ Vector3(4, 2, 15), Vector3(5, 1, 15), Vector3(4, 5, 16) });

	ship->SetPrimitiveType(GeometryPrimitive::Triangles);
	wing1->SetPrimitiveType(GeometryPrimitive::Triangles);
	wing2->SetPrimitiveType(GeometryPrimitive::Triangles);

	ship->SetVertexColours({Vector4(0 ,0.1 ,0 ,1) , Vector4(1 ,0.5 ,0 ,1) , Vector4(0.5 ,0.35 , 0.05,1) });
	wing1->SetVertexColours({ Vector4(0 ,1 ,1 ,1) , Vector4(1 ,0 ,1 ,1) , Vector4(0.5 ,1 ,1 ,1) });
	wing2->SetVertexColours({ Vector4(0 ,1 ,1 ,1) , Vector4(1 ,0 ,1 ,1) , Vector4(0.5 ,1 ,1 ,1) });

	ship->UploadToGPU();
	wing1->UploadToGPU();
	wing2->UploadToGPU();

	Matrix4 transMat = Matrix4::Translation(Vector3(shipX, shipY, shipZ));		//Translation Matrix to allow ship movement based on X, Y and Z input on the keyboard

	renderer.AddRenderObject(new RenderObject(ship, transMat));
	renderer.AddRenderObject(new RenderObject(wing1, transMat));
	renderer.AddRenderObject(new RenderObject(wing2, transMat));
}

void CreditsName(Renderer& credits) {
	OGLMesh* rr = new OGLMesh();

	OGLMesh* hay = (OGLMesh*)RasterMesh::CreateLineFromPoints({
		Vector3(0, 50, 0), Vector3(0, 0, 0), Vector3(0, 25, 0), Vector3(50, 25, 0), Vector3(50, 50, 0), Vector3(50, 0, 0), //H
		Vector3(75, 50, 0), Vector3(50, 0, 0), Vector3(75, 50, 0), Vector3(100, 50, 0), Vector3(50, 25, 0), Vector3(100, 025, 0), //A
		Vector3(100, 25, 0), Vector3(100, 0, 0), Vector3(100, 25, 0), Vector3(150, 0, 0),	//Bottom of R1
		Vector3(150, 25, 0), Vector3(150, 0, 0), Vector3(150, 25, 0), Vector3(200, 0, 0),	//Bottom of R2
		Vector3(200, 50, 0), Vector3(225, 40, 0), Vector3(250, 50, 0), Vector3(225, 40, 0), Vector3(225, 40, 0), Vector3(200, 0, 0)	//Y
	}, {
		Vector4(0 ,1 ,0 ,1) ,  Vector4(0 ,1 ,0 ,1) ,Vector4(0 ,1 ,0 ,1) ,Vector4(0 ,1 ,0 ,1) ,Vector4(0 ,1 ,0 ,1) ,Vector4(0 ,1 ,0 ,1),
		Vector4(0 ,1 ,0 ,1) ,  Vector4(0 ,1 ,0 ,1) ,Vector4(0 ,1 ,0 ,1) ,Vector4(0 ,1 ,0 ,1) ,Vector4(0 ,1 ,0 ,1) ,Vector4(0 ,1 ,0 ,1) ,
		Vector4(0 ,1 ,0 ,1) ,  Vector4(0 ,1 ,0 ,1) ,Vector4(0 ,1 ,0 ,1) ,Vector4(0 ,1 ,0 ,1) ,
		Vector4(0 ,1 ,0 ,1) ,  Vector4(0 ,1 ,0 ,1) ,Vector4(0 ,1 ,0 ,1) ,Vector4(0 ,1 ,0 ,1) ,
		Vector4(0 ,1 ,0 ,1) ,  Vector4(0 ,1 ,0 ,1) ,Vector4(0 ,1 ,0 ,1) ,Vector4(0 ,1 ,0 ,1) ,Vector4(0 ,1 ,0 ,1) ,Vector4(0 ,1 ,0 ,1) 
	}, true);

	rr->SetVertexPositions({
		Vector3(100, 50, 0), Vector3(100, 25, 0), Vector3(150, 25, 0),	//Top of R1
		Vector3(150, 50, 0), Vector3(150, 25, 0), Vector3(200, 25, 0)	//Top of R2
	});

	credits.AddRenderObject(new RenderObject(hay));
	credits.AddRenderObject(new RenderObject(rr));
}

int main() {
	Window*w = Window::CreateGameWindow("CSC3223 Coursework 1!");

	if (!w->HasInitialised()) {
		return -1;
	}

	Renderer*	renderer = new Renderer(*w);
	Renderer*	credits = new Renderer(*w);

	Stars(*renderer);

	int degree = 0;		//Amount of degrees of rotation
	TextureBase * newTex = OGLTexture::RGBATextureFromFilename("pepe.PNG");

	Vector3 viewPosition(0, 0, 0);

	float aspect = w->GetScreenAspect();	Matrix4 proj = Matrix4::Perspective(1.0f, 100.0f, aspect, 45.0f);	renderer->SetProjectionMatrix(proj);

	renderer->EnableDepthBuffer(true);
	//renderer->EnableAplhaBlending(true);

	while (w->UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)) {
		float time = w->GetTimer()->GetTimeDelta();

		renderer->Update(time);

		renderer->DeleteAllRenderObjects();

		StarsDraw(*renderer);
		Planet(*renderer, degree++, newTex);	//Increase the rotation while being drawn
		Spaceship(*renderer);

		renderer->DrawString("OpenGL Rendering!", Vector2(10, 10));

		//renderer->Render();
		glClearColor(0, 0, 0, 0);	//Sets background colour

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

		//Controls ================================================
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_A)) {			viewPosition.x += 1.0f;		}		if (Window::GetKeyboard()->KeyDown(KEYBOARD_D)) {			viewPosition.x -= 1.0f;		}		if (Window::GetKeyboard()->KeyDown(KEYBOARD_W)) {			viewPosition.y -= 1.0f;		}		if (Window::GetKeyboard()->KeyDown(KEYBOARD_S)) {			viewPosition.y += 1.0f;		}		if (Window::GetKeyboard()->KeyDown(KEYBOARD_SPACE)) {			viewPosition.z += 1.0f;		}		if (Window::GetKeyboard()->KeyDown(KEYBOARD_SHIFT)) {			viewPosition.z -= 1.0f;		}

		//Ship Controls ===========================================

		//Move Left
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_L)) {			shipX += 1.0f;		}

		//Move Right
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_J)) {			shipX -= 1.0f;		}

		//Move Up
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_U)) {			shipY += 1.0f;		}

		//Move Down
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_O)) {			shipY -= 1.0f;		}

		//Move In
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_I)) {			shipZ += 1.0f;		}

		//Move Out
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_K)) {			shipZ -= 1.0f;		}

		//Depth Controls ===========================================

		//Toggle Buffer
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F1)) {			if (depth) {				renderer->EnableDepthBuffer(depth);				depth = false;			}			else if (depth == false) {				renderer->EnableDepthBuffer(depth);				depth = true;			}		}

		//DepthAlways
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_F2)) {			renderer->depthAlways(true);		}

		//DepthLess
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_F3)) {			renderer->depthLess(true);		}

		//DepthGreater
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_F4)) {			renderer->depthGreater(true);		}

		//Display Name ===========================================
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F9)) {			displayCredits = true;		}
				if (displayCredits == true) {			renderer->DeleteAllRenderObjects();			CreditsName(*renderer);			credits->Render();					}else {
			renderer->Render();
		}

		renderer->SetViewMatrix(Matrix4::Translation(viewPosition));
		w->SetTitle(std::to_string(time));
	}

	delete renderer;

	Window::DestroyGameWindow();
}