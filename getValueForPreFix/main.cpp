/************************
 *                      *
 *   求前缀表达式的值   *
 *  （操作数的值＜10）  *
 ************************/
#define _CRT_NONSTDC_NO_DEPRECATE
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

int getPriority(char op);
int calSub(float opnd1, char op, float opnd2, float &result);
int calStackTopTwo(float s1[], int &top1, char s2[], int &top2);
float calPreFix(char exp[],int len);

const float MIN = 1e-35;
const int maxSize = 1000;

int main()
{
	char exp[maxSize];
	cin >> exp;
	cout << calPreFix(exp,strlen(exp)) << endl;
	return 0;
}

int getPriority(char op)
{
	if (op == '+' || op == '-')
		return 0;
	else
		return 1;
}

int calSub(float opnd1, char op, float opnd2, float &result)
{
	switch (op)
	{
	case '+':
		result = opnd1 + opnd2;
		break;
	case '-':
		result = opnd1 - opnd2;
		break;
	case '*':
		result = opnd1 * opnd2;
		break;
	case '/':
		if (fabs(opnd2) < MIN)
			return 0;
		else
			result = opnd1 / opnd2;
		break;
	default:
		break;
	}
	return 1;
}

int calStackTopTwo(float s1[], int &top1, char s2[], int &top2)
{
	float opnd1, opnd2, result;
	char op;
	int flag;
	opnd2 = s1[top1--];
	opnd1 = s1[top1--];
	op = s2[top2--];
	flag = calSub(opnd1, op, opnd2, result);
	if (!flag)
		cout << "error" << endl;
	s1[++top1] = result;
	return flag;
}

float calPreFix(char exp[], int len)
{
	float s[maxSize];int top = -1;
	for (int i = len - 1;i >= 0;i--)
	{
		if (exp[i] >= '0'&&exp[i] <= '9')
			s[++top] = exp[i] - '0';
		else
		{
			float opnd1, opnd2, result;
			char op;
			int flag;
			opnd1 = s[top--];
			opnd2 = s[top--];
			op = exp[i];
			flag = calSub(opnd1, op, opnd2, result);
			if (!flag)
			{
				cout << "error" << endl;
				break;
			}
			s[++top] = result;
		}
	}
	return s[top];
}