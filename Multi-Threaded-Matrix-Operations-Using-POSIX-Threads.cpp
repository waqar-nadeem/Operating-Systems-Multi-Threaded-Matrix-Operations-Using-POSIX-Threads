#include <iostream>
#include <pthread.h>
#include <vector>
#define MAX 3
int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
void* addMatrix(void* arg) {
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    std::cout << "Matrix Addition Result:" << std::endl;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            std::cout << C[i][j] << " ";
        }
        std::cout << std::endl;
    }
    return nullptr;
}
void* subtractMatrix(void* arg) {
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    std::cout << "Matrix Subtraction Result:" << std::endl;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            std::cout << C[i][j] << " ";
        }
        std::cout << std::endl;
    }
    return nullptr;
}
void* multiplyMatrix(void* arg) {
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            C[i][j] = 0;
            for (int k = 0; k < MAX; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    std::cout << "Matrix Multiplication Result:" << std::endl;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            std::cout << C[i][j] << " ";
        }
        std::cout << std::endl;
    }
    return nullptr;
}
int main() {
    std::cout << "Enter elements of matrix A:" << std::endl;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            std::cin >> A[i][j];
        }
    }
    std::cout << "Enter elements of matrix B:" << std::endl;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            std::cin >> B[i][j];
        }
    }
    pthread_t addThread, subtractThread, multiplyThread;
    int result;
    result = pthread_create(&addThread, nullptr, addMatrix, nullptr);
    if (result != 0) {
        std::cerr << "Error creating addition thread!" << std::endl;
        return -1;
    }
    result = pthread_create(&subtractThread, nullptr, subtractMatrix, nullptr);
    if (result != 0) {
        std::cerr << "Error creating subtraction thread!" << std::endl;
        return -1;
    }
    result = pthread_create(&multiplyThread, nullptr, multiplyMatrix, nullptr);
    if (result != 0) {
        std::cerr << "Error creating multiplication thread!" << std::endl;
        return -1;
    }
    pthread_join(addThread, nullptr);
    pthread_join(subtractThread, nullptr);
    pthread_join(multiplyThread, nullptr);
    return 0;
}
