#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using std::vector;
using std::ifstream;
using std::ofstream;
using std::string;
using std::cerr;
using std::cout;
using std::endl;
using std::getline;
using std::istringstream;


bool readMatrix(const string& filename, vector<vector<int>>& matrix, int& rows, int& cols) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Unable to open matrix file: " << filename << endl;
        return false;
    }

    string line;

    while (getline(file, line)) {
        if (!line.empty()) break;
    }
    istringstream iss(line);
    if (!(iss >> rows >> cols)) {
        cerr << "Error: Invalid matrix dimensions in file: " << filename << endl;
        return false;
    }

    matrix.resize(rows, vector<int>(cols));

    int rowCount = 0;
    while (getline(file, line)){
        if (line.empty()) continue;
        if (rowCount >= rows){
            cerr << "Error: More rows than expected in file: " << filename << endl;
            return false;
        }
        istringstream iss(line);
        for (int j = 0; j < cols; ++j) {
            if (!(iss >> matrix[rowCount][j])) {
                cerr << "Error: Invalid matrix data in file: " << filename << endl;
                return false;
            }
        }
        rowCount++;
    }
    if (rowCount < rows){  
        cerr << "Error: Fewer rows than expected in file: " << filename << endl;
        return false;
    }

    return true;
}


bool readVector(const string& filename, vector<int>& vec, int& size) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Unable to open vector file: " << filename << endl;
        return false;
    }
    string line;
    while (getline(file, line)) {
        if (!line.empty()) break;
    }
    istringstream iss(line);
    if (!(iss >> size)) {
        cerr << "Error: Invalid vector size in file: " << filename << endl;
        return false;
    }
    vec.resize(size);

    int count = 0;
    while (getline(file, line)){
        if (line.empty()) continue;
        if (count >= size){
            cerr << "Error: More elements than expected in file: " << filename << endl;
            return false;
        }
        istringstream iss(line);
        if (!(iss >> vec[count])) {
            cerr << "Error: Invalid vector data in file: " << filename << endl;
            return false;
        }
        count++;
    }

    if (count < size){ 
        cerr << "Error: Fewer elements than expected in file: " << filename << endl;
        return false;
    }

    return true;
}



vector<int> multiplyMatrixVector(const vector<vector<int>>& matrix, const vector<int>& vec) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    vector<int> result(rows, 0);
    for (int i=0; i < rows; ++i) {
        for (int j=0; j < cols; ++j) {
            result[i] += matrix[i][j] * vec[j];
        }
    }
    return result;
}



int main(int argc, char* argv[]){
    if (argc != 5) {
        cerr << "Usage: " << argv[0] << " -m <matrix_file> -v <vector_file>" << endl;
        return 1;
    }

    string matrixFile, vectorFile;
    for (int i=1; i < argc; i+=2){
        if(string(argv[i]) == "-m"){
            matrixFile = argv[i+1];
        } else if(string(argv[i])=="-v"){
            vectorFile = argv[i+1];
        } else {
            cerr << "ERROR: Invalid INPUT Provided!" << endl;
            return 1;
        }
    }
    
    vector<vector<int>> matrix;
    vector<int> vec;
    int matrixRows=0, matrixCollumns=0, vectorSize=0;

    if (!readMatrix(matrixFile, matrix, matrixRows, matrixCollumns) || !readVector(vectorFile, vec, vectorSize)) {
        return 1;
    }

    if (matrixCollumns != vectorSize){
        cerr << "ERROR: Matrix Columns [" << matrixCollumns << "] do not match vector size [" << vectorSize <<"]" <<endl;
        return 1;
    }
    vector<int> multiplicationResult = multiplyMatrixVector(matrix, vec);

    for (int val : multiplicationResult) {
        cout << val << endl;
    }

    return 0;
}
