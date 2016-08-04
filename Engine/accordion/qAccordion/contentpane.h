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

#ifndef CONTENTPANE_H
#define CONTENTPANE_H

#include <QWidget>
#include <QFrame>
#include <QHBoxLayout>
#include <QStyleOption>
#include <QPainter>
#include <QString>
#include <QPropertyAnimation>
#include <QPoint>

#include <memory>

#include "clickableframe.h"
#include "qaccordion.h"

// TODO: Do i really need to export the ClickableFrame class?
/**
 * @brief Content Pane class
 *
 * @details
 * Content Panes are part of a QAccordion object. They represent a clickable
 * Header and can be expanded or retracted.
 *
 * When a ContentPane is created you have to provide a Header (ContentPane(QString, QWidget*))
 * and, if you want, a QFrame* (ContentPane(QString, QFrame*, QWidget*)) with the
 * content that should be displayed when the ContentPane is expanded.
 *
 * Managing the content is pretty straight forward use getContentFrame() and setContentFrame()
 * to manage the content. You are absolutely free to do anything what you like with
 * this QFrame. Just keep in mind there is a maximumHeight for the container in which
 * the content frame is placed (currently 150). If your content exceeds this height
 * you have to either increase it with setMaximumHeight() or add a [QScrollArea](http://doc.qt.io/qt-5/qscrollarea.html)
 * to the content frame. You may use setContainerFrameStyle() to change the frame
 * style of the container.
 *
 * The Header can be changed after the creation of the ContentPane with setHeader().
 * Additionally you can set a tooltip, a standard stylesheet and a mouseover
 * stylesheet, and the frame style.
 * @sa
 * setHeaderTooltip(), setHeaderStylesheet(), setHeaderHoverStylesheet(),
 * setHeaderFrameStyle()
 *
 * @details
 * The animation speed is influenceable setAnimationDuration().
 */
class QAccordion;
class ContentPane : public QWidget
{
    Q_OBJECT
    QAccordion *Accordion;
public:
    /**
     * @brief ContentPane constructor
     * @param header The Header of the content pane
     * @param parent Parent widget or 0
     */
    explicit ContentPane(QAccordion *Accordion, QString header, QWidget *parent = 0);
    /**
     * @brief ContentPane constructor
     * @param header The Header of the content pane
     * @param content Content to display when expanded
     * @param parent Parent widget or 0
     */
    explicit ContentPane(QAccordion *Accordion, QString header, QFrame *content, QWidget *parent = 0);
    /**
     * @brief Check if this Content pane is active
     * @return boolean True if active
     */
    bool getActive();

    /**
     * @brief Get the content frame of the content pane
     * @return QFrame*
     *
     * @details
     * Use this method to get a pointer to a QFrame where you can place
     * your content. The widget lifetime is managed by qAccordion.
     */
    QFrame *getContentFrame();
    /**
     * @brief Set the content frame
     * @param content QFrame* with your content
     *
     * Set / change the content frame of this content pane with \p content. The
     * lifecycle
     */
    void setContentFrame(QFrame *content);

    /**
     * @brief Get the maximum height of the content pane container frame
     * @return int
     */
    int getMaximumHeight();
    /**
     * @brief Set the maximum height of the content pane container.
     * @param maxHeight
     *
     * @details
     * Every content pane has a container frame that defines the visible maximum
     * height. With this function you can change this setting.
     *
       @note
     * This setting does not set the maximum height of the content frame. It is
     * the users responsibilty to make sure everything in the content frame is
     * visible. This can be influenced by either changing the maximum height of the
     * container or for example by adding a [QScrollArea](http://doc.qt.io/qt-5.5/qscrollarea.html).
     */
    void setMaximumHeight(int maxHeight);

