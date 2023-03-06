#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

unsigned int basicByteEncode(char *imageArray[], unsigned short numLines, unsigned short lineLength);
void basicByteDecode(unsigned short numLines,unsigned short lineLength);
unsigned int bitEncode(char *imageArray[], unsigned short numLines, unsigned short lineLength);
void bitDecode(unsigned short numLines,unsigned short lineLength);
unsigned int rowRunLengthEncode(char *imageArray[], unsigned short numLines, unsigned short lineLength);
void rowRunLengthDecode(unsigned short numLines,unsigned short lineLength);
unsigned int variableRunLengthEncode(char *imageArray[], unsigned short numLines, unsigned short lineLength);
void variableRunLengthDecode(unsigned short numLines,unsigned short lineLength);
// The images stored externally in images.c, along with their names, rows and columns
extern char 				**images[];
extern char 				 *names[];
extern unsigned short rows[];
extern unsigned short cols[];
extern unsigned char  numImages;

int *result;
int result_len;



// This main function simply goes through the images and encodes them with three encoding techniques
int main() {
	for (int i=0; i<numImages; i++) {
		printf("Image: %s\n", names[i]);
		printf("     Basic Byte Encoding Bytes Required = %d\n", basicByteEncode(images[i], rows[i], cols[i]));
		printf("     Bit Encoding Bytes Required = %d\n", bitEncode(images[i], rows[i], cols[i]));
		printf("     Row Run-Length Encoding Bytes Required = %d\n", rowRunLengthEncode(images[i], rows[i], cols[i]));
		printf("     Variable Run-Length Encoding Bytes Required = %d\n\n", variableRunLengthEncode(images[i], rows[i], cols[i]));
	}

	// Display the basic byte decodings for all images
	/*for (int i=0; i<numImages; i++) {
	  printf("-----------------------------------------------------------------------------\n");
	  basicByteEncode(images[i], rows[i], cols[i]);
	  basicByteDecode(rows[i], cols[i]);
	}*/
	
	/*// Display the basic bit decodings for all images
	for (int i=0; i<numImages; i++) {
	  printf("-----------------------------------------------------------------------------\n");
	  bitEncode(images[i], rows[i], cols[i]);
	  bitDecode(rows[i], cols[i]);
	}*/
	
	// Display the row run-length decodings for all images
	/*for (int i=0; i<numImages; i++) {
	  printf("-----------------------------------------------------------------------------\n");
	  rowRunLengthEncode(images[i], rows[i], cols[i]);
	  rowRunLengthDecode(rows[i], cols[i]);
	}*/
	
	// Display the variable run-length decodings for all images
	/*for (int i=0; i<numImages; i++) {
	  printf("-----------------------------------------------------------------------------\n");
	  variableRunLengthEncode(images[i], rows[i], cols[i]);
	  variableRunLengthDecode(rows[i], cols[i]);
	}*/
}




//-----------------------------------------------------------------------
unsigned int basicByteEncode(char *imageArray[], unsigned short numLines, unsigned short lineLength){
	unsigned int bite_count=numLines*lineLength;
	free(result);

	result=(int *)malloc(bite_count *sizeof(int));
	for(int row=0;row<numLines;row++){
		for (int col=0; col<lineLength; col++) {
			result[row*lineLength+col]=imageArray[row][col]-'0';
		}
	}
	result_len=bite_count;
	return bite_count;
}

void basicByteDecode(unsigned short numLines,unsigned short lineLength){
	unsigned int bite_count=numLines*lineLength;
	int sum=0;
	for(int i=0;i<bite_count;i++){
		
		if(i%lineLength==0) printf("\n");
		if(result[i]==1){
			printf("*");
		}else {
			printf(" ");
		}
	}
	printf("\n");
	
}
unsigned int bitEncode(char *imageArray[], unsigned short numLines, unsigned short lineLength){
	
	unsigned int bite_count=ceil(numLines*lineLength/8.0);
	free(result);
	result=(int *)malloc(bite_count *sizeof(int));
	//printf("速出%zu\n",strlen(result));
	int bit_num=8;
	int num=0;
	for(int row=0;row<numLines;row++){
		for (int col=0; col<lineLength; col++) {
			bit_num--;
			num+=(imageArray[row][col]-'0')*pow(2,bit_num);
			if (bit_num==0) {
				result[(row*lineLength+col)/8]=num;

				num=0;
				bit_num=8;
			}
		}

	}
	if(bit_num<8){
		//printf("num=%d\n",num);
		result[bite_count-1]=num;
	}
	result_len=bite_count;
	return bite_count;
}
void bitDecode(unsigned short numLines,unsigned short lineLength){
	// bite_count is the length of array result
	int bite_count=ceil(numLines*lineLength/8.0);
	int sum=0;
	int cur;
	int arr[8];
	// Convert decimal number to binary number
	for(int i=0;i<bite_count-1;i++){
		// Covert byte to bit then printf
		cur=result[i];
		for(int j=7;j>=0;j--){
			arr[j]=cur/pow(2, j);
			cur-=arr[j]*pow(2, j);
		}
		for(int j=7;j>=0;j--){
			if(sum%lineLength==0) printf("\n");
			if(arr[j]==1){
				printf("*");
			}else {
				printf(" ");
			}
			sum++;
		}	
	}
	cur=result[bite_count-1];
	for(int j=7;j>=0;j--){
		arr[j]=cur/pow(2, j);
		cur-=arr[j]*pow(2, j);
	}

	for(int j=7;sum<numLines*lineLength;j--){
		if(sum%lineLength==0) printf("\n");
		if(arr[j]==1){
			printf("*");
		}else {
			printf(" ");
		}
		sum++;
	}

}

