// This file is part of qAccordion. An Accordion widget for Qt
// Copyright © 2015 Christian Rapp <0x2a at posteo dot org>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef QACCORDION_H
#define QACCORDION_H

#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
#include <QStyleOption>
#include <QSpacerItem>
#include <QString>
#include <QDebug>

#include <vector>
#include <memory>
#include <algorithm>
#include <iterator>

#include "contentpane.h"

class ContentPane;

/**
 * @brief QAccordion base class
 *
 * @details
 * This class is the basis of the qAccordion widget. If you want to add a
 * accordion widget to your gui then you have to create an object of this class.
 *
 * Managing content panes is simpel:
 * * You can either add (addContentPane()) or insert (insertContentPane()) new ContentPanes.
 * * Use removeContentPane() to remove existing ContentPanes.
 * * moveContentPane() allows you to change the order of the ContentPanes.
 * * To change a ContentPane in place use swapContentPane()
 *
 * @note
 * Many of the mentioned functions are overloaded, provided for convenience.
 *
 * @details
 * The signal numberOfContentPanesChanged() is emitted whenever the number of
 * content panes changed.
 *
 * In case of an error you may get a more detailed error description with
 * getError().
 *
 * @warning
 * Currently Headers have to be unique
 *
 */
class QAccordion : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief QAccordion constructor
     * @param parent Optionally provide a parent widget
     */
    explicit QAccordion(QWidget *parent = 0);

    /**
     * @brief Returns the number of content panes
     * @return int
     */
    int numberOfContentPanes();

    /**
     * @brief Add a new content Pane
     * @param header Header of the content pane
     * @return Content pane index
     *
     * @details
     * Use this method to add a new content pane with the Header header.
     * The method will return the index of the new content pane, or <b>-1</b> if
     * the pane was not added because \p header already exists.
     */
    int addContentPane(QString header);
    /**
     * @brief Add a new content Pane
     * @param header Header of the content pane
     * @param contentFrame The content of the pane
     * @return Content pane index
     *
     * @details
     * This is an overloaded method of addContentPane(QString), that
     * allows you to provide your own content frame.
     * @warning
     * Headers have to be unique
     */
    int addContentPane(QString header, QFrame *contentFrame);
    /**
     * @brief Add content pane
     * @param cpane New content pane to add
     * @return Content pane index
     *
     * @details
     * This is an overloaded method of addContentPane(QString), that
     * allows you to provide your own content pane.
     */
    int addContentPane(ContentPane *cpane);
    /**
     * @brief Insert content pane
     * @param index Index of the content pane
     * @param header Header of the content pane
     * @return bool True if insert was successfull
     *
     * @details
     * You can use this method to insert a new content pane at given index with
     * \p header defining the Header. An empty content pane will be created that
     * you can get with getContentPane().
     *
     * Returns true if the insert was successfull.
     */
    bool insertContentPane(uint index, QString header);
    /**
     * @brief Insert content pane
     * @param index Index of the content pane
     * @param header Header of the content pane
     * @param contentFrame Content frame of the content pane
     * @return bool True if insert was successfull
     *
     * @details
     * This is an overloaded method of insertContentPane(uint, QString).
     * Use this method when you already created a content frame that you want to
     * insert.
     * @warning
     * Headers have to be unique
     */
    bool insertContentPane(uint index, QString header, QFrame *contentFrame);
    /**
     * @brief Insert content pane
     * @param index Index of the content pane
     * @param cpane Content Pane to insert
     * @return bool True if insert was successfull
     *
     * @details
     * This is an overloaded method of insertContentPane(uint, QString).
     * Use this method when you already created a content pane that you want to
     * insert.
     */
    bool insertContentPane(uint index, ContentPane *cpane);

    /**
     * @brief Swap the content pane
     * @param index Index of the content pane to swap
     * @param cpane New content pane
     * @return bool True if swap was successfull
     *
     * @details
     * With this method you can replace an existing content pane at \p index with
     * a new one \p cpane.
     *
     * Returns true if the swap was successfull.
     *
     * The old content pane will be __deleted__.
     */
    bool swapContentPane(uint index, ContentPane *cpane);

    /**
     * @brief Remove a content pane
     * @param deleteObject Delete the object and free memory
     * @param index Index of the content pane
     * @return bool
     *
     * @details
     * Remove a content pane at \p index. If \p deleteObject is \p true the
     * object will be deleted. Otherwise it is up to the user to
     * free the allocated memory.
     *
     * Returns true if the pane was removed and false otherwise.
     */
    bool removeContentPane(bool deleteObject, uint index);
    /**
     * @brief Remove a content pane
     * @param deleteObject Delete the object and free memory
     * @param header Header of the content pane
     * @return bool
     *
     * @details
     * This is an overloaded method of removeContentPane(bool, uint).
     */
    bool removeContentPane(bool deleteObject, QString header);
    /**
     * @brief Remove a content pane
     * @param deleteObject Delete the object and free memory
     * @param contentframe Content frame of the content pane
     * @return bool
     *
     * @details
     * This is an overloaded method of removeContentPane(bool, uint).
     */
    bool removeContentPane(bool deleteObject, QFrame *contentframe);
    /**
     * @brief Remove a content pane
     * @param deleteObject Delete the object and free memory
     * @param contentPane The content pane to remove
     * @return bool
     *
     * @details
     * This is an overloaded method of removeContentPane(bool, uint).
     */
    bool removeContentPane(bool deleteObject, ContentPane *contentPane);

    /**
     * @brief Move content pane
     * @param currentIndex The current index of the content pane.
     * @param newIndex The new index of the current pane
     * @return bool
     *
     * @details
     * Moves a content from \p currentIndex to \p newIndex. Returns true if the
     * content pane was moved, false otherwise.
     */
    bool moveContentPane(uint currentIndex, uint newIndex);

    /**
     * @brief Get content pane
     * @param index Index of the content pane
     * @return QFrame* or nullptr
     *
     * @details
     * Get a content pane (QFrame*) with \p index. This method will return a
     * __nullptr__ if the content pane does not exist.
     */
    ContentPane *getContentPane(uint index);

    /**
     * @brief Get the index of a content pane
     * @param header Header of the Content Pane
     * @return Index of the content pane
     *
     * @details
     * Get the index of a ContentPane with \p header. This method will return
     * <b>-1</b> if a ContentPane with this header does not exist.
     */
    int getContentPaneIndex(QString header);
    /**
     * @brief Get the index of a content pane
     * @param contentFrame Content Frame
     * @return Index of the content pane
     *
     * @details
     * This is an overloaded function of getContentPaneIndex(QString)
     */
    int getContentPaneIndex(QFrame *contentFrame);
    /**
     * @brief Get the index of a content pane
     * @param contentPane ContentPane*
     * @return Index of the content pane
     *
     * @details
     * This is an overloaded function of getContentPaneIndex(QString)
     */
    int getContentPaneIndex(ContentPane *contentPane);

    /**
     * @brief Get the index of the active ContentPane
     * @return Vector with indexes of all active ContentPanes
     *
     * @details
     * This method will fill a vector with the index of all active ContentPanes.
     * The vector will be empty if no ContentPane is active
     */
    void getActiveContentPaneIndex(std::vector<int> &indexVector);

    /**
     * @brief Get the number of content panes
     * @return Number of content panes
     */
    int getNumberOfContentPanes();

    /**
     * @brief Allow multiple ContentPane to be open
     * @param status
     *
     * @details
     * This option allows you to open several ContentPane at the same time.
     * @note
     * Default value for this option is \p false.
     */
    void setMultiActive(bool status);
    /**
     * @brief Check status of multiActive
     * @return bool
     *
     * @sa
     * setMultiActive()
     */
    bool getMultiActive();

    /**
     * @brief If collapsible is true you can close all ContentPanes
     * @param status
     *
     * @details
     * With the collapsible option you can control if one content pane has to be
     * open and can't be closed.
     */
    void setCollapsible(bool status);
    /**
     * @brief Get collapsible status
     * @return bool
     * @sa
     * setCollapsible()
     */
    bool getCollapsible();

    /**
     * @brief Get error string
     * @return Error string
     *
     * @details
     * Call this method after a function call failed for a detailed error
     * description.
     */
    QString getError();

    int findContentPaneIndex(QString name = "", QFrame *cframe = nullptr,
                             ContentPane *cpane = nullptr);

signals:
    /**
     * @brief Signals the new number of content panes
     * @param number Number of content panes
     *
     * @details
     * Signal will be emitted if the number of content panes changes
     */
    void numberOfContentPanesChanged(int number);

public slots:

private:
    std::vector<ContentPane *> contentPanes;

    QSpacerItem *spacer;

    QString errorString;

    bool multiActive;
    bool collapsible;

    int internalAddContentPane(QString header, QFrame *cframe = nullptr,
                               ContentPane *cpane = nullptr);
    bool internalInsertContentPane(uint index, QString header,
                                   QFrame *contentFrame = nullptr,
                                   ContentPane *cpane = nullptr);
    bool internalRemoveContentPane(bool deleteOject, int index = -1,
                                   QString name = "",
                                   QFrame *contentFrame = nullptr,
                                   ContentPane *cpane = nullptr);


    bool checkIndexError(uint index, bool sizeIndexAllowed,
                         const QString &errMessage);
    void handleClickedSignal(ContentPane *cpane);

private slots:
    void numberOfPanesChanged(int number);

protected:
    /**
     * @brief paintEvent Reimplement paintEvent to use stylesheets in derived Widgets
     * @param event
     */
    void paintEvent(QPaintEvent *event);
};

#endif // QACCORDION_H
