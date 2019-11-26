#include "../include/User.h"

User::User(const std::string &name) : name(name){
}

User::User(const User &user, std::string dupName) : name(dupName) {
    for(int i = 0; i < history.size(); i++){
        history.push_back(user.get_history()[i]->clone());
    }
}

std::string User::getName() const { return name; }

std::vector<Watchable *> User::get_history() const { return history; }

bool User::hasWatched(Watchable *watchable) {
    for(int j = 0; j < history.size(); j++){
        if(watchable->getId() == history[j]->getId())
            return true;
    }
    return false;
}