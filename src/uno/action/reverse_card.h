#ifndef CSU_REVERSE_CARD_H_
#define CSU_REVERSE_CARD_H_

#include "card.h";

namespace Casino { namespace Uno { namespace Action {

using ::Casino::Uno::Action::Card;
using ::Casino::Uno::Action::CARD_COLOR;
using ::Casino::Uno::Action::CARD_VALUE;

class BlockCard :public Card
{
private:
	CARD_COLOR color;
	CARD_VALUE value;
public:
	BlockCard(CARD_COLOR color)
		:color(color)
	{
		value = CARD_VALUE_REVERSE;
	}

	void takeAction(UnoGame* game) {
		game->reverseTurn();
	}
};

}}} //namespace

#endif /* CSU_REVERSE_CARD_H_ */
