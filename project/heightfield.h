#pragma once
#include <GL/glew.h>

class HeightField
{
public:
    void generateMesh(int N);
    void submitTriangles();

private:
    GLuint vao = 0;
    GLuint vbo = 0;
    GLuint ebo = 0;
    int indexCount = 0;
};