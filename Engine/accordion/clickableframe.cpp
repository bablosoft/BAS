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

#include "qAccordion/clickableframe.h"

ClickableFrame::ClickableFrame(QString header, QWidget *parent,
                               Qt::WindowFlags f)
    : header(header), QFrame(parent, f)
{
    QStringList hl = this->header.split(":");
    hl.removeFirst();
    this->header = hl.join(":");
    this->setAttribute(Qt::WA_Hover, true);
    this->clickable = true;
    this->setCursor(Qt::PointingHandCursor);
    QColor background = this->palette().color(QPalette::ColorRole::Background);
    QColor lighter = background.lighter(110);
    this->normalStylesheet = "";
    this->hoverStylesheet = "background-color: " + lighter.name() + ";";
    this->initFrame();
}

void ClickableFrame::setClickable(bool status)
{
    this->clickable = status;
    if (status) {
        this->setCursor(Qt::PointingHandCursor);
    } else {
        this->setCursor(Qt::ForbiddenCursor);
    }
}

bool ClickableFrame::getClickable() { return this->clickable; }

void ClickableFrame::setHeader(QString header)
{
    this->header = header;
    this->nameLabel->setText(this->header);
}

QString ClickableFrame::getHeader() { return this->header; }

void ClickableFrame::setNormalStylesheet(QString stylesheet)
{
    this->normalStylesheet = stylesheet;
    this->setStyleSheet(this->normalStylesheet);
}

QString ClickableFrame::getNormalStylesheet() { return this->normalStylesheet; }

void ClickableFrame::setHoverStylesheet(QString stylesheet)
{
    this->hoverStylesheet = stylesheet;
}

QString ClickableFrame::getHoverStylesheet() { return this->hoverStylesheet; }

void ClickableFrame::setCaretPixmap(QString pixmapPath)
{
    this->caretLabel->setPixmap(QPixmap(pixmapPath));
}

void ClickableFrame::initFrame()
{
    this->setSizePolicy(QSizePolicy::Policy::Preferred,
                        QSizePolicy::Policy::Fixed);
    this->setLayout(new QHBoxLayout());

    this->caretLabel = new QLabel();
    this->caretLabel->setPixmap(QPixmap(":/qAccordionIcons/caret-right.png"));
    this->layout()->addWidget(this->caretLabel);

    this->nameLabel = new QLabel();
    nameLabel->setText(this->header);
    this->layout()->addWidget(nameLabel);

    dynamic_cast<QHBoxLayout *>(this->layout())->addStretch();

    this->setStyleSheet(this->normalStylesheet);
}

void ClickableFrame::mousePressEvent(QMouseEvent *event)
{
    if (this->clickable) {
        emit this->singleClick(event->pos());
        event->accept();
    } else {
        event->ignore();
    }
}

void ClickableFrame::enterEvent(QEvent *event)
{
    if (this->clickable) {
        this->setStyleSheet(this->hoverStylesheet);
    }
}

void ClickableFrame::leaveEvent(QEvent *event)
{
    if (this->clickable) {
        this->setStyleSheet(this->normalStylesheet);
    }
}
