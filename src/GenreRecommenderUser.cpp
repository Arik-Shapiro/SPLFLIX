#include "../include/User.h"

GenreRecommenderUser::GenreRecommenderUser(const std::string &name) : User(name) {}

GenreRecommenderUser::GenreRecommenderUser(const GenreRecommenderUser &user, std::string dupName) : User(user, dupName) {}

User* GenreRecommenderUser::clone(std::string dupName) {
    return new GenreRecommenderUser(*this, dupName);
}

Watchable* GenreRecommenderUser::getRecommendation(Session &s) {

}