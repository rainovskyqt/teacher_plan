#ifndef PRINTGENERICWORK_H
#define PRINTGENERICWORK_H

#include "printdata.h"

class PrintGenericWork : public PrintData
{
    Q_OBJECT
public:
    explicit PrintGenericWork(QObject *parent = nullptr);

    QString approvedPost() const;
    void setApprovedPost(const QString &newApprovedPost);
    QString approvedUser() const;
    void setApprovedUser(const QString &newApprovedUser);

private:
    QString m_approvedPost;
    QString m_approvedUser;

};

#endif // PRINTGENERICWORK_H
