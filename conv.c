#include <stdio.h>
#include <stdlib.h>

void conv2d(
    const float* input,
    const float* kernel,
    float* output, 
    int input_height,
    int input_width,
    int kernel_height,
    int kernel_width,
    int input_channels,
    int output_channels,
    int kernel_size,
    int stride,
    int pad_size
){
    int output_height = (input_height - kernel_height + 2 * pad_size) / stride + 1;
    int output_width = (input_width - kernel_width + 2 * pad_size) / stride + 1;

    int padded_height = input_height + 2 * pad_size;
    int padded_width = input_width + 2 * pad_size;
    float* padded_input = (float*)calloc(padded_height * padded_width * input_channels, sizeof(float)); // Calloc input (padded image, size of padded image)

    //Apply padding 
    for (int c = 0; c < input_channels; c++){
        for (int i = 0; i < input_height; i++){
            for (int j = 0; j < input_width; j++){
                padded_input[((i + pad_size) * padded_width + (j + pad_size)) * input_channels + c] = 
                input[(i * input_width + j) * input_channels + c];
            }
        }
    }

    //perform convolution
    for (int oc = 0; oc<output_channels; oc++){
        for (int oh = 0; oh < output_height; oh++){
            for (int ow = 0; ow < output_width; ow++){
                float sum = 0.0f;

                //Convolution at each position
                for (int ic = 0; ic < input_channels; ic++){
                    for (int kh = 0; kh < kernel_height; kh++){
                        for (int kw = 0; kw < kernel_width; kw++){
                            int input_h_offset = oh * stride + kh;
                            int input_w_offset = ow * stride + kw;

                            sum += padded_input[(input_h_offset * padded_width + input_w_offset) * input_channels + ic] *
                            kernel[((oc * input_channels + ic) * kernel_size + kh) * kernel_size + kw];
                        }
                    }
                }
                output[(oh * output_width + ow) * output_channels + oc] = sum;
            }
        }
    }

    free(padded_input);

}