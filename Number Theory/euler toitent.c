#include<stdio.h>

int gcd(int,int);
int checkPrime(int);

void main(){
	int x,i,gcd_value,prime_value,euler_toitent = 0;
	
	printf("Enter the number:\n");
	scanf("%d",&x);
	
	if(x == 1){
		printf("\nEuler Toitent of %d => phi(%d) is %d",x,x,1);
	}
	else{
		prime_value = checkPrime(x);
		
		if(prime_value == 1){
			euler_toitent = x-1;
		}
		else{
			for(i=2;i<x;i++){
				gcd_value = gcd(x,i);
				if(gcd_value == 1){
					euler_toitent++;
				}
			}
			euler_toitent++;
		}
		
		printf("\nEuler Toitent of %d => phi(%d) is %d",x,x,euler_toitent);
	}	
}

int gcd(p,q){
	if(q == 0 ){
		return p;
	}
	else {
		gcd(q,p % q);
	}
}

int checkPrime(n){
	int m;
	for(m=2;m<n-1;m++){
		if(n%m == 0){
			return 0;
		}
	}
	return 1;
}


















