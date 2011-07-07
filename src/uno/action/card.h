#ifndef CSU_CARD_H_
#define CSU_CARD_H_

#include "../action/action.h"

namespace Casino { namespace Uno { namespace Action {
	class UnoAction;
}}} //namespace

namespace Casino { namespace Uno { namespace Action {

using ::Casino::Uno::Action::UnoAction;

enum CARD_COLOR {
	CARD_COLOR_RED,
	CARD_COLOR_GREEN,
	CARD_COLOR_BLUE,
	CARD_COLOR_YELLOW,
	CARD_COLOR_BLACK
};

enum CARD_VALUE {
	CARD_VALUE_0,
	CARD_VALUE_1,
	CARD_VALUE_2,
	CARD_VALUE_3,
	CARD_VALUE_4,
	CARD_VALUE_5,
	CARD_VALUE_6,
	CARD_VALUE_7,
	CARD_VALUE_8,
	CARD_VALUE_9,
	CARD_VALUE_BLOCK,
	CARD_VALUE_REVERSE,
	CARD_VALUE_PLUSTWO,
	CARD_VALUE_COLORPICK,
	CARD_VALUE_PLUSFOUR
};

class UnoCard :public UnoAction
{
protected:
	CARD_COLOR color;
	CARD_VALUE value;
public:
	UnoCard() {}
	UnoCard(CARD_COLOR color, CARD_VALUE value)
		:color(color),
		 value(value)
	{}

	virtual bool isDisposeable() {
		return true;
	}

	virtual CARD_COLOR getColor() {
		return color;
	}

	virtual CARD_VALUE getValue() {
		return value;
	}
};

}}} //namespace

#endif /* CSU_CARD_H_ */
