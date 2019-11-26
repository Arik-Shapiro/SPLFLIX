#include "../include/User.h"

LengthRecommenderUser::LengthRecommenderUser(const std::string &name) : User(name), totalWatchTime(0) {

}

LengthRecommenderUser::LengthRecommenderUser(const LengthRecommenderUser &user, std::string dupName) : User(user, dupName), totalWatchTime(0) {}

User* LengthRecommenderUser::clone(std::string dupName) {
    return new LengthRecommenderUser(*this, dupName);
}

Watchable* LengthRecommenderUser::getRecommendation(Session &s) {
    int avg = totalWatchTime/history.size();
    std::vector<Watchable *> content = s.getContent();
    Watchable* watchable = nullptr;
    bool hasWatched = false;
    for(int i = 0; i < content.size(); i++){
        hasWatched = this->hasWatched(content[i]);
        if(!hasWatched){
            if(watchable == nullptr)
                watchable = content[i];
            else if((abs(content[i]->getLength() - avg) < abs(watchable->getLength() - avg))){
                watchable = content[i];
            }
        }
    }
    return watchable;
}