#include <iostream>
#include <string>
#include <sstream>
using namespace std;

double executeOperation(string op)
{
	istringstream instr(op);

	char operation;
	double op1, op2;
	instr >> op1 >> operation >> op2;

	double result_op;
	switch (operation)
	{
	case '+':
		result_op = op1 + op2;
		break;
	case '-':
		result_op = op1 - op2;
		break;
	case '*':
		result_op = op1 * op2;
		break;
	case '/':
		result_op = op1 / op2;
		break;
	}

	return result_op;
}

int main()
{
	string op;
	cout << "Insert a numeric operation: ";
	getline(cin, op);

	cout << "Result = " << 
		executeOperation(op) << endl;

	return 0;
}