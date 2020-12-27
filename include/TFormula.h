#pragma once

#include<iostream>
#include<string>
#include<Collection.h>

using namespace std;

const int MaxSizeCollection = 1000;

enum TypeElem {VALUE, UNARYOP, BINARYOP, LP, RP};
enum State {q0, q1, q2, q3};

struct Lexem {
	string s;
	TypeElem te;
    int val = -1;
};

class TFormula {
	string InpFormula;
	string OutFormula;
	bool isReadyOutFormula;

	ICollection<Lexem*>* qRevPolNot;

    void LexicalAnalysis(ICollection<Lexem*>* q);
	void SyntacticAnalysis(ICollection<Lexem*>* qI, ICollection<Lexem*>* qO);
public:
	TFormula();
	TFormula(const string& str);

	void init(const string& str);

	const string& getInpFormula() const;
	const string& getOutFormula() const;

	void conversToRevPolNot();
	int calcArithmExp();
};


void TFormula::LexicalAnalysis(ICollection<Lexem*>* q)
{
	string st;
	State state = q0;
	InpFormula += " ";
	int n = InpFormula.length();
	char c;

	for (int i = 0; i < n; i++)
	{
		c = InpFormula[i];
		if (state == q0)
		{
			st = c;
			switch (c) {
			case(('0') || ('1') || ('2') || ('3') || ('4') || ('5') || ('6') || ('7') || ('8') || ('9')):
				state = q2;
				continue;
			case('-'):
				q->push(new Lexem{ st, UNARYOP });
				continue;
			case('('):
				q->push(new Lexem{ st, LP });
				continue;
			case(')'):
				state = q2;
				q->push(new Lexem{ st, RP });
				continue;
			case(' '):
				continue;

			default:
				throw logic_error("Calculator_expression_is_invalid");
				continue;
			}
		}
		if (state == q1)
		{
			st = c;
			switch (c) {
				case(('0') || ('1') || ('2') || ('3') || ('4') || ('5') || ('6') || ('7') || ('8') || ('9')):
					state = q2;
					continue;
				case(('+') || ('-') || ('*') || ('/')):
					q->push(new Lexem{ st, BINARYOP });
					continue;
				case('('):
					state = q0;
					q->push(new Lexem{ st, LP });
					continue;
				case(')'):
					state = q1;
					q->push(new Lexem{ st, RP });
					continue;
				case(' '):
					continue;

				default:
					throw logic_error("Calculator_expression_is_invalid");
				continue;
			}
		}
		if (state == q2)
		{
			
			if ((c >= '0') && (c <= '9'))
			{
				st += c;
				state = q2;
			}
			else
			{

				int v = atoi(st.c_str());
				q->push(new Lexem{ st, VALUE, v });
				state = q1;
				st = c;
				switch (c) {
				case(('+') || ('-') || ('*') || ('/')):
					q->push(new Lexem{ st, BINARYOP });
					continue;
				case('('):
					q->push(new Lexem{ st, LP });
					continue;
				case(')'):
					q->push(new Lexem{ st, RP });
					continue;
				case(' '):
					continue;
				default:
					throw logic_error("Calculator_expression_is_invalid");
					continue;
				}
			}
		}
	}
}

