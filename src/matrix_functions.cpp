//
// Created by tyson on 01/11/24.
//

#include "matrix_functions.h"
#include <Epetra_MpiComm.h>
#include <Epetra_Map.h>
#include <EpetraExt_MatrixMatrix.h>

Epetra_CrsMatrix Epetra_Matrix_Create(const int rows, const int cols, const Epetra_Comm &comm)
{
    const Epetra_Map row_map(rows, 0 ,comm);
    const Epetra_Map col_map(cols, 0 ,comm);
    // Currently only works with Copy, might need a new method for view
    Epetra_CrsMatrix A(Epetra_DataAccess::Copy, row_map, cols);
    const int A_local_rows  = row_map.NumMyElements();
    for(int row = 0; row < A_local_rows; row++)
    {
        int globalRow = row_map.GID(row);
        auto values = new double[cols];
        auto indices = new int[cols];
        for (int j = 0; j < cols; j++)
        {
            values[j] =static_cast<double>(rand()) / RAND_MAX * 100;
            indices[j] = j;
        }
        A.InsertGlobalValues(globalRow,cols,values,indices);
        delete[] values;
        delete[] indices;
    }
    A.FillComplete(col_map,row_map);
    return A;
}

void pre_mult_self_transpose(const Epetra_CrsMatrix &In, Epetra_CrsMatrix &Out, const Epetra_DataAccess data_access)
{
    Epetra_CrsMatrix InTIn(data_access,In.ColMap(), In.NumGlobalCols());
    EpetraExt::MatrixMatrix::Multiply(In,true,In,false,InTIn);
    Out = InTIn;
}

bool compare_maps(const Epetra_CrsMatrix &A, const Epetra_CrsMatrix &B)
{
    return true;
}

void compare_copy_pre_self_mult(const int iterations, const Epetra_DataAccess data_access, const Epetra_Comm &comm, const int rows, const int cols)
{
    // Create A matrix
    const Epetra_CrsMatrix A(Epetra_Matrix_Create(rows, cols, comm));
    // Create AtA Matrix
    Epetra_CrsMatrix AtA(data_access,A.ColMap(), A.NumMyCols());
    // Preform Calc a number of times
    for(int iter=0; iter<iterations; ++iter)
    {
        pre_mult_self_transpose(A,AtA,data_access);
    }
}