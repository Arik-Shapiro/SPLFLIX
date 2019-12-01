#include "../include/Action.h"

ChangeActiveUser::ChangeActiveUser(std::string userToChange) : userToChange(userToChange) {}

ChangeActiveUser::~ChangeActiveUser() {}

void ChangeActiveUser::act(Session &sess) {
    std::unordered_map<std::string, User *> userMap = sess.getUserMap();
    if (userMap.find({userToChange}) != userMap.end()) {
        sess.setActiveUser(userMap[userToChange]);
        complete();
    } else {
        error("Error - couldn't change user");
    }
}

std::string ChangeActiveUser::toString() const {
    return "ChangeActiveUser " + this->statusToString();
}

BaseAction* ChangeActiveUser::clone() const {
    return new ChangeActiveUser(*this);
}