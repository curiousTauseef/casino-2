#ifndef SRC_UNO_PLAYER_ASYNC_ROBOT_EASY_PLAYER_H_
#define SRC_UNO_PLAYER_ASYNC_ROBOT_EASY_PLAYER_H_

#include "./player.h"
#include "../action/card.h"
#include "../event/event.h"

namespace Uno { namespace Game {
    class AsyncGame;
}}  // namespace

namespace Uno { namespace Player {

using ::Uno::Player::Player;
using ::Uno::Game::AsyncGame;
// Card, CARD_COLOR, CARD_VALUE
using namespace ::Uno::Action;
namespace Event = ::Uno::Event;

class AsyncRobotEasyPlayer :public Player {

 public:
    AsyncRobotEasyPlayer();
    virtual void setGame(AsyncGame* game);
    virtual void notify(Event::EVENT event_type, void* event);

 protected:
    AsyncGame* game;
    bool game_runs;	/**< true if game started but not ended */

    virtual void takeAction();
    virtual CARD_COLOR chooseColor();
    static bool compareCardValue(Card* a, Card* b);
};

}}  // namespace

#endif  // SRC_UNO_PLAYER_ASYNC_ROBOT_EASY_PLAYER_H_