#include "../include/User.h"

GenreRecommenderUser::GenreRecommenderUser(const std::string &name) : User(name), tagToAmount() {}

GenreRecommenderUser::GenreRecommenderUser(const GenreRecommenderUser &user, std::string dupName) : User(user,dupName), tagToAmount(user.tagToAmount) {}

GenreRecommenderUser::GenreRecommenderUser(const GenreRecommenderUser &user, const std::vector<Watchable *> &history)
    : User(user, history), tagToAmount(user.tagToAmount) {}


GenreRecommenderUser::~GenreRecommenderUser() {}
User *GenreRecommenderUser::clone(std::string dupName) {
    return new GenreRecommenderUser(*this, dupName);
}

User* GenreRecommenderUser::clone(const std::vector<Watchable *> &history) {
    return new GenreRecommenderUser(*this, history);
}

Watchable *GenreRecommenderUser::getRecommendation(Session &s) {
    Watchable *watchable = findBestTag(s.getContent());
    return watchable;
}

Watchable *GenreRecommenderUser::findBestTag(const std::vector<Watchable *> &content) {
    std::vector<std::pair<std::string, int>> sortedTags;
    for (std::pair<std::string, int> p: tagToAmount) {
        sortedTags.push_back((p));
    }
    std::sort(sortedTags.begin(), sortedTags.end(),
              [](std::pair<std::string, int> const &p1, std::pair<std::string, int> const &p2) {
                  return p1.second == p2.second ? p1.first.compare(p2.first) : p1.second > p2.second;
              });

    for (std::pair<std::string, int> p : sortedTags) {
        string bestTag = p.first;
        for (Watchable *w : content) {
            auto itContent = std::find_if(w->getTags().begin(), w->getTags().end(),
                                          [&bestTag](const std::string &tag) { return tag.compare(bestTag) == 0; });
            if (itContent != w->getTags().end() && !hasWatched(*w)) {
                return w;
            }
        }
    }
    return nullptr;
}

void GenreRecommenderUser::watch(Watchable *watchable) {
    history.push_back(watchable);
    for (std::string tag : watchable->getTags()) {
        if (tagToAmount.find({tag}) == tagToAmount.end())
            tagToAmount.insert({tag, 1});
        else
            tagToAmount[tag]++;
    }
}