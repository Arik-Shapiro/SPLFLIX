#include "../include/Action.h"

DuplicateUser::DuplicateUser(std::string userToDuplicate, std::string newUserName)
        : userToDuplicate(userToDuplicate), newUserName(newUserName) {}

DuplicateUser::~DuplicateUser() {}

void DuplicateUser::act(Session &sess) {
    std::unordered_map<std::string, User *> userMap = sess.getUserMap();
    auto user = userMap.find({userToDuplicate});
    if (user != userMap.end()) {
        User *dupUser = user->second->clone(newUserName);
        if(!sess.insertUser(dupUser)) {
            error("Error - username already exists.");
            delete dupUser;
        }
        else
           complete();
    } else {
        error("Error - couldn't copy user");
    }
}

std::string DuplicateUser::toString() const {
    return "DuplicateUser " + this->statusToString();
}

BaseAction* DuplicateUser::clone() const {
    return new DuplicateUser(*this);
}