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

#include "qAccordion/qaccordion.h"

namespace clickcon = ClickableFrame_constants;

QAccordion::QAccordion(QWidget *parent) : QWidget(parent)
{
    // make sure our resource file gets initialized
    //Q_INIT_RESOURCE(qaccordionicons);

    this->multiActive = false;
    this->collapsible = true;

    // set our basic layout
    this->setLayout(new QVBoxLayout());

    // add a stretch to the end so all content panes are at the top
    dynamic_cast<QVBoxLayout *>(this->layout())->addStretch();
    this->layout()->setSpacing(1);
    this->layout()->setContentsMargins(QMargins());
    // TODO: Do we need to keep a pointer to the spacer?
    this->spacer = dynamic_cast<QSpacerItem *>(this->layout()->itemAt(0));

    // seome things we want to do if the number of panes change
    QObject::connect(this, &QAccordion::numberOfContentPanesChanged, this,
                     &QAccordion::numberOfPanesChanged);
}

int QAccordion::numberOfContentPanes() { return this->contentPanes.size(); }

int QAccordion::addContentPane(QString header)
{
    return this->internalAddContentPane(std::move(header));
}

int QAccordion::addContentPane(QString header, QFrame *contentFrame)
{
    return this->internalAddContentPane(std::move(header), contentFrame);
}

int QAccordion::addContentPane(ContentPane *cpane)
{
    return this->internalAddContentPane("", nullptr, cpane);
}

bool QAccordion::insertContentPane(uint index, QString header)
{
    return this->internalInsertContentPane(index, header);
}

bool QAccordion::insertContentPane(uint index, QString header,
                                   QFrame *contentFrame)
{
    return this->internalInsertContentPane(index, header, contentFrame);
}

bool QAccordion::insertContentPane(uint index, ContentPane *cpane)
{
    return this->internalInsertContentPane(index, "", nullptr, cpane);
}

bool QAccordion::swapContentPane(uint index, ContentPane *cpane)
{
    if (this->checkIndexError(index, false,
                              "Can not swap content pane at index " +
                                  QString::number(index) +
                                  ". Index out of range.")) {
        return false;
    }

    if (this->findContentPaneIndex("", nullptr, cpane) != -1) {
        this->errorString = "Can not swap content pane as new pane is already "
                            "managed by accordion widget";
        return false;
    }

    // remove the old content pane from the accordion layout
    dynamic_cast<QVBoxLayout *>(this->layout())
        ->removeWidget(this->contentPanes.at(index));
    delete this->contentPanes.at(index);

    // add the new content pane to the appropriate vector
    this->contentPanes.at(index) = cpane;

    // add the new content pane to the layout
    dynamic_cast<QVBoxLayout *>(this->layout())
        ->insertWidget(index, this->contentPanes.at(index));

    return true;
}

bool QAccordion::removeContentPane(bool deleteObject, uint index)
{
    return this->internalRemoveContentPane(deleteObject, index);
}

bool QAccordion::removeContentPane(bool deleteObject, QString header)
{
    return this->internalRemoveContentPane(deleteObject, -1, header);
}

bool QAccordion::removeContentPane(bool deleteObject, QFrame *contentframe)
{
    return this->internalRemoveContentPane(deleteObject, -1, "", contentframe);
}

bool QAccordion::removeContentPane(bool deleteObject, ContentPane *contentPane)
{
    return this->internalRemoveContentPane(deleteObject, -1, "", nullptr,
                                           contentPane);
}

bool QAccordion::moveContentPane(uint currentIndex, uint newIndex)
{
    if (this->checkIndexError(currentIndex, false,
                              "Can not move from " +
                                  QString::number(currentIndex) +
                                  ". Index out of range.") ||
        this->checkIndexError(newIndex, false, "Can not move to " +
                                                   QString::number(newIndex) +
                                                   ". Index out of range.")) {
        return false;
    }

    QVBoxLayout *layout = dynamic_cast<QVBoxLayout *>(this->layout());
    // get the pane we want to move
    ContentPane *movePane = this->contentPanes.at(currentIndex);

    // remove the widget from the layout and insert it at the new position
    layout->removeWidget(movePane);
    layout->insertWidget(newIndex, movePane);

    // keep our vector synchronized
    this->contentPanes.erase(this->contentPanes.begin() + currentIndex);
    this->contentPanes.insert(this->contentPanes.begin() + newIndex, movePane);

    return true;
}

