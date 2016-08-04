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

#ifndef CLICKABLEFRAME_H
#define CLICKABLEFRAME_H

#include <QFrame>
#include <QMouseEvent>
#include <QString>
#include <QHBoxLayout>
#include <QLabel>
#include <QGraphicsView>

// TODO: No need to use a namespace for our constants as we are using them only
// in this class
namespace ClickableFrame_constants
{
const char *const CARRET_ICON_CLOSED = ":/qAccordionIcons/caret-right.png"; /**< Qt qrc "path" for the closed icon */
const char *const CARRET_ICON_OPENED = ":/qAccordionIcons/caret-bottom.png"; /**< Qt qrc "path" for the opened icon */
}

/**
 * @brief The ClickableFrame class
 *
 * This class represents a clickable QFrame. It is used by a ContentPane. The class
 * is used internally.
 */
class ClickableFrame : public QFrame
{

    Q_OBJECT
public:
    /**
     * @brief ClickableFrame constructor
     * @param header Header of the frame
     * @param parent Parent widget or 0
     * @param f Qt::WindowFlags
     */
    explicit ClickableFrame(QString header, QWidget *parent = 0,
                            Qt::WindowFlags f = 0);

    // TODO: Expose this function to the ContentPane api
    /**
     * @brief Change clickable status
     * @param status
     *
     * @warning
     * This function is currently not exposed by the qAccordion api.
     */
    void setClickable(bool status);
    /**
     * @brief Check if the frame is clickable
     * @return bool
     */
    bool getClickable();
    /**
     * @brief Set the header string
     * @param header
     */
    void setHeader(QString header);
    /**
     * @brief Get the header string
     * @return QString
     */
    QString getHeader();
    /**
     * @brief Set the default stylesheet
     * @param stylesheet
     */
    void setNormalStylesheet(QString stylesheet);
    /**
     * @brief Get the default stylesheet
     * @return QString
     */
    QString getNormalStylesheet();
    /**
     * @brief Set mouseover stylesheet
     * @param stylesheet
     */
    void setHoverStylesheet(QString stylesheet);
    /**
     * @brief Get mouseover stylesheet
     * @return
     */
    QString getHoverStylesheet();

signals:
    /**
     * @brief Signal that is emitted upon a singleclick
     * @param pos
     */
    void singleClick(QPoint pos);

public slots:

    /**
     * @brief Set the caret pixmap
     * @param pixmapPath
     *
     * @details
     * Set the carret pixmap according to the state (expanded, retracted) of the
     * ContentPane that this ClickableFrame belongs to.
     */
    void setCaretPixmap(QString pixmapPath);

private:
    QLabel *caretLabel;
    QLabel *nameLabel;

    QString hoverStylesheet;
    QString normalStylesheet;

    QString header;
    QString tooltip;

    bool clickable;

    void initFrame();

protected:

    /**
     * @brief Reimplemented function to QMouseEvents
     * @param event
     */
    void mousePressEvent(QMouseEvent *event);

    /**
     * @brief Enter event for mouse over effects.
     * @param event
     */
    void enterEvent(QEvent *event);
    /**
     * @brief Leave effect for mouse over effects.
     * @param event
     */
    void leaveEvent(QEvent *event);
};

#endif // CLICKABLEFRAME_H
