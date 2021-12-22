#include <iostream>
#include <fstream>
#include <iomanip>
#include "matrix_operations.h"
using namespace std;

Matrix fill_with_sequence(string filename)
{
    
    ifstream file(filename);
    int size;
    file >> size;
    Matrix mat = crate_matrix(size);
    int i, j;
    int n = mat.size;
    int flag = 1;
    int diag_flag = 1;
    i = 0;
    j = n - 1;
    for (int num = 1; num <= n * n; num++)
    {
        mat.arr[i][j] = num;

        if ((j == n - 1) && (i == n - 1) || (j == 0) && (i == 0)) // проверяем, не достигли ли мы главной диагонали
        {
            if (diag_flag == 1)
            {
                i += flag;
                j += flag;
                diag_flag = -1;
            }
            else
            {
                flag *= -1;
                if (flag == -1)
                {
                    j -= 1;
                }
                else if (flag == 1)
                {
                    i += 1;
                }
            }
        }
        else if (flag == 1 && j == n - 1) // проверяем, не дошли ли мы до нижней границы по j
        {
            i += 1;
            flag *= -1;
        }
        else if (flag == -1 && i == 0) // if (i == 0) // проверяем, не дошли ли мы до верхней границы по i
        {
            j -= 1;
            flag *= -1;
        }
        else if (flag == -1 && j == 0) // проверяем, не дошли ли мы до верхней границы по j
        {
            i += 1;
            flag *= -1;
        }
        else if (flag == 1 && i == n - 1) // if (i == 0) // проверяем, не дошли ли мы до нижней границы по i
        {
            j -= 1;
            flag *= -1;
        }
        else
        {
            i += flag;
            j += flag;
        }
    }
    return mat;
}

Matrix fill_from_file(string filename)
{
    int size;
    ifstream file(filename);
    file >> size;
    Matrix mat = crate_matrix(size);
    for (int i = 0; i < mat.size; i++)
    {
        for (int j = 0; j < mat.size; j++)
        {
            int a;
            file >> a;
            mat.arr[i][j] = a;
        }
    }
    return mat;
}


void print_matrix_to_file(Matrix mat, string filename)
{
    ofstream file(filename, ofstream::app);
    int offset = floor(log10(mat.size * mat.size) + 1);
    file << "------------------\n";
    file << "Square matrix with size of " << mat.size << ":\n";
    for (int i = 0; i < mat.size; i++)
    {
        for (int j = 0; j < mat.size - 1; j++)
        {
            file << setw(offset) << mat.arr[i][j] << " ";
        }
        file << setw(offset) << mat.arr[i][mat.size - 1] << "\n";
    }
    file << "------------------\n";
}

int main()
{
    Matrix a = fill_with_sequence("test.txt");
    print_matrix(a);
    Matrix b = fill_from_file("test.txt");
    print_matrix(b);    
    print_matrix_to_file(a, "matrix.txt");    
    delete_matrix(b);
    Matrix c = Transposed(a);
    Matrix d = Minor(a, 1, 1);    
    print_matrix(c);
    print_matrix(d);
    Multiply_on_number(d, 5);
    print_matrix(d);
    Matrix d_1 = Inverse_matrix(d);
    print_matrix(d_1);
    Matrix a1 = crate_matrix(2);
    a1.arr[0][0] = 1;
    a1.arr[0][1] = 2;
    a1.arr[1][0] = 3;
    a1.arr[1][1] = 4;
    print_matrix(a1);
    Matrix a2 = crate_matrix(2);
    a2.arr[0][0] = 5;
    a2.arr[0][1] = 6;
    a2.arr[1][0] = 7;
    a2.arr[1][1] = 8;
    print_matrix(a2);
    print_matrix(Matrix_multiply(a1, a2));
    return 0;
}