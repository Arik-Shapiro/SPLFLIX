#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <unordered_map>
#include <string>
#include "Action.h"
#include "json.hpp"

class User;
class BaseAction;
class Watchable;

class Session {
public:
    Session(const std::string &configFilePath);

    ~Session();

    void start();
    void exit();


    std::unordered_map<std::string, User *> getUserMap();
    void setActiveUser(User * user);
    User* getActiveUser();
    std::vector<Watchable *> getContent();
    std::vector<BaseAction *> getActionsLog();
private:
    std::vector<Watchable *> content;
    std::vector<BaseAction *> actionsLog;
    std::unordered_map<std::string, User *> userMap;
    User *activeUser;
};

#endif
