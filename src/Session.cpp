#include "../include/Session.h"

Session::Session(const std::string &configFilePath) : isActive(true), content(), actionsLog(), userMap(), activeUser(nullptr) {
    userMap["default"] = new LengthRecommenderUser("default");
    activeUser = userMap["default"];
    readData(configFilePath);
}

Session::Session(const Session &sess) : isActive(true), content(), actionsLog(), userMap(), activeUser(nullptr) {
    cloneAll(sess);
}
Session::Session(Session &&sess) : isActive(true), content(std::move(sess.content)), actionsLog(std::move(sess.actionsLog)), userMap(std::move(sess.userMap)), activeUser(sess.activeUser){
    sess.activeUser = nullptr;
}

Session &Session::operator=(const Session &sess) {
    if(this != &sess){
        clearAll();
        cloneAll(sess);
    }
    return *this;
}
Session &Session::operator=(Session &&sess){
    if(this != &sess){
        clearAll();
        this->content = std::move(sess.content);
        this->actionsLog = std::move(sess.actionsLog);
        this->userMap = std::move(sess.userMap);
        this->activeUser = sess.activeUser;
        sess.activeUser = nullptr;
    }
    return *this;
}
const std::unordered_map<std::string, User *> &Session::getUserMap() const {
    return userMap;
}

Session::~Session() {
    clearAll();
}

void Session::start() {
    isActive = true;
    std::cout << "SPLFLIX is now on!" << endl;

    if (userMap.find({"default"}) == userMap.end()) {
        userMap["default"] = new LengthRecommenderUser("default");
    }

    while (isActive) {
        std::string input;
        getline(std::cin, input);
        int space = input.find(" ");
        string command = input.substr(0, space);
        if (command.compare("createuser") == 0) {
            input = input.substr(space + 1, input.size() - space - 1);
            space = input.find(" ");
            string name = input.substr(0, space);
            string algorithm = input.substr(space + 1, input.length() - space - 1);
            BaseAction *createUser = new CreateUser(name, algorithm);
            createUser->act(*this);
            actionsLog.push_back(createUser);
        } else if (command.compare("changeuser") == 0) {
            string name = input.substr(space + 1, input.length() - space - 1);
            BaseAction *changeUser = new ChangeActiveUser(name);
            changeUser->act(*this);
            actionsLog.push_back(changeUser);
        } else if (command.compare("deleteuser") == 0) {
            string name = input.substr(space + 1, input.length() - space - 1);
            BaseAction *deleteUser = new DeleteUser(name);
            deleteUser->act(*this);
            actionsLog.push_back(deleteUser);
        } else if (command.compare("duplicate") == 0) {
            input = input.substr(space + 1, input.length() - space - 1);
            space = input.find(' ');
            std::string nameToCopy = input.substr(0, space);
            string newName = input.substr(space + 1, input.length() - space - 1);
            BaseAction *duplicateUser = new DuplicateUser(nameToCopy, newName);
            duplicateUser->act(*this);
            actionsLog.push_back(duplicateUser);
        } else if (command.compare("content") == 0) {
            BaseAction *printContent = new PrintContentList();
            printContent->act(*this);
            actionsLog.push_back(printContent);
        } else if (command.compare("watchlist") == 0) {
            BaseAction *printWatchList = new PrintWatchHistory();
            printWatchList->act(*this);
            actionsLog.push_back(printWatchList);
        } else if (command.compare("log") == 0) {
            BaseAction *printLog = new PrintActionsLog();
            printLog->act(*this);
            actionsLog.push_back(printLog);
        } else if (command.compare("watch") == 0) {
            std::string id = input.substr(space + 1, input.length() - space - 1);
            BaseAction *watch = new Watch(std::atol(id.c_str()));
            watch->act(*this);
            actionsLog.push_back(watch);
        } else if (command.compare("exit") == 0) {
            BaseAction *exit = new Exit();
            exit->act(*this);
            actionsLog.push_back(exit);
        }
    }
}

void Session::setActiveUser(User *user) {
    activeUser = user;
}

void Session::exit() { isActive = false; }

User &Session::getActiveUser() const {
    return *activeUser;
}

const std::vector<Watchable *> &Session::getContent() const {
    return content;
}

std::vector<BaseAction *> &Session::getActionsLog() {
    return actionsLog;
}

void Session::readData(const std::string &configFilePath) {
    try {
        using json = nlohmann::json ;
        json j;
        std::ifstream reader("../config1.json");
        reader >> j;
        long id = 1;
            for (const auto &movie : j["movies"]) {
                std::string name(movie["name"].get<std::string>());
                int length(movie["length"].get<int>());
                std::vector<std::string> tags(movie["tags"].get<std::vector<std::string>>());
                content.push_back(new Movie(id, name, length, tags));
                id++;
            }
            for (const auto &series : j["tv_series"]) {
                int seasonNum = 1;
                std::string name(series["name"].get<std::string>());
                int length(series["episode_length"].get<int>());
                std::vector<std::string> tags(series["tags"].get<std::vector<std::string>>());
                Episode *lastEpisode;
                for (const auto &season : series["seasons"]) {
                    int episodeNum = 1;
                    for (int seasonLen = 1; seasonLen < season.get<int>(); seasonLen++) {
                        Episode *currentEpisode = new Episode(id, name, length, seasonNum, episodeNum, tags);
                        lastEpisode = currentEpisode;
                        content.push_back(currentEpisode);
                        episodeNum++;
                        id++;
                    }
                    seasonNum++;
                }
                lastEpisode->setNextEpisodeId(-1);
            }
            reader.close();
    } catch (exception &e) {
        // output exception information
        std::cout << "message: " << e.what() << '\n';
    }
}

bool Session::insertNewUser(std::string userName, std::string algo) {
    if(userMap.find({userName}) != userMap.end()){
        return false;
    }
    User *user;
    if(algo == "len")
        user = new LengthRecommenderUser(userName);
    else if(algo == "rer")
        user = new RerunRecommenderUser(userName);
    else if(algo == "gen")
        user = new GenreRecommenderUser(userName);
    else
        return false;
    userMap[user->getName()] = user;
    return true;
}

bool Session::insertUser(User *user) {
    if(userMap.find({user->getName()}) == userMap.end()){
        userMap[user->getName()] = user;
        return true;
    }
    return false;
}
void Session::insertAction(BaseAction *action) {
    actionsLog.push_back(action);
}
bool Session::deleteUser(std::string userName) {
    if(userMap.find({userName}) != userMap.end()){
        User *userToDelete = userMap[userName];
        userMap.erase(userName);
        delete userToDelete;
        return true;
    }
    return false;
}

void Session::clearAll() {
    for (std::pair<std::string, User *> userPair : userMap)
        delete userPair.second;
    for(Watchable *watchable : content)
        delete watchable;
    for(BaseAction *baseAction : actionsLog)
        delete baseAction;
}

void Session::cloneAll(const Session &sess) {
    for(Watchable *watchable : sess.content){
        this->content.push_back(watchable->clone());
    }
    for(std::pair<std::string, User *> user : sess.userMap) {
        std::vector<Watchable *> copyHistory;
        for(Watchable *watchable : user.second->get_history()){
            copyHistory.push_back(this->content[watchable->getId() - 1]);
        }
        userMap[user.first] = user.second->clone(copyHistory);
    }
    activeUser = userMap[sess.getActiveUser().getName()];
    for(BaseAction *action : sess.actionsLog){
        actionsLog.push_back(action->clone());
    }
}





