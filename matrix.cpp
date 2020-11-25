//
// Created by Admin on 19.10.2020.
//

#include "matrix.h"
#include <algorithm>

Matrix::Matrix(unsigned r, unsigned c) {
    this->m_colSize = c;
    this->m_rowSize = r;
    this->matrix = new double*[r];
    for (int i = 0; i<r; ++i) {
        this->matrix[i] = new double[c];
    }
    //fill with default value = 0
    for (int i = 0; i<r; ++i) {
        for (int j = 0; j<c; j++) {
            this->matrix[i][j] = 0;
        }
    }
}

Matrix::Matrix(const Matrix& matrix) {
    this->m_rowSize = matrix.m_rowSize;
    this->m_colSize = matrix.m_colSize;

    this->matrix = new double*[this->m_rowSize];
    for (int i = 0; i < this->m_rowSize; i++) {
        this->matrix[i] = new double[this->m_colSize];
        for (int j = 0; j < this->m_colSize; j++) {
            this->matrix[i][j] = matrix.matrix[i][j];
        }
    }
}


//  God forgive my sins
Matrix::Matrix(std::string filename) {
    std::cout<<"reading: "<< filename<<std::endl;
    std::ifstream f(filename);
    std::string line;

    getline(f, line);
    for (char i : line) {
        if (i == '|') {
            this->m_colSize++;
        }
    }

    f.clear();
    f.seekg(0,std::ios::beg); // reset position

    while (getline(f, line)) {
        this->m_rowSize++;
    }

//
//    std::cout<<this->m_rowSize<< " " << this->m_colSize;

    this->matrix = new double*[this->m_rowSize];
    for (int i = 0; i<this->m_rowSize; ++i) {
        this->matrix[i] = new double[this->m_colSize];
    }

    f.clear();
    f.seekg(0,std::ios::beg);

    int counter1 = 0;
    int counter2 = 0;
    while (getline(f, line)) {
        line.erase(std::remove(line.begin(), line.end(), ' '), line.end()); //remove space characters

        std::istringstream ss(line);
        std::string token;


        while(std::getline(ss, token, '|')) {
            this->matrix[counter1][counter2] = std::stod(token);
            counter2++;
        }
        counter2 = 0;
        counter1++;
    }

    f.close();
}

Matrix::Matrix(unsigned squareDim) {
    this->m_colSize = squareDim;
    this->m_rowSize = squareDim;
    this->matrix = new double*[squareDim];
    for (int i = 0; i<squareDim; ++i) {
        this->matrix[i] = new double[squareDim];
    }
    //fill with default value = 0
    for (int i = 0; i<squareDim; ++i) {
        for (int j = 0; j<squareDim; j++) {
            this->matrix[i][j] = 0;
        }
    }
}

Matrix::~Matrix() {
    for (int i = 0; i < this->rows(); i++) {
        free(this->matrix[i]);
    }
    free(this-> matrix);
}


void Matrix::print() const {
    for (int i = 0; i<this->m_rowSize; ++i) {
        for (int j = 0; j<this->m_colSize; j++) {
            std::string additonalSpace = this->matrix[i][j] < 10 ? " " : "";
            std::cout << this->matrix[i][j] << additonalSpace << "|";
        }
        std::cout << std::endl;
    }
}

unsigned Matrix::rows() {
    return this->m_rowSize;
}

unsigned Matrix::cols() {
    return this->m_colSize;
}

void Matrix::set(unsigned r, unsigned c, double val) {
    this->matrix[r][c] = val;
}

double Matrix::get(unsigned r, unsigned c) {
    return this->matrix[r][c];
}

Matrix Matrix::add(Matrix &m2) {
    if (m2.cols() != this->cols() || m2.rows() != this->rows()) {
        return m2;
    }

    auto *newMatrix = new Matrix(this->m_rowSize, this->m_colSize);

    for (unsigned i = 0; i < this->rows(); i++) {
        for (unsigned j = 0; j < this->cols(); j++) {
            newMatrix->set(i, j, this->get(i, j) + m2.get(i, j));
        }
    }

    return *newMatrix;
}

Matrix Matrix::subtract(Matrix &m2) {
    if (m2.cols() != this->m_colSize || m2.rows() != this->m_rowSize) {
        return m2;
    }

    Matrix *newMatrix = new Matrix(this->m_rowSize, this->m_colSize);

    for (int i = 0; i < this->m_rowSize; i++) {
        for (int j = 0; j < this->m_colSize; j++) {
            newMatrix->set(i, j, this->get(i, j) - m2.get(i, j));
        }
    }

    return *newMatrix;
}

Matrix Matrix::multiply(Matrix &m2) {
    if (m2.cols() != this->m_rowSize || m2.rows() != this->m_colSize) {
        return m2;
    }

    Matrix *newMatrix = new Matrix(this->m_rowSize, this->m_colSize);

    for (int i = 0; i < this->m_rowSize; i++) {
        for (int j = 0; j < this->m_colSize; j++) {
            double res = 0;

            for (int k = 0; k < this->m_colSize; k++) {
                res += this->get(i, k) * m2.get(k, j);
            }

            newMatrix->set(i, j, res);
        }
    }

    return *newMatrix;
};

void Matrix::store(std::string filename, std::string path) {
    std::string filepath = path + filename;
    std::ofstream f(filepath);
    for (int i = 0; i < this->rows(); i++) {
        for (int j = 0; j < this->cols(); j++) {
            std::string additonalSpace = this->matrix[i][j] < 10 ? " " : "";
            f << this->matrix[i][j] << additonalSpace << "|";
        }
        f << std::endl;
    }

    f.close();
    std::cout << "saved: " + filepath << std::endl;
}
