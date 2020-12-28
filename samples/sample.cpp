#include<iostream>
#include<string>
#include<TFormula.h>
#include<Collection.h>

using namespace std;

int main()
{
	string s = { "1+2*3" };
	SecondAnalytics A(s);

	A.Analytics();
	A.out();
	system("pause");
	return 0;
}