//g++ -g -o2 -std=c++11 -pthread -march=native cr1.cpp -o cr1 -lntl -lgmp -lm -I/home/nastyan/NTL/sw/include -L/home/nastyan/NTL/sw/lib

#include "NTL/ZZ.h"
#include <iostream>
#include <cstdlib>
NTL::ZZ f_euler(NTL::ZZ n)
{
using NTL::ZZ;
using NTL::conv;
  ZZ i, m;
  m=conv<ZZ>("1");
  for (i=2; i <= n/2; i++)
      if (n % i == 0)
         {
         n/=i;
         while (n % i == 0)
           {
             m*=i;
             n/=i;
             }
         if (n==1) return m*(i-1);
         else return m*(i-1)*f_euler(n);
         }
  return n-1;
}
int main()
{
using std::cout;
using std::cin;
using std::endl;
using namespace NTL;
ZZ a, b, m, x, phi, A, B, r, c, re;
int w;
w=1;
cout << "Введіть модуль m: ";
cin >> m;

	while (w==1){
		int ch;
		cout << "\nОберіть пункт з меню:" << endl;
		cout << "1. Подивитись модуль обчислень m" << endl;
		cout << "2. Розв’язати рівняння виду  a mod m = x" << endl;
		cout << "3. Розв’язати рівняння виду a^b mod m = x" << endl;
		cout << "4. Розв’язати рівняння виду  a*x ≡ b mod m" << endl;
		cout << "5. Згенерувати просте число у діапазоні від A до B." << endl;
		cout << "6. Вихід" << endl;
		cin >> ch;
		switch (ch){
			case 1:
				cout << "Модуль обчислень m = " << m << endl;
				break;
			case 2:
				cout << "Введіть a: ";
				cin >> a;
				cout << "a mod m = " << a%m << endl;
				break;
			case 3:
				cout << "Введіть a: ";
				cin >> a;
				cout << "Введіть b: ";
				cin >> b;
				x=PowerMod(a,b,m);
				cout << "a^b mod m = " << x << endl;
				break;
			case 4:
				cout << "Введіть a: ";
				cin >> a;
				cout << "Введіть b: ";
				cin >> b;
				if (GCD(a,m)!=1){
					a/=GCD(a,m);
					m/=GCD(a,m);
				}
				phi = f_euler(m);
				x=MulMod(PowerMod(a,(phi-1),m),b,m);
				cout << "x = " << x << endl;
				break;
			case 5:
				cout << "Введіть A: ";
				cin >> A;
				cout << "Введіть B: ";
				cin >> B;
				if (A>B){
					c=A;
					A=B;
					B=c;
				}
				r=RandomBnd(B);
				c=NextPrime(r%A+A);
				if (NextPrime(A+1)>=B) {cout << "В заданому діапазоні нема простих чисел!" << endl;}
				else {
					while (c>=B){
						r=RandomBnd(B);
						c=NextPrime((r)%A+A);
					}
					cout << "Просте число у діапазоні від A до B - " << c << endl;
				}
				break;
			case 6:
				w--;
				break;
		}
	}
return 0;
}
