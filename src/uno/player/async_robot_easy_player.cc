#include "./async_robot_easy_player.h"

#include <vector>
#include <string>
#include <algorithm>
#include <map>

#include "../action/card.h"
#include "../action/wild_card.h"
#include "../game/async_game.h"

namespace Uno { namespace Player {

// Card, CARD_VALUE, WildCard
using namespace ::Uno::Action;

AsyncRobotEasyPlayer::AsyncRobotEasyPlayer()
	:game_runs(false)
{}

void AsyncRobotEasyPlayer::notify(Event::EVENT event_type, void* event) {
    switch (event_type) {
    case Event::EVENT_PLAYERS_TURN:
    {
        Event::players_turn* players_turn = reinterpret_cast<Event::players_turn*>(event);

        if (players_turn->player == this && game_runs) {
            takeAction();
        }
    }
        break;
    case Event::EVENT_GAME_START:
    {
    	game_runs = true;
    }
    	break;
    case Event::EVENT_GAME_END:
    {
    	game_runs = false;
    }
    	break;
    case Event::EVENT_CARD_PLAYED:
    	break;
    case Event::EVENT_DRAW_CARD:
    	break;
    case Event::EVENT_COLORPICK:
    	break;
    case Event::EVENT_UNO_SAID:
    	break;
    case Event::EVENT_GETS_BLOCKED:
    	break;
    case Event::EVENT_PLAYER_JOINED:
    	break;
    default:
        break;
    }
}

void AsyncRobotEasyPlayer::setGame(AsyncGame* game) {
    this->game = game;
}

void AsyncRobotEasyPlayer::takeAction() {
    std::vector<Card*> valid_moves;
    card_iterator card;
    std::string dummy_str;

    for (card = hand.begin(); card < hand.end(); card++) {
        if (game->isValidMove(this, *card, dummy_str)) {
            valid_moves.push_back(*card);
        }
    }

    if (valid_moves.size() < 1) {
        // no valid move, draw
        game->takeDraw(this);
    } else {

        std::sort(valid_moves.begin(), valid_moves.end(), compareCardValue);
        Card* picked = valid_moves.front();

        if (picked->getColor() == CARD_COLOR_BLACK) {
            CARD_COLOR new_color = chooseColor();
            static_cast<WildCard*>(picked)->setColor(new_color);
        }

        if (hand.size() == 2) {
            setUnoFlag(true);
            game->sayUno(this);
        }

        game->takeAction(this, picked);
    }
}

CARD_COLOR  AsyncRobotEasyPlayer::chooseColor() {
    std::map<CARD_COLOR, int> colors;

    colors[CARD_COLOR_RED] = 0;
    colors[CARD_COLOR_GREEN] = 0;
    colors[CARD_COLOR_BLUE] = 0;
    colors[CARD_COLOR_YELLOW] = 0;

    card_iterator card;
    for (card = hand.begin(); card < hand.end(); card++) {
        colors[(*card)->getColor()]++;
    }

    CARD_COLOR picked = CARD_COLOR_RED;
    if (colors[CARD_COLOR_GREEN] > colors[picked]) {
        picked = CARD_COLOR_GREEN;
    }
    if (colors[CARD_COLOR_BLUE] > colors[picked]) {
        picked = CARD_COLOR_BLUE;
    }
    if (colors[CARD_COLOR_YELLOW] > colors[picked]) {
        picked = CARD_COLOR_YELLOW;
    }

    return picked;
}

bool AsyncRobotEasyPlayer::compareCardValue(Card* a, Card* b) {
    CARD_VALUE values[] = {
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
    const int value_count = 15;

    int value_a = 0, value_b = 0;

    for (int i = 0; i < value_count; i++) {
        if (a->getValue() == values[i]) {
            value_a = i;
        }
        if (b->getValue() == values[i]) {
            value_b = i;
        }
    }

    return value_a < value_b;
}

}}  // namespace
