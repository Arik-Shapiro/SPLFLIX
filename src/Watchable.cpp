#include "../include/Watchable.h"

Watchable::Watchable(long id, int length, const std::vector<std::string> &tags)
        : id(id), length(length), tags(tags) {}

long Watchable::getId() const {
    return id;
}

int Watchable::getLength() const {
    return length;
}

const std::vector<std::string> &Watchable::getTags() const {
    return tags;
}

Watchable::~Watchable() {

}