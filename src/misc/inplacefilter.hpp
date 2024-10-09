#ifndef INPLACE_FILTER_HPP
#define INPLACE_FILTER_HPP

#include <QObject>
#include <QEvent>
#include <QSet>

#include <functional>

class InplaceFilter : public QObject {
    Q_OBJECT
public:
    using TCallback = std::function<bool(QEvent*)>;

    virtual ~InplaceFilter();

    using TEvents = QSet<QEvent::Type>;

    InplaceFilter* set(const TCallback& c, const TEvents& = {});
    static InplaceFilter* make(QObject* obj);

private:
    InplaceFilter(QObject* obj);

    bool eventFilter(QObject* watched, QEvent* event) override;

    TEvents m_types;
    TCallback m_callback;
};

#endif // INPLACE_FILTER_HPP
