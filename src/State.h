class State
{
public:
    enum States
    {
        MENU,
        GAME,
        QUIT,
    };

    State();
    void setState(States);
    States getState();

private:
    States state;
};



