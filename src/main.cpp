#include <iostream>
#include <string>

#include "objloader.hpp"
using namespace std;
using namespace d3;





int main(void){
    cout << "testing object loader" << endl;
    obj o("res/testobj.obj");
    cout << "loading complete" << endl;

    cout << "cleaning object" << endl;
    o.recenter();
    o.scaleTo(10);

    cout << "serializing to .obj" << endl;
    o.saveAsObj("res/transformed.obj");
    cout << "exiting" << endl << endl;
    

    return 0;
}