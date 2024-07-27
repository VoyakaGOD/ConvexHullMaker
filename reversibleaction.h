#ifndef REVERSIBLEACTION_H
#define REVERSIBLEACTION_H

#include <QString>
#include "lambdautils.h"

struct ReversibleAction
{
    QString redoMessage;
    QString undoMessage;
    ActionPtr undo;
    ActionPtr redo;

    ReversibleAction(QString redoMessage, Action *redo, QString undoMessage, Action *undo);
};

#endif // REVERSIBLEACTION_H
