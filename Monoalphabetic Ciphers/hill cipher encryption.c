#include<stdio.h>
#include<conio.h>
#include<string.h>

int key[2][2]; // 2x2 key for encryption
char plain_text[5]; // plaintext for encryption
int cipher_text_position[5]; // ciphertext postion for encryption

void getPlaintext(void);
void displayPlaintext(void);

void getKey(void);
void checkKey(void);
void displayKey(void);

void encrypt(void);

void main(){
	getPlaintext();
	displayPlaintext();
	
	getKey();
	checkKey();
	displayKey();
	encrypt();
}


void getPlaintext(){
	int i,j,k,len = 0;
	
	printf("\nEnter the plaintext\n");
	fgets(plain_text,5,stdin);  // read string	

	len = strlen(plain_text);
	
	for(i=0;i<len;i++){  
		if(plain_text[i] == ' '){			// to remove any white spacing
			plain_text[i] = plain_text[i+1]; // replacing white space with next character if available
			len--;
		}
	}
		
	if(len < 4){
		for(j = len; j < 4; j++){
			plain_text[j] = 'z';		// add missing characters in a string
		}
	}
	else if(len > 4){
		plain_text[4] = '\0';			// truncate extra characters from a string
	}
}

void displayPlaintext(){
	
	printf("\nPlaintext:\n");
	puts(plain_text);
}

void getKey(){
	int i,j;
	
	for(i = 0; i<2; i++){
		for(j=0;j<2;j++){
			printf("\nEnter the [%d][%d] elements of 2x2 key\n",i+1,j+1);
			scanf("%d",&key[i][j]);
		}
	}
}

void checkKey(){ // reduce any element of matrix into the 0-26 range
	int i,j;
	
	for(i =0; i<2; i++){
		for (j = 0; j<2; j++){
			key[i][j] = (key[i][j] + 26) % 26;
		}
	}
}

void displayKey(){
	int i,j;
	
	printf("Key:\n");
	for(i = 0; i<2; i++){
		for(j=0;j<2;j++){
			printf("%d\t",key[i][j]);
		}
		printf("\n");
	}
}
void encrypt(){
	int i, j, k=0;
	int plain_text_value[4]; // to represent the character by integers
	int plain_text_status[4]; // to track upper or lower case in a string
	int cipher_text_value[4]; // to store the value of cipher characters
	int encryption_convention = 0; // varibale to store the status of convention either row or column	
	
	for(i=0;i<4;i++){		// loop for getting the actual value of plain text characters
		for(j = 0; j<26; j++){
			if(plain_text[i] == (j+65)){
				plain_text_value[i] = j;
				plain_text_status[i] = 1; // 1 status for upper case
			}
			else if(plain_text[i] == (j+97)){
				plain_text_value[i] = j;
				plain_text_status[i] = 0; // 0 status for lower case
			}
		}
	}
	
	printf("\nEnter 1 for column or anything for row convention");
	scanf("%d",&encryption_convention);
	
	printf("\nEncrypting Vector......");
	
	// for row or column vector encryption
	if(encryption_convention == 1){
		printf("\nUsing Column Vector Convention for Encryption\n");
		for(i=0;i<4;i++){
			cipher_text_value[i] = 0; // initialize to avoid garbage value
		
			if(i>1){ // change the value of k to start encrypting for second column vector
				k = 2;
			}
			
			for(j = k; j<(k+2); j++){
				cipher_text_value[i] += key[i-k][j-k] * plain_text_value[j];
			}
			cipher_text_value[i] = cipher_text_value[i] % 26;
		}
	}
	
	else{
		printf("\nUsing Row Vector Convention for Encryption\n");
		for(i=0;i<4;i++){
			cipher_text_value[i] = 0; // initialize to avoid garbage value

			if(i>1){ // change the value of k to start encrypting for second row vector
				k = 2;
			}
			
			for(j = k; j<(k+2); j++){
				cipher_text_value[i] += key[j-k][i-k] * plain_text_value[j];
			}
			cipher_text_value[i] = cipher_text_value[i] % 26;
		}
	}
	
	for(i=0;i<4;i++){		// loop for getting the actual cipher text characters from values
		if(plain_text_status[i] == 1){
			cipher_text_position[i] = cipher_text_value[i] + 65;
		}
		else{
			cipher_text_position[i] = cipher_text_value[i] + 97;
		}
	}
	printf("\nCiphertext: \n");
	for(i=0;i<4;i++){		
		printf("%c",cipher_text_position[i]);
	}
}
