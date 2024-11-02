#include <iostream>
#include <vector>
#include <random>
#include <omp.h>

template<typename T>
class Matrix {
protected:
    std::vector<T> data;
    int m;
    int n;

public:
    Matrix(int M, int N) : m(M), n(N) {
        this->data.resize(m * n);  // Resize the data vector to hold m*n elements
    }

    std::vector<T> get_data() {
        return this->data;
    } 

    int get_M() {
        return this->m;
    }

    int get_N() {
        return this->n;
    }

    void set_data(std::vector<T> Data) {
        for (int i = 0; i <m*n; i++) {
            this->data[i] = Data[i];
        } 
    }

    void print_matrix() {
        for (int i = 0; i < this->data.size(); i++) {        
            std::cout << this->data[i] << " ";
            if (i % n == (n - 1)) {
                std::cout << "\n";
            } 
        }
    }

    void fill_random() {
        int lower_bound = 1;
        int upper_bound = 100;

        // Create a random device and generator for each thread
        std::random_device rd;
        
        #pragma omp parallel
        {
            std::mt19937 gen(rd());  // Local generator for each thread
            std::uniform_int_distribution<T> dist(lower_bound, upper_bound);

            // Fill the matrix in parallel
            #pragma omp for
            for (int i = 0; i < m * n; i++) {
                this->data[i] = dist(gen);  // Directly assign to data
            }
        }
    }
};