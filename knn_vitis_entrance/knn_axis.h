#include "knn.h"
#include <cmath>
#include <algorithm>
#include <map>

void knn_axis(
    hls::stream<AXI_VALUE>& training_features_in,
    hls::stream<AXI_VALUE>& training_labels_in,
    hls::stream<AXI_VALUE>& test_features_in,
    hls::stream<AXI_VALUE>& predicted_label_out
) {
    float training_features[NUM_TRAINING][NUM_FEATURES];
    int training_labels[NUM_TRAINING];
    float test_features[NUM_FEATURES];

    #pragma HLS INTERFACE axis port=training_features_in
    #pragma HLS INTERFACE axis port=training_labels_in
    #pragma HLS INTERFACE axis port=test_features_in
    #pragma HLS INTERFACE axis port=predicted_label_out
    #pragma HLS INTERFACE ap_ctrl_none port=return
    #pragma HLS PIPELINE II=1

    // Read training data
    for (int i = 0; i < NUM_TRAINING; ++i) {
        for (int j = 0; j < NUM_FEATURES; ++j) {
            AXI_VALUE val = training_features_in.read();
            training_features[i][j] = *((float*)&val.data);
        }
        AXI_VALUE label = training_labels_in.read();
        training_labels[i] = label.data;
    }

    // Read test point
    for (int i = 0; i < NUM_FEATURES; ++i) {
        AXI_VALUE val = test_features_in.read();
        test_features[i] = *((float*)&val.data);
    }

    // Distance computation and vote
    float distances[NUM_TRAINING];
    int vote_count[3] = {0};

    for (int i = 0; i < NUM_TRAINING; ++i) {
        double dist = 0;
        for (int j = 0; j < NUM_FEATURES; ++j) {
            double diff = pow(training_features[i][j] - test_features[j],2);
            dist += diff * diff;
        }
        distances[i] = sqrt(dist);
    }

    // KNN (k = 3)
    for (int k_idx = 0; k_idx < K; ++k_idx) {
        int min_idx = -1;
        float min_dist = 1e9;
        for (int i = 0; i < NUM_TRAINING; ++i) {
            if (distances[i] < min_dist) {
                min_dist = distances[i];
                min_idx = i;
            }
        }
        vote_count[training_labels[min_idx]]++;
        distances[min_idx] = 1e9; // so it won't be picked again
    }

    // Determine majority vote
    int predicted_label = 0;
    int max_vote = vote_count[0];
    for (int i = 1; i < 3; ++i) {
        if (vote_count[i] > max_vote) {
            max_vote = vote_count[i];
            predicted_label = i;
        }
    }

    // Write output
    AXI_VALUE out_val;
    out_val.data = predicted_label;
    out_val.keep = -1;
    out_val.last = 1;
    predicted_label_out.write(out_val);
}
