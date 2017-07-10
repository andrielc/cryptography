/*
Exercise 2 - 13.1 book Cryptography, Theory and Pratice Third Edition
*/

#include<iostream>
#define ll long long
#define ull unsigned long long

//Prime number for the module value
#define PRIME 31847

using namespace std;

ll x[10] = {413,432,451,470,489,508,527,546,565,584};
ll y[10] = {25439,14847,24780,5910,12734,12492,12555,28578,20806,21462};

//Short Fermat theorem, if M is prime -> a^(m-1) CONGR 1 (mod m)
ll gcd (ll a, ll b) {
	if (a == 0) return b;
	return gcd (b%a,a);
}

ll power (ll x , ull y = PRIME-2, ull m = PRIME) {
	if (y == 0) return 1;
	ll p = power (x,y/2,m) % m;
	p = (p * p) % m;

	return (y%2 == 0) ? p : (x*p) % m;
}

ll modInverse (ll a, ll m = PRIME){

	if (gcd (a,m) != 1){
		cout << "Inverso nao existe!!" << endl;
		return 0;
	}
	ll ans = power(a);
	if (ans < 0) ans = (PRIME+ans);
	return ans;
}
//

//modular exp
ll pow2(ll base, ll expoente){
	ll res = 1;
	while ( expoente ) {
		if ( expoente & 1 ) res = (res*base) % PRIME;
		expoente >>= 1;
		base = (base*base) % PRIME;
	}
	return res;
}

/*Lagrange interpolation to find the key distribution over the polynomial f(x).
 f(0) is the key value in point x=0.
 */
ll keySharedJoin (int start , int finish, ll numShares) {
	//SUM
	ll sum = 0;
	for (int i = start; i < finish; ++i ){
		ll num = 1;
		ll den = 1;

		//Multiplication
		for (int j = start; j < finish; ++j) {
			if (i == j) continue;

			num = (num * x[j]) % PRIME;
			ll expr = (x[j] - x[i]) >= 0 ? (x[j] - x[i]) : PRIME + (x[j] - x[i]);
			den = (den * (expr)) % PRIME;
		}
		sum = (sum + PRIME + y[i] * num * modInverse(den)) % PRIME;
	}
	return sum;
}

//Lagrange method to distribute the key around the point x, method returns f(x)
ll keySharedDistOverX (ll valX, ll numShares) {

	//Sum
	ll sum = 0;
	for (int i = 0; i < numShares; ++i ){
		ll num = 1;
		ll den = 1;

		//Multiplication
		for (int j = 0; j < numShares; ++j) {
			if (i == j) continue;
			ll expr = valX - x[j];
			expr = expr >= 0 ? expr : PRIME + expr;
			num = (num * expr) % PRIME;
			expr = (x[j] - x[i]) >= 0 ? (x[j] - x[i]) : PRIME + (x[j] - x[i]);
			den = (den * (expr)) % PRIME;
		}
		sum = (sum + PRIME + y[i] * num *  modInverse(den)) % PRIME;
	}
	return sum;
	
}

int main () {
	ll t = 5, w = 10, start, finish, key, x = 10000;
	/*Is well know that is necessary to choose at least t-1 random points from x's and y's sets.
	For this kind of problem I defined the interval as : [a , b].
	*/
	START: cout << "Choose the start and end values, such that (end-start) >= 5 and end<=10" << endl;
	cin >> start >> finish ;
	if (finish - start >= 5 && finish <= 10) {
		key = keySharedJoin (start,finish, t);
		cout << "The key value is: " << key << endl;
	}else{
		cout << "Choose other value to follow the conditions." << endl;
		goto START;
	}

	cout << "For x = 10000, the value of f(x) is: "<< keySharedDistOverX(x,t) << endl;
	return 0;
}
