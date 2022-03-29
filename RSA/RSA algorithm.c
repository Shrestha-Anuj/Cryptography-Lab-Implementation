#include<stdio.h>

int public_key_value_1, both_key_value_2; // public key elements for alice

int power(int,int); // simple power function
long long int powerLong(long long int,long long int); // power function for Long Long int
int getPrime();
int getInteger();
int gcd(int,int);
int checkGcd(int,int);
int multiplicativeInverse(int,int);
int createPairedKey(); // to create the paired key for alice
int calculateModular(int,int,int);
int getPlaintext();
int encryptionByBob(); // encryption by bob using alice's public key
int decryptionByAlice(int,int); // decryption by alice using alice's private key

int main(){
	int secret_key, encrypted_message, decrypted_message;
	
	secret_key = createPairedKey();
	
	encrypted_message = encryptionByBob();
	
	printf("\nEncrypting the message.....\n");
	
	printf("\nEncrypted Message %d\n", encrypted_message);
	
	printf("\nDecrypting the message.....\n");
		
	decrypted_message = decryptionByAlice(encrypted_message,secret_key);
	
	printf("\nDecrypted Message %d\n", decrypted_message);
	
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
	
	return new_x;
}

int getPrime(){
	
	int prime,m;
	
	scanf("%d",&prime);
	
	m = prime-1; // preceeding element of the prime

	// loop until prime is entered
	while(m>1){
		if(prime % m == 0){
			return getPrime();
		}
		m--;
	}
	
	return prime;
}

int getInteger(){
	
	int x;
	
	printf("\nSelect an integer such that it is co-prime with the euler toitent\n");
	scanf("%d",&x);
	
	return x;
}

int gcd(int p, int q){
	
	if(q == 0 ){
		return p;
	}
	
	else {
		gcd(q,p % q);
	}
}

int checkGcd(int euler_toitent_value,int integer_value){
	
	int x,y,temp,gcd_value;
	
	x = euler_toitent_value;
	y = integer_value;
	
	if(x<y){
		temp = x;
		x = y;
		y = temp;
	}
	
	gcd_value = gcd(x,y);
	printf("gcd %d",gcd_value);
	
	return gcd_value; // gcd_value 1 refers that the numbers are co-prime.
}

int multiplicativeInverse(int integer_value,int modulo){
	
	int j = 1;
	int inverse_key;
	
	for(j=1; j<modulo; j++){
		if((integer_value*j) % modulo == 1){
			printf("\nMultiplicative Inverse of %d is %d\n",integer_value,j);
			break;
		}
	}
	
	inverse_key = j;
	
	return inverse_key;
}

// creating private key for alice
int createPairedKey(){
	
	int p,q,n,euler_toitent_n,status_gcd = 0,e;
	
	printf("\nEnter first prime number\n");
	p = getPrime();
	
	printf("\nEnter second prime number\n");
	q = getPrime();
	
	n = p*q; // creating a composite number
	euler_toitent_n = (p-1) * (q-1);
	
	printf("\nEuler Toitent is %d",euler_toitent_n);
	
	while(status_gcd == 0){
		e = getInteger();
		status_gcd = checkGcd(euler_toitent_n,e);
	}
	
	int d;
	d = multiplicativeInverse(e,euler_toitent_n);
	
	printf("\nPublic Key {%d,%d}\n",e,n);
	printf("\nPrivate Key {%d,%d}\n",d,n);
	
	int private_key_value_1;
	
	public_key_value_1 = e;
	private_key_value_1 = d;
	both_key_value_2 = n;
	
	return private_key_value_1;
}

// performing modular arithmetic for simpler calculations.
int calculateModular(int base_integer,int full_power,int modulo){
	
	long long int temp_power_result;
	long long int mod = 1, temp_mod_remainder;
	int partial_power;
			
	while(full_power>0){
		partial_power = (full_power/5000) + 1;
		temp_power_result = powerLong(base_integer,partial_power); // a^power
		temp_mod_remainder = temp_power_result % modulo; // a^power % b
		mod = (mod * temp_mod_remainder) % modulo;
		full_power = full_power - partial_power;
	}
	
	return (int)mod;
}

int getPlaintext(){
	
	int p;
	
	printf("\nEnter an integer plaintext\n");
	scanf("%d",&p); // plaintext refers to a number less than the calculated composite number
	
	return p;
}

int encryptionByBob(){
	
	int m;
	
	m = getPlaintext();
	if(m>both_key_value_2){
		encryptionByBob();
	}
	
	int cipher_text;
	
	cipher_text = calculateModular(m, public_key_value_1, both_key_value_2);
	
	return cipher_text;
}

int decryptionByAlice(int encrypted_text,int alice_private_key){
	
	int c,plain_text;
	
	c = encrypted_text;
	
	plain_text = calculateModular(c, alice_private_key, both_key_value_2);
	
	return plain_text;
}


