void TFormula::SyntacticAnalysis(ICollection<Lexem*>* qI, ICollection<Lexem*>* qO)
{
	State state;
	state = q0;
	int k = 0;

	while (!qI->IsEmpty())
	{
		Lexem *l = qI->pop();
		if (qI->IsEmpty()) state = q3;
		if (state == q0) {
			switch(l->te){
			case(LP): {
				k++;
				state = q0;
			}
			case(VALUE):
				state = q1;
			case(UNARYOP):
				state = q2;
			case((RP) || (BINARYOP)):
				throw logic_error("Calc_expression_is_invalid");
			default:
				qO->push(l);
				continue;
			}
		}
		if (state == q1) {
			switch (l->te) {
			case(BINARYOP):
				state = q2;
			case(RP): {
				k--;
				if (k < 0)  throw logic_error("Calc_expression_is_invalid");
			}
			case((RP) || (UNARYOP) || (VALUE)):
				throw logic_error("Calc_expression_is_invalid");
			default:
				qO->push(l);
				continue;
		}
		if (state == q2) {
			switch (l->te) {
			case(LP): {
				k++;
				state = q0;
			}
			case(VALUE):
				state = q1;
			case((RP) || (BINARYOP) || (UNARYOP)):
				throw logic_error("Calc_expression_is_invalid");
			default:
				qO->push(l);
				continue;
			}
		}
		if (state == q3) {
			switch (l->te) {
			case(RP): {
				k--;
				if (k < 0)  throw logic_error("Calc_expression_is_invalid");
			}
			case((LP) || (BINARYOP) || (UNARYOP)):
				throw logic_error("Calc_expression_is_invalid");
			default:
				qO->push(l);
				continue;
			}
		}
	}
	if (k != 0)  throw logic_error("Calc_expression_is_invalid");
}

TFormula::TFormula()
{
	isReadyOutFormula = false;
	InpFormula = "";
	OutFormula = "";
	qRevPolNot = new Queue<Lexem*>(MaxSizeCollection);
}

TFormula::TFormula(const string& str)
{
	if (str.length() == 0) throw logic_error("String_length_is_zero");
	InpFormula = str;
	OutFormula = "";
	isReadyOutFormula = false;
	qRevPolNot = new Queue<Lexem*>(MaxSizeCollection);
}

void TFormula::init(const string& str)
{
	if (str.length() == 0) throw logic_error("String_length_is_zero");
	InpFormula = str;
	OutFormula = "";
	isReadyOutFormula = false;
	while (!qRevPolNot->IsEmpty())
	{
		qRevPolNot->pop();
	}
}

const string& TFormula::getInpFormula() const
{
	return InpFormula;
}

const string& TFormula::getOutFormula() const
{
	if (!isReadyOutFormula) throw logic_error("The_output_formula_is_not_ready");
	return OutFormula;
}

void TFormula::conversToRevPolNot()
{
	if (InpFormula.length() == 0) throw logic_error("String_is_not_initialized");
	ICollection<Lexem*>* q = new Queue<Lexem*>(MaxSizeCollection);
	LexicalAnalysis(q);

	ICollection<Lexem*>* qN = new Queue<Lexem*>(MaxSizeCollection);
	SyntacticAnalysis(q, qN);



	State state;
	state = q0;

	ICollection<Lexem*>* s = new Stack<Lexem*>(MaxSizeCollection);
	while (!qN->IsEmpty())
	{
		Lexem *l = qN->pop();
		if ((l->te == LP) || (l->te == UNARYOP)) {
			s->push(l);
		}
		if ((l->te == VALUE)) {
			qRevPolNot->push(l);
			OutFormula += l->s;
			OutFormula += " ";
		}
		if ((l->te == RP)) {
			while (!s->IsEmpty()) {
				l = s->pop();
				if (l->te != LP) {
					qRevPolNot->push(l);
					OutFormula += l->s;
				}
				else
				{
					break;
				}
			}
		}
		if ((l->te == BINARYOP)) {
			Lexem* l1;
			if ((l->s == "+") || (l->s == "-"))
			{
				while (!s->IsEmpty())
				{
					l1 = s->pop();
					if ((l1->te == BINARYOP) || (l1->te == UNARYOP)) {
						qRevPolNot->push(l1);
						OutFormula += l1->s;
					}
					else
					{
						s->push(l1);
						break;
					}
				}
			}
			else
			{
				while (!s->IsEmpty())
				{
					l1 = s->pop();
					if (l1->te == BINARYOP) {
						if ((l1->s == "*") || (l1->s == "/")) {
							qRevPolNot->push(l1);
							OutFormula += l1->s;
						}
						else
						{
							s->push(l1);
							break;
						}

					}
					else if (l1->te == UNARYOP) {
						qRevPolNot->push(l1);
						OutFormula += l1->s;
					}
					else
					{
						s->push(l1);
						break;
					}
				}
			}
			s->push(l);
		}
	}
	Lexem *l;
	while (!s->IsEmpty())
	{
		l = s->pop();
		qRevPolNot->push(l);
		OutFormula += l->s;
	}
	isReadyOutFormula = true;
	delete q;
	delete qN;
	delete s;
}

int TFormula::calcArithmExp()
{
	if (!isReadyOutFormula) throw logic_error("The_output_formula_is_not_ready");
	ICollection<Lexem*>* s = new Stack<Lexem*>(MaxSizeCollection);
	Lexem *l;
	while (!qRevPolNot->IsEmpty())
	{
		l = qRevPolNot->pop();
		if (l->te == VALUE)
		{
			s->push(l);
		}
		if (l->te == UNARYOP)
		{
			Lexem* l;
			int k;
			l = s->pop();
			k = -l->val;
			s->push(new Lexem{ to_string(k),VALUE, k });
		}
		if (l->te == BINARYOP)
		{
			Lexem* l1;
			Lexem* l2;
			int k;

			switch(l->s){
			case("+"):
			{
				l1 = s->pop();
				l2 = s->pop();
				k = l1->val + l2->val;
				s->push(new Lexem{ to_string(k),VALUE, k });
			}
			case("-"):
			{
				l1 = s->pop();
				l2 = s->pop();
				k = l2->val - l1->val;
				s->push(new Lexem{ to_string(k),VALUE, k });
			}
			case("*"):
			{
				l1 = s->pop();
				l2 = s->pop();
				k = l2->val * l1->val;
				s->push(new Lexem{ to_string(k),VALUE, k });
			}
			case("/"):
			{
				l1 = s->pop();
				l2 = s->pop();
				k = l2->val / l1->val;
				s->push(new Lexem{ to_string(k),VALUE, k });
			}
			default:
				continue;
		}
	}
	int ans = s->pop()->val;
	delete s;
	return ans;
}