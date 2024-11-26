#include <iostream>
#include <vector>
#include <ctime>
#include <omp.h>
#include <fstream> // For file operations
#include <iomanip> // For setting precision

//checkSym parrallel   
bool checkSymOMP(std::vector<std::vector<float>>& A, int N, int numT){
    int count = 0;
    omp_set_num_threads(numT);

    #pragma omp parallel for collapse(2) reduction(+:count)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (A[i][j] != A[j][i])
                count += 1;
        }
    }

    return (N*N)==count;
}

//OMP transposition
std::vector<std::vector<float>> matTransposeOMP(std::vector<std::vector<float>>& A, int N, int numT){
    std::vector<std::vector<float>> T(N, std::vector<float>(N));
    omp_set_num_threads(numT);
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            T[j][i] = A[i][j];
        }
    }
    return T;
}
float generateRandomNumber(float min = 0.0, float max = 1.0) {
    // Generate a random float between min and max
    float random = static_cast<float>(rand()) / RAND_MAX; // Random float between 0.0 and 1.0
    return min + random * (max - min);
}

int main(int argc, char *argv[]){ 
    srand(time(NULL));
    double repeat = 10;
    double sum = 0.0;
    std::ofstream file("output.csv", std::ios::app);
    
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

    int th[6] = {2,4,8,16,32,64};
    int numT = 0;
    for(int j=0; j<6; j++){
        numT = th[j];
        sum = 0;
        for(int i=0; i<repeat; i++){
            //Parallelised matrix transposition
            startOMP = omp_get_wtime();
            if(!checkSymOMP(A, N, numT)){
                std::vector<std::vector<float>> T = matTransposeOMP(A, N, numT);
            }
            endOMP = omp_get_wtime();
            durationOMP = endOMP - startOMP;
            //std::cout << "Duration with omp: " << durationOMP << " s -" << " with numT: " << numT << std::endl;
            file << N << "," << numT << "," << durationOMP << std::endl;
            sum += durationOMP;
        }
    double exeOmp = sum/repeat;
    std::cout << "Avarage Duration with omp ("<<N<<"): " << exeOmp << " s -" << " with numT: " << numT << std::endl;
    }       
    std::cout<<std::endl;
    return 0;
}