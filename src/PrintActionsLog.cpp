#include "../include/Action.h"

void PrintActionsLog::act(Session &sess) {
    std::vector<BaseAction *> actionsLog = sess.getActionsLog();
    for (BaseAction *i : actionsLog) {
        std::cout << i->toString() << endl;
    }
}

std::string PrintActionsLog::toString() const {
    return "PrintActionsLog " + this->statusToString();
}