#ifndef ACTION_H_
#define ACTION_H_

#include <string>
#include <iostream>
#include <unordered_map>
#include "Session.h"
#include "User.h"
#include "Watchable.h"

class Session;
class User;

enum ActionStatus{
	PENDING, COMPLETED, ERROR
};


class BaseAction{
public:
	BaseAction();
	ActionStatus getStatus() const;
	virtual void act(Session& sess)=0;
	virtual std::string toString() const=0;
	std::string statusToString() const;
protected:
	void complete();
	void error(const std::string& errorMsg);
	std::string getErrorMsg() const;
private:
	std::string errorMsg;
	ActionStatus status;
};

class CreateUser  : public BaseAction {
public:
    CreateUser(std::string userName, std::string userAlgo);
	virtual void act(Session& sess);
	virtual std::string toString() const;
private:
    std::string userName;
    std::string userAlgo;
};

class ChangeActiveUser : public BaseAction {
public:
    ChangeActiveUser(std::string userToChange);
	virtual void act(Session& sess);
	virtual std::string toString() const;
private:
    std::string userToChange;
};

class DeleteUser : public BaseAction {
public:
    DeleteUser(std::string userToDelete);
	virtual void act(Session & sess);
	virtual std::string toString() const;
private:
    std::string userToDelete;
};


class DuplicateUser : public BaseAction {
public:
    DuplicateUser(std::string userToDuplicate);
	virtual void act(Session & sess);
	virtual std::string toString() const;
private:
    std::string userToDuplicate;
};

class PrintContentList : public BaseAction {
public:
	virtual void act (Session& sess);
	virtual std::string toString() const;
};

class PrintWatchHistory : public BaseAction {
public:
	virtual void act (Session& sess);
	virtual std::string toString() const;
};


class Watch : public BaseAction {
public:
    Watch(long contentId);
	virtual void act(Session& sess);
	virtual std::string toString() const;
private:
    long contentId;
};


class PrintActionsLog : public BaseAction {
public:
	virtual void act(Session& sess);
	virtual std::string toString() const;
};

class Exit : public BaseAction {
public:
	virtual void act(Session& sess);
	virtual std::string toString() const;
};
#endif
