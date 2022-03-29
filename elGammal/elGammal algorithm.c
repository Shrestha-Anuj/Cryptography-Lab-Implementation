#include<stdio.h>

int prime_number,primitive_integer,y_alice;
int cipher_text[2]; // to store the ciphertext elements sent by bob C1 and C2
int power(int,int); // simple power function
long long int powerLong(long long int,long long int); // power function for Long Long int

int getPrime();
void getPrimitive();
int creatPrivateKey(char[]); // to create the private key for alice or bob
int calculatePublicKey(int); // to create the public key for alice or bob
int calculateModular(int,int);
int createPairKeyAlice();
int randomInteger();
void encryptionByBob();
int multiplicativeInverse(int);
int decryptionByAlice(int[],int);

int main(){
	int private_key_alice;
	
	getPrime();
	getPrimitive();
	
	private_key_alice = createPairKeyAlice();

	encryptionByBob();
	
	decryptionByAlice(cipher_text,private_key_alice);
	
	return 0;
}

int power(int x, int y){
	if(y == 0){
		return 1;
	}
	int i,old_x = x,new_x =1;
	for(i=1;i<=y;i++){
		new_x = new_x * old_x;
	}
	return (new_x);
}

long long int powerLong(long long int x,long long  int y){
	if(y == 0){
		return 1;
	}
	long long int i, old_x = x,new_x =1;
	for(i=1;i<=y;i++){
		new_x = new_x * old_x;
	}
	
	return (new_x);
}

int getPrime(){
	int p,n;
	
	printf("\nEnter a prime number\n");
	scanf("%d",&p);
	
	n = p-1; // preceeding element than p
	
	// loop until prime is entered
	while(n>1){
		if(p%n == 0){
			return getPrime();
		}
		n--;
	}
	prime_number = p;
	
	return 0;
}

void getPrimitive(){
	int i, potential_primitive_root,remainder[prime_number-1];
	
	printf("\nEnter the primitive root of the prime number\n");
	scanf("%d",&potential_primitive_root);
		
	for(i=1;i<prime_number;i++){
		int p;
		int k = i; // power for primitive root
		long long int mod = 1;
			
		// performing modular arithmetic for simpler calculations.
		while(k>0){ 
			p = (k/4) + 1;
			mod = (mod * (power(potential_primitive_root,p) % prime_number)) % prime_number;
			k = k - p;
		}
		
		remainder[i] = mod % prime_number; // actual remainder after modular arithmetic
	}
	
	int x,y, not_primitive = 0, remainder_frequency;

	// for a number < prime check whether it is in the remainder array
	for(x=1;x<prime_number;x++){
		if(not_primitive == 0){ // to check if the potential primitive is already found not primitive after at least one loop check
			remainder_frequency = 0; // to count the occurence of a number < prime in the remainders
				
			for(y=1;y<prime_number;y++){
				if(remainder[y] == x){
					remainder_frequency++;  // if the number < prime equals remainder then increment remainder_frequency by 1 
				}
			}
				
			// if any number < prime is missing or repeats then set flag as not primitive.
			if((remainder_frequency == 0) || (remainder_frequency > 1)){
				not_primitive = 1; 
			}
		}	
	}
	
	printf("\n");
	if(not_primitive == 0){ // after the frequency check, if the not_primitive is still 0 then the number is primitive.
		primitive_integer = potential_primitive_root;
	}
	else{
		getPrimitive();
	}
}

int createPrivateKey(char name[10]){
	int private_key, check_key;
	
	printf("\n");
	printf("\nEnter the private key for %s\n",name);
	scanf("%d",&private_key);
	
	if(private_key<prime_number){
		return private_key;
	}
	else{
		private_key	= createPrivateKey(name);
	}
}

// performing modular arithmetic for simpler calculations.
int calculateModular(int base_integer,int full_power){
	long long int temp_power_result;
	long long int mod = 1, temp_mod_remainder;
	int partial_power;
			
	while(full_power>0){
		partial_power = (full_power/4) + 1;
		temp_power_result = powerLong(base_integer,partial_power); // a^power
		temp_mod_remainder = temp_power_result % prime_number; // a^power % b
		mod = (mod * temp_mod_remainder) % prime_number;
		full_power = full_power - partial_power;
	}
	
	return (int)mod;
}

int calculatePublicKey(int p_key){
	int public_key;
	
	public_key =  calculateModular(primitive_integer,p_key);
	return public_key;
}

int createPairKeyAlice(){
	int x_alice;
	
	x_alice = createPrivateKey("Alice");
	y_alice = calculatePublicKey(x_alice);
	
	printf("\nAlice Private Key %d\n", x_alice);
	printf("\nAlice Public Key {%d, %d, %d}", prime_number, primitive_integer, y_alice);
	
	return x_alice;
}

int randomInteger(){
	int x;
	
	printf("\nEnter a random number\n");
	scanf("%d",&x);
	
	return x;
}

int plaintext(){
	int text;
	
	printf("\n");
	printf("\nEnter plaintext less than the given prime number %d\n",prime_number);
	scanf("%d",&text);
	
	return text;
}

void encryptionByBob(){
	int plain_text = 0; // plaintext here is refered to as a integer less than given prime number.
	int random_k = 0;
	int private_key_element_K;
	
	while((plain_text<1) || (plain_text>prime_number)){
		plain_text = plaintext();
	}
	
	printf("\nMessage = %d\n",plain_text);
	
	while((random_k<1) || (random_k>prime_number)){
		random_k = randomInteger();
	}
	
	private_key_element_K = calculateModular(y_alice,random_k);
	
	int element_C1 = calculateModular(primitive_integer,random_k);
	int p = private_key_element_K * plain_text;
	int element_C2 = p % prime_number;
	
	cipher_text[0] = element_C1;
	cipher_text[1] = element_C2;			
}

int multiplicativeInverse(int key){
	int j = 1;
	int inverse_key;
	
	for(j=1; j<prime_number; j++){
		if((key*j) % prime_number == 1){
			printf("\nMultiplicative Inverse of %d is %d\n",key,j);
			break;
		}
	}
	inverse_key = j;
	
	return inverse_key;
}

int decryptionByAlice(int encrypted_text[],int alice_private_key){
	int C1,C2;
	
	C1 = encrypted_text[0];
	C2 = encrypted_text[1];
	
	printf("\nEncrypted text:{%d,%d}\n",C1,C2);

	int secret_element_K = calculateModular(C1,alice_private_key);
	
	printf("\nsecret_element_K:{%d}\n",secret_element_K);

	
	printf("\nBob side Secret Key = %d\n",secret_element_K);
	
	int secret_element_K_inverse = multiplicativeInverse(secret_element_K);
	
	printf("\nsecret_element_K_inverse:{%d}\n",secret_element_K_inverse);

	
	int message = (C2 * secret_element_K_inverse) % prime_number;
	
	printf("\nPlaintext = %d\n",message);
	
	return 0;
}



















