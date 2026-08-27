#include <stdio.h>

int main(){
	int n=10, ant=0, sig=1, aux=0;
	while(n>0){
		printf("%d, ", ant);
		aux = ant + sig;
		ant = sig;
		sig = aux;
		n--;
	}
	printf("\n");
	return 0;
}


