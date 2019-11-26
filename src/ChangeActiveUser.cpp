#include "../include/Action.h"

ChangeActiveUser::ChangeActiveUser(std::string userToChange) : userToChange(userToChange) {}

void ChangeActiveUser::act(Session &sess) {
    User *user = sess.getUserMap()[userToChange];
    if (user != nullptr) {
        complete();
    } else {
        error("Error - couldn't change user");
    }
}

std::string ChangeActiveUser::toString() const {
    return "ChangeActiveUser " + this->statusToString();
}