#include <stdio.h>
#include <string>
#include <cstring>
#include <iostream>


typedef long long LL;

class Matrix{

public :

	int N;
	static const int MAXN = 100;
	LL a[MAXN][MAXN];
	
	Matrix(){
		N = MAXN;
		for(int i = 0; i < MAXN; ++i){
			for(int j = 0; j < MAXN; ++j){
				a[i][j] = 0;
			}
			a[i][i] = 1;
		}
	}
	
	Matrix(int n){
		if(n <= MAXN){
			N = n;
			for(int i = 0; i < N; ++i){
				for(int j = 0; j < N; ++j){
					a[i][j] = 0;
				}
				a[i][i] = 1;
			}
		}
	}
	
	void clr(){
		for(int i = 0; i < N; ++i){
			for(int j = 0; j < N; ++j){
				a[i][i] = 0;
			}
		}
	}

	bool setN(int n){
		if(n <= MAXN){
			N = n;
			return true;
		}
		return false;
	}
	void print(){
		for(int i = 0; i < N; ++i, puts("")){
			for(int j = 0; j < N; ++j){
				printf("%d ",a[i][j]);
			}
		}
	}
	Matrix multi(Matrix mat1, Matrix mat2){  // matrix multiply a[i][j] = sigm( a[i][0..k..n] * a[0..k..n][j]) 
		Matrix res(N);
	    res.clr();
		for(int k = 0; k < N; ++k){
			for(int i = 0; i < N; ++i){
				
				if(a[i][k] == 0)  continue;

				for(int j = 0; j < N; ++j){
					res.a[i][j] += mat1.a[i][k] * mat2.a[k][j];
					
					if(res.a[i][j] < 0){
						std::cout<<"溢出"<<std::endl;
					}
				}
			}
		}
		return res;
	}

	Matrix operator * (Matrix mat){
		return multi(*this, mat);
	}

	Matrix exp(LL n){
		if(n == 1)  return *this;
		if(n == 0)  return Matrix( N);

		Matrix res = exp( n >> 1);
		res = res * res;
		if(n & 1)   res = res * (*this);
		return res;
	}
};

void test(){

	Matrix mat(2);
	
	mat.a[0][0] = 1;
	mat.a[0][1] = 2;
	mat.a[1][0] = 3;
	mat.a[1][1] = 4;
	
	mat = mat.exp(2);
	mat.print();
}

int main(int argc,  char *argv[]){

	test();


	return 0;
}
