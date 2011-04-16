#ifndef CARD_HPP_INCLUDED
#define CARD_HPP_INCLUDED

#include "common.hpp"

class card {
public:
    card (CARDS _card)
    {
		this->type = _card;
    }
	CARDS type;
};

#endif // CARD_HPP_INCLUDED
