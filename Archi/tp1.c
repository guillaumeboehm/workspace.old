#include <stdio.h>
#include <stdlib.h>

int n_b (char *addr, int i){
  return (char)0x1 & ((char) *(addr + i/8))>>i%8;
}

char d2c (int n){
  return ( n<0? '?': (n<10? '0'+n : (n<36 ? 'A' + (n-10) : '?') ));
}

long long int P2(int n) {
  return (n<0?0:(n==0?1 : 2*P2(n-1)));
}

// Fonctions à compléter

// Exo 1
void base2(int n) {
	if(n !=0){
		base2(n/2);
		printf("%d", n%2);
	}
}

// Exo 3
void baseB(int B, int n){
	if(n != 0){
		baseB(B, n/B);
		printf("%c", d2c(n%B));
	}
}

// Exo 4
void mantisse(float f, int result[]) {
	for(unsigned int i=0; i<23; ++i){
		result[i] = n_b((char*)&f, i);
	}
}

float mantisseNormalisee(float f){

  int *mantisse_val = malloc(23*sizeof(int));
  mantisse(f, mantisse_val);
  
  int puissance_2 = 1;
  float a = 0.f;
  
  for(int i = 0; i<23; ++i){
  	a += mantisse[i] * puissance_2;
  	puissance_2 *= 2;
  }

  return a-127.f;
}

void exposant(float f, int result[]) {
	
}

int exposantSansExces(float f) {
  return 0;
}

int signe(float f) {
  return 0;
}

int main(){

  baseB(32, 16);

  return EXIT_SUCCESS;
}
