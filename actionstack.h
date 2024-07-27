#ifndef ACTIONSTACK_H
#define ACTIONSTACK_H

#include <QString>

template <typename HostT>
using ReversibleActionHandler = void (*)(HostT *host);

template <typename HostT>
struct ReversibleAction
{
    QString redo_log;
    QString undo_log;
    ReversibleActionHandler<HostT> undo;
    ReversibleActionHandler<HostT> redo;
};

template <typename HostT>
class ActionStack
{
public:
    ActionStack(int capacity);
    void AddRecord(ReversibleAction<HostT> action);
    void Undo();
    void Redo();
};

#endif // ACTIONSTACK_H
