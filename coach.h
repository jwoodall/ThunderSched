#ifndef COACH_H
#define COACH_H

class coach
{
private:
    int _id;
    QString _handle;
    QString _name;
    QString _phone;
    QString _email;
public:
    coach(int id, QString handle);
    coach(int id, QString handle, QString name, QString phone, QString email);
};

#endif // COACH_H
