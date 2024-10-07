#ifndef MODELHEADER_H
#define MODELHEADER_H

#include <QSqlQueryModel>

class ModelHeader : public QSqlQueryModel
{
public:
    ModelHeader();

    void selectData(int userId);
};

#endif // MODELHEADER_H
