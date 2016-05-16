/****************************************************************************
 **
 ** Copyright (C) Qxt Foundation. Some rights reserved.
 **
 ** This file is part of the QxtGui module of the Qxt library.
 **
 ** This library is free software; you can redistribute it and/or modify it
 ** under the terms of the Common Public License, version 1.0, as published
 ** by IBM, and/or under the terms of the GNU Lesser General Public License,
 ** version 2.1, as published by the Free Software Foundation.
 **
 ** This file is provided "AS IS", without WARRANTIES OR CONDITIONS OF ANY
 ** KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY
 ** WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR
 ** FITNESS FOR A PARTICULAR PURPOSE.
 **
 ** You should have received a copy of the CPL and the LGPL along with this
 ** file. See the LICENSE file and the cpl1.0.txt/lgpl-2.1.txt files
 ** included with the source distribution for more information.
 ** If you did not receive a copy of the licenses, contact the Qxt Foundation.
 **
 ** <http://libqxt.org>  <foundation@libqxt.org>
 **
 ****************************************************************************/
#include "qxtcheckcombobox.h"
#include <QKeyEvent>
#include <QDebug>
#include <QStylePainter>



bool QxtCheckComboBox::eventFilter(QObject* receiver, QEvent* event)
{
    if(event->type() == QEvent::MouseButtonPress && receiver == Edit)
    {
        if(Edit->underMouse())
        {
            showPopup();
        }
        else
        {
            hidePopup();
        }
        return true;
    }




    switch (event->type())
    {
    case QEvent::KeyPress:
    case QEvent::KeyRelease:
    {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        if (receiver == this && (keyEvent->key() == Qt::Key_Up || keyEvent->key() == Qt::Key_Down))
        {
            showPopup();
            return true;
        }
        else if (keyEvent->key() == Qt::Key_Enter ||
                 keyEvent->key() == Qt::Key_Return ||
                 keyEvent->key() == Qt::Key_Escape)
        {
            // it is important to call QComboBox implementation
            QComboBox::hidePopup();
            if (keyEvent->key() != Qt::Key_Escape)
                return true;
        }
    }
    case QEvent::MouseButtonPress:
        containerMousePress = (receiver == view()->window());
        break;
    case QEvent::MouseButtonRelease:

        containerMousePress = false;
        break;
    default:
        break;
    }
    return false;
}



void QxtCheckComboBox::updateCheckedItems()
{
    QStringList items = checkedItems();
    QList<int> indexes = checkedIndexes();
    if (items.isEmpty())
    {
        //text = _defaultText;
        setEditText(_defaultText);
    }
    else
    {
        //text = items.join(_separator);
        setEditText(items.join(_separator));
    }

    // TODO: find a way to recalculate a meaningful size hint

    emit checkedItemsChanged(items);
    QList<int> New = indexes,Old = LastItemsSelected;
    LastItemsSelected = indexes;

    emit checkedIndexesChanged(Old,New);
}

/*void QxtCheckComboBox::paintEvent(QPaintEvent *event)
{
    (void)event;

    QStylePainter painter(this);

    painter.setPen(palette().color(QPalette::Text));

    QStyleOptionComboBox option;

    initStyleOption(&option);

    painter.drawComplexControl(QStyle::CC_ComboBox, option);

    QRect textRect = rect().adjusted(mDisplayRectDelta.left(), mDisplayRectDelta.top(),
                                     mDisplayRectDelta.right(), mDisplayRectDelta.bottom());

    painter.drawText(textRect, Qt::AlignVCenter, text);
}*/

void QxtCheckComboBox::toggleCheckState(int index)
{
    QVariant value = itemData(index, Qt::CheckStateRole);
    if (value.isValid())
    {
        Qt::CheckState state = static_cast<Qt::CheckState>(value.toInt());
        setItemData(index, (state == Qt::Unchecked ? Qt::Checked : Qt::Unchecked), Qt::CheckStateRole);
    }
}

QxtCheckComboModel::QxtCheckComboModel(QObject* parent)
        : QStandardItemModel(0, 1, parent) // rows,cols
{
}

Qt::ItemFlags QxtCheckComboModel::flags(const QModelIndex& index) const
{
    return QStandardItemModel::flags(index) | Qt::ItemIsUserCheckable;

}

QVariant QxtCheckComboModel::data(const QModelIndex& index, int role) const
{
    QVariant value = QStandardItemModel::data(index, role);
    if (index.isValid() && role == Qt::CheckStateRole && !value.isValid())
        value = Qt::Unchecked;
    return value;
}

bool QxtCheckComboModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    bool ok = QStandardItemModel::setData(index, value, role);
    if (ok && role == Qt::CheckStateRole)
    {
        emit dataChanged(index, index);
        emit checkStateChanged();
    }
    return ok;
}

/*!
    \class QxtCheckComboBox
    \inmodule QxtGui
    \brief The QxtCheckComboBox widget is an extended QComboBox with checkable items.

    QxtComboBox is a specialized combo box with checkable items.
    Checked items are collected together in the line edit.

    \code
    QxtCheckComboBox* comboBox = new QxtCheckComboBox(this);
    comboBox->addItems(...);
    comboBox->setItemCheckState(2, Qt::Checked);
    comboBox->setItemCheckState(4, Qt::Checked);
    // OR
    comboBox->setCheckedItems(QStringList() << "dolor" << "amet");
    \endcode

    \image qxtcheckcombobox.png "QxtCheckComboBox in Plastique style."
 */

/*!
    \fn QxtCheckComboBox::checkedItemsChanged(const QStringList& items)

    This signal is emitted whenever the checked \a items have been changed.
 */

