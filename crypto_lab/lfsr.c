#include<stdio.h>
#include<stdlib.h> 
void display_binary(int n){
	for(int i = 3 ; i >= 0 ; i--){
		printf("%d" , (n>>i)&1 ) ; 
	}	
	printf("   ") ; 
	return ; 
}
int main(int argc , char* argv[]){
	int seed = atoi(argv[1]) ;
        printf("%d\n" , seed ) ; 	
	for(int i = 0 ; i < 16 ; i++){
	int third = (seed&0b0100)>0?1:0 ; 
	int output = (seed&0b1000)>0?1:0 ; 
		int new = third^output ; 
		int disp = (seed<<1)&(0b1111) ; 
		seed = disp+new ; 
		printf("%d th output is %d : ", i , seed ) ; 
		display_binary(seed) ; 
		printf("\n") ; 
	}
	return 0 ; 
}




	

		

