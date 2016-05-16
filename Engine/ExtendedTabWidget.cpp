#include <QtGui>

#if QT_VERSION >= 0x050000
    #include <QtWidgets>
#endif

#include "ExtendedTabWidget.h"
#include "every_cpp.h"

ExtendedTabWidget::ExtendedTabWidget(QWidget *parent) : QWidget(parent)
{
    buttonGroup = new QButtonGroup;
    
    stackWidget = new QStackedWidget;
    stackWidget->setFrameShape(QFrame::StyledPanel);

    connect(buttonGroup,  SIGNAL(buttonClicked(int)), this, SLOT(setCurrentIndex(int)));

    buttonLayout = new QVBoxLayout();
    buttonLayout->setSpacing(0);

    QVBoxLayout* buttonStretchLayout = new QVBoxLayout();
    buttonStretchLayout->setSpacing(0);
    buttonStretchLayout->addLayout(buttonLayout);
    buttonStretchLayout->addStretch();

    layout = new QHBoxLayout;
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addLayout(buttonStretchLayout);
    layout->addWidget(stackWidget);
    setLayout(layout);
}

QSize ExtendedTabWidget::sizeHint() const
{
    int xMax=0, yMax=0;
    foreach( QAbstractButton* button, buttonGroup->buttons() )
    {
        xMax = qMax(xMax, button->sizeHint().width());
        yMax = qMax(yMax, button->sizeHint().height());
    }
    return QSize(xMax, yMax);
}

void ExtendedTabWidget::addPage(QWidget *page, const QIcon &icon, const QString &title)
{
    insertPage(count(), page, icon, title);
}

void ExtendedTabWidget::removePage(int index)
{
    QWidget *widget = stackWidget->widget(index);
    stackWidget->removeWidget(widget);
   
    QPushButton* button = (QPushButton*)buttonGroup->button(index);
    buttonLayout->removeWidget(button);
    buttonGroup->removeButton(button);
    delete button;
    
    setCurrentIndex(0);
}

int ExtendedTabWidget::count() const
{
    return stackWidget->count();
}

int ExtendedTabWidget::currentIndex() const
{
    return stackWidget->currentIndex();
}

void ExtendedTabWidget::HideEmptyTabsAndShowVisibleTabs()
{
    int size = count();
    for(int i = 0;i<size;i++)
    {
        QLayout *layout = widget(i)->layout();
        int j = 0;
        bool visible = false;
        while(j < layout->count())
        {
            QLayoutItem* item = layout->itemAt(j);
            if(item)
            {
                QWidget* w = item->widget();
                if(w && w->isVisibleTo(widget(i)))
                {
                    visible = true;
                    break;
                }

            }
            j++;
        }
        buttonGroup->button(i)->setVisible(visible);
    }
}

QPushButton *ExtendedTabWidget::GetButton(int index)
{
    return qobject_cast<QPushButton*>(buttonGroup->button(index));
}

void ExtendedTabWidget::insertPage(int index, QWidget *page, const QIcon &icon, const QString &title)
{
    page->setParent(stackWidget);
    stackWidget->insertWidget(index, page);

    // Set label
    QString label = title;

    
    page->setWindowTitle(label);

    // Set icon
    QIcon pix = icon;
    if( pix.isNull() )
    {
        /*pix = QIcon(iconList.value(index));
        if( pix.isNull() )
        {
            pix = QApplication::style()->standardIcon(QStyle::SP_ArrowUp);
            page->setWindowIcon(pix);
        }*/
    }
    else
        page->setWindowIcon(pix);

    // Add QPushButton
    QPushButton* button = new QPushButton(pix, label);
    button->setObjectName("__qt__passive_pushButton"); //required for interaction within Designer
    button->setCheckable(true);
    if( count()==1 )
        button->setChecked(true);
    buttonGroup->addButton(button, index);
    buttonLayout->addWidget(button);
}

