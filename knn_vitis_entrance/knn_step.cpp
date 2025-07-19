// Designer: Mariano Viegas Andre
// Implemanted date: 2025
// Vitis Entrance


#include <iostream>
#include <vector>
#include "knn.h"
using namespace std;


int main() {
    #pragma HLS DATAFLOW
    // Enter your Dataset for Analysis
    vector<DataPoint> trainingData = {
    // Values for your 1th class 1
        {{5.1, 3.5, 1.4, 0.2}, 0}, 
        {{4.9, 3.0, 1.4, 0.2}, 0},
    // Values for your 2th class 2
        {{6.2, 2.8, 4.8, 1.8}, 1},  
        {{6.0, 2.7, 5.1, 1.6}, 1},
    // Values for your 3th class 3 
        {{6.3, 3.3, 6.0, 2.5}, 2}, 
        {{5.8, 2.7, 5.1, 1.9}, 2}
    };
    
    // Test Point
    vector<double> testPoint = {5.7, 2.8, 4.1, 1.3};
    
    // K value 
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

///This study was implemanted testing fall detection systems, Mariano Andre
