#pragma once
#include <string>
#include <iostream>


class Error
{
	public:
		virtual void what() { };
};




class IndexError : public Error
{
	protected:
		std::string message;
	public:
		IndexError() { message = "INDEX ERROR: "; }
		virtual void what() { }
};


class MinIndexError : public IndexError
{
	private:
		std::string _message;
	public:
		MinIndexError() { _message = "index < 0"; }
		void what() { std::cout << message << _message << std::endl; }
};


class MaxIndexError : public IndexError
{
	private:
		std::string _message;
	public:
		MaxIndexError() { _message = "index > size"; }
		void what() { std::cout << message << _message << std::endl; }
};




class SizeError : public Error
{
	protected:
		std::string message;
	public:
		SizeError() { message = "SIZE ERROR: "; }
		virtual void what() { };
};


class MinSizeError : public SizeError
{
	private:
		std::string _message;
	public:
		MinSizeError() { _message = "size < 0"; }
		void what() { std::cout << message << _message << std::endl; }
};


class MaxSizeError : public SizeError
{
	private:
		std::string _message;
	public:
		MaxSizeError() { _message = "size > MAX_SIZE"; }
		void what() { std::cout << message << _message << std::endl; }
};