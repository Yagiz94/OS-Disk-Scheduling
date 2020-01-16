#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

#define REQUEST_SIZE 1000
#define CYLINDER_SIZE 5000
#define RUN_SIZE  100

void printStatistics(char* name, int *movementArray){
	int i = 0;
	double mean = 0;
	for(i = 0; i < RUN_SIZE; i++)
		mean += movementArray[i];
	mean /= RUN_SIZE;

	double variance = 0;
	for(i = 0; i < RUN_SIZE; i++){
		double difference = (movementArray[i] - mean);
		variance += difference * difference;
	}
	variance/= (RUN_SIZE-1);
	variance = sqrt(variance);
	printf("%s :\t\t%.3f\t%.3f\n",name,mean,variance );
}

int* cloneBlockNumbers(int* blockNumbers){
	int* tempBlockNumbers = malloc(REQUEST_SIZE*sizeof(int));
	for(int i = 0; i < REQUEST_SIZE; i++){
		tempBlockNumbers[i] = blockNumbers[i];
	}
	return tempBlockNumbers;
}

int  FCFS(int* blockNumbers, int n){
	int block = n,movement = 0;
	for(int i = 0; i < REQUEST_SIZE; i++){
		movement += abs(blockNumbers[i]-block);
		block = blockNumbers[i];
	}
    return movement;
}


int SSTF (int* blockNumbers, int n){
	int block = n,movement = 0;

	int* tempBlockNumbers = cloneBlockNumbers(blockNumbers);
    int totalNumber = REQUEST_SIZE;


    while(totalNumber > 0){
		int minMovement = 50000;
		int minIndex = -1;
        for(int i = 0; i < totalNumber; i++){
            int currentMovement = abs(tempBlockNumbers[i] - block);
            if(currentMovement < minMovement){
                minMovement = currentMovement;
                minIndex = i;
            }
        }
        totalNumber--;
        movement += minMovement;
        block = tempBlockNumbers[minIndex];
        tempBlockNumbers[minIndex] = tempBlockNumbers[totalNumber];
    }
    return movement;
}


int SCAN (int* blockNumbers, int n){
	int block = n,movement = 0;

	int* tempBlockNumbers = cloneBlockNumbers(blockNumbers);
    int totalNumber = REQUEST_SIZE;

	//go right until reach the 4999
	for(int i = block; i < CYLINDER_SIZE && totalNumber > 0; i++){
        for(int j = 0; j < totalNumber; j++){
			if(tempBlockNumbers[j] == i){
				totalNumber--;
				tempBlockNumbers[j] = tempBlockNumbers[totalNumber];
				j--;
			}
        }
		movement+=i-block;
		block = i;
	}

	//go back to left
	for(int i = CYLINDER_SIZE-1; i >= 0 && totalNumber > 0; i--){
        for(int j = 0; j < totalNumber; j++){
			if(tempBlockNumbers[j] == i){
				totalNumber--;
				tempBlockNumbers[j] = tempBlockNumbers[totalNumber];
				j--;
			}
        }
		movement+=block-i;
		block = i;
	}
    return movement;
}


int CSCAN (int* blockNumbers, int n){
	int block = n,movement = 0;

	int* tempBlockNumbers = cloneBlockNumbers(blockNumbers);
    int totalNumber = REQUEST_SIZE;

	//go right until reach the 4999
	for(int i = block; i < CYLINDER_SIZE && totalNumber > 0; i++){
        for(int j = 0; j < totalNumber; j++){
			if(tempBlockNumbers[j] == i){
				totalNumber--;
				tempBlockNumbers[j] = tempBlockNumbers[totalNumber];
				j--;
			}
        }
		movement+=i-block;
		block = i;
	}

	//go back to start
	if(totalNumber > 0){
		movement+= block;
		block = 0;
	}

	
	for(int i = block; i < CYLINDER_SIZE && totalNumber > 0; i++){
        for(int j = 0; j < totalNumber; j++){
			if(tempBlockNumbers[j] == i){
				totalNumber--;
				tempBlockNumbers[j] = tempBlockNumbers[totalNumber];
				j--;
			}
        }
		movement+=i-block;
		block = i;
	}
    return movement;
}




int LOOK (int* blockNumbers,int n ){
	int block = n,movement = 0;

	int* tempBlockNumbers = cloneBlockNumbers(blockNumbers);
    int totalNumber = REQUEST_SIZE;

	//go right until reach the 4999
	for(int i = block; i < CYLINDER_SIZE && totalNumber > 0; i++){
		int isRightRemaining = 0;
        for(int j = 0; j < totalNumber; j++){
			if(tempBlockNumbers[j] >= i){
				isRightRemaining = 1;
			}
        }
		if(!isRightRemaining){
			break;
		}
        for(int j = 0; j < totalNumber; j++){
			if(tempBlockNumbers[j] == i){
				totalNumber--;
				tempBlockNumbers[j] = tempBlockNumbers[totalNumber];
				j--;
			}
        }
		movement+=i-block;
		block = i;
	}

	//go back to left
	for(int i = CYLINDER_SIZE-1; i >= 0 && totalNumber > 0; i--){
		int isLeftRemaining = 0;
        for(int j = 0; j < totalNumber; j++){
			if(tempBlockNumbers[j] <= i){
				isLeftRemaining = 1;
			}
        }
		if(!isLeftRemaining){
			break;
		}

        for(int j = 0; j < totalNumber; j++){
			if(tempBlockNumbers[j] == i){
				totalNumber--;
				tempBlockNumbers[j] = tempBlockNumbers[totalNumber];
				j--;
			}
        }
		movement+=block-i;
		block = i;
	}
    return movement;
}