ContentPane *QAccordion::getContentPane(uint index)
{
    try {
        return this->contentPanes.at(index);
    } catch (const std::out_of_range &ex) {
        qDebug() << Q_FUNC_INFO << "Can not return Content Pane: " << ex.what();
        this->errorString = "Can not return Content Pane: " + QString(ex.what());
        return nullptr;
    }
}

int QAccordion::getContentPaneIndex(QString header)
{
    return this->findContentPaneIndex(header);
}

int QAccordion::getContentPaneIndex(QFrame *contentFrame)
{
    return this->findContentPaneIndex("", contentFrame);
}

int QAccordion::getContentPaneIndex(ContentPane *contentPane)
{
    return this->findContentPaneIndex("", nullptr, contentPane);
}

void QAccordion::getActiveContentPaneIndex(std::vector<int> &indexVector)
{
    // first of all make sure it is empty
    indexVector.clear();
    std::for_each(this->contentPanes.begin(), this->contentPanes.end(),
                  [&indexVector, this](ContentPane *pane) {
                      if (pane->getActive()) {
                          indexVector.push_back(
                              this->findContentPaneIndex("", nullptr, pane));
                      }
                  });
}

int QAccordion::getNumberOfContentPanes() { return this->contentPanes.size(); }

void QAccordion::setMultiActive(bool status) { this->multiActive = status; }

bool QAccordion::getMultiActive() { return this->multiActive; }

void QAccordion::setCollapsible(bool status) { this->collapsible = status; }

bool QAccordion::getCollapsible() { return this->collapsible; }

QString QAccordion::getError() { return this->errorString; }

int QAccordion::internalAddContentPane(QString header, QFrame *cframe,
                                       ContentPane *cpane)
{
    if (this->findContentPaneIndex(header, cframe, cpane) != -1) {
        this->errorString = "Can not add content pane as it already exists";
        return -1;
    }

    if (cpane == nullptr) {
        if (cframe != nullptr) {
            cpane = new ContentPane(this,std::move(header), cframe);
        } else {
            cpane = new ContentPane(this,std::move(header));
        }
    }
    dynamic_cast<QVBoxLayout *>(this->layout())
        ->insertWidget(this->layout()->count() - 1, cpane);
    this->contentPanes.push_back(cpane);

    // manage the clicked signal in a lambda expression
    QObject::connect(cpane, &ContentPane::clicked,
                     [this, cpane]() { this->handleClickedSignal(cpane); });

    emit numberOfContentPanesChanged(this->contentPanes.size());

    return this->contentPanes.size() - 1;
}

bool QAccordion::internalInsertContentPane(uint index, QString header,
                                           QFrame *contentFrame,
                                           ContentPane *cpane)
{
    if (this->checkIndexError(
            index, true, "Can not insert Content Pane at index " +
                             QString::number(index) + ". Index out of range")) {
        return false;
    }

    if (this->findContentPaneIndex(header, contentFrame, cpane) != -1) {
        return false;
    }

    if (cpane == nullptr) {
        if (contentFrame != nullptr) {
            cpane = new ContentPane(this,std::move(header), contentFrame);
        } else {
            cpane = new ContentPane(this,std::move(header));
        }
    }

    dynamic_cast<QVBoxLayout *>(this->layout())->insertWidget(index, cpane);

    this->contentPanes.insert(this->contentPanes.begin() + index, cpane);

    // manage the clicked signal in a lambda expression
    QObject::connect(cpane, &ContentPane::clicked,
                     [this, cpane]() { this->handleClickedSignal(cpane); });

    emit numberOfContentPanesChanged(this->contentPanes.size());

    return true;
}

