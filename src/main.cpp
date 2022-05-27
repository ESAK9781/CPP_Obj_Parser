#include <iostream>
#include <string>

#include "objloader.hpp"
#include "mathConstants.hpp"

using namespace std;
using namespace d3;





int main(void){
    obj cube("res/complexShape.obj");
    cout << "cube loaded" << endl << endl;

    cout << "transforming pbject" << endl;
    cube.scaleTo(1);
    cube.rotate(1, 1, 1);
    cout << "transformations complete" << endl << endl;

    cout << "saving object" << endl;
    cube.saveAsObj("res/ncomplexShape.obj");
    cout << "object saved" << endl << endl;

    cout << "exiting" << endl << endl;

    return 0;
}