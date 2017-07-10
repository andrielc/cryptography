#include <iostream>
#include <cstring>
#define ll long long

//Prime number for the module value
#define PRIME 21383

using namespace std;

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

string discreteLogGenerator(ll k, ll l, ll x_0 = 15888, ll prime = PRIME){
	ll alfa = 5;
	string ans = "";
	prime >>= 1;
	for(int i = 1; i <= l; ++i){
		ll x = pow2(alfa,x_0) % PRIME;
		if (x > prime)
			ans += "1";
		else {
			ans += "0";
		}
		x_0 = x;
	}
	return ans;
}

int main () {
	string ans =  discreteLogGenerator(0,100);

	cout << "The first 100 bits generated are:"<< endl << ans << endl;
	return 0;
}