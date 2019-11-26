#include "../include/Session.h"

Session::Session(const std::string &configFilePath) {

}

std::unordered_map<std::string, User *> Session::getUserMap() {
    return userMap;
}

Session::~Session() {

}

void Session::start() {

}

void Session::setActiveUser(User *user) {
    activeUser = user;
}

void Session::exit() {

}

User *Session::getActiveUser() {
    return activeUser;
}

std::vector<Watchable *> Session::getContent() {
    return content;
}

std::vector<BaseAction *> Session::getActionsLog() {
    return actionsLog;
}
