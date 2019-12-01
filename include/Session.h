#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <unordered_map>
#include <string>
#include "Action.h"
#include "json.hpp"
#include <fstream>


class User;
class BaseAction;
class Watchable;

class Session {
public:
    Session(const std::string &configFilePath);
    Session(const Session &sess);
    Session(Session &&sess);
    Session& operator= (const Session& sess);
    Session& operator= (Session&& sess);
    virtual ~Session();

    void start();
    void exit();

    const std::unordered_map<std::string, User *> &getUserMap() const;
    void setActiveUser(User * user);
    User &getActiveUser() const;
    const std::vector<Watchable *> &getContent() const;
    std::vector<BaseAction *> &getActionsLog();
    bool insertNewUser(std::string userName, std::string algo);
    bool insertUser(User *user);
    bool deleteUser(std::string userName);
    void insertAction(BaseAction *action);
private:
    void readData(const std::string &configFilePath);
    void clearAll();
    void cloneAll(const Session &sess);
    void nullifyAll();
    bool isActive;
    std::vector<Watchable *> content;
    std::vector<BaseAction *> actionsLog;
    std::unordered_map<std::string, User *> userMap;
    User *activeUser;
};

#endif