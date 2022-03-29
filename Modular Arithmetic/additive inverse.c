#include<stdio.h>

int main(){
	int modular = 0;
	int i,j;
	
	printf("\nEnter the modulo number for the additive inverse\n");
	scanf("%d", &modular);
	
	printf("\nFor Modulo %d\n",modular);
	
	for(i=0; i<modular; i++){
		for(j=0; j<modular; j++){
			if((i+j) % modular == 0){
				printf("\nAdditive Inverse of %d is %d\n",i,j);
			}
		}
	}
	return 0;
}





















