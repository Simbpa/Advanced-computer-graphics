#include "heightfield.h"

#include <vector>


void HeightField::generateMesh(int N)
{
    std::vector<float> vertices;
    std::vector<unsigned int> indices;


    // Generate grid
    for (int z = 0; z < N; z++) {
        for (int x = 0; x < N; x++) {
            float xf = (float)x / (N - 1);
            float zf = (float)z / (N - 1);

            vertices.push_back((xf - 0.5f));
            vertices.push_back(0.0f);
            vertices.push_back((zf - 0.5f));
        }
    }

    // Generate indices
    for (int z = 0; z < N - 1; z++) {
        for (int x = 0; x < N - 1; x++) {
            int i = z * N + x;

            indices.push_back(i);
            indices.push_back(i + N);
            indices.push_back(i + 1);

            indices.push_back(i + 1);
            indices.push_back(i + N);
            indices.push_back(i + N + 1);
        }
    }

    indexCount = (int)indices.size();

    // Create buffers
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void HeightField::submitTriangles(void)
{
	glBindVertexArray(vao);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
