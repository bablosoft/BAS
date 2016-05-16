#ifndef COMPILEROPTIONS_H
#define COMPILEROPTIONS_H

#include <QObject>

class Compiler : public QObject
{
    Q_OBJECT
    QString Name;
    QString Version;
    QString Os;
    QString EngineFolder;
    QString CompiledFolder;
    QString ReleaseFolder;
    QString BuildFolder;
    void CalculateCompiledFolder();
public:
    void SetName(const QString & Name);
    void SetOs(const QString & Os);
    void SetVersion(const QString & Version);
    QString GetName();
    QString GetOs();
    QString GetVersion();
    explicit Compiler(QObject *parent = 0);
    void Compile();
    QString GetEngineFolder();
    QString GetCompiledFolder();
    void SetReleaseFolder(const QString& ReleaseFolder);
    void SetBuildFolder(const QString& BuildFolder);
signals:

public slots:

};

#endif // COMPILEROPTIONS_H
