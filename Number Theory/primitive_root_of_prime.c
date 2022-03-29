#include<stdio.h>

int prime_number;

int power(int,int); // power function
int getPrime(); // to get a prime number
void primitiveExtract(); // getting the primitive roots for the prime number


void main(){
	getPrime();
	primitiveExtract();
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

void primitiveExtract(){
	int potential_primitive_root; // variable to hold the potential primitive number
	int remainder[prime_number-1]; // array to hold the remainder for each number < prime ; re-initialized at each iteration
	int primitive_root[prime_number-1]; // arrray to hold the primitive root
	int i,k;
	int primitive_count = 0; // varibale used to increase the counter of the primitive_root array after a primitive root has been added.
	
	for(k=1; k<prime_number; k++){
		potential_primitive_root = k;
		printf("\nFor %d\n",k);
		
		for(i=1;i<prime_number;i++){
			int p;
			int k = i;
			long long int mod = 1;
			
			// performing modular arithmetic for simpler calculations.
			while(k>0){ 
				p = (k/4) + 1;
				mod = (mod * (power(potential_primitive_root,p) % prime_number)) % prime_number;
				k = k - p;
			}
		
			remainder[i] = mod; // actual remainder after modular arithmetic
			printf("%d, ",remainder[i]);
		}
		
		int x,y,remainder_frequency, not_primitive = 0;
		
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
			primitive_root[primitive_count] = potential_primitive_root;
			primitive_count++; //increase the array of by 1 after adding a primitive root to the array.
		}
	}
	
	int z;
			
	printf("\nPrimitive Root of Prime Number %d\n",prime_number);
	
	for(z=0;z<primitive_count;z++){ 
		printf("%d, ",primitive_root[z]);
	}
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



















