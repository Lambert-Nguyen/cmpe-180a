// Write a C++ program that multiplies INTEGER matrix by a vector given to you in two files whose names will be passed via command line arguments, your program must print out the output vector to STDOUT in the format displayed below 

// IMPORTANT NOTE: we are defining the format of input matrix to have a first line that includes the number of rows and columns in the first line. 
// The output format is not changed, just the resulting matrix should be output. for the vector file the first line has the number of rows in the vector. This should make your job easier.

// matrix.txt

// 2 3

// 1 2 1

// 2 1 2

// vector.txt

// 3 

// 1 

// 1

// 1 

// matrixproduct -m matrix.txt -v vector.txt

// 4

// 5

// Note any type of space can be used as separator. Must use streams for input output and as much use of C++ as possible, i.e. use of printf instead of cout will result in deductions from grade. 

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::cerr;
using std::endl;
using std::vector;
using std::string;

int main(int argc, char* argv[]){
    if (argc != 5) {
        cerr << "Usage: " << argv[0] << " -m <matrix_file> -v <vector_file>" << endl;
        return 1;
    }

    string matrixFile, vectorFile;
    for (int i=1; i < argc, i+=2){
        if(string(argv[i]=='-m')){
            matrixFile = argv[i+1];
        } else if(string(argv[i]=='-v')){
            vectorFile = argv[i+1];
        } else {
            cerr << "ERROR: Invalid INPUT Provided!" << endl;
            return 1;
        }
    }
    
    vector<vector<int>> maxtrix;
    vector<int> vector;
    int matrixRows=0, matrixCollumns=0, vectorSize=0;
    




}