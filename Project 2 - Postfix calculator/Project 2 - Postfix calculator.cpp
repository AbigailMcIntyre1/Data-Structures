// Abigail McIntyre
// due 9/17/2021 revised 9/20/2021 based on comments
// takes a postfix expression and evaluates it

#pragma warning(disable : 4996)		// to get rid of errors in visual studio

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const int MAXSIZE = 200;			// maximum stack size

// to store nodes with data and pointers in the linked list
struct Node
{
	double data;
	struct Node* link;

	Node()
	{
		data = 0;
		link = NULL;
	}

};

// function prototypes
bool isEmpty(Node* top);									// returns true if the stack is empty
void push(double data, Node* &top);							// puts a value on the top of the stack
double pop(Node* &top);										// takes a value off the top of the stack
void display(Node* top);									// displays the stack

int main()
{
	// create a node
	Node* top = new Node();

	char expression[MAXSIZE];								// stores the expression
	string expressionSaved;									// saves the original expression for later use
	double operand1, operand2;								// two operands to hold the values popped from the stack

	
	// get the postfix expression to evaluate
	cout << "Please enter a postfix value: ";
	cin.getline(expression, MAXSIZE + 1);
	cout << endl;
	expressionSaved = expression;							// save the expression

	// Returns first token
	char* token = strtok(expression, " \n");

	cout << "Operator Stack (top on left):" << endl << endl;

	// while there's still values in the expression
	while (token != NULL)
	{
		// number, push to stack
		if (atof(token))
		{
			push(atof(token), top);
			display(top);
			cout << endl;
		}

		// pop the top two values if an operator is the token, calculate, and then push the result to the stack
		else
		{
			operand1 = pop(top);
			operand2 = pop(top);

			if (token[0] == '+')							// if a plus is found
			{
				push(operand2 + operand1, top);
				display(top);
				cout << endl;
			}
			else if (token[0] == '-')						// if a minus is found
			{
				push(operand2 - operand1, top);
				display(top);
				cout << endl;
			}
			else if (token[0] == '*')						// if a plus is found
			{
				push(operand2 * operand1, top);
				display(top);
				cout << endl;
			}
			else											// if a divide is found
			{
				push(operand2 / operand1, top);
				display(top);
				cout << endl;
			}

		} // end else

		token = strtok(NULL, " ");

	} // end while

	// display the results
	cout << endl << "The result of " << expressionSaved << " is: " << top->data << endl << endl;
}

// ----------- functions ----------------------------------------------------------------------------------------------------------

// create a new node - add the data to the data section of the node - then set the link to the node
void push(double data, Node* &top)
{
	// create a pointer to a new node
	struct Node* ptr;
	ptr = new Node();

	// set the data for that node to the input data
	ptr->data = data;

	// set the link
	ptr->link = top;
	top = ptr;
}


// takes the top value off the stack
double pop(Node* &top)
{
	struct Node* ptr;										// make a new node
	double returnNum;										// holds the value of the top of the stack

	if (top == NULL)
	{
		cout << "Error: Stack is empty, cannot perform a pop" << endl;
	}
	else
	{
		// take the top value of the stack
		returnNum = top->data;

		// make ptr equal top
		ptr = top;

		// make top equal to the second node
		top = top->link;

		// delete the connection
		ptr->link = NULL;
		delete ptr;
	}

	return returnNum;
}


// display the stack
void display(Node* top)
{
	struct Node* ptr;

	// Check for stack underflow
	if (isEmpty(top) == true)
	{
		cout << "Stack empty" << endl;
	}

	else
	{
		ptr = top;
		while (ptr->link != NULL)
		{
			// Print node data
			cout << ptr->data << " ";

			// Assign ptr to the next link
			ptr = ptr->link;
		}
	}
}


// check if the stack is empty
bool isEmpty(Node* top)
{
	if (top == NULL)
		return true;
	else
		return false;
}
