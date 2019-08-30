#pragma once
#include "../../Plugins/OpenGLRendering/OGLRenderer.h"
#include "../../Plugins/OpenGLRendering/OGLShader.h"
#include "../../Plugins/OpenGLRendering/OGLTexture.h"
#include "../../Plugins/OpenGLRendering/OGLMesh.h"

#include "RenderObject.h"
#include "../../Common/Vector2.h"



namespace NCL {
	namespace CSC3223 {



		class Renderer : public OGLRenderer
		{
			struct Light {
				Vector3 position;
				float radius;
				Vector3 colour;
			};

		public:
			Renderer(Window& w);
			~Renderer();

			void EnableDepthBuffer(bool state);

			void WriteDepthBuffer(const string & filepath) const;

			void AddRenderObject(RenderObject* ro) {
				renderObjects.emplace_back(ro);
			}

			void SetBlendToLinear();
			void SetBlendToAdditive();
			void SetBlendToInvert();

			void SetLightProperties(Vector3 pos, Vector3 colour, float radius);

			void DeleteAllRenderObjects() {
				for (const RenderObject* object : renderObjects) {
					delete object;
				}
				renderObjects.clear();
			}
			
			void SetProjectionMatrix(const Matrix4&m) {
				projMatrix = m;
			}

			void SetViewMatrix(const Matrix4&m) {
				viewMatrix = m;
			}

			void EnableBlending(bool state) {
				if (state) {
					glEnable(GL_BLEND);
				}
				else {
					glDisable(GL_BLEND);
				}
			}

		protected:
			void RenderNode(RenderObject* root);

			GameTimer frameTimer;

			void ApplyLightToShader(const Light&l, const OGLShader*s);
			Light activeLight;
	
			void OnWindowResize(int w, int h)	override;

			void RenderFrame()	override;
			OGLShader*		defaultShader;

			Matrix4		projMatrix;
			Matrix4		viewMatrix;

			vector<RenderObject*> renderObjects;
		};


	}
}