#include "reversibleaction.h"

ReversibleAction::ReversibleAction(QString redoMessage, Action *redo, QString undoMessage, Action *undo) :
    redoMessage(redoMessage), redo(redo), undoMessage(undoMessage), undo(undo) {}
