#include <chrono>
#include <iostream>
#include <mpi.h>
#include <Epetra_MpiComm.h>
#include <Epetra_Map.h>
#include <Epetra_CrsMatrix.h>

#include <EpetraExt_MatrixMatrix.h>
int main() {
    // Init MPI
    MPI_Init(NULL, NULL);
    Epetra_MpiComm comm(MPI_COMM_WORLD);
    const int rank = comm.MyPID();
    // Set Matrix Size (of A)
    const int num_of_rows = 1000;
    const int num_of_cols = 500;
    // Create Epetra Maps
    const Epetra_Map row_map(num_of_rows, 0 ,comm);
    const Epetra_Map col_map(num_of_cols, 0 ,comm);
    // Create A & B
    Epetra_CrsMatrix A(Epetra_DataAccess::Copy, row_map, num_of_cols);
    Epetra_CrsMatrix B(Epetra_DataAccess::Copy, col_map, num_of_rows);
    // Set Random seed for consistent results
    std::srand(0);
    // Fill A
    const int A_local_rows  = row_map.NumMyElements();
    for(int row = 0; row < A_local_rows; row++)
    {
        int globalRow = row_map.GID(row);
        auto values = new double[num_of_cols];
        auto indices = new int[num_of_cols];
        for (int j = 0; j < num_of_cols; j++)
        {
            values[j] = rand() % 100;
            indices[j] = j;
        }
        A.InsertGlobalValues(globalRow,num_of_cols,values,indices);
        delete[] values;
        //delete[] indices;
    }
    A.FillComplete(col_map,row_map);
    // Fill B
    const int B_local_rows  = col_map.NumMyElements();
    for(int row = 0; row < B_local_rows; row++)
    {
        int globalRow = col_map.GID(row);
        auto values = new double[num_of_rows];
        auto indices = new int[num_of_rows];
        for (int j = 0; j < num_of_rows; j++)
        {
            values[j] = rand() % 100;
            indices[j] = j;
        }
        B.InsertGlobalValues(globalRow,num_of_rows,values,indices);
        delete[] values;
        delete[] indices;
    }
    B.FillComplete(row_map,col_map);
    // Create C
    Epetra_CrsMatrix C(Epetra_DataAccess::Copy, row_map,num_of_rows);
    // Print Matrix info
    if (rank == 0)
    {
        std::cout << "A Rows: "<< A.NumGlobalRows() << " A Cols: " << A.NumGlobalCols() << std::endl;
        std::cout << "B Rows: "<< B.NumGlobalRows() << " B Cols: " << B.NumGlobalCols() << std::endl;
        std::cout << "C Rows: "<< C.NumGlobalRows() << " C Cols: " << C.NumGlobalCols() << std::endl;
    }
    // Multiply
    const int number_of_multiplication = 5;
    for(int i = 0 ; i < number_of_multiplication; i++)
    {
        auto start = std::chrono::high_resolution_clock::now();
        EpetraExt::MatrixMatrix::Multiply(A,false,B,false,C);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::cout << "Multiplication time: " << elapsed_seconds.count() << std::endl;
    }
    std::cout << "My Process ID = " << comm.MyPID() << std::endl;
    MPI_Finalize();
    return 0;
}