bool QAccordion::internalRemoveContentPane(bool deleteOject, int index,
                                           QString name, QFrame *contentFrame,
                                           ContentPane *cpane)
{
    if (index != -1 &&
        this->checkIndexError(
            index, false, "Can not remove content pane at index " +
                              QString::number(index) + ". Index out of range")) {
        return false;
    }

    if (index == -1) {
        index = this->findContentPaneIndex(std::move(name), contentFrame, cpane);
        if (index == -1) {
            this->errorString = "Can not remove content pane as it is not part "
                                "of the accordion widget";
            return false;
        }
    }

    dynamic_cast<QVBoxLayout *>(this->layout())
        ->removeWidget(this->contentPanes.at(index));

    // only delete the object if user wants to.
    if (deleteOject) {
        delete this->contentPanes.at(index);
        this->contentPanes.at(index) = nullptr;
    }

    this->contentPanes.erase(this->contentPanes.begin() + index);

    emit numberOfContentPanesChanged(this->contentPanes.size());

    return true;
}

int QAccordion::findContentPaneIndex(QString name, QFrame *cframe,
                                     ContentPane *cpane)
{
    // simple method that finds the index of a content by Header, content frame
    // or content pane.
    int index = -1;
    if (name != "") {
        auto result = std::find_if(
            this->contentPanes.begin(), this->contentPanes.end(),
            [&name](ContentPane *pane) { return pane->getHeader() == name; });
        if (result != std::end(this->contentPanes)) {
            // get the index by subtracting begin iterator from result
            // iterator
            // TODO: Is this cast really necessary?
            index = static_cast<int>(result - this->contentPanes.begin());
        }
    }
    if (cframe != nullptr) {
        auto result =
            std::find_if(this->contentPanes.begin(), this->contentPanes.end(),
                         [cframe](ContentPane *cpane) {
                             return cpane->getContentFrame() == cframe;
                         });
        if (result != std::end(this->contentPanes)) {
            index = static_cast<int>(result - this->contentPanes.begin());
        }
    }
    if (cpane != nullptr) {
        auto result = std::find(this->contentPanes.begin(),
                                this->contentPanes.end(), cpane);
        if (result != std::end(this->contentPanes)) {
            index = static_cast<int>(result - this->contentPanes.begin());
        }
    }
    return index;
}

bool QAccordion::checkIndexError(uint index, bool sizeIndexAllowed,
                                 const QString &errMessage)
{
    // sizeIndexAllowed is only used by inserting. If there is one pane you will
    // be able to insert a new one before and after.
    // FIXME: Actually there seem to be some bugs hidden here. User may now for
    // example delete index 0 even if there isn't any content pane. I think we
    // excluded checking 0 because of inserting.
    // Update, I removed the 0 exclusion in the second if statement. Really a
    // fix??
    if (sizeIndexAllowed) {
        if (index != 0 && index > this->contentPanes.size()) {
            qDebug() << Q_FUNC_INFO << errMessage;
            this->errorString = errMessage;
            return true;
        }
    } else {
        if (index >= this->contentPanes.size()) {
            qDebug() << Q_FUNC_INFO << errMessage;
            this->errorString = errMessage;
            return true;
        }
    }
    return false;
}

void QAccordion::handleClickedSignal(ContentPane *cpane)
{
    // if the clicked content pane is open we simply close it and return
    if (cpane->getActive()) {
        // if collapsible and multiActive are false we are not allowed to close
        // this pane
        if (!this->collapsible && !this->multiActive) {
            return;
        }
        // when multiActive is true we have to check if there is any other open
        // cpane. if so we can close this one
        std::vector<int> activePanes;
        if (!this->collapsible) {
            this->getActiveContentPaneIndex(activePanes);
            if (activePanes.size() == 1)
                return; // only one active --> good bye :)
        }
        cpane->closeContentPane();
        return;
    }
    // if it is not open we will open it and search our vector for other
    // panes that are already open.
    // TODO: Is it really necessary to search for more than one open cpane?
    if (!cpane->getActive()) {
        // check if multiActive is allowed
        if (!this->getMultiActive()) {
            std::for_each(this->contentPanes.begin(), this->contentPanes.end(),
                          [](ContentPane *pane) {
                              if (pane->getActive())
                                  pane->closeContentPane();
                          });
        }
        cpane->openContentPane();
    }
}

void QAccordion::numberOfPanesChanged(int number)
{
    // automatically open contentpane if we have only one and collapsible is
    // false
    if (number == 1 && this->collapsible == false) {
        this->contentPanes.at(0)->openContentPane();
    }
}

void QAccordion::paintEvent(QPaintEvent *event)
{
    QStyleOption o;
    o.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}
