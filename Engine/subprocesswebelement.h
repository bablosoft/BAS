#ifndef SUBPROCESSWEBELEMENT_H
#define SUBPROCESSWEBELEMENT_H
#include "engine_global.h"

#include "iwebelement.h"


namespace BrowserAutomationStudioFramework
{

    class ENGINESHARED_EXPORT SubprocessWebElement : public IWebElement
    {
        Q_OBJECT
        QString CreateXmlElement(const QString& ElementName,const QString& Text1 = QString(),const QString& Text2 = QString());
        QList<QPair<QString,QString> > Selector;
        bool IsNoWait;
        IWorker *Worker;
        QString ID;
        QString GetSelectorString();
    public:
        ~SubprocessWebElement();
        explicit SubprocessWebElement(QObject *parent = 0);
        virtual void SetWorker(IWorker* Worker);
        virtual IWorker* GetWorker();
        void AddSelector(const QString& key,const QString& value);
        void SetNoWait();


    signals:
        void xml();
        void text();
        void script();
        void click();
        void clear();
        void type();
        void fill();
        void exist();
        void submit();
        void style();
        void check();
        void focus();
        void set();
        void set_integer();
        void set_random();
        void attr();
        void length();
        void highlight();
        void set_attr();
        void render_file();
        void render_base64();
        void system_click();
        void system_click_up();
        void system_click_down();
        void random_point();
        void move();
        void clarify();

    public slots:
        virtual void GetInternalList(QList<IWebElement*>& List);
        virtual void xml(const QString& callback);
        virtual void text(const QString& callback);
        virtual void script(const QString& javascript, const QString& callback);
        virtual void RunScriptAsync(const QString& javascript, const QObject *object_success,const char * slot_success);
        virtual QString RunScriptNoCallback(const QString& javascript);
        virtual void click(const QString& callback);
        virtual void move(const QString& callback);
        virtual void system_click(const QString& callback);
        virtual void system_click_up(const QString& callback);
        virtual void system_click_down(const QString& callback);
        virtual void random_point(const QString& callback);
        virtual void clear(const QString& callback);
        virtual void type(const QString& text, int interval, const QString& callback);
        virtual void type(const QString& text, const QString& callback);
        virtual void fill(const QString& text, const QString& callback);
        virtual void exist(const QString& callback);
        virtual void submit(const QString& callback);
        virtual void style(const QString& text, const QString& callback);
        virtual void check(const QString& callback);
        virtual void focus(const QString& callback);
        virtual void set(const QString& text,const QString& callback);
        virtual void set_integer(int index,const QString& callback);
        virtual void set_random(const QString& callback);
        virtual void attr(const QString& text,const QString& callback);
        virtual void set_attr(const QString& val,const QString& text,const QString& callback);
        virtual void length(const QString& callback);
        virtual void highlight(const QString& callback);
        virtual void clarify(int x, int y, const QString& callback);
        virtual IWebElement* at(int index);
        virtual IWebElement* nowait();
        virtual IWebElement* css(const QString& css);
        virtual IWebElement* frame(const QString& name);
        virtual IWebElement* frame_css(const QString& name);
        virtual IWebElement* frame_match(const QString& name);
        virtual IWebElement* frame_element();
        virtual IWebElement* position(int x, int y);
        virtual IWebElement* all(const QString& css);
        virtual void render_file(const QString& path,const QString& callback);
        virtual void render_base64(const QString& callback);
        virtual IWebElement* match(const QString& text);
        virtual IWebElement* match_all(const QString& text);
        virtual IWebElement* xpath(const QString& text);
        virtual IWebElement* xpath_all(const QString& text);
        void Received(const QString& value);
        QString PrepareCallback(const QString& callback);
        virtual QRect GetGeometry();

    };
}

#endif // SUBPROCESSWEBELEMENT_H
