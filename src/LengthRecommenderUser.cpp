#include "../include/User.h"

LengthRecommenderUser::LengthRecommenderUser(const std::string &name) : User(name), totalWatchTime(0) {

}

LengthRecommenderUser::LengthRecommenderUser(const LengthRecommenderUser &user, std::string dupName) : User(user, dupName), totalWatchTime(user.totalWatchTime) {}

LengthRecommenderUser::LengthRecommenderUser(const LengthRecommenderUser &user, const std::vector<Watchable *> &history)
        : User(user, history), totalWatchTime(user.totalWatchTime) {}
LengthRecommenderUser::~LengthRecommenderUser() {}
User* LengthRecommenderUser::clone(std::string dupName) {
    return new LengthRecommenderUser(*this, dupName);
}

User* LengthRecommenderUser::clone(const std::vector<Watchable *> &history) {
    return new LengthRecommenderUser(*this, history);
}

Watchable* LengthRecommenderUser::getRecommendation(Session &s) {
    int avg = totalWatchTime/history.size();
    const std::vector<Watchable *> &content = s.getContent();
    Watchable* watchable = nullptr;
    bool hasWatched = false;
    for(Watchable *temp : content){
        hasWatched = this->hasWatched(*temp);
        if(!hasWatched){
            if(watchable == nullptr)
                watchable = temp;
            else if((abs(temp->getLength() - avg) < abs(watchable->getLength() - avg))){
                watchable = temp;
            }
        }
    }
    return watchable;
}

void LengthRecommenderUser::watch(Watchable *watchable) {
    history.push_back(watchable);
    totalWatchTime += watchable->getLength();
}