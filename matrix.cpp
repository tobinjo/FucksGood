#include "Matrix.h"
#include "util.h"
#include "mt19937.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <cstdio>
#include <string>
using namespace std;

/*
Is this motherfucker compiling right now?
 Yeah
*/


//Check the clauses then go from there
// I guess I need to modify ptr but not postive how to go about doing that
//This works I think but I'm not sure if its setting up the matrix or not

void Matrix_init(Matrix *ptr, int num_rows_in, int num_columns_in){
    assert(num_rows_in < 100);
    assert(num_columns_in < 100);
    //I think this is chill but who the fuck knows
    const int rows = num_rows_in;
    const int cols = num_columns_in;
    
    ptr->num_rows = rows;
    ptr->num_columns = cols;
    return;
}


//I think this works
//Need to check requires clause though
int Matrix_size(const Matrix *ptr){
    assert(ptr -> num_rows <= 100);
    assert(ptr -> num_columns <= 100);
    return (ptr -> num_rows)*(ptr -> num_columns);
}

//This seems to work as well
int Matrix_num_rows(const Matrix *ptr){
    int size = Matrix_size(ptr);
    int rows = size / ptr->num_columns;
    return rows;
}

//This is chill, I think it will give the right answers
int Matrix_num_columns(const Matrix *ptr){
    int size = Matrix_size(ptr);
    int cols = size / ptr->num_rows;
    return cols;
}

//This might not work but at least it compiles
//I think it works though
//Need to check if row and column indexing starts from 0 or 1
int Matrix_row(const Matrix *ptr, const char *location_ptr){
    //Making an int to describe the row
    int rownum = 0;
    int totalrows = Matrix_num_rows(ptr);
    int ele = 1;

    if(&(ptr -> array[0]) == location_ptr)
        return 0;
    //ptr -> array++;
    while(&(ptr -> array[ele]) != location_ptr){
        ele += 1;
        if(ele % totalrows == 0)
            rownum += 1;
    }
    return rownum;
}

int Matrix_col(const Matrix *ptr, const char *location_ptr){
    int colnum = 0;
    int totalcols = Matrix_num_columns(ptr);
    int ele = 1;
    
    if(&(ptr -> array[0]) == location_ptr)
        return 0;
    while(&(ptr -> array[ele]) != location_ptr){
        ele += 1;
        if(ele % totalcols == 0)
            colnum +=1;
    }
    
    return colnum;
}

//This works, this compiles
void Matrix_print(const Matrix *ptr){
    int size = Matrix_size(ptr);
    int cols = Matrix_num_columns(ptr);
    for(int i = 0; i < size; i+=1){
        cout << ptr -> array[i];
        if((i+1) % cols == 0){
            cout << endl;
        }
    }
}

//I think this will work, this compiles
char * Matrix_at(Matrix *ptr, int row, int col){
    int totalcols = Matrix_num_rows(ptr);
    int ElePos = totalcols*row + col;
    char * returnptr = &(ptr -> array[ElePos]);
    return returnptr;
}

//This is the exact same thing as above
const char * Matrix_at(const Matrix *ptr, int row, int col){
    int totalcols = Matrix_num_rows(ptr);
    int ElePos = totalcols*row + col;
    const char * returnptr = &(ptr -> array[ElePos]);
    return returnptr;
}

//This compiles, I think it will work
void Matrix_range_radius(const Matrix *src, int row_center, int col_center,
                         int radius, char *dest, int *dest_size){
    //Making sure we don't go off the grid
    int topRow = row_center - radius;
    if(topRow < 0) topRow = 0;
    int botRow = row_center + radius;
    if(topRow > Matrix_num_rows(src)) botRow = Matrix_num_rows(src);
    int RCol = col_center - radius;
    if(RCol < 0) RCol = 0;
    int LCol = col_center + radius;
    if(LCol > Matrix_num_columns(src)) LCol = Matrix_num_columns(src);
    
    //Finding the element number for the corners, don't actually need this
    int TRPos = Matrix_num_columns(src)*topRow + RCol;
    int TLPos = Matrix_num_columns(src)*topRow + LCol;
    //int BRPos = Matrix_num_columns(src)*botRow + RCol;
    //int BLPos = Matrix_num_columns(src)*botRow + LCol;
    
    //This should be ok
    int radiusrows = botRow - topRow + 1;
    
    //Checking Assert Clause;
    assert(*dest_size <= (TLPos - TRPos + 1)*(radiusrows));
    
    //Make an array of ints with all the element positions
    int index = 0;
    for(int i = topRow; i < topRow + radiusrows; i += 1){
        for(int j = LCol; j < (RCol + 1); j += 1){
            dest[index] = src -> array[(Matrix_num_columns(src) * i) + j];
            index += 1;
        }
    }
    //Ok we should be good
}

//This should work
char * Matrix_search_simple(Matrix *ptr, char c){
    for(int i = 0; i < Matrix_size(ptr); i += 1){
        if(ptr -> array[i] == c){
            char * returnptr = &(ptr -> array[i]);
            return returnptr;
        }
    }
    return nullptr;
}

//Compile this after the function eecs280_rand_int(); has been written
/*
char * Matrix_search_random(Matrix *ptr, char c){
    int col = eecs280_rand_int();
    int row = eecs280_rand_int();
    totalcols = Matrix_num_columns(ptr);
    while(ptr -> array[(totalcols*row) + col] != c){
        col = eecs280_rand_int();
        row = eecs280_rand_int();
    }
    char * goodptr = &(ptr -> array[(totalcols*row) + col]);
    return goodptr;
}
 */