unsigned int rowRunLengthEncode(char *imageArray[], unsigned short numLines, unsigned short lineLength){

	free(result);
	result=(int *)malloc(sizeof(int));
	unsigned int bite_count=1;
	int num=0;
	int flag=1;
	for(int row=0;row<numLines;row++){
		if(num>0){
			result[bite_count-1]=num;
			num=0;
			// apply for a space
			result=(int *)realloc(result, sizeof(int)*(bite_count+1));
			// array length add 1
			bite_count++;
		}
		if((imageArray[row][0]-'0')==1){
			num++;
			flag=1;
		}else {
			result[bite_count-1]=0;
			// apply for a space
			result=(int *)realloc(result, sizeof(int)*(bite_count+1));
			// array length add 1
			bite_count++;
			// indicates that the current number is 1
			num++;
			flag=0;
		}
		for (int col=1; col<lineLength; col++) {
			
			if((imageArray[row][col]-'0')==flag){
				num++;
				if(num>255){
					num%=255;
					result[bite_count-1]=255;
					result=(int *)realloc(result, sizeof(int)*(bite_count+2));
					bite_count+=2;
					result[bite_count-2]=0;
				}
			}else {
				result[bite_count-1]=num;
				num=1;
				result=(int *)realloc(result, sizeof(int)*(bite_count+1));
				bite_count++;
				if(flag==0){
					flag=1;
				}else {
					flag=0;
				}
			}
		}

	}
	if(num>0){
		result[bite_count-1]=num;
	}

	result_len=bite_count;
	return bite_count;

}

void rowRunLengthDecode(unsigned short numLines,unsigned short lineLength){
	
	int char_count=0;
	int flag=1;
	// Convert decimal number to binary number
	if(result[0]==0) flag=0;
	
	/*for(int i=0;i<result_len-1;i++){
		printf("%d\n",result[i]);
	}*/
	for(int i=0;i<result_len;i++){
		
		char_count+=result[i];
		//if(result[i]==255) continue;
		
		for(int j=0;j<result[i];j++){
			
			if (flag==0) {
				printf(" ");
				//char_count++;
			}else {
				
				printf("*");
				//char_count++;
			}
			
		}
		
		// Convert the character type of the next output
		if(flag==0){
			flag=1;
		}else {
			flag=0;
		}
		
		if(char_count%lineLength==0 && result[i]!=0 && char_count!=0) {
			printf("\n");
			flag=1;
		}
		
	}
	printf("\n");
	

}

unsigned int variableRunLengthEncode(char *imageArray[], unsigned short numLines, unsigned short lineLength){

	free(result);
	result=(int *)malloc(sizeof(int));
	unsigned int bite_count=1;
	int num=0;
	int flag=1;
	for(int row=0;row<numLines;row++){
		
		for (int col=0; col<lineLength; col++) {
			
			if((imageArray[row][col]-'0')==flag){
				num++;
				if(num>255){
					num%=255;
					result[bite_count-1]=255;
					result=(int *)realloc(result, sizeof(int)*(bite_count+2));
					bite_count+=2;
					result[bite_count-2]=0;
				}
			}else {
				result[bite_count-1]=num;
				num=1;
				result=(int *)realloc(result, sizeof(int)*(bite_count+1));
				bite_count++;
				if(flag==0){
					flag=1;
				}else {
					flag=0;
				}
			}
		}

	}
	if(num>0){
		result[bite_count-1]=num;
	}
	/*for(int i=0;i<bite_count-1;i++){
		printf("%d\n",result[i]);
	}
	printf("length=%d\n",bite_count);*/
	result_len=bite_count;
	return bite_count;

}

void variableRunLengthDecode(unsigned short numLines,unsigned short lineLength){
	
	int char_count=0;
	int flag=1;
	
	for(int i=0;i<result_len;i++){
		
		//char_count+=result[i];
		//if(result[i]==255) continue;
		
		for(int j=0;j<result[i];j++){
			// Line break required internally
			if(char_count%lineLength==0) {
				printf("\n");
				//flag=1;
			}
			if (flag==0) {
				printf(" ");
				char_count++;
			}else {
				
				printf("*");
				char_count++;
			}
			
		}
		// Convert the character type of the next output
		if(flag==0){
			flag=1;
		}else {
			flag=0;
		}
		
		
		
	}
	printf("\n");
	

}










 
