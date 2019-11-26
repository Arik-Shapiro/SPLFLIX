#include "../include/Action.h"

DeleteUser::DeleteUser(std::string userToDelete) : userToDelete(userToDelete) {}

void DeleteUser::act(Session &sess) {
    User *user = sess.getUserMap()[userToDelete];
    if (user != nullptr) {
        complete();
        delete user;
    } else {
        error("Error - Couldn't delete user");
    }
}

std::string DeleteUser::toString() const {
    return "DeleteUser " + this->statusToString();
}