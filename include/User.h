#ifndef USER_H_
#define USER_H_

#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include "Session.h"

class Watchable;
class Session;

class User{
public:
    User(const std::string& name);
    User(const User &user, std::string dupName);
    virtual Watchable* getRecommendation(Session& s) = 0;
    std::string getName() const;
    std::vector<Watchable*> get_history() const;
    virtual User* clone(std::string dupName) = 0;
protected:
    std::vector<Watchable*> history;
    bool hasWatched(Watchable * watchable);
private:
    std::string name;
};


class LengthRecommenderUser : public User {
public:
    LengthRecommenderUser(const std::string& name);
    LengthRecommenderUser(const LengthRecommenderUser &user, std::string dupName);
    virtual Watchable* getRecommendation(Session& s);
    virtual User* clone(std::string dupName);
private:
    int totalWatchTime;
};

class RerunRecommenderUser : public User {
public:
    RerunRecommenderUser(const std::string& name);
    RerunRecommenderUser(const RerunRecommenderUser &user, std::string dupName);
    virtual Watchable* getRecommendation(Session& s);
    virtual User* clone(std::string dupName);
private:
    int recommendationIndex;
};

class GenreRecommenderUser : public User {
public:
    GenreRecommenderUser(const std::string& name);
    GenreRecommenderUser(const GenreRecommenderUser &user, std::string dupName);
    virtual Watchable* getRecommendation(Session& s);
    virtual User* clone(std::string dupName);
private:
};

#endif
