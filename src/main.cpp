#include <iostream>
#include <string>

#include "objloader.hpp"
using namespace std;
using namespace d3;





int main(void){
    cout << "testing object loader" << endl;
    obj o("res/testobj.obj");
    cout << "loading complete" << endl << "exiting" << endl;
    return 0;
}