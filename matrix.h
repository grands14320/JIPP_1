//
// Created by Admin on 19.10.2020.
//

#include <stdio.h>
#include <fstream> // for file access
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
#include <cmath>


class Matrix {
private:
    unsigned m_rowSize = 0;
    unsigned m_colSize = 0;
    double **matrix;

public:
    Matrix(unsigned, unsigned);
    Matrix(unsigned);
    Matrix(std::string);
    Matrix(const Matrix& matrix);
    ~Matrix();

    void print() const;
    unsigned rows();
    unsigned cols();
    void set(unsigned, unsigned, double);
    double get(unsigned, unsigned);
    Matrix add(Matrix &);
    Matrix subtract(Matrix &);
    Matrix multiply(Matrix &);
    void store(std::string filename, std::string path);
};
