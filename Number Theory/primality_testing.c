#include<stdio.h>

int q,k,random_int;

int getOdd(); // get the odd number
void getParameters(int); // get the q and k parameters
void enterRandomInteger(int); // enter a random integer
int checkPrimalityP1(int); // checking primality of a number using property number 1
int checkPrimalityP2(int); // checking primality of a number using property number 2

void main(){
	int n, p1_check, p2_check;
	int prime_status = 1; // to check whether any random integer is composite
	
	n = getOdd();
	getParameters(n);
	printf("\nq and k are %d , %d respectively\n",q,k);
	
	int j;
	for(j=1; j<n; j++){
		random_int = j;
		printf("\nRandom integer = %d\n",random_int);
		
		p1_check = checkPrimalityP1(n);
		
		if(p1_check == 1){
			printf("Inconclusive\n");
		}
		else{
			p2_check = checkPrimalityP2(n);
			
			if(p2_check == 1){
				printf("Inconclusive\n");
			}
			else{
				prime_status = 0;
				printf("Composite\n");
			}
		}
	}
	
	if(prime_status == 1){
		printf("\nNumber %d is a Prime Number",n);
	}
	else{
		printf("\nNumber %d is a not Prime Number",n);
	}
}

int getOdd(){
	int odd;
	
	printf("\nEnter an Odd number greater than 2\n");
	scanf("%d",&odd);
	
	if((odd % 2 == 0) || (odd < 3)){
		odd = getOdd();
	}
	
	return odd;
}

void getParameters(int x){
	int w,c = 0;
	
	w = x-1;
	while((w % 2) == 0){ // loop until the quotient is odd
		w = w/2; // divison until a becomes odd
		c++;  // number of divisons
	}
	
	q = w;
	k = c;
}

void enterRandomInteger(int x){
	int r;
	
	printf("\nEnter any random integer between 1 to %d \n",x);
	scanf("%d",&r);
	
	if((r<1) || (r>x) || (r == x)){
		enterRandomInteger(x);
	}
	
	random_int = r;
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

int modularRemainder(int m, int odd){
	int remainder,p;
	long long int mod = 1;
			
	// performing modular arithmetic for simpler calculations.
	while(m>0){ 
		p = (m/5000) + 1; // more the value of denominator more will be the breaking of modulo 
		mod = (mod * (power(random_int,p) % odd)) % odd;
		m = m - p;
	}		
	
	remainder = mod % odd; // actual remainder after modular arithmetic
	
	return remainder;
}

int checkPrimalityP1(int odd){
	int d, rem_p1;
	
	rem_p1 = modularRemainder(q,odd);
	
	if(rem_p1 == 1){
		return 1;
	}
	
	return 0;
}

int checkPrimalityP2(int odd){
	int j, power_of_two, t, rem_p2;
	
	for(j = 0; j<k; j++){
		power_of_two = power(2,j);
		
		rem_p2 = modularRemainder((power_of_two * q),odd);
		
		if(rem_p2 == (odd-1)){
			
			return 1;
		}
	}
	
	return 0;
}

















