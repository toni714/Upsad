#pragma once

#include "Object3DScaled.h"

#include <vector>
#include <array>
#include <glad\glad.h>
#include "Vertex.h"
#include "MathHelper.h"
#include "ModelData.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include <stdexcept>

class Terrain : public Object3D {
public:
	static std::shared_ptr<RawModel> generateTerrain(const glm::vec3& position, const glm::vec3& rotation, float scaleXZ, float scaleY, int tiles)/* :Object3D(position, rotation)*/ {
		if (tiles < 1) {
			throw std::runtime_error("Number of Tiles should be >1");
		}
		std::vector<glm::vec3> positions;
		std::vector<glm::vec2> uvs;
		double tileWidth = scaleXZ / tiles;
		for (int xIndex = 0; xIndex < (tiles+1); xIndex++) {
			for (int zIndex = 0; zIndex < (tiles+1); zIndex++) {
				float x = tileWidth*xIndex;
				float z = tileWidth*zIndex;
				float y = scaleY * MathHelper::generateRandomFloat();
				//float y = (xIndex*zIndex)/(float)(tiles*tiles);
				glm::vec3 position = glm::vec3(x, y, z);
				positions.push_back(position);
				uvs.push_back(glm::vec2(xIndex/(float)tiles, zIndex/(float)tiles));

			}
		}

		std::vector<std::array<GLuint, 3>>triangles;
		std::vector<GLuint> indices;
		for (int xIndex = 0; xIndex < tiles; xIndex++) {
			for (int zIndex = 0; zIndex < tiles; zIndex++) {
				GLuint v1 =  xIndex      +  (zIndex      * (tiles + 1));//X|Y
				GLuint v2 =  xIndex      + ((zIndex + 1) * (tiles + 1));//X|Y+1
				GLuint v3 = (xIndex + 1) + ((zIndex + 1) * (tiles + 1));//X+1|Y+1
				GLuint v4 = (xIndex + 1) +  (zIndex      * (tiles + 1));

				std::array<GLuint, 3> triangle1 = { v1, v4, v2 };
				triangles.push_back(triangle1);
				indices.push_back(v1);
				indices.push_back(v4);
				indices.push_back(v2);

				std::array<GLuint, 3> triangle2 = { v2,  v4, v3 };
				triangles.push_back(triangle2);
				indices.push_back(v2);
				indices.push_back(v4);
				indices.push_back(v3);
			}
		}

		std::vector<glm::vec3> normals;
		normals.resize((tiles + 1)*(tiles + 1));
		std::fill(normals.begin(), normals.end(), glm::vec3(0.f, 0.f, 0.f));
		for (const auto& triangle : triangles) {
			const GLuint& indexA= triangle[0];
			const GLuint& indexB= triangle[1];
			const GLuint& indexC= triangle[2];
			glm::vec3& a = positions[indexA];
			glm::vec3& b = positions[indexB];
			glm::vec3& c = positions[indexC];

			glm::vec3 l = b - a;
			glm::vec3 r = c - a;
			glm::vec3 faceNormal = glm::cross(l, r);
			normals[indexA]+=faceNormal;
			normals[indexB]+=faceNormal;
			normals[indexC]+=faceNormal;
		}
		std::vector<Vertex> vertices;
		for (int i = 0; i < positions.size(); i++) {
			vertices.push_back(Vertex(positions[i], uvs[i], normals[i]));
		}

		ModelData data = ModelData(vertices, indices, LimitBox(0,0,0,0,0,0));//todo implement bounding

		return ModelHelper::loadModelDataToRawModel(data);
	}
};