#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "objloader.hpp"
using namespace std;
using namespace d3;

// outp must be a pointer to the first element of an array of three integers
int * splitFaceData(string data, int * outp) { // returns the three values in the a/b/c portion of the face data as an array of three integers
    int out[3];
    int opos = 0;

    string value;
    for (int i = 0; i < data.size(); i++){
        if (data[i] == '/') {
            out[opos] = stoi(value);
            opos++;
            if (opos >= 3) break;
            value.clear();
        } else {
            value += data[i];
        }
    }
    out[2] = stoi(value);

    // cout << "face: " << out[0] << " " << out[1] << " " << out[2] << endl;

    for (int i = 0; i < 3; i++){
        *(outp + i) = out[i];
    }

    return outp;
}

struct vertex obj::createVertex(float x, float y, float z) {
    struct vertex out;
    out.x = x;
    out.y = y;
    out.z = z;
    return out;
}
union vect obj::createVect(float x, float y, float z) {
    union vect out;
    out.v.x = x;
    out.v.y = y;
    out.v.z = z;
    return out;
}
struct triface obj::createFace(int v1, int v2, int v3) {
    struct triface out;
    out.verts[0] = v1;
    out.verts[1] = v2;
    out.verts[2] = v3;
    return out;
}

obj::obj(string path) { // construct from file
    cout << "loading file: " + path << endl;
    fstream reader;
    reader.open(path);

    string line; // to store the line itself
    string token; // to find the type of information in the line
    string data; // to record the data in the line
    int commentCount;
    int vertexCount;
    int faceCount;
    while (getline(reader, line)){
        stringstream contents; // to separate the line into words
        contents << line;
        contents >> token;
        switch (getToken(token)) {
            case ctok:
                commentCount++;
                break;
            case vtok: {
                contents >> data;
                float x = stof(data);
                contents >> data;
                float y = stof(data);
                contents >> data;
                float z = stof(data);
                verts.push_back(createVect(x, y, z));
                vertexCount++;
                break;
            }
            case ftok: {
                int vs[3];
                for (int i = 0; i < 3; i++){
                    contents >> data;
                    int split[3];
                    vs[i] = *(splitFaceData(data, &split[0])) - 1; // the -1 makes the vertices zero indexed, rather than 1 indexed
                }
                faces.push_back(createFace(vs[0], vs[1], vs[2]));
                break;
            }
            default:
                break;
        }
    }

    reader.close();
}

obj::obj() { // default constructor, returns empty object
    // nothing here yet
}

obj::~obj() { // free memory
    // TODO find out if vectors need to be cleared
}

void addTabs(string s, int tcount) {
    for (int i = 0; i < tcount; i++) {
        
    }
}
string obj::toJSON() {
    string out;
    int tabs = 0;



}

int obj::getToken(string token){ // map token to integer
    if (token.compare("v") == 0){
        return vtok;
    } else if (token.compare("f") == 0){
        return ftok;
    } else {
        return ctok;
    }
}





