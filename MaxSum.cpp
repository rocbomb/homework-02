#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define FIE "Input string was not in a correct format"
FILE* in;
int matrix[100][100] = {0};

void error(char* s){
	printf("Error: ");
	printf("%s\n",s);
	
	exit(0);
}

int maxNum1(int m,int n){
	int pre[100][100] = {0};
	int sum = 0,max = 0;
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			pre[i][j]=pre[i-1][j]+pre[i][j-1]-pre[i-1][j-1]+matrix[i-1][j-1];
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
			pre[i][j] = pre[i][j-1] + matrix[i-1][j-1];
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
int getNum(){
	char num[15],input;
	int i=0,n;
	input = fgetc(in);
	while(!isdigit(input) && input != '-' )
		if(input != ' ' && input != '\n' &&
			input != NULL && input != ',' &&
			input != '\0')
			error(FIE);

	do{
		num[i++] = input;
		input = fgetc(in);
	}while(isdigit(input));

	num[i] = '\0';
	n = atoi(num);

	return n;
}



int main(){

	int m,n;
	char input,num[10];

    if((in = fopen("input.txt", "r")) == NULL)
        error("File can not open");
	
	m = getNum();
	if(fgetc(in)!= '\n')
		error(FIE);
	n = getNum();
	if(fgetc(in)!= '\n')
		error(FIE);

	printf("%d,%d",m,n);

	for(int i=0; i<m; i++){
		for(int j=0; j<n; j++){
			matrix[i][j] = getNum();
			std::cout<<" "<<matrix[i][j];
		}
	}

	std::cout<<std::endl<<maxNum2(m,n);



	return 0;
}
