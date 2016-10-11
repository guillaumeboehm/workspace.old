#include <stdio.h>
#include <stdlib.h>

#define BIT(A,B) ((A>>B)&0x1)

int XOR(int A,int B){
	return A&&!B || !A&&B;
}

long long int P2(int n) {
  return (n<0?0:(n==0?1 : 2*P2(n-1)));
}

void display(int p){
	for(int i = 0; i < P2(p); ++i){
		printf("(");
		for(int j = p-1; j >= 0; --j){
			printf(" ");
			printf("%d", BIT(i, j));
			printf(" ");
		}
		printf(")\n");
	}
}

///exo2
int F2(int args){
	int ret = 0;
	for(int i = 0; i<args; ++i){
		ret = XOR(BIT(args, i), ret);
	}
	return ret;
}

int F3(int args){
	int ret = 0;
	for(int i = 0; i<args; i = i+2){
		ret = ret&&!BIT(args, i) || BIT(args, i)&&!BIT(args, i+1) || !BIT(args, i)&&BIT(args, i+1);
	}
	return ret;
}

int F4(int args){
	int ret = 0;
	for(int i = 0; i<args; i = i+3){
		ret = XOR(ret&&BIT(args, i)&&!BIT(args, i+1),ret&&!BIT(args, i)&&BIT(args, i+2))
			|| BIT(args, i+1)&&!BIT(args, i+2);
	}
	return ret;

}

///exo3

void verite2var( int (*func) (int) ){
}

///exo4

void veriteNvar(int N, int (*func) (int) ){
}

///exo5

void disjonctive( int N, int (*func) (int)) {
}

void conjonctive( int N, int (*func) (int)) {
}

int main(){
	printf("%d\n", F4(50));
}
