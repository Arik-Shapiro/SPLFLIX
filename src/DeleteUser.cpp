#include "../include/Action.h"

DeleteUser::DeleteUser(std::string userToDelete) : userToDelete(userToDelete) {}

DeleteUser::~DeleteUser() {}

void DeleteUser::act(Session &sess) {
    if(sess.deleteUser(userToDelete))
        complete();
    else
        error("Error - failed to delete user, user doesn't exist.");
}

std::string DeleteUser::toString() const {
    return "DeleteUser " + this->statusToString();
}

BaseAction* DeleteUser::clone() const {
    return new DeleteUser(*this);
}