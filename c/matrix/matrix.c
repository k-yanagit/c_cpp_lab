#include <stdio.h>
#include <stdlib.h>

/** Struct of Matrix **/
typedef struct {
    int rows;
    int columns;
    double** mat_value;  // 2次元配列を表すポインタ
} Matrix;

// Method
// Constructor
Matrix* mat_new(int rows, int columns) {
    Matrix* mat = (Matrix*)malloc(sizeof(Matrix));
    mat->rows = rows;
    mat->columns = columns;

    // loc dynamic memory
    mat->mat_value = (double**)malloc(rows * sizeof(double*));
    for (int i = 0; i < rows; i++) {
        mat->mat_value[i] = (double*)malloc(columns * sizeof(double));
        // init
        for (int j = 0; j < columns; j++) {
            mat->mat_value[i][j] = 0.0;
        }
    }
    return mat;
}

// Set value of Matrix
void mat_value_set(Matrix* self, double* row_values, int row_num) {
    if (row_num < self->rows) {
        for (int i = 0; i < self->columns; i++) {
            self->mat_value[row_num][i] = row_values[i];
        }
    }
}

// Add Matrix
Matrix* mat_add(Matrix* mat_1, Matrix* mat_2){
    Matrix* mat_result;
    for(int i = 0; i < len(mat_1->mat_value[0]); i++){
        for(int j = 0 ; j < len(mat_1->mat_value); j++){
            mat_result->mat_value[i][j] = mat_1->mat_value[i][j] + mat_1->mat_value[i][j];
        }
    }

    return mat_result;

}

// Dot vector


// Mul Matrix
Matrix* mat_mul(Matrix* mat_1, Matrix* mat_2){
    Matrix* mat_result;
    for(int i = 0; i < len(mat_1->mat_value[0]); i++){
        for(int j = 0 ; j < len(mat_1->mat_value[0]); j++){
            mat_result->mat_value[i][j];
        }
    }

    return mat_result;
}

// Print Matrix
void mat_print(Matrix* self) {
    for (int i = 0; i < self->rows; i++) {
        for (int j = 0; j < self->columns; j++) {
            printf("%.3f\t", self->mat_value[i][j]);
        }
        printf("\n");
    }
}

/*** main ***/
int main(){
    Matrix* mat = mat_new(3, 3);

    double row1[] = {1.0, 2.0, 3.0};
    double row2[] = {2.0, 3.0, 4.0};
    double row3[] = {4.0, 5.0, 6.0};
    mat_value_set(mat, row1, 0);
    mat_value_set(mat, row2, 1);
    mat_value_set(mat, row3, 2);

    mat_print(mat);

    // free mat array
    for (int i = 0; i < mat->rows; i++) {
        free(mat->mat_value[i]);
    }
    // free 2d array pointer
    free(mat->mat_value);
    // free struct
    free(mat);

    return 0;
}
