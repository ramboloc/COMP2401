#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// The images stored externally in images.c, along with their names, rows and columns
extern char 				**images[];
extern char 				 *names[];
extern unsigned short rows[];
extern unsigned short cols[];
extern unsigned char  numImages;


// This main function simply goes through the images and encodes them with three encoding techniques
int main() {
	for (int i=0; i<numImages; i++) {
		printf("Image: %s\n", names[i]);
		//printf("     Basic Byte Encoding Bytes Required = %d\n", basicByteEncode(images[i], rows[i], cols[i]));
		//printf("     Bit Encoding Bytes Required = %d\n", bitEncode(images[i], rows[i], cols[i]));
		//printf("     Row Run-Length Encoding Bytes Required = %d\n", rowRunLengthEncode(images[i], rows[i], cols[i]));
		//printf("     Variable Run-Length Encoding Bytes Required = %d\n\n", variableRunLengthEncode(images[i], rows[i], cols[i]));
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













 
