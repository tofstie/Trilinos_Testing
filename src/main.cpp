#include <iostream>
#include <mpi.h>
#include <Epetra_MpiComm.h>
int main() {
    MPI_Init(NULL, NULL);
    Epetra_MpiComm comm(MPI_COMM_WORLD);
    comm.Barrier();
    std::cout << "My Process ID = " << comm.MyPID() << std::endl;
    MPI_Finalize();
    return 0;
}
