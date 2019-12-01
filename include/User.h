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
    User(const User &user, const std::vector<Watchable *> &history);
    virtual ~User();
    virtual Watchable* getRecommendation(Session& s) = 0;
    std::string getName() const;
    std::vector<Watchable*> get_history() const;
    virtual User* clone(std::string dupName) = 0;
    virtual User* clone(const std::vector<Watchable *> &history) = 0;
    virtual void watch(Watchable *watchable) = 0;
protected:
    std::vector<Watchable*> history;
    bool hasWatched(const Watchable &watchable) const;
private:
    std::string name;
};


class LengthRecommenderUser : public User {
public:
    LengthRecommenderUser(const std::string& name);
    LengthRecommenderUser(const LengthRecommenderUser &user, std::string dupName);
    LengthRecommenderUser(const LengthRecommenderUser &user, const std::vector<Watchable *> &history);
    virtual ~LengthRecommenderUser();
    virtual Watchable* getRecommendation(Session& s);
    virtual User* clone(std::string dupName);
    virtual User* clone(const std::vector<Watchable *> &history);
    virtual void watch(Watchable *watchable);
private:
    int totalWatchTime;
};

class RerunRecommenderUser : public User {
public:
    RerunRecommenderUser(const std::string& name);
    RerunRecommenderUser(const RerunRecommenderUser &user, std::string dupName);
    RerunRecommenderUser(const RerunRecommenderUser &user, const std::vector<Watchable *> &history);
    virtual ~RerunRecommenderUser();
    virtual Watchable* getRecommendation(Session& s);
    virtual User* clone(std::string dupName);
    virtual User* clone(const std::vector<Watchable *> &history);
    virtual void watch(Watchable *watchable);
private:
    long recommendationIndex;
};

class GenreRecommenderUser : public User {
public:
    GenreRecommenderUser(const std::string& name);
    GenreRecommenderUser(const GenreRecommenderUser &user, std::string dupName);
    GenreRecommenderUser(const GenreRecommenderUser &user, const std::vector<Watchable *> &history);
    virtual ~GenreRecommenderUser();
    virtual Watchable* getRecommendation(Session& s);
    virtual User* clone(std::string dupName);
    virtual User* clone(const std::vector<Watchable *> &history);
    virtual void watch(Watchable *watchable);
private:
    std::unordered_map<std::string, int> tagToAmount;
    Watchable* findBestTag(const std::vector<Watchable*>& content);
};

#endif
