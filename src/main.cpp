#include <chrono>
#include <iostream>
#include <mpi.h>
#include <Epetra_MpiComm.h>
#include "matrix_functions.h"
#include "map_functions.h"

int main() {
    // Init MPI
    MPI_Init(NULL, NULL);
    Epetra_MpiComm comm(MPI_COMM_WORLD);
    const int rank = comm.MyPID();
    // Set Random seed for consistent results
    std::srand(0);
    // Set Test variables
    const int iterations = 100;
    // Generate rows and columns between 10 and 1000
    const int rows = 10 + (std::rand() % (1000 - 10 + 1));
    const int cols = 10 + (std::rand() % (1000 - 10 + 1));
    if(rank == 0)
    {
        std::cout << "Rows: " << rows << std::endl;
        std::cout << "Cols: " << cols << std::endl;
    }
    // Copy test
    std::cout << "Begin Copy Test" << std::endl;
    const Epetra_DataAccess copy_access = Epetra_DataAccess::Copy;
    auto start = std::chrono::high_resolution_clock::now();
    compare_copy_pre_self_mult(iterations, copy_access, comm, rows, cols);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Copy time "<< rank << ": " <<  elapsed_seconds.count() << std::endl;
    // View Test
    std::cout << "Begin View Test" << std::endl;
    const Epetra_DataAccess view_access = Epetra_DataAccess::View;
    start = std::chrono::high_resolution_clock::now();
    compare_copy_pre_self_mult(iterations, view_access, comm, rows, cols);
    end = std::chrono::high_resolution_clock::now();
    elapsed_seconds = end - start;
    std::cout << "View time "<< rank << ": " << elapsed_seconds.count() << std::endl;


    MPI_Finalize();
    return 0;
}