/*!
    Constructs a new QxtCheckComboBox with \a parent.
 */
QxtCheckComboBox::QxtCheckComboBox(QWidget* parent) : QComboBox(parent), mDisplayRectDelta(4, 1, -25, 0)
{
    QListView * listView = new QListView(this);

    QPalette palette;


    palette.setColor(QPalette::Window, QColor( 200 , 200 , 200 ));

    palette.setColor(QPalette::Base, QColor( 55, 55 , 55 ));

    listView->setPalette(palette);
    setView(listView);

    _separator = QLatin1String(",");
    setModel(new QxtCheckComboModel(this));
    connect(this, SIGNAL(activated(int)), this, SLOT(toggleCheckState(int)));
    connect(model(), SIGNAL(checkStateChanged()), this, SLOT(updateCheckedItems()));
    connect(model(), SIGNAL(rowsInserted(const QModelIndex &, int, int)), this, SLOT(updateCheckedItems()));
    connect(model(), SIGNAL(rowsRemoved(const QModelIndex &, int, int)), this, SLOT(updateCheckedItems()));

    // read-only contents
    Edit = new QLineEdit(this);
    Edit->setReadOnly(true);
    setLineEdit(Edit);
    Edit->disconnect(this);
    Edit->installEventFilter(this);
    Edit->setEnabled(false);
    setInsertPolicy(QComboBox::NoInsert);

    view()->installEventFilter(this);
    view()->window()->installEventFilter(this);
    view()->viewport()->installEventFilter(this);
    this->installEventFilter(this);
}

/*!
    Destructs the combo box.
 */
QxtCheckComboBox::~QxtCheckComboBox()
{
}

/*!
    \reimp
 */
void QxtCheckComboBox::hidePopup()
{
    if (containerMousePress)
    {
        QComboBox::hidePopup();
    }
}
void QxtCheckComboBox::showPopup()
{
    QComboBox::showPopup();
}

/*!
    Returns the check state of the item at \a index.
 */
Qt::CheckState QxtCheckComboBox::itemCheckState(int index) const
{
    return static_cast<Qt::CheckState>(itemData(index, Qt::CheckStateRole).toInt());
}

/*!
    Sets the check \a state of the item at \a index.
 */
void QxtCheckComboBox::setItemCheckState(int index, Qt::CheckState state)
{
    setItemData(index, state, Qt::CheckStateRole);
}

/*!
    \property QxtCheckComboBox::checkedItems
    \brief the checked items.
 */
QStringList QxtCheckComboBox::checkedItems() const
{
    QStringList items;
    if (model())
    {
        QModelIndex index = model()->index(0, modelColumn(), rootModelIndex());
        QModelIndexList indexes = model()->match(index, Qt::CheckStateRole, Qt::Checked, -1, Qt::MatchExactly);
        foreach(const QModelIndex& index, indexes)
        items += index.data().toString();
    }
    return items;
}

QStringList QxtCheckComboBox::checkedData() const
{
    QStringList items;
    if (model())
    {
        QModelIndex index = model()->index(0, modelColumn(), rootModelIndex());
        QModelIndexList indexes = model()->match(index, Qt::CheckStateRole, Qt::Checked, -1, Qt::MatchExactly);
        foreach(const QModelIndex& index, indexes)
            items += index.data(Qt::UserRole).toString();
    }
    return items;
}


QList<int> QxtCheckComboBox::checkedIndexes()
{
    QList<int> items;
    if (model())
    {
        QModelIndex index = model()->index(0, modelColumn(), rootModelIndex());
        QModelIndexList indexes = model()->match(index, Qt::CheckStateRole, Qt::Checked, -1, Qt::MatchExactly);
        foreach(const QModelIndex& index, indexes)
            items += index.row();
    }
    return items;
}

void QxtCheckComboBox::setCheckedItems(const QStringList& items)
{
    // not the most efficient solution but most likely nobody
    // will put too many items into a combo box anyway so...
    foreach(const QString& text, items)
    {
        const int index = findText(text);
        setItemCheckState(index, index != -1 ? Qt::Checked : Qt::Unchecked);
    }
}

void QxtCheckComboBox::setCheckedData(const QStringList& items)
{
    foreach(const QString& text, items)
    {
        const int index = findData(text);
        setItemCheckState(index, index != -1 ? Qt::Checked : Qt::Unchecked);
    }
}

void QxtCheckComboBox::setCheckedIndexes(const QList<int>& indexes)
{

    for(int index = 0;index<model()->rowCount();index ++)
    {
        setItemCheckState(index, indexes.contains(index) ? Qt::Checked : Qt::Unchecked);
    }
    LastItemsSelected = indexes;
}

QList<int> QxtCheckComboBox::currentIndexes()
{
    return LastItemsSelected;
}

/*!
    \property QxtCheckComboBox::defaultText
    \brief the default text.

    The default text is shown when there are no checked items.
    The default value is an empty string.
 */
QString QxtCheckComboBox::defaultText() const
{
    return _defaultText;
}

void QxtCheckComboBox::setDefaultText(const QString& text)
{
    if (_defaultText != text)
    {
        _defaultText = text;
        this->updateCheckedItems();
    }
}

/*!
    \property QxtCheckComboBox::separator
    \brief the default separator.

    The checked items are joined together with the separator string.
    The default value is a comma (",").
 */
QString QxtCheckComboBox::separator() const
{
    return _separator;
}

void QxtCheckComboBox::setSeparator(const QString& separator)
{
    if (_separator != separator)
    {
        _separator = separator;
        updateCheckedItems();
    }
}
