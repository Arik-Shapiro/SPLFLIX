#include "../include/User.h"

RerunRecommenderUser::RerunRecommenderUser(const std::string &name) : User(name), recommendationIndex(1) {}

RerunRecommenderUser::RerunRecommenderUser(const RerunRecommenderUser &user, std::string dupName) :
        User(user, dupName), recommendationIndex(user.recommendationIndex) {}

RerunRecommenderUser::RerunRecommenderUser(const RerunRecommenderUser &user, const std::vector<Watchable *> &history) :
        User(user, history), recommendationIndex(user.recommendationIndex) {}
RerunRecommenderUser::~RerunRecommenderUser() {}
User *RerunRecommenderUser::clone(std::string dupName) {
    return new RerunRecommenderUser(*this, dupName);
}

User* RerunRecommenderUser::clone(const std::vector<Watchable *> &history) {
    return new RerunRecommenderUser(*this, history);
}

Watchable *RerunRecommenderUser::getRecommendation(Session &s) {
    Watchable *recommend = history[(recommendationIndex - 1) % history.size()];
    recommendationIndex++;
    return recommend;
}

void RerunRecommenderUser::watch(Watchable *watchable) {
    history.push_back(watchable);
}