#include "intpredicate.h"

bool IntPredicate::operator()(int value) const
{
    return false;
}

bool IntAny::operator()(int value) const
{
    return true;
}

IntMinPredicate::IntMinPredicate(int min) : min(min) {}

bool IntMinPredicate::operator()(int value) const
{
    return value >= min;
}

IntMaxPredicate::IntMaxPredicate(int max) : max(max) {}

bool IntMaxPredicate::operator()(int value) const
{
    return value <= max;
}

IntClampPredicate::IntClampPredicate(int min, int max) : min(min), max(max) {}

bool IntClampPredicate::operator()(int value) const
{
    return (value >= min) && (value <= max);
}
