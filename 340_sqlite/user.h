#ifndef USER_H
#define USER_H

class User
{
public:
    User(int p_UserID, string p_Username, string p_Password) :
        m_UserID(p_UserID), m_Username(p_Username), m_Password(p_Password)
    {
    }

    int GetUserID()         { return m_UserID;}
    string GetUsername()    { return m_Username;}
    string GetPassword()    { return m_Password;}

private:
    int m_UserID;
    string m_Username;
    string m_Password;
};

#endif // USER_H
