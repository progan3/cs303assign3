#include "assign3.h"

const string OPEN = "([{";
const string CLOSE = ")]}";

bool is_open(char ch) { //finds if the character is open
	return OPEN.find(ch) != string::npos;
}

bool is_close(char ch) { //checks if the character is closed
	return CLOSE.find(ch) != string::npos;
}

bool is_balanced(const string& expression) { //checks if the expression is balanced
	stack<char> s;
	bool balanced = true;
	string::const_iterator iter = expression.begin();
	while (balanced && (iter != expression.end())) {
		char next_ch = *iter;
		if (is_open(next_ch)) {
			s.push(next_ch);
		}
		else if (is_close(next_ch)) {
			if (s.empty()) {
				balanced = false;
			}
			else {
				char top_ch = s.top();
				s.pop();
				balanced = OPEN.find(top_ch) == CLOSE.find(next_ch);
			}
		}
		++iter;
	}
	return balanced && s.empty();
}

int precedence(char ch) { //determines the precedence of the character

	if (ch == '%' || ch == '/' || ch == '*') {
		return 2;
	}
	else if (ch == '+' || ch == '-') {
		return 1;
	}
	else {
		return -1;
	}
}

void inToPost(string s) { //changes the expression from infix to postfix

	stack<char> st;
	string result;

	for (int i = 0; i < s.length(); i++) {
		char c = s[i];

		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
			|| (c >= '0' && c <= '9')) {
			result += c;
		}

		else if (c == '(') {
			st.push('(');
		}

		else if (c == ')') {
			while (st.top() != '(') {
				result += st.top();
				st.pop();
			}
			st.pop();
		}

		else {
			while (!st.empty()
				&& precedence(s[i]) <= precedence(st.top())) {
				result += st.top();
				st.pop();
			}
			st.push(c);
		}
	}
	while (!st.empty()) {
		result += st.top();
		st.pop();
	}

	cout << result << endl;
}


int main() {
	cout << "Enter and expression\n";
	string expression;
	while (getline(cin, expression) && (expression != "")) {
		cout << expression;
		if (is_balanced(expression)) {
			cout << " is balanced\n";
			inToPost(expression);
		}
		else {
			cout << " is not balanced\n";
		}
	}
	return 0;
}