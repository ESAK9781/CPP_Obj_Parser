#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
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
    verts.clear();
    faces.clear();
}

void addTabs(string * s, int tcount) {
    for (int i = 0; i < tcount; i++) {
        s->append("\t");
    }
}

string obj::toJSON() { // creates a JSON string representing the object
    string out = "{\n";

    addTabs(&out, 1);
    out += "\"vertices\" : [\n";
    union vect curV;
    for (int i = 0; i < verts.size(); i++){
        curV = verts[i];
        addTabs(&out, 2);
        out += "[" + to_string(curV.v.x) + ", " + to_string(curV.v.y) + ", "
            + to_string(curV.v.z) + "]";
        if (i != verts.size() - 1) out += ",";
        out += "\n";
    }
    addTabs(&out, 1);
    out += "],\n";

    addTabs(&out, 1);
    out += "\"faces\" : [\n";
    struct triface curF;
    for (int i = 0; i < faces.size(); i++){
        curF = faces[i];
        addTabs(&out, 2);
        out += "[" + to_string(curF.verts[0]) + ", " + to_string(curF.verts[1])
            + ", " + to_string(curF.verts[2]) + "]";
        if (i != faces.size() - 1) out += ",";
        out += "\n";
    }
    addTabs(&out, 1);
    out += "]\n";

    out += "}";
    return out;
}

void obj::saveAsJSON(string savePath) { // generates a json string using "toJSON" and saves it to the savePath file
    string jsonSave = toJSON();
    ofstream saveLoc(savePath);
    saveLoc << jsonSave;
    saveLoc.close();
}

void obj::scale(float sf) { // scales all points in the object about its local origin
    union vect curV;
    for (int i = 0; i < verts.size(); i++) {
        curV = verts[i];
        curV.a[0] *= sf;
        curV.a[1] *= sf;
        curV.a[2] *= sf;
    }
}

float d3::vDist(struct vertex a, struct vertex b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    float dz = a.z - b.z;

    return sqrt((dx * dx) + (dy * dy) + (dz * dz));
}

void obj::scaleTo(float dist) { // scales the object to fit in a sphere of radius dist about the origin
    float maxDist = 0;
    float curDist;
    struct vertex origin = createVertex(0, 0, 0);
    for (int i = 0; i < verts.size(); i++) {
        curDist = vDist(origin, verts[i].v);
        maxDist = (curDist > maxDist) ? curDist : maxDist;
    }

    float sf = dist / maxDist;
    scale(sf);
}

string obj::toObj() {
    string out;
    union vect curV;
    for (int i = 0; i < verts.size(); i++) {
        curV = verts[i];
        out += "v " + to_string(curV.v.x) + " " + to_string(curV.v.y) + " " + to_string(curV.v.z) + "\n";
    }

    out += "\n";

    struct triface curF;
    for (int i = 0; i < faces.size(); i++) {
        curF = faces[i];
        out += "f " + to_string(curF.verts[0] + 1) + " " + to_string(curF.verts[1] + 1)
            + " " + to_string(curF.verts[2] + 1) + "\n";
    }

    return out;
}

void obj::saveAsObj(string savePath) {
    string objSave = toObj();
    ofstream saveLoc(savePath);
    saveLoc << objSave;
    saveLoc.close();
}


void obj::recenter() { // moves the local origin to the object's center of mass
    union vect com = createVect(0, 0, 0); // the center of mass
    struct vertex curV;

    float sf = 1.f / (faces.size() * 3); // the weight of each vertex in the total
    for (int f = 0; f < faces.size(); f++) {
        for (int v = 0; v < 3; v++) {
            curV = verts[faces[f].verts[v]].v;
            com.v.x += curV.x * sf;
            com.v.y += curV.y * sf;
            com.v.z += curV.z * sf;
        }
    }

    // translate all of the points to center around the center of mass

    for (int i = 0; i < verts.size(); i++) {
        verts[i].v.x -= com.v.x;
        verts[i].v.y -= com.v.y;
        verts[i].v.z -= com.v.z;
    }
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






