#include "matrix_operations.h"
#include <iostream>
#include <iomanip>

using namespace std;

Matrix crate_matrix(int size)
{
    Matrix mat;
    mat.arr = new double* [size];
    for (int i = 0; i < size; i++)
    {
        mat.arr[i] = new double[size];
    }
    mat.size = size;
    return mat;
}

void delete_matrix(Matrix& mat)
{
    for (int i = 0; i < mat.size; i++)
    {
        delete[] mat.arr[i];
    }
    mat.size = -1;
}

void print_matrix(Matrix mat)
{
    if (mat.size <= 0)
        cout << "Matrix is empty\n";

    for (int i = 0; i < mat.size; i++)
    {
        for (int j = 0; j < mat.size; j++)
            cout << setw((int)(log10(mat.size * mat.size)) + 1) << mat.arr[i][j] << " ";
        cout << endl;
    }

    cout << endl;
}

Matrix Transposed(Matrix mat)
{
    Matrix output = crate_matrix(mat.size);
    for (int i = 0; i < mat.size; i++)
    {
        for (int j = 0; j < mat.size; j++)
        {
            output.arr[j][i] = mat.arr[i][j];
        }
    }
    return output;
}

Matrix Minor(Matrix mat, int i, int j)
{
    Matrix output = crate_matrix(mat.size - 1);
    int flag_deleted_i = 0;
    int flag_deleted_j = 0;
    for (int k = 0; k < mat.size; k++)
    {
        if (k == i)
        {
            flag_deleted_i = 1;
            continue;
        }
        for (int m = 0; m < mat.size; m++)
        {
            if (m == j)
            {
                flag_deleted_j = 1;
                continue;
            }
            output.arr[k - flag_deleted_i][m - flag_deleted_j] = mat.arr[k][m];
        }
        flag_deleted_j = 0;
    }
    return output;
}

void Multiply_on_number(Matrix mat, double num)
{
    for (int i = 0; i < mat.size; i++)
    {
        for (int j = 0; j < mat.size; j++)
        {
            mat.arr[i][j] *= num;
        }
    }
}

double Determinant(Matrix mat)
{
    if (mat.size == 1)
    {
        return mat.arr[0][0];
    }
    double result = 0;
    for (int i = 0; i < mat.size; i++)
    {
        double a = mat.arr[0][i] * (i % 2 ? -1 : 1);
        Matrix minor = Minor(mat, 0, i);
        double det_minor = Determinant(minor);
        delete_matrix(minor);
        result += a * det_minor;
    }
    return result;
}


Matrix Allied_matrix(Matrix mat)
{
    Matrix Allied = crate_matrix(mat.size);
    int sign = 1;
    for (int i = 0; i < mat.size; i++)
    {
        for (int j = 0; j < mat.size; j++)
        {
            Matrix M = Minor(mat, i, j);
            Allied.arr[i][j] = sign * Determinant(M);
            sign *= -1;
            delete_matrix(M);
        }
    }
    return Allied;
}

Matrix Inverse_matrix(Matrix mat)
{
    double det = Determinant(mat);
    if (det == 0)
    {
        cout << "Matrix determinant = 0\n";
        return crate_matrix(mat.size);
    }
    Matrix Allied = Allied_matrix(mat);
    Matrix result = Transposed(Allied);
    delete_matrix(Allied);
    
    Multiply_on_number(result, 1 / det);
    return result;
}

Matrix Matrix_multiply(Matrix mat1, Matrix mat2)
{
    Matrix result = crate_matrix(mat1.size);
    if (mat1.size != mat2.size)
    {
        cout << "Wrong sizes of matrix in multiplication function\n";
        return result;
    }
    for (int i = 0; i < mat1.size; i++)
    {
        for (int j = 0; j < mat1.size; j++)
        {
            result.arr[i][j] = 0;
            for (int k = 0; k < mat1.size; k++)
            {
                result.arr[i][j] += mat1.arr[i][k] * mat2.arr[k][j];
            }
        }
    }
    return result;
}