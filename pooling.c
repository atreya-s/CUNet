#include <stdio.h>
#include <stdlib.h>
#include <float.h>


// UNet implements MaxPool2d
float MaxPool(
    const float* input,
    int input_height,
    int input_width,
    int kernel_height,
    int kernel_width,
    int pad_size,
    int stride,
    int dilation,
    float* output
) {

    int output_height = (input_height - kernel_height + 2 * pad_size) / stride + 1;
    int output_width = (input_width - kernel_width + 2 * pad_size) / stride + 1;

    for (int oh = 0; oh < output_height; oh++) {
        for (int ow = 0; ow < output_width; ow++) {
            float max_val = -FLT_MAX; 

            // Iterating over kernel window
            for (int kh = 0; kh < kernel_height; kh++) {
                for (int kw = 0; kw < kernel_width; kw++) {
                    // Calculate input position with stride and dilation
                    int ih = oh * stride + kh * dilation - pad_size;
                    int iw = ow * stride + kw * dilation - pad_size;

                    // Check if we're inside input bounds
                    if (ih >= 0 && ih < input_height && iw >= 0 && iw < input_width) {
                        float val = input[ih * input_width + iw];
                        max_val = (val > max_val) ? val : max_val;
                    }
                }
            }

            
            output[oh * output_width + ow] = max_val;
        }
    }

    return 1.0f; 
}
// I'm just doing AvgPool just to see how good my understanding is 
float AvgPool(
    const float* input,
    int input_height,
    int input_width,
    int kernel_height,
    int kernel_width,
    int pad_size,
    int stride,
    int dilation,
    float* output
){
    int output_height = (input_height - kernel_height + 2 * pad_size) / stride + 1;
    int output_width = (input_width - kernel_width + 2 * pad_size) / stride + 1;

    for (int oh = 0; oh < output_height; oh++) {
        for (int ow = 0; ow < output_width; ow++) {
            float sum = 0.0f;
            int count = 0;
            // Iterating over kernel window
            for (int kh = 0; kh < kernel_height; kh++) {
                for (int kw = 0; kw < kernel_width; kw++) {
                    // Calculate input position with stride and dilation
                    int ih = oh * stride + kh * dilation - pad_size;
                    int iw = ow * stride + kw * dilation - pad_size;

                    // Check if we're inside input bounds
                    if (ih >= 0 && ih < input_height && iw >= 0 && iw < input_width) {
                        sum = input[ih * input_width + iw];
                        count ++;
                    }
                }
            }
            output[oh * output_width + ow] = count > 0 ? sum/count : 0.0f;
            
        }
    }

    return 1.0f; 
}