#include <iostream>
#include <array>
#include <sstream>
#include <ctype.h>
#include "AVL_Tree.cpp"

class Tree_Builder {

public:

	//
	//constructor
	//
	Tree_Builder(void)
		:arr_(new int[10]),
		size_(0)
	{
		bool build;
		bool keepGoing = true;

		while (keepGoing) {
			build = get_response();
			if (build == true) {
				tree_ = new AVL_Tree(arr_, size_);
			}
			else {
				keepGoing = false;
			}
		}
	}

	//
	//destructor
	//
	~Tree_Builder(void) {
		delete[] arr_;
		delete[] tree_;
	}

	//
	//Requests user input, calls create_array()
	//
	bool get_response() {
		bool keepGoing = true;
		while (keepGoing == true) {
			std::cin.clear();
			std::cout << "Please enter up to 10 numbers seperated by commas, or type q to quit" << std::endl;
			std::getline(std::cin, response_);

			try {
				if (response_.compare("q") == 0) {
					keepGoing = false;
				}
				else {
					create_array();
					return true;
				}
			}
			catch (int a) {
				handler(a);
			}
		}
		return false;
	}

	//
	//builds array, calls converter() for converting input to integers, calls check_space() to throw exceptions for whitespace
	//
	void create_array() {

		check_spaces();

		std::stringstream ss(response_);
		response_ = "";
		int value;
		int size = 0;
		std::string token;

		for (size; std::getline(ss, token, ','); size++) {
			value = converter(token);
			if (size > 9) {
				throw 2;
			}
			arr_[size] = value;
		}
		size_ = size;
	}

	//
	//converts strings to int, throws exception when it finds non-integer value, removes charactars placed after integers
	//
	int converter(std::string input) {
		std::stringstream s(input);
		int x = 0;
		s >> x;
		if (s.fail()) {
			throw 1;
		}
		return x;
	}

	//
	//parses given string for whitespace, throws exception if it occurs
	//
	void check_spaces() {
		int length = response_.length();
		for (int i = 0; i < length; i++) {
			if (std::isspace(response_[i])) {
				throw 1;
			}
		}
	}

	//
	//Handles Exceptions
	//
	void handler(int a) {
		if (a == 1) {
			std::cout << "Invalid Input, try again." << std::endl;
		}
		else if (a == 2) {
			std::cout << "Exceeded maximum number of values" << std::endl;
		}
		else {
			std::cout << "Default Exception" << std::endl;
		}
	}

private:
	int size_;
	AVL_Tree * tree_ = NULL;
	int * arr_;
	std::string response_;
};