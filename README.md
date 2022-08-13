# Error Diffusion Dithering
Dithering is a technique used to simulate more colors in fewer number of bits, by spreading different colors with different densities to achieve a desired color when the image gets displayed.

This is a small project to experiment the difference between pure quantization and error diffusion dithering (floyd-stienberg dithering in particular).


Original (8-bit RGB) vs. Quantized (1-bit RGB) vs. Dithered (1-bit RGB):
![1bit result](/results/result_1b.jpeg)


Original (8-bit RGB) vs. Quantized (2-bit RGB) vs. Dithered (2-bit RGB):
![2bit result](/results/result_2b.jpeg)


Original (8-bit RGB) vs. Quantized (4-bit RGB) vs. Dithered (4-bit RGB):
![4bit result](/results/result_4b.jpeg)