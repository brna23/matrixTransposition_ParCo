#include <iostream>
#include <vector>
#include <ctime>
#include <omp.h>
#include <fstream> // For file operations
#include <iomanip> // For setting precision

//checkSym serial
bool checkSym(std::vector<std::vector<float>>& A, int N){
   int count = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (A[i][j] != A[j][i])
                count += 1;
        }
    }

    return (N*N)==count;
}
float generateRandomNumber(float min = 0.0, float max = 1.0) {
    // Generate a random float between min and max
    float random = static_cast<float>(rand()) / RAND_MAX; // Random float between 0.0 and 1.0
    return min + random * (max - min);
}

//serial transposition
std::vector<std::vector<float>> matTranspose(std::vector<std::vector<float>>& A, int N){
    std::vector<std::vector<float>> T(N, std::vector<float>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            T[j][i] = A[i][j];
        }
    }
    return T;
}

int main(int argc, char *argv[]){ 
    srand(time(NULL));
    double repeat = 10;
    double sum = 0.0;
    std::ofstream file("output.csv", std::ios::app);
    //file << "Matrix_Size,Number_of_threads,Execution_time" << std::endl;
    
    int N = atoi(argv[1]);
    //create matrix A with vector
    std::vector<std::vector<float>> A(N, std::vector<float>(N));

    // Initialize matrix A
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            A[i][j] = generateRandomNumber(0.0, 500.0);
        }
    }
    
    double startOMP;
    double endOMP;
    double durationOMP;

    //loop for more results
    for(int i=0; i<repeat; i++){
        //Serial matrix transposition
        startOMP = omp_get_wtime();
        if(!checkSym(A, N)){
            std::vector<std::vector<float>> T = matTranspose(A, N);
        }
        endOMP = omp_get_wtime();
        durationOMP = endOMP - startOMP;
        //std::cout << "Duration: " << durationOMP << " s" << std::endl;
        file << N << "," << 1 << "," << durationOMP << std::endl;
        sum += durationOMP;
    }
    std::cout << "Avarage Duration Serial ("<<N<<"): " << sum/repeat << " s" << std::endl;
     
    return 0;
}