#ifndef MULTISELECT_H
#define MULTISELECT_H

#include <QWidget>
#include "engine_global.h"


namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT MultiSelect : public QWidget
    {
        Q_OBJECT
        QString Type;
    public:
        explicit MultiSelect(QWidget *parent = 0);

    signals:
        void ValueChanged(const QString& Value);
    public slots:
        void Clear();
        void Update(const QString& Type, const QStringList &Lines, QList<int> Selected);
        QStringList GetValues();
        QList<int> GetSelectedIndex();
        QString GetType();
        QString GetSelectedValue();
    private slots:
        void RadioToggle(bool checked);
        void CheckBoxToggle();
        void DragAndDropChanged();
    };
}

#endif // MULTISELECT_H
