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

    float vDist(struct vertex a, struct vertex b);

    class obj {
        public:
            obj(string path);
            obj();
            ~obj();
            string toJSON();
            void saveAsJSON(string savePath);
            string toObj();
            void saveAsObj(string savePath);
            void scale(float f);
            void scaleTo(float dist);
            void rotX(float theta);
            void rotY(float theta);
            void rotZ(float theta);
            void rotate(float xrot, float yrot, float zrot);
            void recenter();
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