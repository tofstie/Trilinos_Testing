set(MAIN_SRC main.cpp
        map_functions.cpp
        matrix_functions.cpp
        matrix_functions.h)

ADD_EXECUTABLE(main ${MAIN_SRC})
TARGET_LINK_LIBRARIES(main ${Trilinos_LIBRARIES} ${Trilinos_TPL_LIBRARIES} MPI::MPI_CXX)