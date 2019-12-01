#include "../include/Action.h"

Watch::Watch(long contentId) : contentId(contentId) {}
Watch::~Watch() {}
void Watch::act(Session &sess) {
    if ((unsigned)contentId <= sess.getContent().size() && (unsigned)contentId > 0) {
        Watchable *watchable = sess.getContent()[contentId - 1]; // change to non-pointer.
        std::cout << "Watching " + watchable->toString() << endl;
        sess.getActiveUser().watch(watchable);
        complete();
        Watchable *recommendation = watchable->getNextWatchable(sess);
        std::cout << "We recommend watching " + recommendation->toString() + ", continue watching? [y/n]" << endl;
        char inp;
        std::cin >> inp;
        if(inp == 'y') {
            Watch *watch = new Watch(recommendation->getId());
            watch->act(sess);
            sess.getActionsLog().push_back(watch);
        }
    } else {
        error("Error - bad content id input");
    }
}

std::string Watch::toString() const {
    return "Watch " + this->statusToString();
}

BaseAction* Watch::clone() const {
    return new Watch(*this);
}