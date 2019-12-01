#include "../include/Action.h"

CreateUser::CreateUser(std::string userName, std::string userAlgo) : userName(userName), userAlgo(userAlgo) {}

CreateUser::~CreateUser() {}

void CreateUser::act(Session &sess) {
    if(sess.insertNewUser(userName, userAlgo))
        complete();
    else
        error("Error - failed creating user, username is taken or bad algorithm input.");
}

std::string CreateUser::toString() const {
    return "CreateUser " + this->statusToString();
}

BaseAction* CreateUser::clone() const {
    return new CreateUser(*this);
}
