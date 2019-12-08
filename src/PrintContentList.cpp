#include "../include/Action.h"
PrintContentList::~PrintContentList() {}
void PrintContentList::act(Session &sess) {
    const std::vector<Watchable *> &content = sess.getContent();
    for(Watchable *i : content){
        string output;
        output = std::to_string(i->getId()) + ". " + i->toString() + " " + std::to_string(i->getLength()) + " minutes" + " [";
        vector<string> tags = i->getTags();
        unsigned long l;
        for(l = 0; l < tags.size() - 1; l++){
            output += tags[l] + ", ";
        }
        output = output + tags[l] + "]";
        std::cout << output << endl;
    }
    complete();
}

std::string PrintContentList::toString() const {
    return "PrintContentList " + this->statusToString();
}

BaseAction* PrintContentList::clone() const {
    return new PrintContentList(*this);
}