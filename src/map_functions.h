//
// Created by tyson on 01/11/24.
//

#ifndef MAP_FUNCTIONS_H
#define MAP_FUNCTIONS_H

#include <Epetra_Map.h>
/// Create Epetra Map size 0
Epetra_Map Epetra_Map_Create();
/// Create Epetra Map size N
Epetra_Map Epetra_Map_Create(int N);
/// Destroy Epetra Map
void Epetra_Map_Destroy(Epetra_Map map);


#endif //MAP_FUNCTIONS_H
