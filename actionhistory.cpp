#include "actionhistory.h"

ActionHistory::Node::Node(const ReversibleAction &action) : prev(nullptr), next(nullptr), action(action) {}

ActionHistory::Node::~Node()
{
    delete next;
}

ActionHistory::ActionHistory() : capacity(0), currentIndex(0), root(nullptr), current(nullptr) {}

void ActionHistory::setCapacity(int capacity)
{
    if(this->capacity != 0)
        return;

    this->capacity = capacity;
}

void ActionHistory::addRecord(const ReversibleAction &action)
{
    if(capacity <= 0)
        return;

    if(!current)
    {
        delete root;
        root = new Node(action);
        current = root;
        currentIndex = 1;
        return;
    }

    if(current->next)
        delete current->next;
    current->next = new Node(action);
    current->next->prev = current;
    current = current->next;

    if(currentIndex == capacity)
    {
        Node *newRoot = root->next;
        newRoot->prev = nullptr;
        operator delete(root);
        root = newRoot;
    }
    else
    {
        currentIndex++;
    }
}

QString ActionHistory::undo()
{
    if(!current)
        return "";

    ReversibleAction &action = current->action;
    action.undo->call();

    current = current->prev;
    currentIndex--;

    return action.undoMessage;
}

QString ActionHistory::redo()
{
    if(!current)
    {
        if(!root)
            return "";
        current = root;
        currentIndex = 1;
    }
    else if(current->next)
    {
        current = current->next;
        currentIndex++;
    }
    else
    {
        return "";
    }

    ReversibleAction &action = current->action;
    action.redo->call();

    return action.redoMessage;
}

ActionHistory::~ActionHistory()
{
    delete root;
}
