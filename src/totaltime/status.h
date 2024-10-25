#ifndef STATUS_H
#define STATUS_H

#include <QString>


class Status{

public:
    static QString less() {return "background-color: rgb(255, 255, 0);"; }
    static QString more() {return "background-color: rgb(255, 0, 0);"; }
    static QString equal() {return "background-color: rgb(0, 255, 0);"; }
};

#endif // STATUS_H
