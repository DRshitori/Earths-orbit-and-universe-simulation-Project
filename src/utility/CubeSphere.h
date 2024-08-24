#pragma once
#include <iostream>
#include <vector>
#include <string>

#include <glm/glm.hpp>
#include <glm/ext/scalar_constants.hpp>

#include "../Mesh/VertexArray.h"
#include "../Mesh/VertexBuffer.h"
#include "../Mesh/VertexBufferLayout.h"
#include "../Mesh/IndexBuffer.h"

class CubeSphere {
public:
    CubeSphere(int subdivision);
    void createCubeSphere();
    void CreateMesh();
    void render();
private:
    int m_subdivision;
    int m_numFaces;
    int m_rowPerFace;
    std::vector<float> m_cubesphereVertices;
    std::vector<unsigned int> m_cubesphereIndices;
   /* VertexArray VAO;
    VertexBuffer VBO;
    IndexBuffer EBO;*/
    unsigned int VAO, VBO, EBO;
    void createCubeSphereFace(int face, int subdivision, std::vector<float>* vertices);
    
    void calculateNormalsCubesphere(int face, float angle, int axis, glm::tvec3<float>* normal);
    void addTextureCoords();
};
