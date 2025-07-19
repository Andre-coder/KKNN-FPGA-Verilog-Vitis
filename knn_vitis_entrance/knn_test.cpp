// Designer: Mariano Viegas Andre
// Implemanted date: 2025
// Vitis Entrance

#include <iostream>
#include <hls_stream.h>
#include <ap_axi_sdata.h>
#include "knn_axis.h"

#define NUM_FEATURES 4
#define NUM_TRAINING 6
#define K 3

typedef ap_axiu<32, 0, 0, 0> AXI_VALUE;

using namespace std;

int main() {
    hls::stream<AXI_VALUE> training_features_in;
    hls::stream<AXI_VALUE> training_labels_in;
    hls::stream<AXI_VALUE> test_features_in;
    hls::stream<AXI_VALUE> predicted_label_out;

    // Define training data
    float training_data[NUM_TRAINING][NUM_FEATURES] = {
        {5.1, 3.5, 1.4, 0.2},  // class 0
        {4.9, 3.0, 1.4, 0.2},  // class 0
        {6.2, 2.8, 4.8, 1.8},  // class 1
        {6.0, 2.7, 5.1, 1.6},  // class 1
        {6.3, 3.3, 6.0, 2.5},  // class 2
        {5.8, 2.7, 5.1, 1.9}   // class 2
    };

    int labels[NUM_TRAINING] = {0, 0, 1, 1, 2, 2};

    float test_point[NUM_FEATURES] = {5.7, 2.8, 4.1, 1.3}; 

    // Send training data
    for (int i = 0; i < NUM_TRAINING; ++i) {
        for (int j = 0; j < NUM_FEATURES; ++j) {
            AXI_VALUE val;
            // reinterpret float as int
			
			val.data = *((int*)&training_data[i][j]);
            val.last = 0;
            training_features_in.write(val);
        }
        AXI_VALUE label_val;
        label_val.data = labels[i];
        label_val.keep = -1;
        label_val.last = 0;
        training_labels_in.write(label_val);
    }

    // Send test point
    for (int j = 0; j < NUM_FEATURES; ++j) {
        AXI_VALUE val;
        val.data = *((int*)&test_point[j]);
        val.keep = -1;
        // last = 1 on final feature
		
		val.last = (j == NUM_FEATURES - 1); 
        test_features_in.write(val);
    }

    // Call the function
    knn_axis(training_features_in, training_labels_in, test_features_in, predicted_label_out);

    // Get predicted label
    AXI_VALUE out_val = predicted_label_out.read();
    int predicted_class = out_val.data;

    // Print results
    cout << "Predicted Class: " << predicted_class << endl;
    cout << "Class Legend:\n  0 = Iris-setosa\n  1 = Iris-versicolor\n  2 = Iris-virginica\n";

    return 0;
}
