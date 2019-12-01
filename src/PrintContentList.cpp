#include "../include/Action.h"
PrintContentList::~PrintContentList() {}
void PrintContentList::act(Session &sess) {
    const std::vector<Watchable *> &content = sess.getContent();
    for(Watchable *i : content){
        std::cout << i->toString() << endl;
    }
    complete();
}

std::string PrintContentList::toString() const {
    return "PrintContentList " + this->statusToString();
}

BaseAction* PrintContentList::clone() const {
    return new PrintContentList(*this);
}