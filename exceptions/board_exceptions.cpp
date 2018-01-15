#include <stdexcept>

#include "board_exceptions.hpp"

board_exceptions::board_exceptions(const std::string& message) 
	: chess_exceptions(message){

}