#include <iostream>
#include "matrix.h"
#include <stdio.h>
#include <fstream> // for file access
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
#include <cmath>

void clearScreen() {
    system("cls");
}

int main() {
    Matrix matrix1(10); // 1 arg square matrix constructor
    Matrix matrix2(10, 10); // 2 args constructor

    std::cout<<"Matrix 1st element: "<<matrix1.get(0, 0)<<std::endl;
    std::cout<<"Matrix1 rows: "<<matrix1.rows()<<std::endl;
    std::cout<<"Matrix1 cols: "<<matrix1.cols()<<std::endl;

    std::cout<<"Matrix 2 fill"<<std::endl;
    for (int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            matrix2.set(i,j, (double) i+j);
        }
    }
    matrix2.print();

    std::cout<<std::endl;

    std::cout<<"Matrix 1 fill"<<std::endl;
    for (int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            matrix1.set(i,j, (double) i*j);
        }
    }

    matrix1.print();
    std::cout<<"Matrix 2 to foo.txt"<<std::endl;
    matrix2.store("foo.txt", "");

    Matrix matrix3("foo.txt");

    std::cout<<"matrix 3 from file(copy of matrix 2): "<<std::endl;
    matrix3.print();

    Matrix sumResult = matrix1.add(matrix2);
    std::cout<<"Sum of m1 and m3"<<std::endl;
    sumResult.print();

    Matrix subResult = sumResult.subtract(matrix3);
    std::cout<<"Substraction: result - matrix2"<<std::endl;
    subResult.print();

    Matrix multiplyResult = matrix1.multiply(matrix1);
    std::cout<<"multipy result: matrix1 * matrix1 (matrix1^2)"<<std::endl;
    multiplyResult.print();

    Matrix copiedMatrix(multiplyResult);
    std::cout << "Copied result:" << std::endl;
    copiedMatrix.print();

    return 0;
}
