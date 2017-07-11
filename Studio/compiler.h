#ifndef COMPILEROPTIONS_H
#define COMPILEROPTIONS_H

#include <QObject>

class Compiler : public QObject
{
    Q_OBJECT
    QString Name;
    QString Version;
    QString Username;
    QString Password;

    QString Os;
    QString EngineFolder;
    QString CompiledFolder;
    QString ReleaseFolder;
    QString BuildFolder;
    bool HideBrowsers;
    void CalculateCompiledFolder();
public:
    enum CompileType{NoProtection,PrivateScriptEnterPassForUser,PrivateScriptUserEnterPass};
private:
    CompileType Type;
public:

    void SetName(const QString & Name);
    void SetHideBrowsers(bool HideBrowsers);
    void SetOs(const QString & Os);
    void SetVersion(const QString & Version);

    void SetUsername(const QString & Username);
    void SetPassword(const QString & Password);
    void SetType(const CompileType & Type);

    bool GetHideBrowsers();
    QString GetName();
    QString GetOs();
    QString GetVersion();
    explicit Compiler(QObject *parent = 0);

    //Returns true if need to copy project.xml
    bool Compile();
    QString GetEngineFolder();
    QString GetCompiledFolder();
    void SetReleaseFolder(const QString& ReleaseFolder);
    void SetBuildFolder(const QString& BuildFolder);
signals:

public slots:

};

#endif // COMPILEROPTIONS_H
