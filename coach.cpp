#include "coach.h"

player::coach(int id, QString handle)
    : _id(id)
    , _handle(handle)
{
}

player::coach(int id, QString handle, QString name, QString phone, QString email)
    : _id(id)
    , _handle(handle)
    , _name(name)
    , _phone(phone)
    , _email(email)
{

}
