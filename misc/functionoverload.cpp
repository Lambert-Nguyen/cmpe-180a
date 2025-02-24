// Implement to test the answer for the below question:

// Assume you have the following two functions using C++ overloading:

// int average(int a, int b);

// double average(double a, double b);

// Then you invoke the function on two integer constants but you want to use double version of the function to get more precision in the result: you will use the following invocation:

// average(double)(3, 7)

// (double)average(3, 7)

// average<double>(3, 7)

// average(3, 7)

#include <iostream>

class math {
    public:
    int sum(int a, int b) {
        return a + b;
    }
    double sum(double a, double b){
        std::cout << "callign double" <<std::endl;
        return a + b;
    }

    private:
};

int sum(int a, int b) {
    std::cout << "calling int" <<std::endl;
    return a + b;
}
double sum(double a, double b){
    std::cout << "calling double" <<std::endl;
    return a + b;
}

int main() {
    int a = 10;
    int b = 20;

    math obj;

    // int c = obj.sum<double>(a,b);
    double c = (double)sum(a,b);
    std::cout << "c = " << c << std::endl;

    return 0;

}