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
#include "RasterMesh.h"

using namespace std;
using namespace NCL;
using namespace CSC3223;
RasterMesh* RasterMesh::CreateLineFromPoints(const std::vector<Vector3>& verticies, const std::vector < Vector4 >& colours, bool bresenham) {
	RasterMesh* line = new RasterMesh();

	if (bresenham) {
		for (int i = 0; i < verticies.size() - 1; i += 2) {
			line->RasterBresenhamLine(verticies[i], verticies[i + 1], colours[i], colours[i + 1]);
		}
	}
	else {
		for (int i = 0; i < verticies.size() - 1; i += 2) {
			line->RasterBasicLine(verticies[i], verticies[i + 1], colours[i], colours[i + 1]);
		}
	}
	line->SetPrimitiveType(GeometryPrimitive::Points);
	line->UploadToGPU();
	return line;

}

void RasterMesh::RasterBasicLine(const Vector3 & p0, const Vector3 & p1, const Vector4 & c0, const Vector4 & c1) {

	float lineLength = (p0 - p1).Length();
	int numPixels = (int)lineLength;

	float lerpAmount = 1.0f / (numPixels - 1);
	float t = 0.0f;

	for (int i = 0; i < numPixels; ++i) {
		positions.emplace_back(Maths::Lerp<Vector3>(p0, p1, t));
		colours.emplace_back(Maths::Lerp < Vector4 >(c0, c1, t));
		t += lerpAmount;
	}
}

void RasterMesh::RasterBresenhamLine(const Vector3 & p0, const Vector3 & p1, const Vector4 & c0, const Vector4 & c1) {
	Vector3 dir = p1 - p0;
	Vector3 currentPos = p0;
	int scanRange = 0;
	float slope = 0.0f;
	float* periodAxis = nullptr;
	float* scanAxis = nullptr;
	int scanDelta = 0;
	int targetDelta = 0;

	if (abs(dir.y) > abs(dir.x)) {
		slope = (dir.x / dir.y);
		scanRange = (int)abs(dir.y);
		periodAxis = &currentPos.x;
		scanAxis = &currentPos.y;
		scanDelta = (dir.y < 0.0f) ? -1 : 1;
		targetDelta = (dir.x < 0.0f) ? -1 : 1;
	}
	else {
		slope = (dir.y / dir.x);
		scanRange = (int)abs(dir.x);
		periodAxis = &currentPos.y;
		scanAxis = &currentPos.x;
		scanDelta = (dir.x < 0.0f) ? -1 : 1;
		targetDelta = (dir.y < 0.0f) ? -1 : 1;
	}

	float absSlope = abs(slope);
	float error = 0.0f;
	Vector4 colourDiff = c1 - c0;
	Vector4 colourDelta = colourDiff / scanRange;	Vector4 currentColour = c0;

	for (int i = 0; i < scanRange; ++i) {
		positions.emplace_back(currentPos);
		colours.emplace_back(currentColour);
		currentColour += colourDelta;

		error += absSlope;

		if (error > 0.5f) {
			error -= 1.0f;
			(*periodAxis) += targetDelta;
		}

		(*scanAxis) += scanDelta;
	}

}

RasterMesh* RasterMesh::CreateTriangleFromPoints(const std::vector<Vector3>& verticies, const std::vector < Vector4 >& colours, int type) {
	RasterMesh* tri = new RasterMesh();

	if (type == 1) {
		for (size_t i = 0; i < verticies.size() - 2; i += 3) {
			tri->RasterSpanTriangle(verticies[i], verticies[i + 1], verticies[i + 2], colours[i], colours[i + 1], colours[i + 2]);
		}
	}

	else if (type == 2) {
		for (size_t i = 0; i < verticies.size() - 2; i += 3) {
			tri->RasterLineEquationTriangle(verticies[i], verticies[i + 1], verticies[i + 2], colours[i], colours[i + 1], colours[i + 2]);
		}
	}

	else {
		for (size_t i = 0; i < verticies.size() - 2; i += 3) {
			tri->RasterLineEquationTriangle(verticies[i], verticies[i + 1], verticies[i + 2], colours[i], colours[i + 1], colours[i + 2]);
		}
	}

	tri->SetPrimitiveType(GeometryPrimitive::Points);
	tri->UploadToGPU();
	return tri;
}

