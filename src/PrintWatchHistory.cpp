#include "../include/Action.h"

PrintWatchHistory::~PrintWatchHistory() {}
void PrintWatchHistory::act(Session &sess) {
    std::vector<Watchable *> history = sess.getActiveUser().get_history();
    std::cout << "Watch history for " + sess.getActiveUser().getName() << endl;
    for (Watchable *i : history) {
        std::cout << i->toString() << endl;
    }
    complete();
}

std::string PrintWatchHistory::toString() const {
    return "PrintWatchHistory " + this->statusToString();
}

BaseAction* PrintWatchHistory::clone() const {
    return new PrintWatchHistory(*this);
}