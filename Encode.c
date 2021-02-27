#include<unistd.h>
#include<stdio.h>
//reading size of image file
int size_of_image(FILE *fp1)
{
	int width, height;
	fseek(fp1, 0x12, SEEK_SET);	//Seek to the Width position
	fread(&width, sizeof(int), 1, fp1);	//Reading Width
	fread(&height, sizeof(int), 1, fp1);	//Read height
	printf("\nDimensions of the Image is %d x %d \n", width, height);
	fseek(fp1, 0L, SEEK_SET);	//Seek to the start position
	return ((width * height * 3) / 8);
}
//Size Of The Secret Message
int secret_text_size(FILE *fp2)
{
	int size_txt;
	fseek(fp2, 0L, SEEK_END);
	size_txt = ftell(fp2);
	fseek(fp2, 0L, SEEK_SET);
	return size_txt;
}
//bits of text file
int get_bit(char byte, int bit)
{
	return ((byte >> (8 - bit)) & 1);
}
//encription of message
void stega_encrypt(FILE *fp1, FILE *fp2, FILE *fp3)
{
	char file_buff = 0, msg_buff = 0, ch;	//temp var for one byte from file and msg
	int i;
	int bit_msg;
	while((msg_buff = fgetc(fp2)) != EOF)
	{
		for(i = 1; i <= 8; i++)
		{
			file_buff = fgetc(fp1);
			int file_byte_lsb = (file_buff & 1);
			bit_msg = get_bit(msg_buff, i);
			if(file_byte_lsb == bit_msg){fputc(file_buff, fp3);}
			else
			{
				if(file_byte_lsb == 0){file_buff = (file_buff | 1);}
				else{file_buff = (file_buff ^ 1);}
				fputc(file_buff, fp3);
			}
		}
	}
	/*copying rest of data */
	while(!feof(fp1))
	{
		char tmp_cpy = fgetc(fp1);
		fputc(tmp_cpy,fp3);
	}
	if(msg_buff == EOF)
		printf("*** Message Encrypted Successfully ***\n");
	else
		printf("*** Failed Encrypting ***\n");
}
//Encription For Strings
void string_encrypt(char *str,FILE *fp1, FILE *fp3)
{

	char file_buff, msg_buff;	//temp var for one byte from file and msg
	int i, j = 0;
	int bit_msg;
	while((msg_buff = str[j]) != '\0')
	{
		for(i = 1; i <= 8; i++)
		{
			file_buff = fgetc(fp1);
			int file_byte_lsb = (file_buff & 1);
			bit_msg = get_bit(msg_buff, i);
			if(file_byte_lsb == bit_msg){fputc(file_buff, fp3);}
			else
			{
				if(file_byte_lsb == 0){file_buff = (file_buff | 1);}
				else{file_buff = (file_buff ^ 1);}
				fputc(file_buff, fp3);
			}
		}j++;
	}
}
//Encription For Numbers
void size_encrypt(int num,FILE *fp1, FILE *fp3)
{
	char file_buff;	
	int i, j = 0;
	int bit_msg;
	for(i = 1; i <= 8; i++)
	{
		file_buff = fgetc(fp1);
		int file_byte_lsb = (file_buff & 1);
		bit_msg = get_bit(num, i);
		if(file_byte_lsb == bit_msg){fputc(file_buff, fp3);}
		else
		{
			if(file_byte_lsb == 0) file_buff = (file_buff | 1);
			else file_buff = (file_buff ^ 1);
			fputc(file_buff, fp3);
		}
	}
}
int Encoding(char *argv_2,char *argv_3,char *argv_4)
{
	FILE *fp1, *fp2, *fp3;
	//opening Image File
	if((fp1 = fopen(argv_2, "r+")) == NULL) 
	{
		printf("Could not open file %s.\nAborting\n", argv_2);
		return 1;
	}
	int size_image = size_of_image(fp1);
	printf("Total %d Characters can be stored in %s.\n", size_image, argv_2);
	//opening secret text file
	fp2 = fopen(argv_3, "r");
	if(fp2==NULL)
	{
		printf("Could not open file %s.\nAborting\n",argv_3);
		return 0;
	}
    printf("Reading Message... from %s\n",argv_3);
    sleep(1);
	int size_txt = secret_text_size(fp2);
	printf("Size of The Secret Message is: %d\n", size_txt);
	//Comparing Image Size With Text
	if(size_image < size_txt)
	{
		printf("*** The Size Of Message Exceeds the Size of image ***\n");
		return 1;
	}

	//opening destination file
	fp3 = fopen(argv_4, "w+");
	if (fp3== NULL) 
	{
		fprintf(stderr, "Cannot create output file %s\n",argv_4);
		exit(1);
	}
	//copying 54 header file
	int i, c = 0;
	char tmp_cpy;
	rewind(fp1);	//Goes back to the beginning of the file
	for(i = 0;i < 54; i++)
	{
		tmp_cpy = fgetc(fp1);
		fputc(tmp_cpy,fp3);
		c++;
	}
    fflush(stdin); //clearing input stream

	//FOR PASSWORD
	char str[100];
	printf("Enter the password: ");
    for (i=0;((str[i] = getchar()) != '\n');i++);
	str[i]= '\0';
	int size1 = strlen(str);
	printf("Size Of The Password is: %d\n", size1);
	size_encrypt(size1,fp1,fp3);
	string_encrypt(str,fp1,fp3);
	printf("*** Password Encrypted ***\n");
	//Encryption for Message
	size_encrypt(size_txt,fp1,fp3);
	stega_encrypt(fp1,fp2,fp3);
    printf("Steg Image is saved as: %s\n",argv_4);
	fclose(fp1);	
	fclose(fp2);
	fclose(fp3);
	return 0;
}