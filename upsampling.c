#include <stdio.h>
#include <stdlib.h>
#include <float.h>

float* upsample(
    const float* input,
    int input_height,
    int input_width
){
    int output_height = input_height * 2;
    int output_width = input_width * 2;
    
    // Allocates memory (malloc) for the output matrix - I keep forgetting to allocate memeory for the output matrix
    float *output = (float*)malloc(output_height * output_width * sizeof(float));
    
    for(int i = 0; i < input_height; i++){
        for(int j = 0; j < input_width; j++){
            int input_idx = i * input_width + j;
            float value = input[input_idx];
            
            int out_i = i * 2;
            int out_j = j * 2;
            output[out_i * output_width + out_j] = value; 
            output[out_i * output_width + out_j + 1] = value;
            output[(out_i + 1) * output_width + out_j] = value;
            output[(out_i + 1) * output_width + out_j + 1] = value;
        }
    }
    return output;
}

void print_array(float* arr, int height, int width) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%.1f ", arr[i * width + j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    int input_height = 2;
    int input_width = 2;
    float input[] = {1.0, 2.0, 
                     3.0, 4.0};
    
    printf("Input array:\n");
    print_array(input, input_height, input_width);
    
    float* output = upsample(input, input_height, input_width);
    printf("Upsampled array:\n");
    print_array(output, input_height*2, input_width*2);
    
    free(output);
    return 0;
}
