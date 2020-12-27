#include<TFormula.h>
/*
void TFormula::LexicalAnalysis(ICollection<Lexem*>* q)
{
    string st;
    State state = q0;
    inpFormula += " ";
    int n = inpFormula.length();
    char c;

    for (int i = 0; i < n;i++)
    {
        c = inpFormula[i];
        if (state == q0)
        {
            st = c;
            if ((c >= '0') && (c <= '9'))
            {
                state = q2;
            }
            else if (c == '-')
            {
                q->push(new Lexem{st, UNARYOP});
            }
            else if (c == '(')
            {
                q->push(new Lexem{st, LP});
            }
            else if (c == ')')
            {
                state = q2;
                q->push(new Lexem{st, RP});
            }
            else if (c == ' ') {}
            else
            {
                throw logic_error("arithmetic_expression_is_invalid(LexAnalysis)");
            }
            continue;
        }
        if (state == q1)
        {
            st = c;
            if ((c >= '0') && (c <= '9'))
            {
                state = q2;
            }
            else if ((c == '+') || (c == '-') || (c == '*') || (c == '/'))
            {
                q->push(new Lexem{st, BINARYOP});
            }
            else if (c == '(')
            {
                state = q0;
                q->push(new Lexem{st, LP});
            }
            else if (c == ')')
            {
                state = q1;
                q->push(new Lexem{st, RP});
            }
            else if (c == ' ') {}
            else
            {
                throw logic_error("arithmetic_expression_is_invalid(LexAnalysis)");
            }
            continue;
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
                q->push(new Lexem{st, VALUE, v});
                state = q1;
                st = c;
                if ((c == '+') || (c == '-') || (c == '*') || (c == '/'))
                {
                    q->push(new Lexem{st, BINARYOP});
                }
                else if (c == '(')
                {
                    q->push(new Lexem{st, LP});
                }
                else if (c == ')')
                {
                    state = q1;
                    q->push(new Lexem{st, RP});
                }
                else if (c == ' ') {}
                else
                {
                    throw logic_error("arithmetic_expression_is_invalid(LexAnalysis)");
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
     
    while(!qI->isEmpty())
    {
        Lexem *l = qI->pop();
        if (qI->isEmpty()) state = q3;
        if (state == q0){
            if (l->te == LP) {
                k++;
                state = q0;
            }
            if ((l->te == VALUE)) {
                state = q1;
            }
            if ((l->te == UNARYOP)) {
                state = q2;
            }
            if ((l->te == RP) || (l->te == BINARYOP)) {
                throw logic_error("arithmetic_expression_is_invalid(SynAnalysis)");
            }
            qO->push(l);
            continue;
        }
        if (state == q1){
            if (l->te == RP) {
                k--;
                if (k < 0)  throw logic_error("arithmetic_expression_is_invalid(SynAnalysis)");
            }
            if ((l->te == BINARYOP)) {
                state = q2;
            }
            if ((l->te == LP)|| (l->te == UNARYOP) || (l->te == VALUE)) {
                throw logic_error("arithmetic_expression_is_invalid(SynAnalysis)");
            }
            qO->push(l);
            continue;
        }
        if (state == q2){
            if (l->te == LP) {
                k++;
                state = q0;
            }
            if ((l->te == VALUE)) {
                state = q1;
            }
            if ((l->te == RP) || (l->te == BINARYOP) || (l->te == UNARYOP)) {
                throw logic_error("arithmetic_expression_is_invalid(SynAnalysis)");
            }
            qO->push(l);
            continue;
        }
        if (state == q3){
            if (l->te == RP) {
                k--;
                if (k < 0)  throw logic_error("arithmetic_expression_is_invalid(SynAnalysis)");
            }
            if ((l->te == VALUE)) {
            }
            if ((l->te == LP) || (l->te == BINARYOP) || (l->te == UNARYOP)) {
                throw logic_error("arithmetic_expression_is_invalid(SynAnalysis)");
            }
            qO->push(l);
        }
    }
    if (k != 0)  throw logic_error("arithmetic_expression_is_invalid(SynAnalysis)");
}

TFormula::TFormula()
{
	isReadyOutFormula = false;
    inpFormula = "";
    outFormula = "";
    qRevPolNot = new Queue<Lexem*>(maxSizeCollection);
}

TFormula::TFormula(const string& str)
{
    if (str.length() == 0) throw logic_error("string_length_is_zero");
	inpFormula = str;
    outFormula = "";
	isReadyOutFormula = false;
    qRevPolNot = new Queue<Lexem*>(maxSizeCollection);
}

void TFormula::init(const string& str)
{
    if (str.length() == 0) throw logic_error("string_length_is_zero");
	inpFormula = str;
    outFormula = "";
	isReadyOutFormula = false;
    while(!qRevPolNot->isEmpty())
    {
        qRevPolNot->pop();
    }
}

const string& TFormula::getInpFormula() const
{
	return inpFormula;
}

const string& TFormula::getOutFormula() const
{
    if (!isReadyOutFormula) throw logic_error("the_output_formula_is_not_ready");
	return outFormula;
}

void TFormula::conversToRevPolNot()
{
    if (inpFormula.length() == 0) throw logic_error("string_is_not_initialized");
    ICollection<Lexem*>* q = new Queue<Lexem*>(maxSizeCollection);
    LexicalAnalysis(q);

    //while(!q->isEmpty())
    //{
    //    Lexem* l = q->pop();
    //    cout << l->s << " " << l->te << " " << l->val << endl;
    //}

    ICollection<Lexem*>* qN = new Queue<Lexem*>(maxSizeCollection);
    SyntacticAnalysis(q, qN);

    //while(!qN->isEmpty())
    //{
    //    Lexem* l = qN->pop();
    //    cout << l->s << " " << l->te << " " << l->val << endl;
    //}

    State state;
    state = q0;

    ICollection<Lexem*>* s = new Stack<Lexem*>(maxSizeCollection);
    while (!qN->isEmpty())
    {
        Lexem *l = qN->pop();
        if ((l->te == LP) || (l->te == UNARYOP)) {
            s->push(l);
        }
        if ((l->te == VALUE)) {
            qRevPolNot->push(l);
            outFormula += l->s;
            outFormula += " "; 
        }
        if ((l->te == RP)) {
            while (!s->isEmpty()){
                l = s->pop();
                if (l->te != LP){
                    qRevPolNot->push(l);
                    outFormula += l->s;
                }
                else
                {
                    break;
                }
            }
        }
        if ((l->te == BINARYOP)) {
            Lexem* l1;
            if ((l->s == "+")||(l->s == "-"))
            {
                while(!s->isEmpty())
                {
                    l1 = s->pop();
                    if ((l1->te == BINARYOP) || (l1->te == UNARYOP)){
                        qRevPolNot->push(l1);
                        outFormula += l1->s;
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
                while(!s->isEmpty())
                {
                    l1 = s->pop();
                    if (l1->te == BINARYOP){
                        if ((l1->s == "*")||(l1->s == "/")){
                            qRevPolNot->push(l1);
                            outFormula += l1->s;
                        }
                        else
                        {
                            s->push(l1);
                            break;
                        }
                        
                    }
                    else if (l1->te == UNARYOP) {
                        qRevPolNot->push(l1);
                        outFormula += l1->s;
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
    while(!s->isEmpty())
    {
        l = s->pop();
        qRevPolNot->push(l);
        outFormula += l->s;
    }
    isReadyOutFormula = true;
	delete q;
	delete qN;
	delete s;
}

int TFormula::calcArithmExp()
{
    if (!isReadyOutFormula) throw logic_error("the_output_formula_is_not_ready");
    ICollection<Lexem*>* s = new Stack<Lexem*>(maxSizeCollection);
    Lexem *l;
    while(!qRevPolNot->isEmpty())
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
            s->push(new Lexem{to_string(k),VALUE, k});
        }
        if (l->te == BINARYOP)
        {
            Lexem* l1;
            Lexem* l2;
            int k;
            if (l->s == "+")
            {
                l1 = s->pop();
                l2 = s->pop();
                k = l1->val + l2->val;
                s->push(new Lexem{to_string(k),VALUE, k});
            }
            if (l->s == "-")
            {
                l1 = s->pop();
                l2 = s->pop();
                k = l2->val - l1->val;
                s->push(new Lexem{to_string(k),VALUE, k});
            }
            if (l->s == "*")
            {
                l1 = s->pop();
                l2 = s->pop();
                k = l2->val * l1->val;
                s->push(new Lexem{to_string(k),VALUE, k});
            }
            if (l->s == "/")
            {
                l1 = s->pop();
                l2 = s->pop();
                k = l2->val / l1->val;
                s->push(new Lexem{to_string(k),VALUE, k});
            }
        }
    }
	int ans = s->pop()->val;
	delete s;
	return ans;
}*/