#include "OBJWrapper.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

OBJWrapper::OBJWrapper(const char* filename) {
	tinyobj::attrib_t vertexAttributes;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string errorString;

	bool success = tinyobj::LoadObj(&vertexAttributes, &shapes, &materials, &errorString, filename);
	if (!success) {
		throw std::runtime_error(errorString);
	}

	std::unordered_map<Vertex, uint32_t> vertices;
	for (tinyobj::shape_t shape : shapes) {
		for (tinyobj::index_t index : shape.mesh.indices) {
			glm::vec3 pos = {
				vertexAttributes.vertices[3 * index.vertex_index + 0],
				vertexAttributes.vertices[3 * index.vertex_index + 1],
				vertexAttributes.vertices[3 * index.vertex_index + 2]
			};
			glm::vec3 normal = {
				vertexAttributes.normals[3 * index.normal_index + 0],
				vertexAttributes.normals[3 * index.normal_index + 1],
				vertexAttributes.normals[3 * index.normal_index + 2]
			};
			glm::vec2 uv = {
				vertexAttributes.texcoords[2 * index.texcoord_index + 0],
				vertexAttributes.texcoords[2 * index.texcoord_index + 1]
			};

			Vertex vert(pos, normal, uv);
			if (vertices.count(vert) == 0) {
				vertices[vert] = vertices.size();
				m_vertices.push_back(vert);
			}
			m_indices.push_back(vertices[vert]);
		}
	}
}

std::vector<Vertex> OBJWrapper::getVertices() {
	return m_vertices;
}
std::vector<unsigned int> OBJWrapper::getIndices() {
	return m_indices;
}