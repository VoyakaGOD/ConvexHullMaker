#ifndef LAMBDAUTILS_H
#define LAMBDAUTILS_H

#include <QSharedPointer>

class Action
{
    virtual void operator()();
};

template <typename T>
class LambdaAction : public Action
{
private:
    T lambda;

public:
    explicit LambdaAction(T lambda) : lambda(lambda) {}
    void operator()() override { lambda(); }
};

using ActionPtr = QSharedPointer<Action>;

#endif // LAMBDAUTILS_H
