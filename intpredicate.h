#ifndef INTPREDICATE_H
#define INTPREDICATE_H

class IntPredicate
{
protected:
    IntPredicate() = default;

public:
    virtual bool operator()(int value) const;
};

class IntAny : public IntPredicate
{
public:
    IntAny() = default;
    bool operator()(int value) const override;
};

class IntMinPredicate : public IntPredicate
{
private:
    int min;

public:
    IntMinPredicate(int min);
    bool operator()(int value) const override;
};

class IntMaxPredicate : public IntPredicate
{
private:
    int max;

public:
    IntMaxPredicate(int max);
    bool operator()(int value) const override;
};


class IntClampPredicate : public IntPredicate
{
private:
    int min;
    int max;

public:
    IntClampPredicate(int min, int max);
    bool operator()(int value) const override;
};

#endif // INTPREDICATE_H
