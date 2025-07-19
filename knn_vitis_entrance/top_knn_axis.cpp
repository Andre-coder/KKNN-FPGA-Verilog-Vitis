// Designer: Mariano Viegas Andre
// Implemanted date: 2025
// Vitis Entrance


#include "knn_axis.h"
#include <hls_stream.h>
#include <ap_axi_sdata.h>

typedef ap_axiu<32, 0, 0, 0> AXI_VALUE;

// This is the top-level function for synthesis
void top_knn_axis(
    hls::stream<AXI_VALUE>& training_features_in,
    hls::stream<AXI_VALUE>& training_labels_in,
    hls::stream<AXI_VALUE>& test_features_in,
    hls::stream<AXI_VALUE>& predicted_label_out
) {
    #pragma HLS INTERFACE axis port=training_features_in
    #pragma HLS INTERFACE axis port=training_labels_in
    #pragma HLS INTERFACE axis port=test_features_in
    #pragma HLS INTERFACE axis port=predicted_label_out
    #pragma HLS INTERFACE ap_ctrl_none port=return

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

    // Call the real implementation
    knn_axis(training_features_in, training_labels_in, test_features_in, predicted_label_out);
}