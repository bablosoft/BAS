#ifndef SUBPROCESSLISTWIDGET_H
#define SUBPROCESSLISTWIDGET_H
#include "engine_global.h"


#include <QCheckBox>
#include <QWidget>
#include "flowlayout.h"
#include "iprocesscomunicator.h"
#include <QHash>
namespace Ui {
class SubprocessListWidget;
}


#include "iskincontroller.h"

namespace BrowserAutomationStudioFramework
{

    class ENGINESHARED_EXPORT SubprocessListWidget : public QWidget
    {
        Q_OBJECT
        FlowLayout *Layout;
        QVBoxLayout *MainLayout;
        QWidget *MainWidget;
        QHash<QCheckBox *,IProcessComunicator*> Data;
        QHash<int, QCheckBox *> Indexes;
        bool AutoStart;
    public:
        explicit SubprocessListWidget(QWidget *parent = 0);
        ~SubprocessListWidget();
        void Clear();
        void Add(IProcessComunicator* Communicator, int index);
        void SetAutoStart(bool AutoStart);

    private:
        Ui::SubprocessListWidget *ui;
        void changeEvent(QEvent *e);
    private slots:
        void ChangedCheckState(bool state);
        void Received(const QString & Message);
        void CommunicatorDestroyed();
    };
}
#endif // SUBPROCESSLISTWIDGET_H
