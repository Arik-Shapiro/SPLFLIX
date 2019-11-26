#include "../include/Watchable.h"

Episode::Episode(long id, const std::string &seriesName, int length, int season, int episode,
                 const std::vector<std::string> &tags) : Watchable(id, length, tags),
                 seriesName(seriesName), season(season), episode(episode) {}
Watchable* Episode::getNextWatchable(Session &) const {}

std::string Episode::toString() const {
    string output = std::to_string(getId()) + ". " + seriesName + " " + std::to_string(season)
            + std::to_string(episode) + " " + std::to_string(getLength()) + "[";
    vector<string> tags = getTags();
    unsigned long i;
    for(i = 0; i < tags.size() - 1; i++){
        output += tags[i] + ", ";
    }
    output = output + tags[i] + "]";
    return output;
}

Watchable* Episode::clone() {
    return new Episode(*this);
}