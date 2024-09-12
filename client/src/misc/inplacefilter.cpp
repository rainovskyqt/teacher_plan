#include "inplacefilter.hpp"

InplaceFilter::InplaceFilter(QObject* obj)
    : QObject(obj) {
}

InplaceFilter::~InplaceFilter() {
}

InplaceFilter* InplaceFilter::set(const TCallback& c, const TEvents& ev) {
    m_callback = c;
    m_types = ev;
    parent()->installEventFilter(this);
    return this;
}

InplaceFilter* InplaceFilter::make(QObject* obj) {
    return new InplaceFilter(obj);
}

bool InplaceFilter::eventFilter(QObject* watched, QEvent* event) {
    if (!m_types.isEmpty()) {
        if (!m_types.contains(event->type()))
            return QObject::eventFilter(watched, event);
    }

    if (m_callback(event))
        return true;

    return QObject::eventFilter(watched, event);
}
