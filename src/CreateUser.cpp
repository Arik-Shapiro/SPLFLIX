#include "../include/Action.h"

CreateUser::CreateUser(std::string userName, std::string userAlgo) : userName(userName), userAlgo(userAlgo) {}

void CreateUser::act(Session &sess) {
    std::unordered_map<std::string,User*> userMap = sess.getUserMap();
    User * user = nullptr;
    if(userAlgo == "len")
        user = new LengthRecommenderUser(userName);
    else if(userAlgo == "rer")
        user = new RerunRecommenderUser(userName);
    else if(userAlgo == "gen")
        user = new GenreRecommenderUser(userName);
    else
        error("Error - bad algorithm input");
    if(user != nullptr) {
        userMap.insert({userName, user});
        complete();
    }
}

std::string CreateUser::toString() const {
    return "CreateUser " + this->statusToString();
}
