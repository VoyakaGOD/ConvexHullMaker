#ifndef ACTIONHISTORY_H
#define ACTIONHISTORY_H

#include "reversibleaction.h"

class ActionHistory
{
private:
    int capacity;

public:
    ActionHistory(int capacity);
    void AddRecord(const ReversibleAction &action);
    void Undo();
    void Redo();
};

#endif // ACTIONHISTORY_H
