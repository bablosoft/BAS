#ifndef IWEBELEMENT_H
#define IWEBELEMENT_H
#include "engine_global.h"

#include <QObject>
#include <QRect>
#include "iworker.h"

namespace BrowserAutomationStudioFramework
{
    class IWorker;
    class ENGINESHARED_EXPORT IWebElement : public QObject
    {
    Q_OBJECT
    public:
        explicit IWebElement(QObject *parent = 0);
        virtual void SetWorker(IWorker* Worker) = 0;
        virtual IWorker* GetWorker() = 0;
    signals:

    public slots:
        virtual void GetInternalList(QList<IWebElement*>& List) = 0;
        virtual void xml(const QString& callback) = 0;
        virtual void text(const QString& callback) = 0;
        virtual void script(const QString& javascript, const QString& callback) = 0;
        virtual void RunScriptAsync(const QString& javascript, const QObject *object_success,const char * slot_success) = 0;
        virtual void click(const QString& callback) = 0;
        virtual void move(const QString& callback) = 0;
        virtual void random_point(const QString& callback) = 0;
        virtual void system_click(const QString& callback) = 0;
        virtual void system_click_up(const QString& callback) = 0;
        virtual void system_click_down(const QString& callback) = 0;
        virtual void clear(const QString& callback) = 0;
        virtual void type(const QString& text, int interval, const QString& callback) = 0;
        virtual void type(const QString& text, const QString& callback) = 0;


        virtual void fill(const QString& text, const QString& callback) = 0;
        virtual void exist(const QString& callback) = 0;
        virtual void submit(const QString& callback) = 0;
        virtual void style(const QString& text, const QString& callback) = 0;
        virtual void check(const QString& callback) = 0;
        virtual void focus(const QString& callback) = 0;
        virtual void set(const QString& text,const QString& callback) = 0;
        virtual void set_integer(int index,const QString& callback) = 0;
        virtual void set_random(const QString& callback) = 0;
        virtual void attr(const QString& text,const QString& callback) = 0;
        virtual void set_attr(const QString& val,const QString& text,const QString& callback) = 0;
        virtual void length(const QString& callback) = 0;
        virtual void highlight(const QString& callback) = 0;
        virtual IWebElement* at(int index) = 0;
        virtual IWebElement* css(const QString& css) = 0;
        virtual IWebElement* frame(const QString& name) = 0;
        virtual IWebElement* frame_css(const QString& name) = 0;
        virtual IWebElement* frame_match(const QString& name) = 0;
        virtual IWebElement* frame_element() = 0;
        virtual IWebElement* position(int x, int y) = 0;
        virtual IWebElement* nowait() = 0;

        virtual IWebElement* all(const QString& css) = 0;
        virtual void render_file(const QString& path,const QString& callback) = 0;
        virtual void render_base64(const QString& callback) = 0;
        virtual IWebElement* match(const QString& text) = 0;
        virtual IWebElement* match_all(const QString& text) = 0;
        virtual IWebElement* xpath(const QString& text) = 0;
        virtual IWebElement* xpath_all(const QString& text) = 0;
        virtual QRect GetGeometry() = 0;

    };
}
#endif // IWEBELEMENT_H
