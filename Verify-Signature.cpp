/*
Aluno: Andriel Carlos de Souza Biagioni
RA: 189935
Ex 3ac
*/
#include <iostream>

#define ll long long
#define ull unsigned long long

//Prime number for the module value
#define PRIME 2357

using namespace std;

//Structure for the signature values
struct Values {
	ll gama;
	ll delta;
};

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

Values signature(ll message, ll randomNumber){
	
	Values out;
	ll alfa = 2;
	ll key = 1751;
	out.gama = pow2(alfa,randomNumber) % PRIME;
	out.delta = ( (key * out.gama) % (PRIME -1) + (randomNumber * message) %(PRIME -1) ) % (PRIME-1);
	return out;
}

bool verifySignature(ll message, Values s, ll alfa, ll beta, ll prime) {
	/*
	beta = alfa^x mod p
	gama = alfa^k mod p
	(1) delta = x*gama + k*m mod(p-1)
	Exponnential of (1) in alfa and using Fermat Theorem:
	alfa^delta = alfa^(x*gama) * alfa^(k*m) mod (p)
	alfa^delta == ( beta^gama mod p * gama^m mod p ) mod (p)
	*/
	
	ll var1 = pow2(alfa,s.delta);
	ll var2 = pow2(beta, s.gama) % prime;
	 
	ll var3 = pow2(s.gama,message) % prime;
	
	ll var4 = (var2 * var3) % (prime);

	if (var1 == var4) return true;
	else return false;
}

int main () {
	ll alfa = 2, beta = 1185, message = 1468, randomNumber = 1529;

	Values var = signature(message, randomNumber);
	cout <<"Gama Value " << var.gama << ", Delta value " <<var.delta << endl;
	if (verifySignature (message, var, alfa, beta, PRIME) ) {
		cout << "Signature valid for " << var.gama << " " << var.delta << endl;
	}else{
		cout << "Signature not valid" << endl;
	}
	return 0;
}