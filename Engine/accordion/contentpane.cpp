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

#include "qAccordion/contentpane.h"

namespace clickcon = ClickableFrame_constants;

ContentPane::ContentPane(QAccordion *Accordion,QString header, QWidget *parent) : QWidget(parent)
{
    this->content = nullptr;
    this->Accordion = Accordion;

    this->initDefaults(std::move(header));
}

ContentPane::ContentPane(QAccordion *Accordion, QString header, QFrame *content, QWidget *parent)
    : content(content), QWidget(parent)
{
    this->Accordion = Accordion;
    this->initDefaults(std::move(header));
}

void ContentPane::selfRemove()
{
    Accordion->removeContentPane(false,this);
}

void ContentPane::selfUp()
{
    int Index = Accordion->findContentPaneIndex(QString(),nullptr,this);
    if(Index <= 0)
        return;

    Accordion->moveContentPane(Index,Index-1);
}
void ContentPane::selfDown()
{
    int Index = Accordion->findContentPaneIndex(QString(),nullptr,this);
    if(Index == -1 || Index >= Accordion->numberOfContentPanes() - 1)
        return;

    Accordion->moveContentPane(Index,Index+1);
}

bool ContentPane::getActive() { return this->active; }

QFrame *ContentPane::getContentFrame() { return this->content; }

void ContentPane::setContentFrame(QFrame *content)
{
    this->container->layout()->removeWidget(this->content);
    if (this->content != nullptr)
        delete (this->content);
    this->content = content;
    dynamic_cast<QVBoxLayout *>(this->container->layout())
        ->insertWidget(0, this->content);
}

int ContentPane::getMaximumHeight() { return this->container->maximumHeight(); }

void ContentPane::setMaximumHeight(int maxHeight)
{
    this->containerAnimationMaxHeight = maxHeight;

    if (this->getActive())
        this->container->setMaximumHeight(this->containerAnimationMaxHeight);
    this->openAnimation->setEndValue(this->containerAnimationMaxHeight);
    this->closeAnimation->setStartValue(this->containerAnimationMaxHeight);
}

void ContentPane::setHeader(QString header)
{
    this->header->setHeader(std::move(header));
}

QString ContentPane::getHeader() { return this->header->getHeader(); }

void ContentPane::setHeaderTooltip(QString tooltip)
{
    this->header->setToolTip(tooltip);
}

QString ContentPane::getHeaderTooltip() { return this->header->toolTip(); }

void ContentPane::setHeaderStylesheet(QString stylesheet)
{
    this->header->setNormalStylesheet(std::move(stylesheet));
}

QString ContentPane::getHeaderStylesheet()
{
    return this->header->getNormalStylesheet();
}

void ContentPane::setHeaderHoverStylesheet(QString stylesheet)
{
    this->header->setHoverStylesheet(std::move(stylesheet));
}

QString ContentPane::getHeaderHoverStylesheet()
{
    return this->header->getHoverStylesheet();
}

void ContentPane::setHeaderFrameStyle(int style)
{
    this->header->setFrameStyle(style);
}

int ContentPane::getHeaderFrameStyle() { return this->header->frameStyle(); }

void ContentPane::setContainerFrameStyle(int style)
{
    this->container->setFrameStyle(style);
}

int ContentPane::getContainerFrameStyle()
{
    return this->container->frameStyle();
}

void ContentPane::openContentPane()
{
    if (this->getActive())
        return;
    this->openAnimation->start();
    this->header->setCaretPixmap(clickcon::CARRET_ICON_OPENED);
    this->active = true;
}

void ContentPane::closeContentPane()
{
    if (!this->getActive())
        return;
    this->closeAnimation->start();
    this->header->setCaretPixmap(clickcon::CARRET_ICON_CLOSED);
    this->active = false;
}

void ContentPane::initDefaults(QString header)
{
    this->active = false;

    this->headerFrameStyle = QFrame::Shape::StyledPanel | QFrame::Shadow::Raised;
    this->contentPaneFrameStyle =
        QFrame::Shape::StyledPanel | QFrame::Shadow::Plain;
    this->containerAnimationMaxHeight = 150;
    // TODO: Why do I need to set the vertial policy to Maximum? from the api
    // documentation Minimum would make more sens :/
    this->setSizePolicy(QSizePolicy::Policy::Preferred,
                        QSizePolicy::Policy::Maximum);

    this->setLayout(new QVBoxLayout());
    this->layout()->setSpacing(1);
    this->layout()->setContentsMargins(QMargins());

    this->initHeaderFrame(std::move(header));
    this->initContainerContentFrame();
    this->initAnimations();
}

void ContentPane::initHeaderFrame(QString header)
{
    this->header = new ClickableFrame(std::move(header));
    this->header->setFrameStyle(this->headerFrameStyle);
    this->layout()->addWidget(this->header);

    QObject::connect(this->header, &ClickableFrame::singleClick, this,
                     &ContentPane::headerClicked);
}

void ContentPane::initContainerContentFrame()
{
    this->container = new QFrame();
    this->container->setLayout(new QVBoxLayout());
    this->container->setFrameStyle(this->contentPaneFrameStyle);
    this->container->setMaximumHeight(0);
    this->container->setSizePolicy(QSizePolicy::Policy::Preferred,
                                   QSizePolicy::Policy::Preferred);
    this->layout()->addWidget(this->container);

    if (this->content == nullptr) {
        this->content = new QFrame();
    }

    this->container->layout()->addWidget(this->content);
    this->container->layout()->setSpacing(0);
    this->container->layout()->setContentsMargins(QMargins());
}

void ContentPane::initAnimations()
{
    this->openAnimation =
        std::unique_ptr<QPropertyAnimation>(new QPropertyAnimation());
    this->closeAnimation =
        std::unique_ptr<QPropertyAnimation>(new QPropertyAnimation());
    // TODO: Currently these animations only animate maximumHeight. This leads to
    // different behaviour depending on whether the Accordion Widget is placed
    // inside a QScollWidget or not. Maybe we also need to animate minimumHeight
    // as well to get the same effect.
    this->openAnimation->setTargetObject(this->container);
    this->openAnimation->setPropertyName("maximumHeight");
    this->closeAnimation->setTargetObject(this->container);
    this->closeAnimation->setPropertyName("maximumHeight");

    this->openAnimation->setDuration(0);
    this->closeAnimation->setDuration(0);
    this->openAnimation->setStartValue(0);
    this->closeAnimation->setStartValue(this->containerAnimationMaxHeight);
    this->openAnimation->setEndValue(this->containerAnimationMaxHeight);
    this->closeAnimation->setEndValue(0);
    this->openAnimation->setEasingCurve(
        QEasingCurve(QEasingCurve::Type::Linear));
    this->closeAnimation->setEasingCurve(
                QEasingCurve(QEasingCurve::Type::Linear));
}

void ContentPane::headerClicked(QPoint pos) {
    emit this->clicked();
}

void ContentPane::paintEvent(QPaintEvent *event)
{
    QStyleOption o;
    o.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}
