#pragma once
#include <string>
#include <vector>
using namespace std;



namespace d3 {
    struct vertex {
        float x;
        float y;
        float z;
    };

    union vect {
        struct vertex v; // vertex format
        float a[3]; // array format
    };

    struct triface {
        int verts[3];
    };

    class obj {
        public:
            obj(string path);
            obj();
            ~obj();
            string toJSON();
            static struct vertex createVertex(float x, float y, float z);
            static union vect createVect(float x, float y, float z);
            static struct triface createFace(int v1, int v2, int v3);
        private:
            vector<union vect> verts;
            vector<struct triface> faces;
            enum objtokens { // for loading .obj files
                ctok, // line is irrelevant (like "#")
                vtok, // line is vertex
                ftok // line is face
            };
            static int getToken(string token);
    };
}