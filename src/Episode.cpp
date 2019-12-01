#include "../include/Watchable.h"

Episode::Episode(long id, const std::string &seriesName, int length, int season, int episode,
                 const std::vector<std::string> &tags) : Watchable(id, length, tags),
                 seriesName(seriesName), season(season), episode(episode), nextEpisodeId(id + 1) {}

Watchable* Episode::getNextWatchable(Session & sess) const {
    if(nextEpisodeId != -1){
        return sess.getContent()[nextEpisodeId - 1];
    }
    return sess.getActiveUser().getRecommendation(sess);
}

void Episode::setNextEpisodeId(int nextEpisodeId) { this->nextEpisodeId = nextEpisodeId; }

std::string Episode::toString() const {
    string output = std::to_string(getId()) + ". " + seriesName + " S" + std::to_string(season)
            + "E" + std::to_string(episode) + " " + std::to_string(getLength()) + " minutes " + "[";
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

Episode::~Episode() {}