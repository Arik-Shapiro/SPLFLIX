#include "../include/User.h"

User::User(const std::string &name) : history(), name(name) {}
User::User(const User &user, const std::vector<Watchable *> &history) : history(history), name(user.name) {}
User::~User() {}
User::User(const User &user, std::string dupName) : history(), name(dupName) {
    for(Watchable *watchable : user.history){
        history.push_back(watchable);
    }
}

std::string User::getName() const { return name; }

std::vector<Watchable *> User::get_history() const { return history; }

bool User::hasWatched(const Watchable &watchable) const {
    for(Watchable *checkWatch : history){
        if(watchable.getId() == checkWatch->getId())
            return true;
    }
    return false;
}



