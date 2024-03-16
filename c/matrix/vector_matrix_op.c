#include <stdio.h>
#include <stdlib.h>

/************************/
/*** Struct of Vector ***/
/************************/
typedef struct{
    int dim;
    double* com;
} Vector;

// Constructor
Vector* set_vec(int dim){
    Vector* vec = (Vector*)malloc(sizeof(Vector));
    vec->dim = dim;

    vec->com = (double*)malloc(sizeof(double) * vec->dim);

    return vec;
}

// Set of Component
void set_vec_com(Vector* vec, double* com, int len){

    if (vec->dim != len){
        printf("The dimension of the vector and the length of the given array are different.\n");
        exit(0);
    }

    for (int i = 0; i < len; i++) {
        vec->com[i] = com[i];
    }
}

// Add Vector
Vector* add_vec(Vector* vec_1, Vector* vec_2){

    if (vec_1->dim != vec_2->dim){
        printf("The dimensions of the two vectors you are trying to add are different.\n");
        exit(0);
    }

    Vector* vec_add = set_vec(vec_1->dim);


    for(int i = 0; i < vec_1->dim; i++){
        vec_add->com[i] = vec_1->com[i] + vec_2->com[i];
    }

    return vec_add;
}

// Sub Vector
Vector* sub_vec(Vector* vec_1, Vector* vec_2){

    if (vec_1->dim != vec_2->dim){
        printf("The dimensions of the two vectors you are trying to sub are different.\n");
        exit(0);
    }

    Vector* vec_sub = set_vec(vec_1->dim);

    for(int i = 0; i < vec_1->dim; i++){
        vec_sub->com[i] = vec_1->com[i] - vec_2->com[i];
    }

    return vec_sub;
}
// Time Vector
Vector* time_vec(Vector* vec, double times){
    Vector* vec_times = set_vec(vec->dim);

    for(int i = 0; i < vec->dim; i++){
        vec_times->com[i] = vec->com[i] * times;
    }

    return vec_times;
}

// Dot Vector
double dot_vec(Vector* vec_1, Vector* vec_2){

    if (vec_1->dim != vec_2->dim){
        printf("The dimensions of the two vectors you are trying to dot are different.\n");
        exit(0);
    }

    double vec_dot = 0;
    for(int i = 0; i < vec_1->dim; i++){
        vec_dot += vec_1->com[i] * vec_2->com[i];
    }

    return vec_dot;
}

// Print component of Vector
void print_vec(Vector* vec){
    for(int i = 0; i < vec->dim; i++){
        printf("%.3f, ", vec->com[i]);
    }
    printf("\n");
}

void free_vec(Vector* vec){
        free(vec->com);
        free(vec);
}


/************************/
/*** Struct of Matrix ***/
/************************/
typedef struct {
    int rows;
    int columns;
    Vector** value;
} Matrix;

double** convert_2d_to_pointer_array(double* array, int rows, int columns) {

    double** pointer_array = (double**)malloc(rows * sizeof(double*));

    for (int i = 0; i < rows; i++) {
        pointer_array[i] = array + i * columns;
    }

    return pointer_array;
}

// Constructor
Matrix* set_mat(int rows, int columns){

    Matrix* mat = (Matrix*)malloc(sizeof(Matrix));

    mat->rows = rows;
    mat->columns = columns;

    mat->value = (Vector**)malloc(sizeof(Vector) * mat->rows);
    for(int i = 0; i < mat->columns; i++){
            mat->value[i] = set_vec(mat->rows);
    }

    return mat;
}

// Set value of Matrix
void set_mat_value(Matrix* mat, double* value, int rows, int columns){

    if (mat->rows != rows || mat->columns != columns){
        printf("The rows or columns of the matrix and the length of the given values set array are different.\n");
        exit(0);
    }

    double** value_pointer = convert_2d_to_pointer_array(value, rows, columns);

    for(int i = 0; i < mat->rows; i++){
            set_vec_com(mat->value[i], value_pointer[i], mat->columns);
    }

    free(value_pointer);
}

// Add Matrix
Matrix* add_mat(Matrix* mat_1, Matrix* mat_2){

    if (mat_1->rows != mat_2->rows || mat_1->columns != mat_2->columns){
        printf("The rows or columns of the two matrix you are trying to add are different.\n");
        exit(0);
    }

    Matrix* mat_add = set_mat(mat_1->rows, mat_2->columns);
    for(int i = 0; i < mat_1->rows; i++){
        mat_add->value[i] = add_vec(mat_1->value[i], mat_2->value[i]);
    }

    return mat_add;
}

// Sub Matrix
Matrix* sub_mat(Matrix* mat_1, Matrix* mat_2){

    if (mat_1->rows != mat_2->rows || mat_1->columns != mat_2->columns){
        printf("The rows or columns of the two matrix you are trying to sub are different.\n");
        exit(0);
    }

    Matrix* mat_sub = set_mat(mat_1->rows, mat_2->columns);
    for(int i = 0; i < mat_1->rows; i++){
        mat_sub->value[i] = sub_vec(mat_1->value[i], mat_2->value[i]);
    }

    return mat_sub;
}

// Time Matrix
Matrix* time_mat(Matrix* mat, double times){
    Matrix* mat_time = set_mat(mat->rows, mat->columns);

    for(int i = 0; i < mat->rows; i++){
        mat_time->value[i] = time_vec(mat_time->value[i], times);
    }

    return mat_time;
}

//T Matrix
Matrix* t_mat(Matrix* mat){
    Matrix* mat_t = set_mat(mat->columns, mat->rows);
    for(int i = 0; i < mat->rows; i++){
        for(int j =0; j < mat->columns; j++){
            mat_t->value[i]->com[j] = mat->value[j]->com[i];
        }
    }

    return mat_t;
}

// Mul Matrix
Matrix* mul_mat(Matrix* mat_1, Matrix* mat_2){

    if(mat_1->rows != mat_2->columns){
        printf("The rows of front matrix and columns of back matrix you are trying to mul are different.\n");
        exit(0);
    }
    Matrix* mul_mat = set_mat(mat_1->rows, mat_1->rows);
    Matrix* mat_2_t = t_mat(mat_2);

    for(int i = 0; i < mat_1->rows; i++){
            for(int j = 0; j < mat_1->columns; j++){
                mul_mat->value[i]->com[j]= dot_vec(mat_1->value[i], mat_2_t->value[i]);
            }
    }

    return mul_mat;
}

// Print Matrix
void print_mat(Matrix* mat){
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->columns; j++) {
            printf("%.3f\t", mat->value[i]->com[j]);
        }
        printf("\n");
    }
}

void free_mat(Matrix* mat){
    for (int i = 0; i < mat->rows; i++) {
        free_vec(mat->value[i]);
    }

    free(mat->value);
    free(mat);
}

int main(){

    double value_1[][3] = {
        {1.0, 2.0, 2.0},
        {2.0, 3.0, 5.0},
        {3.0, 5.0, 1.0}
    };

    double value_2[][3] = {
        {1.0, 2.0, 2.0},
        {2.0, 3.0, 5.0},
        {3.0, 5.0, 1.0}
    };

    Matrix* mat_1 = set_mat(3, 3);
    Matrix* mat_2 = set_mat(3, 3);
    set_mat_value(mat_1, *value_1, 3, 3);
    set_mat_value(mat_2, *value_2, 3, 3);

    print_mat(add_mat(mat_1, mat_2));

    free_mat(mat_1);
    free_mat(mat_2);

    return 0;
}
