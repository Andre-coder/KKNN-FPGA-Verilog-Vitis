#include <hls_stream.h>
#include <ap_axi_sdata.h>

#define NUM_FEATURES 4
#define NUM_TRAINING 6
#define K 3

typedef ap_axiu<32, 0, 0, 0> AXI_VALUE;  // 32-bit AXIS data (float or int)

