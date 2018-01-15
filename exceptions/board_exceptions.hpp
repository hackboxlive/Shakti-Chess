#ifndef BOARD_EXCEPTION_HPP
#define BOARD_EXCEPTION_HPP

#include "chess_exceptions.hpp"

class board_exceptions : public chess_exceptions {
	public:
		board_exceptions(const std::string&);
};

#endif