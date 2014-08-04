#include "coach.h"

coach::coach(int id, QString handle)
    : _id(id)
    , _handle(handle)
{
}

coach::coach(int id, QString handle, QString name, QString phone, QString email)
    : _id(id)
    , _handle(handle)
    , _name(name)
    , _phone(phone)
    , _email(email)
{

}
