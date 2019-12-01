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
	virtual ~BaseAction();
	ActionStatus getStatus() const;
	virtual void act(Session& sess) = 0;
	virtual std::string toString() const = 0;
	std::string statusToString() const;
	virtual BaseAction* clone() const = 0;
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
    virtual ~CreateUser();
    CreateUser(std::string userName, std::string userAlgo);
	virtual void act(Session& sess);
	virtual std::string toString() const;
    virtual BaseAction* clone() const;
private:
    std::string userName;
    std::string userAlgo;
};

class ChangeActiveUser : public BaseAction {
public:
    virtual ~ChangeActiveUser();
    ChangeActiveUser(std::string userToChange);
	virtual void act(Session& sess);
	virtual std::string toString() const;
    virtual BaseAction* clone() const;
private:
    std::string userToChange;
};

class DeleteUser : public BaseAction {
public:
    virtual ~DeleteUser();
    DeleteUser(std::string userToDelete);
	virtual void act(Session & sess);
	virtual std::string toString() const;
    virtual BaseAction* clone() const;
private:
    std::string userToDelete;
};


class DuplicateUser : public BaseAction {
public:
    virtual ~DuplicateUser();
    DuplicateUser(std::string userToDuplicate, std::string newUserName);
	virtual void act(Session & sess);
	virtual std::string toString() const;
    virtual BaseAction* clone() const;
private:
    std::string userToDuplicate;
    std::string newUserName;
};

class PrintContentList : public BaseAction {
public:
    virtual ~PrintContentList();
    virtual void act (Session& sess);
	virtual std::string toString() const;
    virtual BaseAction* clone() const;
};

class PrintWatchHistory : public BaseAction {
public:
    virtual ~PrintWatchHistory();
    virtual void act (Session& sess);
	virtual std::string toString() const;
    virtual BaseAction* clone() const;
};


class Watch : public BaseAction {
public:
    virtual ~Watch();
    Watch(long contentId);
	virtual void act(Session& sess);
	virtual std::string toString() const;
    virtual BaseAction* clone() const;
private:
    long contentId;
};


class PrintActionsLog : public BaseAction {
public:
    virtual ~PrintActionsLog();
    virtual void act(Session& sess);
	virtual std::string toString() const;
    virtual BaseAction* clone() const;
};

class Exit : public BaseAction {
public:
    virtual ~Exit();
    virtual void act(Session& sess);
	virtual std::string toString() const;
    virtual BaseAction* clone() const;
};
#endif