    /**
     * @brief Return the header of the content pane
     * @return QString
     */
    QString getHeader();
    /**
     * @brief Set header tooltip
     * @param tooltip String to show as tooltip
     *
     * @details
     * Set a string as header tooltip that will be shown when the mouse hovers
     * over the header area.
     */
    void setHeaderTooltip(QString tooltip);
    /**
     * @brief Get the header tooltip
     * @return Tooltip as QString
     *
     * @details
     * Get the header tooltip as QString.
     */
    QString getHeaderTooltip();
    /**
     * @brief Set a stylesheet for the header frame
     * @param stylesheet CSS Style Sheet as string
     *
     * @details
     * You can use [Cascading Style Sheets](http://doc.qt.io/qt-5/stylesheet.html) as supported by Qt to
     * style the header. This is the standard style sheet. You may also set a
     * style for mouse over with setHeaderHoverStylesheet().
     */
    void setHeaderStylesheet(QString stylesheet);
    /**
     * @brief Get the current header style sheet
     * @return CSS string
     *
     * @details
     * Get the css of the content pane header as QString.
     */
    QString getHeaderStylesheet();
    /**
     * @brief Set a stylesheet for the header frame when the mouse hovers over it
     * @param stylesheet CSS Style Sheet as string
     *
     * @details
     * Set a \p stylesheet for the header for a special effect when the mouse
     * hovers over it.
     * @sa
     * setHeaderStylesheet() for additional details.
     */
    void setHeaderHoverStylesheet(QString stylesheet);
    /**
     * @brief Get the mouse over header style sheet
     * @return CSS Style Sheet as string
     *
     * @details
     * Returns the mouse over header style sheet.
     */
    QString getHeaderHoverStylesheet();
    /**
     * @brief Set the header frame style
     * @param style
     *
     * @details
     * The style is the bitwise OR between a frame shape and a frame shadow style.
     * See the [Qt Documentation](http://doc.qt.io/qt-5/qframe.html#setFrameStyle) for additional details.
     */
    void setHeaderFrameStyle(int style);
    /**
     * @brief Get the header frame style
     * @return int
     *
     * @sa
     * setHeaderFrameStyle() for additional information.
     */
    int getHeaderFrameStyle();
    /**
     * @brief Set the container frame style
     * @param style
     *
     * @sa
     * setHeaderFrameStyle() for additional information
     */
    void setContainerFrameStyle(int style);
    /**
     * @brief Get the container frame style
     * @return int
     *
     * @sa
     * setHeaderFrameStyle() for additional information
     */
    int getContainerFrameStyle();
    /**
     * @brief Set the duration for the open and close animation
     * @param duration Duration in milliseconds
     *
     * @details
     * Set the duration of the QPropertyAnimation in milliseconds.
     */
    void setAnimationDuration(uint duration);
    /**
     * @brief Get the duration of the open, close animation.
     * @return Duration in milliseconds
     */
    uint getAnimationDuration();

signals:

    /**
     * @brief Clicked signal is emitted when the header is clicked
     */
    void clicked();
    /**
     * @brief Signal will be emitted after the open animation finished
     */
    void isActive();
    /**
     * @brief Signal will be emitted after the close animation finished
     */
    void isInactive();

public slots:

    /**
     * @brief Slot that is called when the header has been triggered
     * @param pos Currently unused
     *
     * @details
     * This slot is used to notify the ContentPane widget that the header
     * has been triggered. You can use this slot yourself to open or close the
     * ContentPane. Check the state of the pane before with getActive() as this
     * slot might not do what you intended to do (for example you want to close
     * the ContentPane. If it is already inactive and you call this slot without
     * checking the state it will be opened).
     */
    void headerClicked(QPoint pos);

    /**
     * @brief Set the header of the content pane
     * @param header
     */
    void setHeader(QString header);

    void selfRemove();
    void selfUp();
    void selfDown();

private:
    // yeah we are friends. this is important to keep openContentPane and
    // closeContentPane private
    friend class QAccordion;

    ClickableFrame *header;
    QFrame *container;
    QFrame *content;

    int headerFrameStyle;
    int contentPaneFrameStyle;
    int containerAnimationMaxHeight;

    bool active;

    std::unique_ptr<QPropertyAnimation> openAnimation;
    std::unique_ptr<QPropertyAnimation> closeAnimation;

    void initDefaults(QString header);
    void initHeaderFrame(QString header);
    void initContainerContentFrame();
    void initAnimations();

private slots:

    /**
     * @brief Open the content pane
     *
     * @details
     * This will open the content pane if it is currently closed.
     * @warning
     * Currently there is no inbuild mechanism to close an already open
     * Content Pane when you open another one programmatically. Meaning you have
     * to take care of this yourself.
     */
    void openContentPane();
    /**
     * @brief Close the content pane
     *
     * @details
     * This will close the content pane if it is currently open.
     */
    void closeContentPane();

protected:
    /**
     * @brief paintEvent Reimplement paintEvent to use stylesheets in derived Widgets
     * @param event
     */
    void paintEvent(QPaintEvent *event);
};

#endif // CONTENTPANE_H
