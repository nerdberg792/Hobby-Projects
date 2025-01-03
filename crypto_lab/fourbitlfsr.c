#include<stdio.h> 
#include<stdlib.h> 
int lfsr(int state){
	int feedback = (state & 1)^(state & 10) ; 
	int next_state = (state>>1)|(feedback<<3) ; 
	return next_state ; 

}
int main( int argc , char* argv[]){
	int seed = 0x12 ; 

	printf("Initial State : %x \n" , seed ) ; 
	for(int i = 0 ; i < 16 ; i++){
		seed = lfsr(seed) ;
		printf("Next State is : %x \n" , seed) ; 

	}

	return 0 ; 

}
