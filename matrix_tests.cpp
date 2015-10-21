#include "Matrix.h"
#include "util.h"
#include <iostream>
#include <cassert>
using namespace std;

void test_minimum_size_matrix();
void test_max_size_matrix();
void test_matrix_num_rows();
void test_matrix_num_cols();
void test_matrix_print();
void test_matrix_at();

// ADD PROTOTYPES FOR YOU TEST FUNCTIONS HERE

int main() {

  test_minimum_size_matrix();
  test_max_size_matrix();
    test_matrix_num_rows();
    test_matrix_num_cols();
    test_matrix_print();
    test_matrix_at();
  // CALL YOUR TEST FUNCTIONS HERE
  
  cout << "Matrix_tests passed" << endl;
  return 0;
}

void test_minimum_size_matrix() {
  Matrix matrix;
  Matrix *ptr = &matrix;
  Matrix_init(ptr, 0, 0);
  assert(Matrix_size(ptr) == 0);
}

void test_max_size_matrix(){
    Matrix matrix;
    Matrix *ptr = &matrix;
    Matrix_init(ptr, 99, 99);
    assert(Matrix_size(ptr) == 9801);
}


void test_matrix_num_rows(){
    Matrix matrix;
    Matrix *ptr = &matrix;
    Matrix_init(ptr, 4, 5);
    assert(Matrix_num_rows(ptr) == 4);
}

//These are super basic, add better ones later
void test_matrix_num_cols(){
    Matrix matrix;
    Matrix *ptr = &matrix;
    Matrix_init(ptr, 4, 5);
    assert(Matrix_num_columns(ptr) == 5);
}

void test_matrix_print(){
    Matrix matrix;
    Matrix *ptr = &matrix;
    Matrix_init(ptr, 3, 3);
    for(int i = 0; i < 9; i++){
        if(i % 2 == 0)
            ptr -> array[i] = 'X';
        else
            ptr -> array[i] = 'O';
    }
    const Matrix * cptr = ptr;
    Matrix_print(cptr);
    return;
}

void test_matrix_at(){
    Matrix matrix;
    Matrix *ptr = &matrix;
    Matrix_init(ptr, 3, 3);
    for(int i = 0; i < 9; i++){
        if(i % 2 == 0)
            ptr -> array[i] = 'X';
        else
            ptr -> array[i] = 'O';
    }
    assert(&(ptr->array[0]) == Matrix_at(ptr, 0, 0));
}


// IMPLEMENT YOUR TEST FUNCTIONS HERE
