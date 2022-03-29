#include<stdio.h>
void eea(int,int);

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
	
	eea(x,y);
		
	return 0;
}

void eea(a,b){
	int r[100], q[100], x[100], y[100];
	int gcd, x_variable, y_variable;
	int i = 1;
		
	r[0] = a;
	r[1] = b;
	
	x[0] = 1;
	x[1] = 0;
	
	y[0] = 0;
	y[1] = 1;
	
	do{
		i = i + 1;
		r[i] = r[i-2] % r[i-1];
		q[i] = r[i-2]/r[i-1];
		x[i] = x[i-2] - (q[i]*x[i-1]);
		y[i] = y[i-2] - (q[i]*y[i-1]);
	}while(r[i] != 0);
	
	gcd = r[i-1];
	x_variable = x[i-1];
	y_variable = y[i-1];
	
	printf("\nGCD of %d and %d is %d\n",a,b,gcd);
	printf("\n x = %d and y = %d\n",x_variable,y_variable);
}
