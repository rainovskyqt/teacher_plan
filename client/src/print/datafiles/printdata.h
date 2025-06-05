#ifndef PRINTDATA_H
#define PRINTDATA_H

#include <QMap>
#include <QObject>

#include "settings.h"


class PrintData : public QObject
{
    Q_OBJECT
public:
    explicit PrintData(QObject *parent = nullptr);

    bool isSecond() const;
    void setSecondSemester(bool newSecondSemester);

protected:
    bool m_secondSemester;

    template<typename T>
    QVector<QMap<int, T>> splitData(QMap<int, T> &originalMap, int landscape){
        int chunkSize = landscape ?
                            Settings::get().maxLandscapeWorkRowCount() :
                            Settings::get().maxPortraitWorkRowCount();
        QVector<QMap<int, T>> chunks;
        QMap<int, T> currentChunk;

        int count = 0;
        for (auto it = originalMap.begin(); it != originalMap.end(); ++it) {
            currentChunk.insert(it.key(), it.value());
            count++;

            if (count == chunkSize) {
                chunks.append(currentChunk);
                currentChunk.clear();
                count = 0;
            }
        }

        if (!currentChunk.isEmpty()) {
            chunks.append(currentChunk);
        }

        return chunks;
    }

};

#endif // PRINTDATA_H
