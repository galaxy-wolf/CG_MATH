#include "vector3.h"
#include <iostream>
#include <string>
#include <time.h>
using namespace std;
using namespace CG_MATH;

void print(string msg, const vector3 &v)
{
	cout << msg << ' ' << v.x <<' ' << v.y <<' ' << v.z << endl;
}

int main()
{
	{
		cout << endl << "case 1" << endl;
		vector3 a=kZeroVector;
		print("a", a);
	}
	
	{
		cout << endl << "case 2" << endl;
		vector3 a(1.0f, 1.0f, 1.0f);
		print("a is ", a);
		vector3 b = a;
		print("b is ", b);
		cout << "a==b" <<' '<< (a == b) << endl;
		cout << "a!=b" <<' '<< (a != b) << endl;
		a.zero();
		print("a is ", a);
		print("-b is ", -b);
	}
	
	{
		cout << endl << "case 3" << endl;
		vector3 a(10.0f, 5.0f, 1.0f);
		vector3 b(1.0f, 3.0f, 10.0f);
		print("a", a);
		print("b", b);
		print("a+b:", a + b);
		print("a-b:", a - b);
		print("a/5:", a / 5);
		print("a*5:", a * 5);
		print("5*a:", 5*a);
		a += b;
		print("a+=b", a);
		a -= b;
		print("a-=b", a);
		a *= 5;
		print("a*=5", a);
		a /= 5;
		print("a/=5", a);
		cout << endl << "case 4" << endl;
		cout << "a*b " << a*b<<endl;
		a.normalize();
		print("a.normalize", a);
		cout << "mag(a) " << vectorMag(a) << endl;
		cout << endl << "case 5" << endl;
		vector3 axb = cross(a, b);
		cout<<"a*(axb): "<< a*axb<<endl;
		cout << "b*(axb): " << b*axb << endl;
		cout << endl << "case 6 " << endl;
		a = vector3(1.0f, 0, 0);
		b = vector3(0, 1.0f, 1.0f);
		cout <<"distance of a, b is " <<distance(a, b) << endl;
	}


	cout << "performance test" << endl;
	double start, end, cost;
	start = clock();
	for (int i = 0; i < (1 << 25); ++i)
	{
		vector3 a(1.0f, 3.0f, 5.0f);
		a /= 7.0f;
	}
	end = clock();
	cost = end - start;
	cout << cost << endl;
	return 0;
}