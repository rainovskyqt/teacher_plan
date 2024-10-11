#ifndef COMBOBOX_H
#define COMBOBOX_H

#include <QComboBox>
#include <QCompleter>
#include <QKeyEvent>
#include <QObject>
#include <QPainter>

class ComboBox : public QComboBox
{
public:
    ComboBox(QWidget *parent = nullptr);
    void addItem(const QString &item);
    void addItems(const QStringList &items);


        void paintEvent(QPaintEvent* event) override {
            // Создаем объект для рисования
            QPainter painter(this);
            painter.setRenderHint(QPainter::Antialiasing);

            // Рисуем стандартный фон и рамку
            QStyleOptionComboBox opt;
            initStyleOption(&opt);
            style()->drawComplexControl(QStyle::CC_ComboBox, &opt, &painter, this);

            // Получаем текст текущего элемента
            QString text = currentText();
            QRect textRect = opt.rect.adjusted(5, 0, -20, 0);  // Оставляем место для стрелки справа

            // Настраиваем параметры переноса текста
            QTextOption textOption;
            textOption.setWrapMode(QTextOption::WordWrap);

            // Вычисляем область текста с учетом переноса
            QFontMetrics metrics(font());
            QRect boundingRect = metrics.boundingRect(textRect, Qt::TextWordWrap, text);

            // Ограничиваем область отображения текста
            boundingRect.setWidth(textRect.width());

            // Рисуем текст с переносом
            painter.drawText(textRect, Qt::TextWordWrap, text);
    }

    // Переопределим метод, чтобы учитывать высоту с учетом переносов
    QSize minimumSizeHint() const override {
        QSize size = QComboBox::minimumSizeHint();
        QFontMetrics metrics(font());
        QString text = currentText();

        // Рассчитываем высоту с учетом переноса текста
        int textHeight = metrics.boundingRect(QRect(0, 0, width() - 10, 0), Qt::TextWordWrap, text).height();
        size.setHeight(textHeight + 10);  // Добавляем небольшой отступ сверху и снизу

        return size;
    }

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    QCompleter *completer;

    void updateCompleterModel();
};

#endif // COMBOBOX_H
