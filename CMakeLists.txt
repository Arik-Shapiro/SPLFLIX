cmake_minimum_required(VERSION 3.15)
project(SPLFLIX)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(include)
include_directories(src)

add_executable(SPLFLIX
        include/Action.h
        include/json.hpp
        include/Session.h
        include/User.h
        include/Watchable.h
        src/BaseAction.cpp
        src/ChangeActiveUser.cpp
        src/CreateUser.cpp
        src/DeleteUser.cpp
        src/DuplicateUser.cpp
        src/Episode.cpp
        src/Exit.cpp
        src/GenreRecommenderUser.cpp
        src/LengthRecommenderUser.cpp
        src/main.cpp
        src/Movie.cpp
        src/PrintActionsLog.cpp
        src/PrintContentList.cpp
        src/PrintWatchHistory.cpp
        src/RerunRecommenderUser.cpp
        src/Session.cpp
        src/User.cpp
        src/Watch.cpp
        src/Watchable.cpp)
