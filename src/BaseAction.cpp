#include "../include/Action.h"

BaseAction::BaseAction() : status(PENDING), errorMsg("") {}

ActionStatus BaseAction::getStatus() const { return status; }

void BaseAction::complete() { status = COMPLETED; }

std::string BaseAction::getErrorMsg() const { return errorMsg; }

void BaseAction::error(const std::string &errorMsg) { this->errorMsg = errorMsg; status = ERROR; }

std::string BaseAction::statusToString() const {
    std::string out;
    switch(getStatus()) {
        case ActionStatus::PENDING:
            out = "PENDING:";
            break;
        case ActionStatus::ERROR:
            out = "ERROR:" +getErrorMsg();
            break;
        case ActionStatus::COMPLETED:
            out = "COMPLETED";
            break;
    }
    return out;
}

