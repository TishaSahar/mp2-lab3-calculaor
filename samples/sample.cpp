#include<iostream>
#include<string>
#include<TFormula.h>
#include<Collection.h>

using namespace std;
/*
int main()
{
	TFormula f;
	//string str = "(1+2*(4+25))+(45*34/(13+4))";
	//string str = "(145+22*450/(41 + 49))*(45/9)+3947";
	string str;
	string strOut;

	cout << "Program for translation to Reverse Polish notation\n";
	cout << "(To finish enter \"exit\")\n";

	while (true)
	{
		try
		{
			cout << "Please enter a string: ";
			getline(cin, str);
			if (str == "exit") break;
			f.init(str);
			f.conversToRevPolNot();
			strOut = f.getOutFormula();
			cout << "Reverse Polish notation: " << strOut << endl;
			int ans = f.calcArithmExp();
			cout << "Answer: " << ans << endl;
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}
	return 0;
}*/