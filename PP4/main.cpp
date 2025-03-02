#include <iostream>
#include "XYPoint.h"

using std::cout;
using std::endl;


int main(int argc, char *argv[]){
    printf("argc = %d\n", argc);
    printf("argv[0] - %s\n", argv[0]);
    if (argc < 3) {
        printf("Argument count should be 3 or larger\n");
        return 1;
    }

    XYPoint dd;
    cout << "Default constructor called: " << dd.getX() << " " << dd.getY() << endl;

    double x = std::stod(argv[1]);
    double y = std::stod(argv[2]);
    
    XYPoint cc(x, y);
    cout << "Parameterized constructor called: " << cc.getX() << " " << cc.getY() << endl;


}