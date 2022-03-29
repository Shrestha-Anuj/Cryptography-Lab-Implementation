#include<stdio.h>
#include<string.h>

int key[2][2]; // 2x2 key for decryption
char cipher_text[5]; // ciphertex for decryption
int plain_text_position[5]; // plaintext postion for encryption

void getCiphertext(void);
void displayCiphertext(void);

void getKey(void);
void checkKey(void);
void displayKey(void);

int determinant();
int multiplicativeInverse(int);
void adjoin();
void displayAdjoin();

void getInverseKey(int);
void displayInverseKey(void);

void decrypt(void);

void main(){
	int d,m;
	
	getCiphertext();
	displayCiphertext();
	
	getKey();
	checkKey();
	displayKey();
	
	d = determinant();
	m = multiplicativeInverse(d);
	adjoin();
	displayAdjoin();
	
	getInverseKey(m);
	displayInverseKey();
	
	decrypt();
}


void getCiphertext(){
	int i,j,k,len = 0;
	
	printf("\nEnter the ciphertext\n");
	gets(cipher_text);  // read string	

	len = strlen(cipher_text);
	
	for(i=0;i<len;i++){  
		if(cipher_text[i] == ' '){			// to remove any white spacing
			cipher_text[i] = cipher_text[i+1]; // replacing white space with next character if available
			len--;
		}
	}
		
	if(len < 4){
		for(j = len; j < 4; j++){
			cipher_text[j] = 'z';		// add missing characters in a string
		}
	}
	else if(len > 4){
		cipher_text[4] = '\0';			// truncate extra characters from a string
	}
}

void displayCiphertext(){
	
	printf("\nCiphertext:\n");
	puts(cipher_text);
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

int determinant(){
	return (((key[0][0] * key[1][1]) - (key[1][0] * key[0][1]) + 26) % 26);
}

int multiplicativeInverse(int input_number){
	int x = 1; // initialize inverse multiplicative number to 1
	int flag = 1;

	while(flag){
		if((input_number*x) % 26 == 1){
			flag = 0;
			return x;
		}
		x++;
	}
	return 0;
}

void adjoin(){
	int temp;
	
	temp = key[0][0];
	key[0][0] = key[1][1];
	key[1][1] = temp;
	
	key[0][1] = ((key[0][1]*-1) + 26) % 26;
	key[1][0] = ((key[1][0]*-1) + 26) % 26;
}

void displayAdjoin(){
	int i,j;
	
	printf("\nCryptography Adjoin of given matrix is\n");

	for(i =0; i<2; i++){
		for (j = 0; j<2; j++){
			printf("%d\t",key[i][j]);
		}
		printf("\n");
	}
}

void getInverseKey(int n){
	int i,j;
	
	printf("\nInverse Key:\n");
	
	for(i=0;i<2;i++){
		for(j=0;j<2;j++){
			key[i][j] = (key[i][j]*n) % 26;
		}
	}
}

void displayInverseKey(){
	int i,j;
	
	for(i=0;i<2;i++){
		for(j=0;j<2;j++){
			printf("%d\t",key[i][j]);
		}
		printf("\n");
	}
}


void decrypt(){
	int i, j, k=0;
	int cipher_text_value[4]; // to represent the cipher character by integers
	int cipher_text_status[4]; // to track upper or lower case in a string
	int plain_text_value[4]; // to store the value of plain characters	
	
	for(i=0;i<4;i++){		// loop for getting the actual value of cipher text characters
		for(j = 0; j<26; j++){
			if(cipher_text[i] == (j+65)){
				cipher_text_value[i] = j;
				cipher_text_status[i] = 1; // 1 status for upper case
			}
			else if(cipher_text[i] == (j+97)){
				cipher_text_value[i] = j;
				cipher_text_status[i] = 0; // 0 status for lower case
			}
		}
	}
	
	int decryption_convention = 0;
	
	printf("\nEnter 1 for column or anything else for row column");
	scanf("%d",&decryption_convention);
	
	printf("\nDecrypting Vector......");
	
	if(decryption_convention == 1){
		printf("\nUsing Column Convention for Decryption\n");
		
		for(i=0;i<4;i++){
			plain_text_value[i] = 0; // initialize to avoid garbage value
		
			if(i>1){ // change the value of k to start decrypting for second and third vector
				k = 2;
			}
	
			for(j = k; j<(k+2); j++){
				plain_text_value[i] += key[i-k][j-k] * cipher_text_value[j];
			}
	
			plain_text_value[i] = plain_text_value[i] % 26;
		}
	}
	
	else{
		printf("\nUsing Row Convention for Decryption\n");
		
		for(i=0;i<4;i++){
			plain_text_value[i] = 0; // initialize to avoid garbage value
		
			if(i>1){ // change the value of k to start decrypting for second and third vector
				k = 2;
			}
	
			for(j = k; j<(k+2); j++){
				plain_text_value[i] += key[j-k][i-k] * cipher_text_value[j];
			}
	
			plain_text_value[i] = plain_text_value[i] % 26;
		}
	}
	
	
	for(i=0;i<4;i++){		// loop for getting the actual plain text characters from values
		if(cipher_text_status[i] == 1){
			plain_text_position[i] = plain_text_value[i] + 65;
		}
		else{
			plain_text_position[i] = plain_text_value[i] + 97;
		}
	}
	printf("\nPlaintext:\n");
	for(i=0;i<4;i++){		
		printf("%c",plain_text_position[i]);
	}
}
