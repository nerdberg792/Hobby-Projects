#include<stdlib.h> 
#include<stdio.h> 
#include<string.h> 
#include<time.h> 
void generate_key(char* key , int length){
	for(int i = 0 ; i < length ; i++){
		key[i] = rand()%256 ; //generate random bytes from 0-255//
	}
}
void otp_encrypt_decrypt(char* ip , char* op , char* key , int length ){
	for(int i = 0 ; i < length ; i++){
		op[i] = ip[i]^key[i] ; 
	}
}
int main(){
	srand(time(NULL)) ; 
	char message[] = "this is a secret message" ; 
	int length = strlen(message) ; 

	char* key = (char *)malloc(length) ; 
	char* ciphertext = (char *)malloc(length) ; 
	char* decrypted_ciphertext = (char *)malloc(length) ; 


	generate_key(key , length) ; 

	otp_encrypt_decrypt(message , ciphertext , key , length) ; 
	otp_encrypt_decrypt(ciphertext , decrypted_ciphertext , key , length) ; 

	decrypted_ciphertext[length] = '\0' ; 
	printf("original message : %s\n" , message) ; 
	printf("encrypted message : %s\n" , ciphertext) ; 
	printf("decrypted message : %s\n" , decrypted_ciphertext) ; 

	free(key) ; 
	free(ciphertext) ; 
	free(decrypted_ciphertext) ; 

	return 0 ; 


}
