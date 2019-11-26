#include "../include/Action.h"

Watch::Watch(long contentId) : contentId(contentId) {}

void Watch::act(Session &sess) {
    if (contentId <= sess.getContent().size()) {
        Watchable *watchable = sess.getContent()[contentId];
        std::cout << "Watching " + watchable->toString();
        sess.getActiveUser()->get_history().push_back(watchable);
        complete();
    } else {
        error("Error - bad content id input");
    }
}

std::string Watch::toString() const {
    return "Watch " + this->statusToString();
}