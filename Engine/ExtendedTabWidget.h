#pragma once

#include <QWidget>
#include <QIcon>
#include <QPushButton>

QT_BEGIN_NAMESPACE
class QComboBox;
class QStackedWidget;
class QVBoxLayout;
class QHBoxLayout;
class QButtonGroup;
QT_END_NAMESPACE

class ExtendedTabWidget : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex STORED true NOTIFY currentIndexChanged)
    Q_PROPERTY(QStringList pageTitleList READ pageTitleList WRITE setPageTitleList STORED true)
    Q_PROPERTY(QString pageTitle READ pageTitle WRITE setPageTitle STORED false NOTIFY pageTitleChanged)
    Q_PROPERTY(QStringList pageIconList READ pageIconList WRITE setPageIconList STORED true)
    Q_PROPERTY(QIcon pageIcon READ pageIcon WRITE setPageIcon STORED false NOTIFY pageIconChanged)

public:
    ExtendedTabWidget(QWidget *parent = 0);

    QSize sizeHint() const;

    int count() const;
    int currentIndex() const;
    QWidget *widget(int index);
    int indexOf(QWidget* w);

    QStringList pageTitleList() const;
    QString pageTitle() const;

    QStringList pageIconList() const;
    QIcon pageIcon() const;

    bool setVisible(QWidget* w, bool b);
    bool setEnabled(QWidget* w, bool b);

    // For lazy programmers migrating from QTabWidget to this class
    void addTab(QWidget *page, const QString &title)
    { addPage(page, QIcon(), title); }
    void addTab(QWidget *page, const QIcon &icon=QIcon(), const QString &title=QString())
    { addPage(page, icon, title); }

    void setTabText(int index, const QString &title)
    { setPageTitle(index, title); }

public slots:   
    void addPage(QWidget *page, const QIcon &icon=QIcon(), const QString &title=QString());
    void insertPage(int index, QWidget *page, const QIcon &icon=QIcon(), const QString &title=QString());
    void removePage(int index);
    void setCurrentIndex(int index);

    void setPageTitleList(QStringList const &newTitleList);
    void setPageTitle(QString const &newTitle);
    void setPageTitle(int index, QString const &newTitle);

    void setPageIconList(QStringList const &newIconList);
    void setPageIcon(QIcon const &newIcon);

    void HideEmptyTabsAndShowVisibleTabs();

    QPushButton *GetButton(int index);

signals:
    void currentIndexChanged(int index);
    void pageTitleChanged(const QString &title);
    void pageIconChanged(const QIcon &icon);

private:
    QStringList titleList, iconList;

    QStackedWidget *stackWidget;
    QButtonGroup *buttonGroup;
    QHBoxLayout *layout;
    QVBoxLayout *buttonLayout;
};

