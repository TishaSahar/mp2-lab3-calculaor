#pragma once

#include<iostream>
#include<string>
#include<Collection.h>


using namespace std;

class FirstAnalytics {
	string in;
public:
	FirstAnalytics(string _s) {
		in = _s;
	}


	void del_space() {
		string temp;
		int k = 0;
		for (int i = 0; i < in.length(); i++) {
			if (in[i] != ' ')
			{
				temp[k] = in[i];
				k++;
			}
		}
		in = temp;
	}

	string LexicalAnalytics() {
		string res = "";
		int nOpen = 0;
		int nOper = 0;
		this->del_space();
		for (int i = 0; i < in.length(); i++) {
			switch (in[i]) {
			case('('): {
				nOpen++;
				if (nOper > 0)nOper--;
				continue;
			}
			case(')'): {
				nOpen--;
				if (nOpen < 0) {
					throw logic_error("Lexic error ()))"); break;
				}
				continue;
			}
			case('+'): {
				nOper++;
				if (nOper > 1) {
					throw logic_error("Lexic error +-");
				}
				continue;
			}
			case('-'): {
				nOper++;
				if (nOper > 1) {
					throw logic_error("Lexic error +-");
				}
				continue;
			}
			case('*'): {
				nOper++;
				if (nOper > 1) {
					throw logic_error("Lexic error +-");
				}
				continue;
			}
			case('/'): {
				nOper++;
				if (nOper > 1) {
					throw logic_error("Lexic error +-");
				}
				continue;
			}
			default:
				continue;
			}

		}
	};



	class SecondAnalytics {
		string in;
		int priority;

	public:
		Queue<string> SQ;
		Stack<char> SO;

		SecondAnalytics(string _in) {
			in = _in;
			priority = 0;
		}
		void out() {
			cout << SQ.pop() << ' ';
			cout << endl;
		}
		int Priority(char c) {
			switch (c) {
			case('+'): {
				return 1 + priority;
			}
			case('-'): {
				return 1 + priority;
			}
			case('*'): {
				return 2 + priority;
			}
			case('/'): {
				return 2 + priority;
			}
			default:
				break;
			}
		}

		void Analytics() {
			int i = 0;
			string temp = { "" };
			char op1;

			while (i < in.length()) {
				while ((in[i] >= '0') && (in[i] <= '9')) {
					temp += in[i];
					i++;
				}
				if (in[i] == '(') {
					priority += 2;
					SO.push(in[i]);
					i++;
					continue;
				}
				else {
					while (!SO.IsEmpty()) {
						op1 = SO.pop();
						if (in[i] == ')') {
							priority -= 2;
							op1 = SO.pop();
							while (op1 != '(') {
								temp = op1;
								if (temp != ")")
									SQ.push(temp);
								op1 = SO.pop();
							}
							op1 = SO.pop();

							if (op1 == '^') {
								temp = op1;
								SQ.push(temp);
							}
							else {
								SO.push(op1);
								break;
							}
						}
						if (Priority(in[i]) >= Priority(op1)) {
							temp = op1;
							cout << temp << ' ';
							SQ.push(temp);
							temp = "";
							continue;
						}
						else {
							SO.push(in[i]);
							SO.push(op1);
							break;
						}
					}
				}
				i++;
			}
			return;
		}
	}
};