#include "Context.h"

Context::Context()
{

}

void Context::setIsv(bool b){
    this->isv=b;
}
void Context::setName(QString name){
    this->name=name;
}
void Context::setValue(QString value){
    this->value=value;
}
bool Context::getIsv(){
    return isv;
}
QString Context::getName(){
    return name;
}
QString Context::getValue(){
    return value;
}
