#include "data_process.h"
#include "sensor_io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/*
 
The main of the program 
We need to pass 2 command line arguments: 
Arugment 1: Complete File Path of the input containing raw sensor data. 
Argument 2: Complete File Path of the output file which will be generated by the program.
Error-handling is built in so that program terminates gracefully. 
 
**/

int main(int argc, char* argv[])
{
    char* inputFileName;
    char* outputFileName;
    
    char* dataArray;
    long dataArrayLen;

    uint16_t* sensorDataArray;      /* Array where each element holds a 12-bit number 
                                    representing sensor data in the order in which it is read */

    uint16_t* sensorDataArraySorted; // sorted copy of sensorDataArray

    long sensorDataArrayLen;  /* Total number of sensor data elements */

    long sensorDataArraySortedLen; /* Total number of sensor data elements in sorted list */


    const char* header1 = "--Sorted Max 32 Values--";
    const char* header2 = "--Last 32 Values--";

    
    printf("\n ******************** Sensor Read & Process ********************\n");
    if(argc != 3)
    {
        printf("\nIncorrect arguments passed !!\nCorrect Format is: client.exe "
               "<InputFile Name With Path> <OutputFile Name With Path>\n");

        printf("\n ************************************************************\n");
        exit(0);
    }

    inputFileName = argv[1];
    outputFileName = argv[2];

    sensorReadFromFile(inputFileName, &dataArray, &dataArrayLen);

    sensorExtract12BitValues(dataArray, dataArrayLen, &sensorDataArray, &sensorDataArrayLen);

    sensorSortAscending(sensorDataArray, sensorDataArrayLen, &sensorDataArraySorted, &sensorDataArraySortedLen);

    sensorWriteIntoFile(outputFileName, sensorDataArraySorted, sensorDataArraySortedLen, header1);

    sensorAppendIntoFile(outputFileName, sensorDataArray, sensorDataArrayLen, header2);

    printf("\n\n OutputFile Written Successfully \n");
    printf("\n ************************************************************\n");

    
    free(dataArray);
    free(sensorDataArray);
    free(sensorDataArraySorted);
    
    return 0;
}
