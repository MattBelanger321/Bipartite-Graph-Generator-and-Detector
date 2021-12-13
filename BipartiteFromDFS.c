#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INPUT "graph5.txt"

const int MAX = 1425;

//this algorithm is based on the following theorem
//a graph is bipartite iff it contains no edge is incident on two vertices whose depths are congruent modulo 2
//where the depth is defined by distance from the root of in the dfs tree
int dfsRun(int adjMat[][MAX], int order, int vertex, int visited[], int depth){
	visited[vertex] = depth;
	for(int i = 0; i<order;i++){
		if(adjMat[vertex][i] && !visited[i]){	//if vertex is adjacent to i and i has not been visited
			if(!dfsRun(adjMat, order, i, visited, depth+1)){	//recursive call
				return 0;
			}
		}else if(adjMat[vertex][i]){ //else edge(vertex,i) is a back edge
			if(visited[vertex] %2 == visited[i]%2){	//an odd cycle is found return false
				return 0;
			}
		}
	}
	return 1;
}

int dfs(int adjMat[][MAX], int order){
	
	int visited[order];	//0 if vertex hasnt been visited, otherwise visited[i] is the depth of vertex i
	for(int i = 0; i<order;i++){
		visited[i] = 0;
	}
	
	for(int i = 0; i<order;i++){
		if(!visited[i]){
			if(!dfsRun(adjMat,order,i,visited,1)){
				return 0;
			}
		}
	}
	
	return 1;

}

int main(){
	FILE* input = fopen(INPUT,"r");
	
	if(!input){
		printf("COULD NOT OPEN %s\n",INPUT);
		exit(0);
	}
	
	int adjMat[MAX][MAX];
	int i = 0;
	int j = 0;
	int order;
	int c;
	
	while(!feof(input)){
		if( (c = fgetc(input)) == '\n'){
			j++;
			order = i;
			i = 0;
		}else{
			adjMat[i][j] = c - '0';
			i++;
		}
	}
	
	for(int i = 0; i < order; i++){
		for(int j = 0; j < order; j++){
			printf("%d",adjMat[i][j]);
		}
		printf("\n");
	}
	
	fclose(input);
	clock_t begin = clock();
	printf("The graph is%sbipartite\n",dfs(adjMat, order)?" ":" not ");
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Runtime: %fms\n", time_spent);
}