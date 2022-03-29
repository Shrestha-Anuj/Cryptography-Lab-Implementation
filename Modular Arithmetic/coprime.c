#include<stdio.h>
int gcd(int,int);

int main(){
	int x,y,temp;
	int gcd_value;
	
	printf("\nEnter the integer x");
	scanf("%d", &x);
	
	printf("\nEnter the integer y");
	scanf("%d", &y);
	
	if(x<y){
		temp = x;
		x = y;
		y = temp;
	}
	
	gcd_value = gcd(x,y);
	
	if(gcd_value == 1){
		printf("\n%d is relatively prime to %d\n",x,y);
	}
	else{
		printf("\nThey are not co-prime integers\n");
	}
	return 0;
}

int gcd(p,q){
	if(q == 0 ){
		return p;
	}
	else {
		gcd(q,p % q);
	}
}


















