#ifndef CLEARINGLINE_H
#define CLEARINGLINE_H

#include <QLineEdit>

class ClearingLine : public QLineEdit
{
    Q_OBJECT
public:
    explicit ClearingLine(QWidget *parent = nullptr);

    void setNum(const int num);
    void setNum(const QString &num);

protected:
    void focusInEvent(QFocusEvent *e) override;

signals:
    void valueChanged();

private:
    QString m_original;
};

#endif // CLEARINGLINE_H
