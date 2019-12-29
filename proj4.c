#include <stdio.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <stdlib.h>

/*
 Function to find the differences in bytes
 between two files. The first FILE 
 in the parameter list is the file used 
 to compare to the second FILE parameter.
 If a difference in bytes is found,
 the byte is written to the third FILE
 parameter.
 */
void step1(FILE *, FILE *, FILE *);

/*
 Reads the first 2 files in the parameter list into two dynamically allocated arrays,
 and writes any byte from the second FILE parameter that is not equal to the corresponding
 byte in the first FILE parameter to a third array.
 The third array is written to the third FILE parameter.
*/
void step2(FILE *, FILE *, FILE *);

/*
 Uses the file input as a parameter and finds how many
 bytes the file is in size and returns it as an integer.
*/
int fileLength(FILE*);

/*
 Fills an array with every byte from a given input file.
 Takes every byte from the file input as a parameter
 and fills the char array input as a parameter. This function
 also takes an int as a parameter to make the array the exact 
 size.
*/
void fillArray(FILE*, char*, int);

/*
  Fills an array with the different bytes found from two given
  input files. 
*/
void fillDiffArr(int, char*, char*, char*);

void step1(FILE * f1, FILE * f2, FILE * f3){
    struct timeval start, end;
    gettimeofday(&start, NULL);//get time at start of process
    char val1;
    char val2;
    while (fread(&val1, sizeof(char), 1, f1) == 1){
        fread(&val2, sizeof(char), 1, f2);
        if (val1 != val2){//check if the byte equals the byte from the other file
            fwrite(&val1, 1, sizeof(char), f3);//writing difference to new file
        }//if
    }//while
    gettimeofday(&end, NULL);//get time after process is over
    printf("Step 1 took %lf milliseconds\n", ((double)((end.tv_usec - start.tv_usec))/1000));
}//stepOne

void step2(FILE* inputFile1, FILE* inputFile2, FILE * outputFile2){
  struct timeval start,end;
  gettimeofday(&start, NULL);
  
  char * ptr1, * ptr2, * ptr3;
  int fileLength1 = fileLength(inputFile1);
  int fileLength2 = fileLength(inputFile2);
  int fileLength3 = 0;

  ptr1 = (char*) malloc(fileLength1);
  ptr2 = (char*) malloc(fileLength2);
  fillArray(inputFile1, ptr1, fileLength1);
  fillArray(inputFile2, ptr2, fileLength2);
  for (int i = 0; i < fileLength2; i++){ // finds the number of differences
    if (*(ptr2 + i) != *(ptr1 + i)){
      fileLength3++;
    }//if
  }//for
  ptr3 = (char*) malloc(fileLength3);
  fillDiffArr(fileLength2, ptr1, ptr2, ptr3);
  fputs(ptr3, outputFile2);

  free(ptr1);
  free(ptr2);
  free(ptr3);

  gettimeofday(&end, NULL);
  printf("Step 2 took %lf milliseconds\n", ((double)((end.tv_usec - start.tv_usec))/1000));
}//step2

int fileLength(FILE* inputFile){
  char c;
  int fileLength = 0;
  while((c = fgetc(inputFile) != EOF)) fileLength++;
  rewind(inputFile);
  return fileLength;
}//fileLength

void fillArray(FILE* inputFile, char* ptr, int fileLength){
  for (int i = 0; i < fileLength; i++){
    *(ptr + i) = fgetc(inputFile);
  }//for
}//fillArray

void fillDiffArr(int fileLength2, char* ptr1, char* ptr2, char * ptr3){
  int j = 0;
  for (int i = 0; i < fileLength2; i++){
    if (*(ptr2 + i) != *(ptr1 + i)){
      *(ptr3 + j) = *(ptr2 + i);
      j++;
    }//if
  }//for
}//fillDiffArr

/*
 Main function used to find the difference in bytes
 between files. Checks for valid input and calls
 two other functions to find the different bytes
 in the files input as command line arguments.
 */
int main(int argc, char ** argv){
    if(argc < 3){
        printf("Usage: proj4.out <file1> <file2>\n");
        return 0;
    }//if
    else{
        FILE * file1 = fopen(argv[1], "r");
        FILE * file2 = fopen(argv[2], "r");
        FILE * file3 = fopen("differencesFoundInFile1.txt", "w");
        FILE * file4 = fopen("differencesFoundInFile2.txt", "w");
        if (file1 == NULL || file2 == NULL){
            printf("There was an error reading a file.\n");
            return 0;
        }//if
        step1(file1, file2, file3);
        rewind(file1);
        rewind(file2);
        step2(file1, file2, file4);

        fclose(file1);
        fclose(file2);
        fclose(file3);
        fclose(file4);
        return 1;
    }//else
}//main
