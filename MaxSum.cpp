#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define FIE "Input string was not in a correct format"
FILE* in;
int matrix[100][100] = {0};
int map[100][100] = {0};
int sxbkM[1000][1000] = {-1};

void positiveSub(int m, int n, int label );
inline void error(char* s){
	printf("Error: ");
	printf("%s\n",s);
	exit(0);
}
int maxNum1(int m,int n){
	int pre[100][100] = {0};
	int sum = 0,max = 0;
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			pre[i][j]=pre[i-1][j]+pre[i][j-1]-pre[i-1][j-1]+matrix[i][j];
	printf("\n");
	for(int i=0;i<=m;i++){
		for(int j=0;j<=n;j++)
			std::cout<<pre[i][j]<<" ";
		printf("\n");
	}

	for(int i=1; i<=m; i++)
		for(int j=1;j<=n;j++)
			for(int k=i; k<=m; k++)
				for(int l=j; l<=n; l++){
					sum = pre[k][l] - pre[k][j-1] - pre[i-1][l] + pre[i-1][j-1];
					if(sum > max)
						max = sum;
				}
	return max;
}
int maxNum2(int m,int n){
	int pre[100][100] = {0};
	int sum = 0,max = 0;
	int columnsMax = 0;
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			pre[i][j] = pre[i][j-1] + matrix[i][j];
		printf("\n");

	for(int i=0;i<=m;i++){
		for(int j=0;j<=n;j++)
			std::cout<<pre[i][j]<<" ";
		printf("\n");
	}

	for(int i=1; i<=n; i++)
		for(int j=i;j<=n;j++){
			for(int k=1; k<=m; k++){
		        if(sum<0)
					sum=pre[k][j] - pre[k][i-1];
		        else
					sum+=pre[k][j] - pre[k][i-1];
				if(columnsMax < sum)
					columnsMax = sum;
			}
//			if(columnsMax > max)
//				max = columnsMax;
//			columnsMax = 0;
			sum = 0;
		}

	return columnsMax;
}
//水平
int maxNum4(int m, int n){
	int pre[100][100] = {0};
	int sum = 0,max = 0;
	int columnsMax = 0;
	for(int i=1;i<=m;i++)
		for(int j=1;j<=2*n;j++)
			pre[i][j] = pre[i][j-1] + matrix[i][(j-1)%n +1];

	for(int i=1; i<=n; i++)
		for(int j=i;j<=i+n-1;j++){
			for(int k=1; k<=m; k++){
		        if(sum<0)
					sum=pre[k][j] - pre[k][i-1];
		        else
					sum+=pre[k][j] - pre[k][i-1];
				if(columnsMax < sum)
					columnsMax = sum;
			}
//			if(columnsMax > max)
//				max = columnsMax;
//			columnsMax = 0;
			sum = 0;
		}

	return columnsMax;
}

//竖直环
int maxNum5(int m,int n){
	int pre[100][100] = {0};
	int sum = 0,max = 0;
	int columnsMax = 0;
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			pre[i][j] = pre[i][j-1] + matrix[i][j];

	int x=1;
	for(int i=1; i<=n; i++)
		for(int j=i;j<=n;j++){
			for(int k=1; k <= m*2; k++){
		        if(sum<0 || x >m){
					x=1;
					sum=pre[(k-1)%m + 1][j] - pre[(k-1)%m + 1][i-1];
				}
		        else{
					x++;
					sum+=pre[(k-1)%m + 1][j] - pre[(k-1)%m + 1][i-1];
				}
				if(columnsMax < sum)
					columnsMax = sum;
			}
			sum = 0;
		}

	return columnsMax;
}
//备胎
int maxNum6(int m, int n){
		int pre[100][100] = {0};
	int sum = 0;
	int columnsMax = 0;
	for(int i=1;i<=m;i++)
		for(int j=1;j<=2*n;j++)
			pre[i][j] = pre[i][j-1] + matrix[i][(j-1)%n +1];

	int x=1;
	for(int i=1; i<=n; i++)
		for(int j=i;j<=i+n-1;j++){
			for(int k=1; k <= m*2; k++){
		        if(sum<0 || x >m){
					x=1;
					sum=pre[(k-1)%m + 1][j] - pre[(k-1)%m + 1][i-1];
				}
		        else{
					x++;
					sum+=pre[(k-1)%m + 1][j] - pre[(k-1)%m + 1][i-1];
				}
				if(columnsMax < sum)
					columnsMax = sum;
			}
			sum = 0;
		}

	return columnsMax;
	
}

int getNum(){
	char num[15],input;
	int i=0,n;
	input = fgetc(in);
	while(!isdigit(input) && input != '-' ){
		if(input != ' ' && input != '\n' &&
			input != NULL && input != ',' &&
			input != '\0')
			error(FIE);
		input = fgetc(in);
	}

	do{
		num[i++] = input;
		input = fgetc(in);
	}while(isdigit(input));

	num[i] = '\0';
	n = atoi(num);

	return n;
}
void initialize(int m,int n){
	for(int i=0; i<1000; i++)
		for(int j=0; j<1000; j++)
			sxbkM[i][j] = -1;
	for(int i=1; i<=m; i++){
		for(int j=1; j<=n; j++){
			matrix[i][j] = getNum();
		}
	}
}
int maxNum3(int m, int n){
	return 0;
}
void positiveSub(int i, int j, int label ){
	map[i][j] = label;
	if(matrix[i][j+1] >= 0 && map[i][j+1] ==0)
		positiveSub(i,j+1,label);

	if(matrix[i+1][j] >= 0 && map[i+1][j] ==0)
		positiveSub(i+1,j,label);

	if(matrix[i][j-1] >= 0 && map[i][j-1] ==0)
		positiveSub(i,j-1,label);

	if(matrix[i-1][j] >= 0 && map[i-1][j] ==0)
		positiveSub(i-1,j,label);
}

int main(int argc, char *argv[]){

	int m,n;
	char input,num[10];
	if( argc == 1)
		error("Plese run with the file name");
	else if(argc == 2){
		if((in = fopen(argv[1], "r")) == NULL)
			error("File can not open");
	}
	else if(argc == 3){
		if((in = fopen(argv[2], "r")) == NULL)
			error("File can not open");
	}
	else if(argc == 4){
		if((in = fopen(argv[3], "r")) == NULL)
			error("File can not open");
	}
	else error("Too many parameters");


	m = getNum();
	if(fgetc(in)!= '\n')
		error(FIE);
	n = getNum();
	if(fgetc(in)!= '\n')
		error(FIE);
	initialize(m,n);

	if( argc == 2)
		std::cout<<std::endl<<"子数组: "<< maxNum2(m,n);
	else if( argc == 3){
		if(strcmp(argv[1],"/a") == 0)
			printf("Sorry,I haven't solved the problem.\n");
		else if(strcmp(argv[1],"/h") == 0)
			std::cout<<std::endl<<"水平环: "<< maxNum4(m,n);
		else if(strcmp(argv[1],"/v") == 0)
			std::cout<<std::endl<<"竖直环: "<< maxNum5(m,n);
		else error("Wrong parameter");
	}
	else{
		if((strcmp(argv[1],"/v") == 0 && strcmp(argv[2],"/h") == 0)
			||(strcmp(argv[1],"/h") == 0 && strcmp(argv[2],"/v") == 0) )
				std::cout<<std::endl<<"备胎环: "<< maxNum6(m,n);
		else error("Wrong parameter\n");
	}
	return 0;
}
