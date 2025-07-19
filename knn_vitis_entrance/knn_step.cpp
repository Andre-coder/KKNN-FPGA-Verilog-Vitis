// Designer: Mariano Viegas Andre
// Implemanted date: 2025
// Vitis Entrance


#include <iostream>
#include <vector>
#include "knn.h"
using namespace std;


int main() {
    #pragma HLS DATAFLOW
    // Example Training Data (Features + Class Labels)
    vector<DataPoint> trainingData = {
        {{5.1, 3.5, 1.4, 0.2}, 0},  // Iris setosa
        {{4.9, 3.0, 1.4, 0.2}, 0},
        {{6.2, 2.8, 4.8, 1.8}, 1},  // Iris versicolor
        {{6.0, 2.7, 5.1, 1.6}, 1},
        {{6.3, 3.3, 6.0, 2.5}, 2},  // Iris virginica
        {{5.8, 2.7, 5.1, 1.9}, 2}
    };
    
    // Test Point
    vector<double> testPoint = {5.7, 2.8, 4.1, 1.3};
    
    // K value (number of neighbors to consider)
    int k = 3;
    
    // Classify the test point
    int predictedClass = knnClassify(trainingData, testPoint, k);
    
    // Output results
    cout << "Test Point Features: ";
    for (double val : testPoint) {
        std::cout << val << " ";
    }
    cout << "\nPredicted Class: " << predictedClass << endl;
    
    // Show class meanings
    cout << "\nClass Meanings:\n";
    cout << "0 - Iris setosa\n";
    cout << "1 - Iris versicolor\n";
    cout << "2 - Iris virginica\n";
    
    return 0;
}