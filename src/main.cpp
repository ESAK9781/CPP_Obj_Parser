#include <iostream>
#include <string>

#include "objloader.hpp"
#include "mathConstants.hpp"

using namespace std;
using namespace d3;





int main(void){
    cout << "loading cube.obj" << endl;
    obj cube("res/cube.obj");
    cout << "cube loaded" << endl << endl;

    cout << "transforming cube" << endl;
    cube.rotate(1, 1, 1);
    cout << "transformations complete" << endl << endl;

    cout << "saving cube" << endl;
    cube.saveAsObj("res/ncube.obj");
    cout << "cube saved" << endl << endl;

    cout << "exiting" << endl << endl;

    return 0;
}