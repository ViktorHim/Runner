#ifndef STATE_H
#define STATE_H
class State
{
public:
    enum States //перечисление состояний
    {
        MENU,
        GAME,
        QUIT,
        SELECT,
        RESTART
    };

    State();
    void setState(States);
    States getState();

private:
    States state;
};
#endif