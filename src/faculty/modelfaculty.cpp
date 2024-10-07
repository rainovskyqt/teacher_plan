#include "modelfaculty.h"

ModelFaculty::ModelFaculty(QObject *parent)
    : QStandardItemModel{parent}
    , m_sourceModel(nullptr)
{
}

void ModelFaculty::setSourceModel(ModelStaffList *newSourceModel)
{
    m_sourceModel = newSourceModel;
}

void ModelFaculty::loadByDepartment(int year, int departmentId)
{
    m_sourceModel->loadByDepartment(year, departmentId);
    populate();
    setHorizontalHeaderLabels(QStringList() << "Кафедра");
}

QModelIndex ModelFaculty::getUserIndex(int userId, int departmentId)
{
    auto dep = getItem(invisibleRootItem(), departmentId);
    if(!dep)
        return QModelIndex();

    auto user = getItem(dep, userId);
    if(!user)
        return QModelIndex();

    return indexFromItem(user);
}

QStandardItem *ModelFaculty::getItem(QStandardItem *parent, int id)
{
    for (int row = 0; row < parent->rowCount(); ++row) {
        QStandardItem* item = parent->child(row);
        if (item->data(Qt::UserRole).toInt() == id) {
            return item;
        }
    }
    return nullptr;
}

void ModelFaculty::populate()
{
    clear();
    QMap<QString, QStringList> uniqueStaffMap;
    QMap<QString, int> userIds;
    QMap<QString, int> deprIds;

    for(int row = 0; row < m_sourceModel->rowCount(); ++row){
        QString dName = m_sourceModel->data(m_sourceModel->index(row, ModelStaffList::DepartmentName)).toString();
        int dId = m_sourceModel->data(m_sourceModel->index(row, ModelStaffList::DepartmentId)).toInt();
        QString uName = QString("%1 %2 %3").arg(m_sourceModel->data(m_sourceModel->index(row, ModelStaffList::UserSurname)).toString(),
                                                m_sourceModel->data(m_sourceModel->index(row, ModelStaffList::UserName)).toString(),
                                                m_sourceModel->data(m_sourceModel->index(row, ModelStaffList::UserMiddleName)).toString());
        deprIds.insert(dName, dId);

        if (!uniqueStaffMap[dName].contains(uName)) {
            uniqueStaffMap[dName].append(uName);
            userIds.insert(uName, m_sourceModel->data(m_sourceModel->index(row, ModelStaffList::UserId)).toInt());
        }
    }

    for (auto it = uniqueStaffMap.constBegin(); it != uniqueStaffMap.constEnd(); ++it) {
        const QString& dName = it.key();
        const QStringList& staffNames = it.value();

        QStandardItem* parentItem = new QStandardItem(dName);
        parentItem->setData(deprIds.value(dName), Qt::UserRole);
        parentItem->setData(false, Qt::UserRole + 1);       //Признак что это преподаватель
        appendRow(parentItem);

        for (const QString& uName : staffNames) {
            QStandardItem* childItem = new QStandardItem(uName);
            childItem->setData(userIds.value(uName), Qt::UserRole);
            childItem->setData(true, Qt::UserRole + 1); //Признак что это преподаватель
            parentItem->appendRow(childItem);
        }
    }
}
