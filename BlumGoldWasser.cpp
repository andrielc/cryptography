#include <iostream>
#include <cstring>
#define ll long long
#define ull unsigned long long

//Prime number for the module value
#define N 192649
#define P 383
#define Q 503

using namespace std;


ll gcd (ll a, ll b) {
	if (a == 0) return b;
	return gcd (b%a,a);
}

ll lcm (ll a, ll b){
	ll temp = gcd (a,b);
	return temp ? ( a/temp * b ) : 0;
}

ll power (ll x , ull y, ull m) {
	if (y == 0) return 1;
	ll p = power (x,y/2,m) % m;
	p = (p * p) % m;

	return (y%2 == 0) ? p : (x*p) % m;
}

ll modInverse (ll a, ll m){

	if (gcd (a,m) != 1){
		cout << "Inverse does not exist!!" << endl;
		return 0;
	}
	ll ans = power (a,m-2,m);
	if (ans < 0) ans = (m+ans);
	return  ans;
}

//remainder chinese theorem
ll remainderChinesTheorem(ll b1, ll b2,ll p = P, ll q = Q)
{
    ll ans = ((b1*modInverse(q,p)*Q)%N + (b2*modInverse(p,q)*P)%N)%N;
    return ans;
}

//exponenciacao modular
ll pow2(ll base, ll expoente,ll mod){
	ll res = 1;
	while ( expoente ) {
		if ( expoente & 1 ) res = (res*base) % mod;
		expoente >>= 1;
		base = (base*base) % mod;
	}
	return res;
}

//
string BBSG(ll l,ll s){
	//Step 1 of BlumGoldwasser encrypt algorithm
	string ans = "";
	for(int i = 1; i <= l; ++i){
		ll aux = pow2(s,2,N) % N;
		if (aux % 2) ans += "1";
		else ans += "0";
		s = aux;
	}
	return ans;
}

string blumGoldwasserEnc(ll l, string plainText ,ll s_0=20749){
	//Passo 2 do Algoritmo BlumGoldwasser
	//From Euler theorem: lambda(M) = lambda(p*q) = lcm (p-1,q-1)
	ll aux = (1 << (l+1)) % lcm (P-1,Q-1);
	ll snext = pow2 (s_0,aux, N) % N;
	//Step 3
	string cript = "";
	string z = BBSG(l,s_0);
	for (int i = 0; i < l; ++i){
		if ( plainText[i] == z[i] )
			cript+="0";
		else cript+= "1";
	}
	//Add delimitator ":" between l and l+1 bits
	cript += (":"+to_string(snext));
	return cript;
}

string blumGoldwasserDec(string cript){
	string plainText = "";
	ll tam = cript.size();
	//Step 1 Decrypt Algorithm
	ll t = cript.find(':'); //l
	ll a1 = pow2((P+1)/4, t+1,P-1) % (P-1);
	//Step 2
	ll a2 = pow2((Q+1)/4, t+1,Q-1) % (Q-1);
	//Step 3
	cout << "a1= " << a1 << " a2= " << a2 << endl;
	ll snext = stoll(cript.substr(t+1,tam));
	cout << "snext = " << snext << endl;
	ll b1 = pow2(snext,a1,P) % P;
	//Step 4
	ll b2 = pow2(snext,a2,Q) % Q;
	//Chinese theorem remainder
	cout << "b1= " << b1 <<" b2= " << b2 << endl;
	ll r = remainderChinesTheorem(b1,b2);
	cout << "s_0 = r = " <<r << endl;
	string z = BBSG(t, r);
	//Plaintext
	ll len = z.size();
	for (int i = 0; i < len; ++i){
		if ( cript[i] == z[i] )
			plainText+="0";
		else plainText+= "1";
	}
	return plainText;
}

int main () {
	ll l = 20;
	string plainText = "10011000011110011111";
	string ans1 = blumGoldwasserEnc (l,plainText);
	string ans2 = blumGoldwasserDec ( ans1 );
	cout << "plainText " << plainText << endl;
	cout << "encriptado " << ans1 << endl;
	cout << "descriptado " << ans2 << endl;
	return 0;
}