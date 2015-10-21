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

bool is_Agent_satisfied(Matrix * ptr, int rowindex, int colindex, double satisfaction_ratio);
bool is_everyone_satisfied(Matrix * ptr, double satisfaction_ratio);
bool is_that_spot_open(Matrix * ptr, int rowindex, int colindex);

int main(int argc, char **argv){
    cout << "Welcome to project 3 fam!" << endl;
    int rows, cols;
    double satisfaction_ratio;
    double percentX, percentY;
    string whatever;
    Matrix matrix;
    Matrix *ptr = &matrix;
    
    if(argc > 1){
        int index = 1;
        if(strcmp(argv[1], "-d") == 0){
            index +=1;
            set_debug_mode(true);
        }
        fstream file;
        file.open(argv[index]);
        if(!file.is_open()){
            cout << "The file " << argv[index] << " didn't open" << endl;
            exit(1);
        }
        else{
            //Time to imput the shit
            string mode;
            //The format is: mode _______, just need something to grab "mode", used the same thing twice
            file >> mode >> mode;
            if(mode.compare("file") == 0){
                //The format is: satisfaction_ratio _____
                file >> whatever >> satisfaction_ratio;
                //The format is: size _ x _
                file >> whatever;
                file >> rows >> whatever >> cols;
                //Time to read in the grid
                //I think the main thing here is to read it in as a c++ string
                //Then convert it to a c string which I can put into an array
                //Initialize the array here before the for loop
                assert(rows >= 1);
                assert(cols >= 1);

                Matrix_init(ptr, rows, cols);
                //Initialized line to a random location because the compiler was complaining about it
                char * line;
                char doesntmatter = 'f';
                line = &doesntmatter;
                for(int i = 0; i < rows; i +=1){
                    file.getline(line, cols);
                    for(int j = 0; j < cols; j +=1){
                        ptr -> array[(cols*i) + j] = line[j];
                    }
                }
            //This should be working but I'm a bit skeptical
            }
            else if(mode.compare("random") == 0){
                file >> whatever >> satisfaction_ratio;
                file >> rows >> whatever >> cols;
                assert(rows >= 1);
                assert(cols >= 1);
                assert(satisfaction_ratio >= 0 && satisfaction_ratio <= 1);
                
                
                file >> whatever >> percentX;
                file >> whatever >> percentY;
                assert(percentX + percentY >= 0 && percentX + percentY < 1);
                
                //Make the grid now

                Matrix_init(ptr, rows, cols);
                for(int i = 0; i < rows*cols; i +=1){
                    double prob = eecs280_rand_probability();
                    if(prob >= 0 && prob <= percentX){
                        ptr -> array[i] = 'X';
                    }
                    else if(prob > percentX && prob <= percentX + percentY)
                        ptr -> array[i] = 'O';
                    else
                        ptr -> array[i] = ' ';
                }
                //Grid is initilized
            }
            else{
                cout << "The input file wasn't a random or an input grid" << endl;
                exit(1);
            }
        }
    }
    else{
        //Initialize with defaults
        satisfaction_ratio = 0.5;
        rows = 5;
        cols = 5;
        percentX = 0.4;
        percentY = 0.4;
        assert(percentX + percentY >= 0 && percentX + percentY < 1);
        Matrix_init(ptr, rows, cols);
        for(int i = 0; i < rows*cols; i +=1){
            double prob = eecs280_rand_probability();
            if(prob >= 0 && prob <= percentX){
                ptr -> array[i] = 'X';
            }
            else if(prob > percentX && prob <= percentX + percentY)
                ptr -> array[i] = 'O';
            else
                ptr -> array[i] = ' ';
        }
        //Grid is initilized
    }
    //
    //         \/ MAIN LOOP BELOW \/
    //
    cout << "Before:" << endl;
    const Matrix * cptr = ptr;
    Matrix_print(cptr);
    int iterations = 0;
    while(!is_everyone_satisfied(ptr, satisfaction_ratio)){
        int agentrow = eecs280_rand_int(rows);
        int agentcol = eecs280_rand_int(cols);
        while(!is_Agent_satisfied(ptr, agentrow, agentcol, satisfaction_ratio)){
            agentrow = eecs280_rand_int(rows);
            agentcol = eecs280_rand_int(cols);
        }
        int moverow = eecs280_rand_int(rows);
        int movecol = eecs280_rand_int(cols);
        while(!is_that_spot_open(ptr, moverow, movecol)){
            moverow = eecs280_rand_int(rows);
            movecol = eecs280_rand_int(cols);
        }
        int oldspotindex = agentrow*(ptr -> num_rows) + agentcol;
        int newspotindex = moverow*(ptr -> num_rows) + movecol;
        ptr -> array[newspotindex] = ptr -> array[oldspotindex];
        ptr -> array[oldspotindex] = ' ';
        iterations += 1;
        //Update debug output here, not totally sure what that is yet
    }
    const Matrix * eptr = ptr;
    cout << "After:" << endl;
    Matrix_print(eptr);
}


bool is_Agent_satisfied(Matrix * ptr, int rowindex, int colindex, double satisfaction_ratio){
    //An element shouldn't have more than 8 neighbors, size of 10 just in case I guess
    char dest[10];
    const Matrix * cptr = ptr;
    int ten = 10;
    int * intptr = &ten;
    Matrix_range_radius(cptr, rowindex, colindex, 1, dest, intptr);
    int numX = 0;
    int numO = 0;
    int total = 0;
    int i = 0;
    while(dest[i] == 'X' || dest[i] == 'O' || dest[i] == ' '){
        if(dest[i] == 'X'){
            numX += 1;
            total += 1;
        }
        if(dest[i] == 'O'){
            numO += 1;
            total +=1;
        }
        i += 1;
    }
    char * agent = Matrix_at(ptr, rowindex, colindex);
    double ratio;
    if(*agent == 'X'){
        ratio = numX / total;
    }
    if(*agent == 'O'){
        ratio = numO / total;
    }
    if(ratio >= satisfaction_ratio)
        return true;
    else
        return false;
}

bool is_everyone_satisfied(Matrix * ptr, double satisfaction_ratio){
    for(int i = 0; i < (ptr -> num_rows); i +=1){
        for(int j = 0; j < (ptr -> num_columns); i +=1){
            if(!is_Agent_satisfied(ptr, i, j, satisfaction_ratio))
                return false;
        }
    }
    return true;
}

bool is_that_spot_open(Matrix * ptr, int rowindex, int colindex){
    int elenum = rowindex*(ptr -> num_columns) + colindex;
    if(ptr -> array[elenum] == ' ')
        return true;
    else
        return false;
}
