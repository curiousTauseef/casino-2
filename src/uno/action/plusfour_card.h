#ifndef CSU_PLUSFOUR_CARD_H_
#define CSU_PLUSFOUR_CARD_H_

#include "card.h";

namespace Casino { namespace Uno { namespace Action {

using ::Casino::Uno::Action::Card;
using ::Casino::Uno::Action::CARD_COLOR;
using ::Casino::Uno::Action::CARD_VALUE;

class PlusfourCard :public Card
{
private:
	CARD_COLOR color;
	CARD_VALUE value;
public:
	PlusfourCard()
	{
		color = CARD_COLOR_BLACK;
		value = CARD_VALUE_PLUSFOUR;
	}

	void takeAction(UnoGame* game) {
		game->increasePenality(4);
	}
};

}}} //namespace

#endif /* CSU_PLUSFOUR_CARD_H_ */
