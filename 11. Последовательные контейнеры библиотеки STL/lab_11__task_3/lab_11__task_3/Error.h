#pragma once
#include <string>
#include <iostream>


class Error
{
	private:
		std::string message;

	public:
		Error(std::string str) { message = str; }
		void what() { std::cout << message << std::endl; }
};

