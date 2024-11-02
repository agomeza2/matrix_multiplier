#include "matrix_class.cpp"
#include <iostream>
#include <vector>
#include <cstdlib> // for exit()
#include <stdexcept> // for std::runtime_error

template <typename T>
class Matrix_Multiplier {
protected:
    Matrix<T> A;
    Matrix<T> B;
    std::vector<T> duply_a;
    std::vector<T> duply_b;
    std::vector<T> result;

public:
    // Constructor to initialize matrices A and B
    Matrix_Multiplier(Matrix<T> AA, Matrix<T> BB) : A(AA), B(BB) {
        if (!check_compability()) { // Check compatibility during initialization
            std::cerr << "Incompatible matrix sizes\n";
            exit(EXIT_FAILURE);
        }
    }

    // Function to check if matrices A and B are compatible for multiplication
    bool check_compability() {
        return A.get_N() == B.get_M(); // B's number of rows must match A's number of columns
    }

    // Duplicate matrix A into duply_a
    void duplyA() {
    int n = this->A.get_N(); // Number of columns
    int m = this->A.get_M(); // Number of rows
    int i = 0; // Index for the current position in the duplicated array
    int repetitions = m; // Number of times to repeat the rows

    while (i < m * repetitions * n) { // Total iterations: m rows, each repeated 3 times with n columns
        // Calculate the current row and column based on i
        int row = (i / (repetitions * n)); // Get the current row
        int rep = (i / n) % repetitions;    // Get the current repetition
        int col = i % n;                    // Get the current column

        // Push the data to duply_a
        this->duply_a.push_back(this->A.get_data()[(row * n) + col]);

        i++; // Move to the next index
    } 
}

    // Print the duplicated matrix A
    void printDuplyA() {
        for (size_t i = 0; i < duply_a.size(); i++) {
            std::cout << duply_a[i] << " ";
        }
        std::cout << std::endl; // Add a newline after printing
    }

   void duplyB() {
    int m = this->B.get_M(); // Number of rows in matrix B
    int n = this->B.get_N(); // Number of columns in matrix B
    int repetitions = n; // Number of times to repeat the sequence
    int total_size = m * n; // Total number of elements in matrix B
    int i = 0; // Index for the resulting vector

    // Calculate the total number of elements to be generated
    int total_repeats = repetitions * n; // Total number of elements to generate in duply_b

    while (i < total_repeats) {
        // For each repetition, loop through the column indices
        for (int j = 0; j < n; j++) {
            // Calculate the index in matrix B based on the current column and the row offset
            for (int k = 0; k < m; k++) {
                this->duply_b.push_back(this->B.get_data()[k * n + j]);
            }
        }
        i += n; // Increment i to proceed to the next repetition
    }
}



void printDuplyB() {
        for (size_t i = 0; i < duply_b.size(); i++) {
            std::cout << duply_b[i] << " ";
        }
        std::cout << std::endl; // Add a newline after printing
    }
void printSizes(){
    std::cout<<"duply_a "<<this->duply_a.size()<<" this is duply_b"<<this->duply_b.size()<<" \n"; 
} 

std::vector<T> actual_multiply(){
    #pragma omp parallel for 
    for(int i=0; i<duply_a.size(); i++){
        result.push_back(duply_a[i]*duply_b[i]);
    } 
    return result;
} 
};
