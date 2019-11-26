#include "../include/User.h"

RerunRecommenderUser::RerunRecommenderUser(const std::string &name) : User(name), recommendationIndex(0) {}

RerunRecommenderUser::RerunRecommenderUser(const RerunRecommenderUser &user, std::string dupName) :
        User(user, dupName), recommendationIndex(0) {}

User *RerunRecommenderUser::clone(std::string dupName) {
    return new RerunRecommenderUser(*this, dupName);
}

Watchable *RerunRecommenderUser::getRecommendation(Session &s) {
    recommendationIndex++;
    return history[recommendationIndex - 1 % history.size()];
}