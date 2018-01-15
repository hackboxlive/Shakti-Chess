#include <stdexcept>

#include "chess_exceptions.hpp"

chess_exceptions::chess_exceptions(const std::string &message) : std::runtime_error(message)	{
	
}