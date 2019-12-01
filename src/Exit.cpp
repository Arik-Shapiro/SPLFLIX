#include "../include/Action.h"


Exit::~Exit() {}
void Exit::act(Session &sess) {
    sess.exit();
    complete();
}

std::string Exit::toString() const {
    return "Exit " + this->statusToString();
}

BaseAction* Exit::clone() const {
    return new Exit(*this);
}