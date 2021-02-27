# Steganography Using C
Image Steganography In C.

Steganography Is The Process To Hide Text Files In A Image Without Altering The Original Image.

This Code Is Designed To Hide/Retrieve Text Files From BMP Format Images.

# Files

    Steganography.c - Functions Prototype And The Main Function
    Decode.c        - Decoding Function.
    Encode.c        - Encoding Function.

# For Execution of the Program, Follow the Steps:

    ~$ cc Steganography.c -o Stegano

# Encoding

    ~$ ./Stegano -E -i input_image.bmp -s secret_text.txt -o output_image.bmp

input_image.bmp - Initial image  
secret_text.txt - Text to Encrypt in input_image.bmp  
output_image.bmp - Final Image after Encryption  

# Decoding

    ~$ ./Stegano -D -i output_image.bmp -o out_text.txt

output_image.bmp - Image with Embedded Text  
out_text.txt     - Text retrieved.

# Index
    -E - Encoding
    -D - Decoding
    -i - Input Source BMP Image
    -s - Secret Text file
    -o - Output Image / Output Text
