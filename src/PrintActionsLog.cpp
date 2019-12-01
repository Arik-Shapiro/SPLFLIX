#include "../include/Action.h"

PrintActionsLog::~PrintActionsLog() {}
void PrintActionsLog::act(Session &sess) {
    std::vector<BaseAction *> &actionsLog = sess.getActionsLog();
    for (BaseAction *i : actionsLog) {
        std::cout << i->toString() << endl;
    }
    complete();
}

std::string PrintActionsLog::toString() const {
    return "PrintActionsLog " + this->statusToString();
}

BaseAction* PrintActionsLog::clone() const {
    return new PrintActionsLog(*this);
}