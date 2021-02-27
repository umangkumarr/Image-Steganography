#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Encode.c"
#include "Decode.c"

//functions prototypes
int size_of_image(FILE *fp1);
void secret_text(FILE *fp2);
int secret_text_size(FILE *fp2);
int get_bit(char byte, int bit);
void stega_encrypt(FILE *fp1, FILE *fp2, FILE *fp3);
void string_encrypt(char *str,FILE *fp1, FILE *fp3);
void size_encrypt(int num,FILE *fp1, FILE *fp3);
void size_decryption(FILE *pf1, int *size_txt);
void string_decryption(FILE *pf1,char *strng,int size);
void secret_decryption(int size_txt,FILE *pf1, FILE *pf2);

int main(int argc,char *argv[])
{
    int i;
    printf("**** Welcome to the Steganography tool ****\n");
    char *argv_2,*argv_3,*argv_4;
    switch(argc)
    {
			//Comparing For 
	case 8 : if(!strcmp(argv[1],"-E"))
			{
			    for (i = 2; i < 8; i++){
				if (!strcmp(argv[i],"-i")) argv_2 = argv[i+1];
				if (!strcmp(argv[i],"-s")) argv_3 = argv[i+1];
				if (!strcmp(argv[i],"-o")) argv_4 = argv[i+1];
			    }			    
			    Encoding(argv_2, argv_3, argv_4);
			    break;
			}
	case 6 : if(!strcmp(argv[1], "-D"))
			{
			    for (i = 2; i < 6; i++){
				if (!strcmp(argv[i],"-i")) argv_2 = argv[i+1];
				if (!strcmp(argv[i],"-o")) argv_4 = argv[i+1];
			    }			    
			    Decode(argv_2, argv_4);
			    break;
			}
	default : 
		printf("\n!! Error !! ERROR !! Error !!\n\n");
		printf("EXECUTION:");
		printf("\n\tENCODING: \t./Stegano -E -i <input.bmp> -s <secret.txt> -o <output.bmp>\n");
		printf("\tDECODING:\t./Stegano -D -i <output.bmp> -o <output_text.txt>\n");
		printf("\tFOR MORE DETAILS: README\n");
    }	
    return 0;
}
