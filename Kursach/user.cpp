#include "user.h"
User* User::instance = nullptr;

User* User::getInstance() {
    if (!instance) {
        instance = new User();
    }
    return instance;
}

void User::setUserId(int id) {
    userId = id;
}

int User::getUserId() const {
    return userId;
}

void User::setUserRole(const QString& role) {
    userRole = role;
}

QString User::getUserRole() const {
    return userRole;
}
