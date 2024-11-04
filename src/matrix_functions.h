//
// Created by tyson on 01/11/24.
//

#ifndef MATRIX_FUNCTIONS_H
#define MATRIX_FUNCTIONS_H
#include <Epetra_CrsMatrix.h>

Epetra_CrsMatrix Epetra_Matrix_Create(const int rows, const int cols, const Epetra_Comm &comm);

void pre_mult_self_transpose(const Epetra_CrsMatrix &In, Epetra_CrsMatrix &Out, const Epetra_DataAccess data_access);

bool compare_maps(const Epetra_CrsMatrix &A, const Epetra_CrsMatrix &B);

void compare_copy_pre_self_mult(const int iterations, const Epetra_DataAccess data_access, const Epetra_Comm &comm, const int rows, const int cols);
#endif //MATRIX_FUNCTIONS_H
