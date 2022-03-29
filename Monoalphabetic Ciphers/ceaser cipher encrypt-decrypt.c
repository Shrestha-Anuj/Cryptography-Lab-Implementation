#include<stdio.h>
#include<string.h>

void encrypt(void);
void decrypt(void);
int key = 3;

void main(){
	printf("Encryption:\n");
	encrypt();
	
	printf("\n\nDecryption:\n");
	decrypt();
}

void encrypt(){
	char plain_text[30];
	int i, j, c, cipher_text_position[30];
		
	printf("\nEnter the plaintext\n");
	fgets(plain_text, sizeof(plain_text), stdin);  // read string	
	
	int len = strlen(plain_text)-1;	
	
	for(i=0; i<(len); i++){
		for(j=0; j<26; j++){
			if(plain_text[i] == 32){ // 32 is ascii value for white space
				cipher_text_position[i] = 32;
			}
			else if(plain_text[i] == (j + 97)){
				c = (key + j) % 26;
				cipher_text_position[i] = (c + 97);
			}
			else if(plain_text[i] == (j + 65)){
				c = (key + j) % 26;
				cipher_text_position[i] = (c + 65);
			}
		}
	}
	
	printf("\nCipherText is\n");
	for(i = 0; i<len; i++){
		printf("%c",cipher_text_position[i]);
	}
}

void decrypt(void){
	char cipher_text[30];
	int i, j, p, plain_text_position[30];
	
	printf("\nEnter the ciphertext\n");
	fgets(cipher_text, sizeof(cipher_text), stdin);  // read string
	
	int len = strlen(cipher_text)-1;	
	
	for(i=0; i<(len); i++){
		for(j=0; j<26; j++){
			if(cipher_text[i] == 32){ // 32 is ascii value for white space
				plain_text_position[i] = 32;
			}
			else if(cipher_text[i] == (j + 97)){
				p = (j + 26 - key) % 26;
				plain_text_position[i] = (p + 97);
			}
			else if(cipher_text[i] == (j + 65)){
				p = (j + 26 - key) % 26;
				plain_text_position[i] = (p + 65);
			}
		}
	}
	
	printf("\nPlainText is\n");
	for(i = 0; i<(len); i++){
		printf("%c",plain_text_position[i]);
	}
}

