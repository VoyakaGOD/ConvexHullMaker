#ifndef LAMBDAUTILS_H
#define LAMBDAUTILS_H

#include <QSharedPointer>

class Action
{
public:
    virtual void call();
};

template <typename T>
class LambdaAction : public Action
{
private:
    T lambda;

public:
    explicit LambdaAction(T lambda) : lambda(lambda) {}
    void call() override { lambda(); }
};

using ActionPtr = QSharedPointer<Action>;

#endif // LAMBDAUTILS_H
