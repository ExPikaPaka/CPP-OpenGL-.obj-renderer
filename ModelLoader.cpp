#define _CRT_SECURE_NO_WARNINGS
#include "ModelLoader.h"

void ModelLoader::load(const char* filename) {
    std::string line;
    std::vector<std::string> lines;
    std::ifstream in(filename);
    if (!in.is_open()) {
        printf("Cannot load model %s\n", filename);
        return;
    }
    while (!in.eof()) {
        std::getline(in, line);
        lines.push_back(line);
    }
    in.close();
    float a, b, c;
    for (std::string& line : lines) {
        if (line[0] == 'v') {
            if (line[1] == ' ') {
                sscanf(line.c_str(), "v %f %f %f", &a, &b, &c);
                vertices.push_back(new float[3]{ a, b, c });
            }
            else if (line[1] == 't') {
                sscanf(line.c_str(), "vt %f %f", &a, &b);
                texcoords.push_back(new float[2]{ a, b });
            }
            else {
                sscanf(line.c_str(), "vn %f %f %f", &a, &b, &c);
                normals.push_back(new float[3]{ a, b, c });
            }
        }
        else if (line[0] == 'f') {
            int v0, v1, v2, t0, t1, t2, n;
            sscanf(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", &v0, &t0, &n, &v1, &t1, &n, &v2, &t2, &n);
            int* v = new int[3]{ v0 - 1, v1 - 1, v2 - 1 };
            faces.push_back(Face(3, v, NULL, n - 1));
        }
    }
    list = glGenLists(1);
    glNewList(list, GL_COMPILE);
    for (Face& face : faces) {
        if (face.normal != -1)
            glNormal3fv(normals[face.normal]);
        else
            glDisable(GL_LIGHTING);
        glBegin(GL_POLYGON);
        for (int i = 0; i < face.edge; i++)
            glVertex3fv(vertices[face.vertices[i]]);
        glEnd();
        if (face.normal == -1)
            glEnable(GL_LIGHTING);
    }
    glEndList();
    printf("Model: %s\n", filename);
    printf("Vertices: %d\n", vertices.size());
    printf("Texcoords: %d\n", texcoords.size());
    printf("Normals: %d\n", normals.size());
    printf("Faces: %d\n", faces.size());
    for (float* f : vertices)
        delete f;
    vertices.clear();
    for (float* f : texcoords)
        delete f;
    texcoords.clear();
    for (float* f : normals)
        delete f;
    normals.clear();
    faces.clear();
}

void ModelLoader::draw() { glCallList(list); }
