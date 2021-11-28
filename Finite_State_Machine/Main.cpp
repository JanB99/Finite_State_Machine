#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define INPUTS 26

struct State {
	int data[INPUTS];
	int id;
};

int asIndex(char c) {
	return c - 'a';
}

std::vector<State> create_FSM(std::string reg) {

	std::vector<State> states;

	for (int i = 0; i < reg.size(); i++) {
		State s = { {}, i };
		std::fill_n(s.data, INPUTS, 0);
		states.push_back(s);
	}

	State a = { {}, reg.size() };
	std::fill_n(a.data, INPUTS, reg.size());
	states.push_back(a);

	for (int i = 0; i < states.size()-1; i++) {
		states[i].data[asIndex(reg[i])] = states[i + 1].id;
	}

	//for (int i = 0; i < states.size(); i++) {
	//	std::cout << "state " << states[i].id << std::endl;
	//	for (int j = 0; j < 26; j++) {
	//		std::cout << states[i].data[j] << std::endl;

	//	}
	//}

	return states;
}

bool regex(std::string reg, std::string text) {

	std::vector<State> states = create_FSM(reg);

	State current = states[0];
	for (int i = 0; i < text.size(); i++) {
		std::cout << current.id << " | " << text[i] << " | " << current.data[asIndex(text[i])] << std::endl;
		current = states[current.data[asIndex(text[i])]];
	}

	return current.id == reg.size();
}

int main(int argc, char* argv[]) {


	std::cout << regex("abc", "gasdasdabcc");

	return 0;
}