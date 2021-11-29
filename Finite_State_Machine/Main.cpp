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

	int id = 0;
	for (int i = 0; i < reg.size(); i++) {
		State s = { {}, id };
		std::fill_n(s.data, INPUTS, reg.size());
		
		if (reg[i] == '*') {
			states.back().data[asIndex(reg[i + 1])] = id+1;
		}
		else if (reg[i] == '.') {
			std::fill_n(s.data, INPUTS, id+1);
			states.push_back(s);
			id++;
		}
		else {
			s.data[asIndex(reg[i])] = id + 1;
			states.push_back(s);
			id++;
		}
		
	}
	State a = { {}, reg.size()-1 };
	std::fill_n(a.data, INPUTS, reg.size()-1);
	states.push_back(a);

	State f = { {}, reg.size() };
	std::fill_n(f.data, INPUTS, reg.size());
	states.push_back(f);

	for (int i = 0; i < reg.size(); i++) {
		if (reg[i] == '*' && i != 0) {
			states[i].data[asIndex(reg[i - 1])] = states[i].id;
		}
		else if (reg[i] == '$') {
			// break
		}
	}



	//int id = 0;
	//for (int i = 0; i < reg.size(); i++) {
	//	if (reg[i] == '*' && i != 0) {
	//		continue;
	//	}
	//	
	//	State s = { {}, id };
	//	std::fill_n(s.data, INPUTS, 0);

	//	s.data[asIndex(reg[i])] = id+1;
	//	states.push_back(s);
	//	id++;
	//}

	//State a = { {}, id };
	//std::fill_n(a.data, INPUTS, id);
	//states.push_back(a);

	//for (int i = 0; i < reg.size(); i++) {
	//	if (reg[i] == '*' && i != 0) {
	//		states[i].data[asIndex(reg[i - 1])] = states[i].id;
	//	}
	//	else if (reg[i] == '$') {
	//		// break
	//	}
	//}

	return states;
}

void print_FSM(std::vector<State> states) {
	std::cout << "  ";
	for (int j = 0; j < states.size(); j++) {
		std::cout << states[j].id;
	}
	std::cout << std::endl;

	for (int i = 0; i < INPUTS; i++) {
		std::cout << (char)('a' + i) << " ";
		for (int j = 0; j < states.size(); j++) {
			std::cout << states[j].data[i];;
		}
		std::cout << std::endl;
	}
}

bool regex(std::string reg, std::string text) {

	std::vector<State> states = create_FSM(reg);

	print_FSM(states);

	State current = states[0];
	for (int i = 0; i < text.size(); i++) {
		std::cout << current.id << " | " << text[i] << " | " << current.data[asIndex(text[i])] << std::endl;
		current = states[current.data[asIndex(text[i])]];
	}
	return current.id == reg.size() - 1;
}

int main(int argc, char* argv[]) {

	std::cout << regex("a..c", "ahsc") << std::endl;

	return 0;
}