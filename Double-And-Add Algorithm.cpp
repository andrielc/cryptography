/*
Double-And-Add Algorithm (Eliptic Curve) -  Understanding Cryptography book
Exercise 1a) - 9.7
*/
#include<bitset>
#include<iostream>
#include<limits>

#define ui unsigned int 
#define ll long long
#define ull unsigned long long
#define MOD 29

using namespace std;
//Structure for eliptic courve y^2 = x^3 + ax + b, point P = (x,y)
struct CoefsEq{
	ll a;
	ll b;
};

struct Points {
	ll x;
	ll y;
};
//
//Short Fermat theorem, if M is prime -> a^(m-1) CONGR 1 (mod m)
ll gcd (ll a, ll b) {
	if (a == 0) return b;
	return gcd (b%a,a);
}

ll power (ll x , ull y = MOD-2, ull m = MOD) {
	if (y == 0) return 1;
	ll p = power (x,y/2,m) % m;
	p = (p * p) % m;

	return (y%2 == 0) ? p : (x*p) % m;
}

ll modInverse (ll a, ll m = MOD){

	if (gcd (a,m) != 1){
		cout << "Inverse does not existe :(!!" << endl;
		return 0;
	}
	ll ans = power (a);
	if (ans < a) ans = MOD + ans; 
	return ans;
}
//


Points addPoint (Points P, Points Q) {
	Points ans;
	ll expr = (Q.x - P.x) % MOD;
	expr = expr >= 0 ? expr : (MOD + expr);
	ll inverse = modInverse ( expr );
	
	expr = (Q.y - P.y) % MOD;
	expr = expr >= 0 ? expr : (MOD + expr)%MOD;
	ll s = (expr *inverse) % MOD;

	expr = (s*s - P.x - Q.x)%MOD;
	expr = expr >= 0 ? expr : MOD + expr;
	ans.x = (expr) % MOD;

	expr = (s*(P.x-ans.x) - P.y)%MOD;
	expr = expr >= 0 ? expr : MOD + expr;
	ans.y = (expr) % MOD;

	return ans;
}

Points doublePoint (Points P, CoefsEq eq) {
	Points ans;
	ll expr = (2*P.y) % MOD;
	expr = expr >= 0 ? expr : ( MOD + expr );

	ll s = ( (3*(P.x * P.x)+eq.a) * modInverse(expr)) % MOD;

	expr = (s*s - 2*P.x) % MOD ;
	expr = expr >= 0 ? expr : (MOD + expr) % MOD; 
	ans.x = (expr) % MOD;

	expr = ((s*(P.x-ans.x)) - P.y) % MOD;
	expr = expr >= 0 ? expr : (MOD + expr) ;
	ans.y = (expr) % MOD;

	return ans;
}


int main() {
	Points P = {8,10};
	CoefsEq eq = {4,20};
	int k1 = 9, k2 = 20;
	bitset <3> k1Bits (k1);
	bitset <4> k2Bits (k2);
    Points T = P;
    
    //Double-and-Add Algorithm for Points multiplication.
    printf(" First step for K = %d: P = (%lld, %lld)\n",k1,P.x,P.y);
	for (int i=k1Bits.size()-1; i >= 0; --i){
		printf("2*(%lld,%lld)=",T.x,T.y);
		T = doublePoint (T,eq);
		printf("(%lld,%lld)\n",T.x,T.y);
		if (k1Bits[i]) {
			printf("(%lld,%lld) + (%lld,%lld) = ",T.x,T.y,P.x,P.y );
			T = addPoint (T,P);
			printf("(%lld,%lld)\n",T.x,T.y);
		}
	}

	T = P;
	printf("\n First step for K = %d: P = (%lld, %lld)\n",k2,P.x,P.y);
	for (int i=k2Bits.size()-1; i >= 0; --i){
		printf("2*(%lld,%lld)=",T.x,T.y);
		T = doublePoint (T,eq);
		printf("(%lld,%lld)\n",T.x,T.y);
		if (k2Bits[i]) {
			printf("(%lld,%lld) + (%lld,%lld) = ",T.x,T.y,P.x,P.y );
			T = addPoint (T,P);
			printf("(%lld,%lld)\n",T.x,T.y);
		}
	}
	return 0;
}