int CLOOK (int* blockNumbers,int n ){
	int block = n,movement = 0;

	int* tempBlockNumbers = cloneBlockNumbers(blockNumbers);
    int totalNumber = REQUEST_SIZE;

	//go right until reach the 4999
	for(int i = block; i < CYLINDER_SIZE && totalNumber > 0; i++){
		int isRightRemaining = 0;
        for(int j = 0; j < totalNumber; j++){
			if(tempBlockNumbers[j] >= i){
				isRightRemaining = 1;
			}
        }
		if(!isRightRemaining){
			break;
		}

        for(int j = 0; j < totalNumber; j++){
			if(tempBlockNumbers[j] == i){
				totalNumber--;
				tempBlockNumbers[j] = tempBlockNumbers[totalNumber];
				j--;
			}
        }
		movement+=i-block;
		block = i;
	}

	//go back to start
	if(totalNumber > 0){
		int minLeftBlock = CYLINDER_SIZE;
        for(int j = 0; j < totalNumber; j++){
			if(tempBlockNumbers[j] <= minLeftBlock){
				minLeftBlock = tempBlockNumbers[j];
			}
        }
		movement+= block-minLeftBlock;
		block = minLeftBlock;
	}

	
	for(int i = block; i < CYLINDER_SIZE && totalNumber > 0; i++){
		int isRightRemaining = 0;
        for(int j = 0; j < totalNumber; j++){
			if(tempBlockNumbers[j] >= i){
				isRightRemaining = 1;
			}
        }
		if(!isRightRemaining){
			break;
		}
        for(int j = 0; j < totalNumber; j++){
			if(tempBlockNumbers[j] == i){
				totalNumber--;
				tempBlockNumbers[j] = tempBlockNumbers[totalNumber];
				j--;
			}
        }
		movement+=i-block;
		block = i;
	}
    return movement;
}


int main(int argc , char *argv[])
{
	if(argc == 1){
		//test mode
		int FCFSMovements[RUN_SIZE];
		int SSTFMovements[RUN_SIZE];
		int SCANMovements[RUN_SIZE];
		int CSCANMovements[RUN_SIZE];
		int LOOKMovements[RUN_SIZE];
		int CLOOKMovements[RUN_SIZE];
		srand (time(NULL));
		for(int i = 0;i < RUN_SIZE; i++){
			int n = rand() % CYLINDER_SIZE;
			int blockNumbers[REQUEST_SIZE];
			for(int j = 0; j < REQUEST_SIZE; j++){
				blockNumbers[j] = rand() % CYLINDER_SIZE;
			}

			FCFSMovements[i] = FCFS(blockNumbers,n);
			SSTFMovements[i] = SSTF(blockNumbers,n);

			SCANMovements[i] = SCAN(blockNumbers,n);
			CSCANMovements[i] = CSCAN(blockNumbers,n);

			LOOKMovements[i] = LOOK(blockNumbers,n);
			CLOOKMovements[i] = CLOOK(blockNumbers,n);
		}
	printf("Algorithm \tMean\t\tVariance\n");
	printStatistics("FCFS",FCFSMovements);

	printStatistics("SSTF",SSTFMovements);

	printStatistics("SCAN",SCANMovements);
	printStatistics("CSCAN",CSCANMovements);

	printStatistics("LOOK",LOOKMovements);
	printStatistics("CLOOK",CLOOKMovements);

	}else if(argc == 2){
		//random numbers
		int n = atoi(argv[1]);
		int blockNumbers[REQUEST_SIZE];

        srand (time(NULL));
        for(int i = 0; i < REQUEST_SIZE; i++){
            blockNumbers[i] = rand() % 5000;
        }
	
    	printf("FCFS : %d\n", FCFS(blockNumbers,n));
    	printf("SSTF : %d\n", SSTF(blockNumbers,n));

    	printf("SCAN : %d\n", SCAN(blockNumbers,n));
    	printf("CSCAN : %d\n", CSCAN(blockNumbers,n));

    	printf("LOOK : %d\n", LOOK(blockNumbers,n));
    	printf("CLOOK : %d\n", CLOOK(blockNumbers,n));
	}else{
		//read file
		int n = atoi(argv[1]);
		char line[1024];
		int blockNumbers[REQUEST_SIZE];

		FILE *file = fopen(argv[2],"r");

		int i=0;
		//get arrive time and block values
		char * pch;
		while (fgets ( line, sizeof line, file ) != NULL && i < REQUEST_SIZE){
			pch = strtok (line, " ");
			atoi(pch);//request number
			pch = strtok (NULL, " ");
			int block = atoi(pch);
			blockNumbers[i++] = block;
		}
		fclose(file);
	
    	printf("FCFS : %d\n", FCFS(blockNumbers,n));
    	printf("SSTF : %d\n", SSTF(blockNumbers,n));

    	printf("SCAN : %d\n", SCAN(blockNumbers,n));
    	printf("CSCAN : %d\n", CSCAN(blockNumbers,n));

    	printf("LOOK : %d\n", LOOK(blockNumbers,n));
    	printf("CLOOK : %d\n", CLOOK(blockNumbers,n));
	}
	return 0;
}
