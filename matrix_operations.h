#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

struct Matrix
{
    double** arr;
    int size;
};

Matrix crate_matrix(int size);

void delete_matrix(Matrix& mat);

void print_matrix(Matrix mat);

double Determinant(Matrix mat);

Matrix Transposed(Matrix mat);

Matrix Minor(Matrix mat, int i, int j);

void Multiply_on_number(Matrix mat, double num);

Matrix Allied_matrix(Matrix mat);

Matrix Inverse_matrix(Matrix mat);

Matrix Matrix_multiply(Matrix mat1, Matrix mat2);
#endif