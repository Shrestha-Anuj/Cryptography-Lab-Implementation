#include<stdio.h>

int main(){
	int i,j,n,key = 3;
	char str[12] = "hello world";
	
	for(i=0;i<11;i++){
		
		if(str[i] == 32){
			printf(" ");
		}else{
			for(j=0;j<26;j++){
				
				if(str[i] == (j+97)){
					n = (j+key) % 26;
					break;
				}
			}
			printf("%c",(n+97));
		}	
	}
	
	return 0;
}

