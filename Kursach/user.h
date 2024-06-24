#ifndef USER_H
#define USER_H
#include<QString>

class User
{
private:
    static User* instance;
    int userId;
    QString userRole;

    User() : userId(0), userRole("") {}

public:
    static User* getInstance();

    void setUserId(int id);
    int getUserId() const;

    void setUserRole(const QString& role);
    QString getUserRole() const;
};

#endif // USER_H
