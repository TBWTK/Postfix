#include <iostream>
#include <string>

using namespace std;

class STACK
{
public:
	STACK() {};
	~STACK() {};
	int empty()
	{
		return valueStack.empty() ? 0 : 1;
	}
	char returnPop()
	{
		char temp = valueStack[valueStack.length() - 1];
		valueStack.pop_back();
		return temp;
	}
	char checkPop()
	{
		char temp = valueStack[valueStack.length() - 1];
		return temp;
	}
	void push(char temp)
	{
		valueStack.push_back(temp);
	}
	void clear()
	{
		valueStack.clear();
	}
private:
	string valueStack;
};


class Postfix
{
public:
	Postfix(char* str);
	~Postfix();
	void display();
private:
	int size = 0;
	char* input;
	char* output;
	string algorithm();
	int prec(char c);
};

Postfix::Postfix(char* str)
{
	size = strlen(str) + 1;
	input = new char[size] {*str};
	memcpy(input, str, size);
	output = new char[size] { *str };
	memcpy(output, algorithm().c_str(), size);
}

void Postfix::display()
{
	cout << output;
}

string Postfix::algorithm()
{
	STACK stackTempVariables;
	stackTempVariables.clear();
	string tempOutput;

	for (int i = 0; i < size - 1; i++)
	{
		if (input[i] > 47 && input[i] < 58)
			tempOutput += input[i];
		else if (input[i] == '(')
			stackTempVariables.push(input[i]);
		else if (input[i] == ')')
		{
			while (stackTempVariables.empty() && stackTempVariables.checkPop() != '(')
			{
				char temp = stackTempVariables.returnPop();
				tempOutput += temp;
			}
			if (stackTempVariables.checkPop() == '(')
			{
				stackTempVariables.returnPop();
			}
		}
		else
		{
			while (stackTempVariables.empty() && prec(input[i]) <= prec(stackTempVariables.checkPop()))
			{
				char temp = stackTempVariables.returnPop();
				tempOutput += temp;
			}
			stackTempVariables.push(input[i]);
		}
	}
	while (stackTempVariables.empty())
	{
		char temp = stackTempVariables.returnPop();
		tempOutput += temp;
	}
	return tempOutput;
}

int Postfix::prec(char c)
{
	if (c == '^')
		return 3;
	else if (c == '*' || c == '/')
		return 2;
	else if (c == '+' || c == '-')
		return 1;
	else
		return -1;
}

Postfix::~Postfix()
{
	delete[] input;
	delete[] output;
}

int main()
{
	string inputExample;
	cout << "Input math example: ";
	cin >> inputExample;
	char* example = &inputExample[0];
	Postfix pst(example);
	pst.display();
	return 0;
}
