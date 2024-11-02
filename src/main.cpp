#include "../lib/matrix_multiply.cpp"
int main(){
    Matrix<int> A(4,3);
    A.fill_random();
    A.print_matrix();
    Matrix<int> B(3,4);
    B.fill_random();
    B.print_matrix();
    Matrix_Multiplier matrix_multiplier(A,B);
    matrix_multiplier.duplyA();
    matrix_multiplier.printDuplyA();
    matrix_multiplier.duplyB();
    matrix_multiplier.printDuplyB();
    matrix_multiplier.printSizes();
    Matrix<int> C(4,4);
    C.set_data(matrix_multiplier.actual_multiply());
    C.print_matrix(); 
} 