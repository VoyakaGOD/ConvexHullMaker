#ifndef ACTIONHISTORY_H
#define ACTIONHISTORY_H

#include "reversibleaction.h"

class ActionHistory
{
private:
    struct Node
    {
        Node *prev;
        Node *next;
        ReversibleAction action;

        Node(const ReversibleAction &action);
        ~Node();
    };

private:
    int capacity;
    int currentIndex;
    Node *root;
    Node *current;

public:
    ActionHistory();
    ActionHistory(const ActionHistory &other) = delete;
    ActionHistory(ActionHistory &&other) = delete;
    ActionHistory& operator=(const ActionHistory &other) = delete;
    ActionHistory& operator=(ActionHistory &&other) = delete;
    ~ActionHistory();

    void setCapacity(int capacity);
    void addRecord(const ReversibleAction &action);
    QString undo();
    QString redo();
};

#endif // ACTIONHISTORY_H