void ExtendedTabWidget::setCurrentIndex(int index)
{
    if( index<0 || index>=count() )
        index = 0;
    if( index != currentIndex() )
    {
        stackWidget->setCurrentIndex(index);
        buttonGroup->button(index)->setChecked(true);
        emit currentIndexChanged(index);
    }
}

QWidget* ExtendedTabWidget::widget(int index)
{
    return stackWidget->widget(index);
}

int ExtendedTabWidget::indexOf(QWidget* widget)
{
    for( int i=0; i<stackWidget->count(); i++ )
    {
        if( stackWidget->widget(i) == widget )
            return i;
    }
    return -1;
}

bool ExtendedTabWidget::setVisible(QWidget* w, bool b)
{
    int index = indexOf(w);
    if( index == -1 ) return false;

    if( currentIndex() == index )
        setCurrentIndex(0);
    buttonGroup->button(index)->setVisible(b);
    return true;
}

bool ExtendedTabWidget::setEnabled(QWidget* w, bool b)
{
    int index = indexOf(w);
    if( index == -1 ) return false;

    if( currentIndex() == index )
        setCurrentIndex(0);
    buttonGroup->button(index)->setEnabled(b);
    return true;
}

QStringList ExtendedTabWidget::pageTitleList() const
{
    QStringList titleList;
    for( int i=0; i<stackWidget->count(); i++ )
        titleList << stackWidget->widget(i)->windowTitle();
    return titleList;
}

QString ExtendedTabWidget::pageTitle() const
{
    if (const QWidget *currentWidget = stackWidget->currentWidget())
        return currentWidget->windowTitle();
    return QString();
}

QStringList ExtendedTabWidget::pageIconList() const
{
    QStringList iconList;
    for( int i=0; i<stackWidget->count(); i++ )
        iconList << stackWidget->widget(i)->windowIcon().name();;
    return iconList;
}

QIcon ExtendedTabWidget::pageIcon() const
{
    if (const QWidget *currentWidget = stackWidget->currentWidget())
        return currentWidget->windowIcon();
    return QIcon();
}

void ExtendedTabWidget::setPageTitleList(QStringList const &newTitleList)
{
    titleList = newTitleList;

    //we have to force translation here
    for( int i=0; i<titleList.count(); ++i )
        titleList[i] = tr(titleList[i].toLatin1());

    if( !count() ) return;
    for( int i=0; i<stackWidget->count() && i<titleList.count(); i++ )
    {
        buttonGroup->button(i)->setText(titleList.at(i));
        stackWidget->widget(i)->setWindowTitle(titleList.at(i));
    }
}

void ExtendedTabWidget::setPageTitle(QString const &newTitle)
{
    if( !count() ) return;
    buttonGroup->button(currentIndex())->setText(newTitle);
    if (QWidget *currentWidget = stackWidget->currentWidget())
        currentWidget->setWindowTitle(newTitle);

    emit pageTitleChanged(newTitle);
}

void ExtendedTabWidget::setPageTitle(int index, QString const &newTitle)
{
    if( index<0 || index>=count() ) return;
    buttonGroup->button(index)->setText(newTitle);
    if (QWidget *currentWidget = stackWidget->widget(index))
        currentWidget->setWindowTitle(newTitle);

    emit pageTitleChanged(newTitle);
}

void ExtendedTabWidget::setPageIconList(QStringList const &newIconList)
{
    iconList = newIconList;

    if( !count() ) return;
    for( int i=0; i<stackWidget->count() && i<newIconList.count(); i++ )
    {
        buttonGroup->button(i)->setIcon(QIcon(newIconList.at(i)));
        stackWidget->widget(i)->setWindowIcon(QIcon(newIconList.at(i)));
    }
}

void ExtendedTabWidget::setPageIcon(QIcon const &newIcon)
{
    buttonGroup->button(currentIndex())->setIcon(newIcon);
    if (QWidget *currentWidget = stackWidget->currentWidget())
        currentWidget->setWindowIcon(newIcon);
    emit pageIconChanged(newIcon);
}
