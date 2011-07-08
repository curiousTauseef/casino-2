#include "full_card_deck.h"

#include "card.h"
#include "simple_card.h"
#include "block_card.h"
#include "reverse_card.h"
#include "plustwo_card.h"
#include "plusfour_card.h"
#include "colorpick_card.h"
#include <list>

namespace Casino { namespace Uno { namespace Action {

using ::Casino::Uno::Game::UnoGame;
using ::Casino::Uno::Action::UnoCard;
using ::Casino::Uno::Action::CARD_COLOR;
using ::Casino::Uno::Action::CARD_VALUE;

using ::Casino::Uno::Action::SimpleCard;
using ::Casino::Uno::Action::BlockCard;
using ::Casino::Uno::Action::ReverseCard;
using ::Casino::Uno::Action::PlustwoCard;
using ::Casino::Uno::Action::PlusfourCard;
using ::Casino::Uno::Action::ColorpickCard;

void UnoFullCardDeck::add(UnoCard *card) {
	deck.push_back(card);
	game->addCardToDeck(card);
}

void UnoFullCardDeck::fillGameWithCards(UnoGame* g) {
	game = g;

	CARD_COLOR colors[] = {
			CARD_COLOR_RED,
			CARD_COLOR_GREEN,
			CARD_COLOR_BLUE,
			CARD_COLOR_YELLOW
	};

	const int color_count = 4;

	CARD_VALUE values[] = {
		CARD_VALUE_1,
		CARD_VALUE_2,
		CARD_VALUE_3,
		CARD_VALUE_4,
		CARD_VALUE_5,
		CARD_VALUE_6,
		CARD_VALUE_7,
		CARD_VALUE_8,
		CARD_VALUE_9
	};

	const int value_count = 9;

	for (int color = 0; color < color_count; color++) {
		// add 0
		add(new SimpleCard(colors[color], CARD_VALUE_0));

		// add two card of a kind
		for (int i = 0; i < 2; i++) {

			// add 1-9
			for (int value = 0; value < value_count; value++) {
				add(new SimpleCard(colors[color], values[value]));
			}

			add(new BlockCard(colors[color]));
			add(new ReverseCard(colors[color]));
			add(new PlustwoCard(colors[color]));
		}
	}

	const int black_count = 4;

	for (int i = 0; i < black_count; i++) {
		add(new PlusfourCard());
		add(new ColorpickCard());
	}
}

UnoFullCardDeck::~UnoFullCardDeck() {
	std::list<UnoCard *>::iterator it;

	for (it = deck.begin(); it != deck.end(); it++) {
		delete *it;
	}
}

}}} //namespace
