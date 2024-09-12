#ifndef WHEEL_BLOCKER_HPP
#define WHEEL_BLOCKER_HPP

#include <QObjectList>

// Blocks wheel events

class WheelBlocker {
public:
    static void make(const QObjectList&);
};

#endif // WHEEL_BLOCKER_HPP
