#include "State.h"

State::State() {
    state = States::MENU;
}

void State::setState(States state) {
    this->state = state;
}

State::States State::getState() {
    return state;
}