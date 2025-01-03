#include<stdio.h> 
#include<stdlib.h> 
#include<fcntl.h> 
#include<unistd.h>
#include<string.h>
#include<stdint.h>

void get_random_bytes(unsigned char *buffer , size_t size){
	int fd = open("/dev/urandom" , O_RDONLY) ; 
	if(fd<0){
		perror("Failed to open urandom " ) ; 
	        exit(EXIT_FAILURE) ; 
	}
	if(read(fd , buffer , size) != size ) {
		perror("Failed to open /dev/urandom") ; 
		exit(EXIT_FAILURE) ; 
	}
	if(read(fd , buffer , size) != size) {
		perror("Failed to read random bytes") ; 
		close(fd) ; 
		exit(EXIT_FAILURE) ; 
	}
	close(fd) ; 
}
void prf(const unsigned char *key , size_t key_len , const unsigned char *message , size_t message_len , unsigned char *output , size_t output_len){
	uint32_t state = (uint32_t)key_len*31 +(uint32_t)message_len*17 ; 
	for(size_t i = 0 ; i <key_len ; i++){
		state ^= (uint32_t)key[i] << (i%8) ; 
		state = (state*33)^(state>>16) ; 
	}
	for(size_t i = 0 ; i<message_len ; i++){
		state ^= (uint32_t)message[i] ^ (state>>16) ; 
		state = (state*33) ^ (state>>16) ; 
	}
	for(size_t i = 0 ; i <output_len ; i++){
		state = (state*1103415245 + 12345)&0x7FFFFFFF ; 
		output[i] = (unsigned char)(state & 0xFF) ; 
	}

}
int main(int argc , char** argv){
	unsigned char key[16] ; 
	unsigned char prf_output[32] ; 
	const char *message = argv[1] ; 
	get_random_bytes(key , sizeof(key) ) ; 
	prf(key , sizeof(key) , (const unsigned char *)message , strlen(message) , prf_output , sizeof(prf_output) ) ; 
	printf("PRF output : ") ; 
	for(size_t i = 0 ; i <sizeof(prf_output) ; i++) {
		printf("%02x" , prf_output[i]) ; 
	}
	printf("\n") ; 
	return 0 ; 
}

		
