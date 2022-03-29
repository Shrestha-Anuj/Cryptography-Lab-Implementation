#include<stdio.h>
int prime_number,primitive_integer,y_alice,y_bob;
int power(int,int); // simple power function
long long int powerLong(long long int,long long int); // power function for Long Long int

int getPrime();
void getPrimitive();
int creatPrivateKey(char[]); // to create the private key for alice or bob
int calculatePublicKey(int); // to create the public key for alice or bob
int calculateModular(int,int);
int createPairKeyAlice();
int createPairKeyBob();
int createSecretKeyAlice(int);
int createSecretKeyBob(int);

int main(){
	int private_key_alice, private_key_bob;
	
	getPrime();
	getPrimitive();
	
	private_key_alice = createPairKeyAlice();
	private_key_bob = createPairKeyBob();
	
	printf("\n");
	
	createSecretKeyAlice(private_key_alice);
    createSecretKeyBob(private_key_bob);
    
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
	
	printf("\nEnter the primitive root of prime number");
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
	printf("\nEnter the private key for %s",name);
	scanf("%d",&private_key);
	
	//check_key = private_key;
	if(private_key<prime_number){
		return private_key;
	}
	else{
		private_key	= createPrivateKey(name);
	}
}

// performing modular arithmetic for simpler calculations.
int calculateModular(int base_integer, int full_power){
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
	
	printf("\nAlice Private Key %d, Alice Public Key %d", x_alice,y_alice);
	
	return x_alice;
}

int createPairKeyBob(){
	int x_bob;
	
	x_bob = createPrivateKey("Bob");
	y_bob = calculatePublicKey(x_bob);
	
	printf("\nBob Private Key %d, Bob Public Key %d", x_bob,y_bob);
	
	return x_bob;
}

int createSecretKeyAlice(int alice_private_key){
	int secret_key_alice_side;
	int p;
	long long int mod = 1;
			
	secret_key_alice_side = calculateModular(y_bob,alice_private_key);
	
	printf("\nAlice side Secret Key = %d",secret_key_alice_side);
	
	return 0;
}

int createSecretKeyBob(int bob_private_key){
	int secret_key_bob_side;
	
	secret_key_bob_side = calculateModular(y_alice,bob_private_key);
	
	printf("\nBob side Secret Key = %d",secret_key_bob_side);
	
	return 0;
}



















