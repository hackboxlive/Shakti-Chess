#ifndef CHESS_EXCEPTIONS_HPP
#define CHESS_EXCEPTIONS_HPP

#include <stdexcept>

class chess_exceptions : public std::runtime_error	{
	public:
		chess_exceptions(const std::string&);
};

#endif