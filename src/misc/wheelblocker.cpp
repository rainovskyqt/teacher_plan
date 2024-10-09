#include "wheelblocker.hpp"

#include <misc/inplacefilter.hpp>

void WheelBlocker::make(const QObjectList& objs) {
    for(auto* o : objs) {
        InplaceFilter::make(o)->set([](auto) {
            return true;
        }, { QEvent::Wheel });
    }
}
