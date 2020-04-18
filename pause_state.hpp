//
// Created by loic on 18/04/2020.
//

#ifndef LD46_PAUSE_STATE_HPP
#define LD46_PAUSE_STATE_HPP

#include <states/state.hpp>

class PauseState : public State
{
public:
    PauseState(StateStack& stack, Context context);

    void draw() override;
    bool update(sf::Time dt) override;
    bool handleEvent(const sf::Event& event) override;

private:
    sf::Text mText;
};


#endif //LD46_PAUSE_STATE_HPP
