#include "CubeSphere.h"

CubeSphere::CubeSphere(int subdivision) : m_subdivision(subdivision), m_numFaces(6) ,m_cubesphereIndices(152100) , m_cubesphereVertices(76050 + 50700){
    m_rowPerFace = (int)glm::pow(2, subdivision) + 1;
    
}

void CubeSphere::createCubeSphereFace(int face, int subdivision, std::vector<float>* vertices) {

    glm::tvec3<float> n1(0, 0, 0);
    glm::tvec3<float> n2(0, 0, 0);
    glm::tvec3<float> v;
    float a1;
    float a2;

    int pointsPerRow = (int)pow(2, subdivision) + 1;

    // rotate latitudinal plane from 45 to -45 degrees along Z-axis (top-to-bottom)
    for (int i = 0; i < pointsPerRow; ++i)
    {
        a2 = glm::radians((45.0f - 90.0f * i / (pointsPerRow - 1)));

        calculateNormalsCubesphere(face, a2, 2, &n2);

        // rotate longitudinal plane from -45 to 45 along Y-axis (left-to-right)
        for (int j = 0; j < pointsPerRow; ++j)
        {
            a1 = glm::radians((-45.0f + 90.0f * j / (pointsPerRow - 1)));

            calculateNormalsCubesphere(face, a1, 1, &n1);

            // find direction vector of intersected line, n1 x n2
            v = normalize(glm::cross(n1, n2));

            (*vertices).push_back(v[0]);
            (*vertices).push_back(v[1]);
            (*vertices).push_back(v[2]);
        }
    }
}
void CubeSphere::calculateNormalsCubesphere(int face, float angle, int axis, glm::tvec3<float>* normal) {
    switch (face) {

    case 0: // Right
        if (axis == 1) {
            (*normal)[0] = -sin(angle);
            (*normal)[1] = 0;
            (*normal)[2] = -cos(angle);
        }
        else if (axis == 2) {
            (*normal)[0] = -sin(angle);
            (*normal)[1] = cos(angle);
            (*normal)[2] = 0;
        }
        break;
    case 1: // Back
        if (axis == 1) {
            (*normal)[0] = -cos(angle);
            (*normal)[1] = 0;
            (*normal)[2] = sin(angle);
        }
        else if (axis == 2) {
            (*normal)[0] = 0;
            (*normal)[1] = cos(angle);
            (*normal)[2] = sin(angle);
        }
        break;
    case 2: // Left
        if (axis == 1) {
            (*normal)[0] = sin(angle);
            (*normal)[1] = 0;
            (*normal)[2] = cos(angle);
        }
        else if (axis == 2) {
            (*normal)[0] = sin(angle);
            (*normal)[1] = cos(angle);
            (*normal)[2] = 0;
        }
        break;
    case 3: // Forward
        if (axis == 1) {
            (*normal)[0] = cos(angle);
            (*normal)[1] = 0;
            (*normal)[2] = -sin(angle);
        }
        else if (axis == 2) {
            (*normal)[0] = 0;
            (*normal)[1] = cos(angle);
            (*normal)[2] = -sin(angle);
        }
        break;
    case 4: // Down
        if (axis == 1) {
            (*normal)[0] = -cos(angle);
            (*normal)[1] = sin(angle);
            (*normal)[2] = 0;
        }
        else if (axis == 2) {
            (*normal)[0] = 0;
            (*normal)[1] = sin(angle);
            (*normal)[2] = -cos(angle);
        }
        break;
    case 5: //Up
        if (axis == 1) {
            (*normal)[0] = cos(angle);
            (*normal)[1] = -sin(angle);
            (*normal)[2] = 0;
        }
        else if (axis == 2) {
            (*normal)[0] = 0;
            (*normal)[1] = -sin(angle);
            (*normal)[2] = -cos(angle);
        }
        break;
    }
}

void CubeSphere::addTextureCoords() {

    int totalVerCoords = m_rowPerFace * m_rowPerFace * m_numFaces * 3;
    for (int i = 0; i < m_rowPerFace * m_rowPerFace * m_numFaces * 3;) {
        float cx = 0, cy = 0, cz = 0, r = 1;

        float theta, phi;

        theta = atan2(-(m_cubesphereVertices[i + 2] - cz), m_cubesphereVertices[i] - cx);
        phi = acos(-(m_cubesphereVertices[i + 1] - cy) / r);

        float u = (theta + glm::pi<float>()) / (2 * glm::pi<float>());
        float v = phi / glm::pi<float>();

        if (u == 1) {
            u = 0;
        }
        m_cubesphereVertices[totalVerCoords++] = u;
        m_cubesphereVertices[totalVerCoords++] = v;
        i += 3;
    }
}

void CubeSphere::CreateMesh()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, m_cubesphereVertices.size() * sizeof(float), m_cubesphereVertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_cubesphereIndices.size() * sizeof(unsigned int), m_cubesphereIndices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(m_rowPerFace * m_rowPerFace * m_numFaces * 3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

void CubeSphere::createCubeSphere() {
    std::vector<float> cubesphereVerticesVector;
    for (int i = 0; i < m_numFaces; i++) {
        createCubeSphereFace(i, m_subdivision, &cubesphereVerticesVector);
    }
    for (int i = 0; i < cubesphereVerticesVector.size(); i++) {
        m_cubesphereVertices[i] = cubesphereVerticesVector[i];
    }
    int j = 0;
    for (int i = 0; ((float)i + m_rowPerFace + 1) <= cubesphereVerticesVector.size() / 3; i++) {
        if ((i + m_rowPerFace) % (m_rowPerFace * m_rowPerFace) == 0) {
            i += m_rowPerFace - 1; //-1 because after continue i++ 
            continue;
        }
        if ((i + 1) % m_rowPerFace == 0) continue;
        m_cubesphereIndices[j] = i;
        m_cubesphereIndices[j + 1] = i + 1;
        m_cubesphereIndices[j + 2] = i + m_rowPerFace;
        m_cubesphereIndices[j + 3] = i + 1;
        m_cubesphereIndices[j + 4] = i + m_rowPerFace;
        m_cubesphereIndices[j + 5] = i + m_rowPerFace + 1;
        j += 6;
    }

    addTextureCoords();
}


void CubeSphere::render() {
   
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, m_cubesphereIndices.size() * sizeof(unsigned int) / 4, GL_UNSIGNED_INT, 0);
}