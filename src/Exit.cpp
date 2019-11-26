#include "../include/Action.h"

void Exit::act(Session &sess) {
    sess.exit();
    complete();
}

std::string Exit::toString() const {
    return "Exit " + this->statusToString();
}