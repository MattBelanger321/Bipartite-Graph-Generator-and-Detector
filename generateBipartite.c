#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//This program generates the adjacency matrix for a simple graph
int main(int argc, char *argv[]){
	int order;	//the Order of the graph that will be outputted
	srand(time(NULL));   // Initialization, should only be called once.
	
	
	if(argc != 2){
		printf("NOT ENOUGH/TOO MANY ARGUMENTS\nUSAGE: <program> <Vertex set size (int)>\n");
		exit(-2);
	}else{
		order = atoi(*(argv+1));
		if(order == 0){
			printf("Bad Argument given, Please enter a Non-Zero positive integer\nUSAGE: <program> <Vertex set size (int)>\n");
			exit(-1);
		}
	}
	
	int adjMat[order][order];
	
	for(int i = 0; i <order; i++){
		for(int j = 0; j<order; j++){
			adjMat[i][j] = 0;
		}
	}
	
	for(int i = 0; i < order; i++){	//build spanning tree
		if(i*2+1 >= order){
			break;
		}
		
		if(i*2+2 >= order){
			adjMat[i][i*2 + 1] = 1;
			adjMat[i*2 + 1][i] = 1;
			break;
		}
		
		adjMat[i][i*2 + 1] = 1;
		adjMat[i][i*2 + 2] = 1;
		adjMat[i*2 + 1][i] = 1;
		adjMat[i*2 + 2][i] = 1;
	}
	
	int logi;
	int logj;	//holds log base 2
	
	for(int i = 0; i <order; i++){	//add back edges such that no odd cycles are formed
		for(int j = i; j<order; j++){
			if(i==j){
				adjMat[i][j] = 0;	//no self loops
			}else if(adjMat[i][j] == 0){
				logi = (int)(log((double)(i+1))/log(2.0));	//calculate depths
				logj = (int)(log((double)(j+1))/log(2.0));
				
				if(logi %2 != logj%2){	// adding edge would create no odd cycle
					adjMat[i][j] = rand() % 2;	//random chance of adding an edge here
					adjMat[j][i] = adjMat[i][j];
				}
			}
		}
	}
	
	for(int i = 0; i <order; i++){
		for(int j = 0; j<order; j++){
			printf("%d",adjMat[i][j]);
		}
		printf("\n");
	}

}