void RasterMesh::RasterLineEquationTriangle(const Vector3 & p0, const Vector3 & p1, const Vector3 & p2, const Vector4 & c0, const Vector4 & c1, const Vector4 & c2) {
	Vector2 topLeft, bottomRight;
	Maths::ScreenBoxOfTri(p0, p1, p2, topLeft, bottomRight);

	Vector3 linev0v1 = Vector3::Cross(Vector3(p0.x, p0.y, 1), Vector3(p1.x, p1.y, 1));
	Vector3 linev1v2 = Vector3::Cross(Vector3(p1.x, p1.y, 1), Vector3(p2.x, p2.y, 1));
	Vector3 linev2v0 = Vector3::Cross(Vector3(p2.x, p2.y, 1), Vector3(p0.x, p0.y, 1));
	for (int y = (int)topLeft.y; y < bottomRight.y; ++y) {
		for (int x = (int)topLeft.x; x < bottomRight.x; ++x) {
			Vector3 screenPos((float)x, (float)y, 1.0f);

			float line01 = Vector3::Dot(linev0v1, screenPos);
			float line12 = Vector3::Dot(linev1v2, screenPos);
			float line20 = Vector3::Dot(linev2v0, screenPos);

			if (line01 <= 0 && line12 <= 0 && line20 <= 0) {
				positions.emplace_back(screenPos);
				float lineSum = line01 + line12 + line20;
				line01 /= lineSum;
				line12 /= lineSum;
				line20 /= lineSum;				Vector4 colour = (c0 * line12) + (c1 * line20) + (c2 * line01);
				colours.emplace_back(colour);

			}

		}

	}

}

void RasterMesh::RasterSpanTriangle(const Vector3 & p0, const Vector3 & p1, const Vector3 & p2, const Vector4 & c0, const Vector4 & c1, const Vector4 & c2) {
	const Vector3 * vertices[3] = { &p0 ,&p1 ,&p2 };

	if (vertices[1]->y < vertices[0]->y) {
		std::swap(vertices[1], vertices[0]);
	}
	if (vertices[2]->y < vertices[0]->y) {
		std::swap(vertices[2], vertices[0]);
	}

	if (vertices[2]->y < vertices[1]->y) {
		std::swap(vertices[2], vertices[1]);
	}


	Vector3 longDir = *vertices[2] - *vertices[0];
	Vector3 longDelta = longDir / longDir.y;
	Vector3 shortDir = *vertices[1] - *vertices[0];
	Vector3 shortDelta = shortDir / shortDir.y;

	float longX = vertices[0]->x;
	float shortX = vertices[0]->x;

	for (int y = vertices[0]->y; y < vertices[1]->y; ++y) {
		int startX = min(longX, shortX);
		int endX = max(longX, shortX);

		for (int x = startX; x < endX; ++x) {
			positions.emplace_back(Vector3(x, y, 1));
		}
		longX += longDelta.x;
		shortX += shortDelta.x;
	}

	shortDir = *vertices[2] - *vertices[1];
	shortDelta = shortDir / shortDir.y;
	for (int y = vertices[1]->y; y < vertices[2]->y; ++y) {
		int startX = min(longX, shortX);
		int endX = max(longX, shortX);

		for (int x = startX; x < endX; ++x) {
			positions.emplace_back(Vector3(x, y, 1));
		}
		longX += longDelta.x;
		shortX += shortDelta.x;
	}
}

void RasterMesh::RasterBarycentricTriangle(const Vector3 & p0, const Vector3 & p1, const Vector3 & p2, const Vector4 & c0, const Vector4 & c1, const Vector4 & c2) {	Vector2 topLeft, bottomRight;	Maths::ScreenBoxOfTri(p0, p1, p2, topLeft, bottomRight);
	float triArea = Maths::ScreenAreaOfTri(p0, p1, p2);
	float areaRecip = 1.0f / triArea;	int subTriArea[3];	for (int y = (int)topLeft.y; y < bottomRight.y; ++y) {		for (int x = (int)topLeft.x; x < bottomRight.x; ++x) {			Vector3 screenPos((float)x, (float)y, 0.0f);			subTriArea[0] = abs(ScreenAreaOfTri(p0, screenPos, p1));			subTriArea[1] = abs(ScreenAreaOfTri(p1, screenPos, p2));			subTriArea[2] = abs(ScreenAreaOfTri(p2, screenPos, p0));			float triSum = subTriArea[0] + subTriArea[1] + subTriArea[2];			if ((int)triSum > triArea) {				continue;			}			float alpha = subTriArea[1] * areaRecip;			float beta = subTriArea[2] * areaRecip;			float gamma = subTriArea[0] * areaRecip;			Vector4 colour = ((c0 * alpha) + (c1 * beta) + (c2 * gamma));			positions.emplace_back(screenPos);			colours.emplace_back(colour);		}	}}