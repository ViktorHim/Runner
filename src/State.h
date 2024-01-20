#ifndef STATE_H
#define STATE_H
class State
{
public:
    enum States
    {
        MENU,
        GAME,
        QUIT,
        PAUSE
    };

    State();
    void setState(States);
    States getState();

private:
    States state;
};
#endif


