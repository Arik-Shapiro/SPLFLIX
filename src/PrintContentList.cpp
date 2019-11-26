#include "../include/Action.h"

void PrintContentList::act(Session &sess) {
    std::vector<Watchable *> content = sess.getContent();
    for(Watchable *i : content){
        std::cout << i->toString();
    }
}

std::string PrintContentList::toString() const {
    return "PrintContentList " + this->statusToString();
}