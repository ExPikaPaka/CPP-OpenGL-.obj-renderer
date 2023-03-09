#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <windows.h>
#include <gl/gl.h>
#pragma comment(lib, "opengl32.lib")

#include "Engine.h"

class ModelLoader
{
    class Face {
    public:
        int edge;
        int* vertices;
        int* texcoords;
        int normal;

        Face(int edge, int* vertices, int* texcoords, int normal = -1) {
            this->edge = edge;
            this->vertices = vertices;
            this->texcoords = texcoords;
            this->normal = normal;
        }
    };
    std::vector<float*> vertices;
    std::vector<float*> texcoords;
    std::vector<float*> normals;
    std::vector<Face> faces;
    GLuint list;

public:
    void load(const char* filename);
    void draw();
};

