#include "../include/Action.h"

void PrintWatchHistory::act(Session &sess) {
    std::vector<Watchable *> history = sess.getActiveUser()->get_history();
    std::cout << "Watch history for " + sess.getActiveUser()->getName();
    for (Watchable *i : history) {
        std::cout << i->toString();
    }
}

std::string PrintWatchHistory::toString() const {
    return "PrintWatchHistory " + this->statusToString();
}