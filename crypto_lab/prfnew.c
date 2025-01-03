#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint32_t drawarandombit() {
    FILE *urandom = fopen("/dev/urandom", "rb");
    if (urandom == NULL) {
        perror("Error opening /dev/urandom");
        exit(EXIT_FAILURE);
    }

    uint32_t random_value;
    size_t result = fread(&random_value, 1, sizeof(random_value), urandom);
    if (result != sizeof(random_value)) {
        perror("Error reading from /dev/urandom");
        fclose(urandom);
        exit(EXIT_FAILURE);
    }

    fclose(urandom);
    return random_value;
}

int main(int argc, char **argv) {
    
    
    
	 
	static uint32_t ary[100][100] = {0};

	while(1){
    int key;
    char message[100];
	printf("Enter message: \n");
	scanf("%s", message);
	printf("Message is: %s\n", message);
	printf("Enter key: \n");
	scanf("%d", &key);
	printf("Key is: %d\n", key);

	if (key < 0 || key >= 100) {
        printf("Key must be between 0 and 99.\n");
        return EXIT_FAILURE;
    }
     

    
    unsigned int msgint = 0;
    int multiplier = 1;
    int itr = 0;
    while (message[itr] != '\0') {
        msgint = (multiplier * message[itr]) + msgint;
        multiplier++;
        itr++;
    }

    msgint = msgint % 100;
    if (ary[key][msgint] != 0) { 
        printf("Generated random number: %x\n", ary[key][msgint]);
    } else {
        uint32_t value = drawarandombit();
        ary[key][msgint] = value; 
        printf("For message F(%s, %d) = %x\n", message, key, value);
    }
	char input ; 
	printf("Do you want to continue? (y/n): \n");
	scanf(" %c", &input);
	if (input == 'n') {
		break;

	}
	}

    return 0;
}


