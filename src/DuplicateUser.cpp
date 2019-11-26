#include "../include/Action.h"

DuplicateUser::DuplicateUser(std::string userToDuplicate) : userToDuplicate(userToDuplicate) {}

void DuplicateUser::act(Session &sess) {
    User *user = sess.getUserMap()[userToDuplicate];
    if (user != nullptr) {
        User *dupUser = user->clone(userToDuplicate);
        sess.getUserMap().insert({dupUser->getName(), dupUser});
        complete();
    } else {
        error("Error - couldn't copy user");
    }
}
std::string DuplicateUser::toString() const {
    return "DuplicateUser " + this->statusToString();
}