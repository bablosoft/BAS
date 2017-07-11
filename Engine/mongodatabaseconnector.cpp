#include "mongodatabaseconnector.h"
#include "every_cpp.h"
#include <QXmlStreamReader>
#include <QFile>
#include <QDebug>
#include <QTimer>
#include <QDir>
#include <QUrl>
#include <QDirIterator>
#include <QSettings>
#include <QDialog>
#include <QPlainTextEdit>
#include <QLayout>
#include <QStandardPaths>
#include <QJsonDocument>
#include <QJsonArray>
#include <QCoreApplication>


namespace BrowserAutomationStudioFramework
{
    MongoDatabaseConnector::MongoDatabaseConnector(QObject *parent) :
        IDatabaseConnector(parent), _c(true)
    {
        CurrentMongoProcess = 0;
        IsDatabasePresent = false;
        IsBusy = false;
        _HasDatabase = false;
        DatabaseConnectionWindow = 0;
    }

    MongoDatabaseConnector::~MongoDatabaseConnector()
    {
        ClosePort();
    }

    QString MongoDatabaseConnector::GetDatabaseBaseLocation()
    {
        QString res = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + "/BasDatabases/";
        if(res.isEmpty())
            res = "../../data/";
        return res;
    }
    QString MongoDatabaseConnector::GetDatabaseLocation()
    {
        return GetDatabaseBaseLocation() + DatabaseId + "/";
    }

    void MongoDatabaseConnector::SetDatabaseConnectionWindow(IDatabaseConnectionWindow * DatabaseConnectionWindow)
    {
        this->DatabaseConnectionWindow = DatabaseConnectionWindow;
        connect(DatabaseConnectionWindow,SIGNAL(ContinueWithoutDatabase()), this,SLOT(StartAnyway()));
        connect(DatabaseConnectionWindow,SIGNAL(Cancel()), this,SLOT(UserCancel()));
        connect(DatabaseConnectionWindow,SIGNAL(DatabaseConnectionOk()), this,SLOT(DatabaseConnectionOk()));
        connect(DatabaseConnectionWindow,SIGNAL(ShowLog()), this,SLOT(ShowLog()));
    }

    void MongoDatabaseConnector::DatabaseConnectionOk()
    {
        _WasError = false;
        emit Started();
        this->DatabaseConnectionWindow->deleteLater();
        this->DatabaseConnectionWindow = 0;
    }

    void MongoDatabaseConnector::StartAnyway()
    {
        _WasError = false;
        _HasDatabase = false;
        emit Started();
        this->DatabaseConnectionWindow->deleteLater();
        this->DatabaseConnectionWindow = 0;
    }

    void MongoDatabaseConnector::UserCancel()
    {
        _WasError = true;
        _ErrorString = tr("User cancel");
        _HasDatabase = true;
        emit Started();
        this->DatabaseConnectionWindow->deleteLater();
        this->DatabaseConnectionWindow = 0;
    }

    void MongoDatabaseConnector::ShowLog()
    {
        QDialog dialog;
        QHBoxLayout *layout = new QHBoxLayout(&dialog);
        dialog.setLayout(layout);
        QPlainTextEdit * edit = new QPlainTextEdit(&dialog);
        layout->addWidget(edit);
        edit->setPlainText(ConnectionLog);
        dialog.resize(800,600);

        dialog.exec();
    }

    void MongoDatabaseConnector::SetCsvHelper(ICsvHelper * CsvHelper)
    {
        this->CsvHelper = CsvHelper;
    }

    void MongoDatabaseConnector::ExportExcel(const QString& File, QList<int> ColumnIds, DatabaseMassSelector Selector)
    {
        _WasError = false;
        try
        {
            BSONObj o = CombineQueryAnd(GenerateDatabaseGroupsAndItemsQuery(Selector.Groups,Selector.Items),GenerateFilterQuery(Selector.Filters));
            Query q(o);
            if(!Selector.Sort.IsNull)
            {
                int sort = (Selector.Sort.OrderIsAsc)?1:-1;

                q.sort(QString::number(Selector.Sort.ColumnId).toStdString(),sort);
            }

            std::auto_ptr<DBClientCursor> cursor = _c.query(QString("%1.res").arg(Selector.TableId).toStdString(), q);
            if(cursor.get() == 0)
            {
                throw std::exception();
            }

            QFile FileObject(File);

            if(!FileObject.open(QIODevice::WriteOnly | QIODevice::Append))
            {
                _WasError = true;
                _ErrorString = tr("Failed to write to file");
                return;
            }



            QTextStream out(&FileObject);
            out.setCodec("UTF-8");

            out<<"<?xml version=\"1.0\"?><?mso-application progid=\"Excel.Sheet\"?><Workbook xmlns=\"urn:schemas-microsoft-com:office:spreadsheet\" xmlns:o=\"urn:schemas-microsoft-com:office:office\" xmlns:x=\"urn:schemas-microsoft-com:office:excel\" xmlns:ss=\"urn:schemas-microsoft-com:office:spreadsheet\" xmlns:html=\"http://www.w3.org//REC-html40\">  <Styles> <Style ss:ID=\"s62\"> <NumberFormat ss:Format=\"Short Date\"/> </Style><Style ss:ID=\"s22\"> <Alignment ss:Horizontal=\"Center\" ss:Vertical=\"Bottom\"/> <Font ss:FontName=\"Arial Cyr\" x:CharSet=\"204\" ss:Bold=\"1\"/> </Style> </Styles> <Worksheet ss:Name=\"Data\"> <Table>";

            QList<DatabaseColumn> ColumnsAll = GetColumns(Selector.TableId);
            QList<DatabaseColumn> Columns;
            foreach(int id,ColumnIds)
            {
                out<<"<Column ss:AutoFitWidth=\"0\" ss:Width=\"150\"/>";
            }
            out<<"<Row>";

            foreach(int id,ColumnIds)
            {
                foreach(DatabaseColumn c, ColumnsAll)
                {
                    if(c.Id == id)
                    {
                        out<<"<Cell ss:StyleID=\"s22\"><Data ss:Type=\"String\">";
                        out<<c.Description;
                        out<<"</Data></Cell>";
                        Columns.append(c);
                        break;
                    }
                }

            }
            out<<"</Row>";

            while (cursor->more())
            {
               BSONObj obj = cursor->next();

               out<<"<Row>";

               foreach(DatabaseColumn Column,Columns)
               {
                    std::string column = QString::number(Column.Id).toStdString();
                    if(obj.getField(column).isNull())
                    {
                        out<<"<Cell><Data ss:Type=\"String\">";
                        out<<"</Data></Cell>";
                        continue;
                    }
                    switch(Column.Type)
                    {
                        case DatabaseColumn::String:
                            if(obj.getField(column).type() == mongo::String)
                            {
                                out<<"<Cell><Data ss:Type=\"String\">";
                                out<<QString::fromUtf8(obj.getStringField(column)).replace("&","&amp;").replace(">","&gt;").replace("<","&lt;");
                                out<<"</Data></Cell>";
                            }
                            else
                            {
                                out<<"<Cell><Data ss:Type=\"String\">";
                                out<<"</Data></Cell>";
                            }
                        break;
                        case DatabaseColumn::Int:
                            if(obj.getField(column).type() == mongo::NumberInt)
                            {
                                out<<"<Cell><Data ss:Type=\"Number\">";
                                out<<QString::number(obj.getIntField(column));
                                out<<"</Data></Cell>";
                            }
                            else
                            {
                                out<<"<Cell><Data ss:Type=\"Number\">";
                                out<<"0";
                                out<<"</Data></Cell>";
                            }
                        break;
                        case DatabaseColumn::Date:
                            if(obj.getField(column).type() == mongo::Date)
                            {
                                out<<"<Cell ss:StyleID=\"s62\"><Data ss:Type=\"DateTime\">";
                                out<<QDateTime::fromMSecsSinceEpoch(obj.getField(column).Date().asInt64()).toString(Qt::ISODate);
                                out<<"</Data></Cell>";
                            }
                            else
                            {
                                out<<"<Cell ss:StyleID=\"s62\"><Data ss:Type=\"DateTime\">";
                                out<<"2000-01-01 00:00:00";
                                out<<"</Data></Cell>";
                            }

                        break;
                        case DatabaseColumn::Bool:
                            if(obj.getField(column).type() == mongo::Bool)
                            {
                                out<<"<Cell><Data ss:Type=\"String\">";
                                out<<(obj.getBoolField(column)?"true":"false");
                                out<<"</Data></Cell>";
                            }
                            else
                            {
                                out<<"<Cell><Data ss:Type=\"String\">";
                                out<<"false";
                                out<<"</Data></Cell>";
                            }
                        break;
                    }

               }
               out<<"</Row>";
            }

            out<<"</Table></Worksheet></Workbook>";

            FileObject.close();
        }catch( const mongo::DBException &e ) {
            _WasError = true;
            QString error = QString::fromStdString(e.what());
            _ErrorString = tr("Database Error : ") + error;
            qDebug()<<_ErrorString;
            return;
        }catch(...)
        {
            _WasError = true;
            _ErrorString = tr("Database Error");
            qDebug()<<"Database Error";
            return;

        }
    }

    void MongoDatabaseConnector::ExportCsv(const QString& File, QList<int> ColumnIds, DatabaseMassSelector Selector)
    {
        _WasError = false;
        try
        {
            BSONObj o = CombineQueryAnd(GenerateDatabaseGroupsAndItemsQuery(Selector.Groups,Selector.Items),GenerateFilterQuery(Selector.Filters));
            Query q(o);
            if(!Selector.Sort.IsNull)
            {
                int sort = (Selector.Sort.OrderIsAsc)?1:-1;

                q.sort(QString::number(Selector.Sort.ColumnId).toStdString(),sort);
            }


            std::auto_ptr<DBClientCursor> cursor = _c.query(QString("%1.res").arg(Selector.TableId).toStdString(), q);
            if(cursor.get() == 0)
            {
                throw std::exception();
            }

            QList<DatabaseColumn> ColumnsAll = GetColumns(Selector.TableId);
            QList<DatabaseColumn> Columns;
            foreach(int id,ColumnIds)
            {
                foreach(DatabaseColumn c, ColumnsAll)
                {
                    if(c.Id == id)
                    {
                        Columns.append(c);
                        break;
                    }
                }

            }

            QFile FileObject(File);

            if(!FileObject.open(QIODevice::WriteOnly | QIODevice::Append))
            {
                _WasError = true;
                _ErrorString = tr("Failed to write to file");
                return;
            }
            QTextStream out(&FileObject);
            out.setCodec("UTF-8");
            while (cursor->more())
            {
               QStringList Item;

               BSONObj obj = cursor->next();

               //Item.Id = QString::fromStdString(obj.getField("_id").OID().toString());

               foreach(DatabaseColumn Column,Columns)
               {

                    std::string column = QString::number(Column.Id).toStdString();
                    if(obj.getField(column).isNull())
                    {
                        Item.append(QString());
                        continue;
                    }
                    QString cell;
                    switch(Column.Type)
                    {
                        case DatabaseColumn::String:
                            if(obj.getField(column).type() == mongo::String)
                                cell = QString::fromUtf8(obj.getStringField(column));
                            else
                                cell = "";
                        break;
                        case DatabaseColumn::Int:
                            if(obj.getField(column).type() == mongo::NumberInt)
                                cell = QString::number(obj.getIntField(column));
                            else
                                cell = "0";
                        break;
                        case DatabaseColumn::Date:
                            if(obj.getField(column).type() == mongo::Date)
                                cell = QDateTime::fromMSecsSinceEpoch(obj.getField(column).Date().asInt64()).toString("yyyy-MM-dd HH:mm:ss");
                            else
                                cell = "2000-01-01 00:00:00";
                        break;
                        case DatabaseColumn::Bool:
                            if(obj.getField(column).type() == mongo::Bool)
                                cell = obj.getBoolField(column)?"true":"false";
                            else
                                cell = "false";
                        break;
                    }
                    Item.append(cell);
               }
               QString Line = CsvHelper->Generate(Item,':');
               out<<Line<<"\r\n";
            }
            FileObject.close();
        }catch( const mongo::DBException &e ) {
            _WasError = true;
            QString error = QString::fromStdString(e.what());
            _ErrorString = tr("Database Error : ") + error;
            qDebug()<<_ErrorString;
            return;
        }catch(...)
        {
            _WasError = true;
            _ErrorString = tr("Database Error");
            qDebug()<<"Database Error";
            return;

        }
    }
    void MongoDatabaseConnector::ImportCsv(const QString& File, QList<int> ColumnIds, QString GroupId, int TableId)
    {
        _WasError = false;
        try
        {
            QList<DatabaseColumn> ColumnsAll = GetColumns(TableId);
            QList<DatabaseColumn> Columns;
            foreach(int id,ColumnIds)
            {
                foreach(DatabaseColumn c, ColumnsAll)
                {
                    if(c.Id == id)
                    {
                        Columns.append(c);
                        break;
                    }
                }

            }

            QFile FileObject(File);

            if(!FileObject.open(QIODevice::ReadOnly))
            {
                _WasError = true;
                _ErrorString = tr("Failed to read to file");
                return;
            }
            QTextStream in(&FileObject);
            in.setCodec("UTF-8");
            while(!in.atEnd())
            {
                QStringList Items = CsvHelper->Parse(in.readLine());
                int index = 0;

                OID oid = OID::gen();
                BSONObjBuilder ItemBuild;
                ItemBuild.append("_id", oid);

                foreach(QString Item, Items)
                {
                    if(index>=Columns.length())
                        break;
                    DatabaseColumn Column = Columns.at(index);

                    std::string column_name = QString::number(Column.Id).toStdString();
                    switch(Column.Type)
                    {
                        case DatabaseColumn::Int:
                        {
                            ItemBuild.append(column_name,Item.toInt());
                        }break;
                        case DatabaseColumn::String:
                        {
                            ItemBuild.append(column_name,Item.toStdString());
                        }break;
                        case DatabaseColumn::Bool:
                        {
                            ItemBuild.append(column_name,Item == "true");
                        }break;
                        case DatabaseColumn::Date:
                        {
                            ItemBuild.append(column_name,Date_t(QDateTime::fromString("yyyy-MM-dd HH:mm:ss").toMSecsSinceEpoch()));
                        }break;

                    }
                    index++;
                }

                BSONArrayBuilder ar;
                ar.append(OID(GroupId.toStdString()));

                ItemBuild.append("groups", ar.arr());
                BSONObj o = ItemBuild.obj();
                //qDebug()<<o.toString().c_str();
                _c.insert(QString("%1.res").arg(TableId).toStdString(), o);
                //qDebug()<<Items;



            }
            FileObject.close();
        }catch( const mongo::DBException &e ) {
            _WasError = true;
            QString error = QString::fromStdString(e.what());
            _ErrorString = tr("Database Error : ") + error;
            qDebug()<<_ErrorString;
            return;
        }catch(...)
        {
            _WasError = true;
            _ErrorString = tr("Database Error");
            qDebug()<<"Database Error";
            return;

        }
    }

    QStringList MongoDatabaseConnector::SelectFormatted(DatabaseSelector Selector,QString Format)
    {
       return QStringList();
    }


    BSONObj MongoDatabaseConnector::GenerateFilterQuery(DatabaseFilters Filters)
    {
        BSONObj o;
        QList<BSONObj> ol;
        if(!Filters.IsNull)
        {
            foreach(DatabaseFilter Filter,Filters.FilterList)
            {
                BSONObj on;
                std::string c = QString::number(Filter.ColumnId).toStdString();
                switch(Filter.Type)
                {

                    case DatabaseFilter::StringNotEmpty:
                        on = BSON(c << BSON("$ne"<<""));
                    break;
                    case DatabaseFilter::StringEmpty:
                        on = BSON(c << "");
                    break;
                    case DatabaseFilter::StringContains:
                        on = BSON(c << BSON("$regex"<< QString(QString(".*") + Filter.Data.toString() + QString(".*")).toStdString()));
                    break;

                    case DatabaseFilter::BoolIsFalse:
                        on = BSON(c << false);
                    break;
                    case DatabaseFilter::BoolIsTrue:
                        on = BSON(c << true);
                    break;

                    case DatabaseFilter::IntEquals:
                        on = BSON(c << Filter.Data.toInt());
                    break;
                    case DatabaseFilter::IntGreater:
                        on = BSON(c << BSON("$gt"<<Filter.Data.toInt()));
                    break;
                    case DatabaseFilter::IntGreaterOrEqual:
                        on = BSON(c << BSON("$gte"<<Filter.Data.toInt()));
                    break;
                    case DatabaseFilter::IntLessThan:
                        on = BSON(c << BSON("$lt"<<Filter.Data.toInt()));
                    break;
                    case DatabaseFilter::IntLessThanOrEqual:
                        on = BSON(c << BSON("$lte"<<Filter.Data.toInt()));
                    break;
                    case DatabaseFilter::IntNotEquals:
                        on = BSON(c << BSON("$ne"<<Filter.Data.toInt()));
                    break;

                    case DatabaseFilter::DateGreaterThan:
                        on = BSON(c << BSON("$gt"<<Date_t(Filter.Data.toDateTime().toMSecsSinceEpoch())));
                    break;
                    case DatabaseFilter::DateIsLessThan:
                        on = BSON(c << BSON("$lt"<<Date_t(Filter.Data.toDateTime().toMSecsSinceEpoch())));
                    break;
                    case DatabaseFilter::DateIsSameYear:
                    {
                        BSONArrayBuilder build;
                        QDateTime Start,End,Current;
                        Current = Filter.Data.toDateTime();
                        Start = QDateTime(QDate(Current.date().year(),1,1));
                        End = QDateTime(QDate(Current.date().year()+1,1,1));
                        build.append(BSON(c << BSON("$gte"<<Date_t(Start.toMSecsSinceEpoch()))));
                        build.append(BSON(c << BSON("$lt"<<Date_t(End.toMSecsSinceEpoch()))));
                        on = BSON("$and" << build.arr());
                    }
                    break;
                    case DatabaseFilter::DateIsSameMonth:
                    {
                        BSONArrayBuilder build;
                        QDateTime Start,End,Current;
                        Current = Filter.Data.toDateTime();
                        Start = QDateTime(QDate(Current.date().year(),Current.date().month(),1));
                        End = QDateTime(QDate(Current.date().year(),Current.date().month(),1));
                        End = End.addMonths(1);
                        build.append(BSON(c << BSON("$gte"<<Date_t(Start.toMSecsSinceEpoch()))));
                        build.append(BSON(c << BSON("$lt"<<Date_t(End.toMSecsSinceEpoch()))));
                        on = BSON("$and" << build.arr());
                    }
                    break;
                    case DatabaseFilter::DateIsSameDay:
                    {
                        BSONArrayBuilder build;
                        QDateTime Start,End,Current;
                        Current = Filter.Data.toDateTime();
                        Start = QDateTime(QDate(Current.date().year(),Current.date().month(),Current.date().day()));
                        End = QDateTime(QDate(Current.date().year(),Current.date().month(),Current.date().day()));
                        End = End.addDays(1);
                        build.append(BSON(c << BSON("$gte"<<Date_t(Start.toMSecsSinceEpoch()))));
                        build.append(BSON(c << BSON("$lt"<<Date_t(End.toMSecsSinceEpoch()))));
                        on = BSON("$and" << build.arr());
                    }
                    break;
                    case DatabaseFilter::DateIsSameHour:
                    {
                        BSONArrayBuilder build;
                        QDateTime Start,End,Current;
                        Current = Filter.Data.toDateTime();
                        Start = QDateTime(QDate(Current.date().year(),Current.date().month(),Current.date().day()),QTime(Current.time().hour(),0,0));
                        End = QDateTime(QDate(Current.date().year(),Current.date().month(),Current.date().day()),QTime(Current.time().hour(),0,0));
                        End = End.addSecs(60*60);
                        build.append(BSON(c << BSON("$gte"<<Date_t(Start.toMSecsSinceEpoch()))));
                        build.append(BSON(c << BSON("$lt"<<Date_t(End.toMSecsSinceEpoch()))));
                        on = BSON("$and" << build.arr());
                    }
                    break;

                }

                ol.append(on);

            }
        }
        if(ol.isEmpty())
            return o;

        if(ol.length() == 1)
            return ol.first();
        BSONArrayBuilder ar;

        foreach(BSONObj on, ol)
        {
            ar.append(on);
        }
        o = BSON("$and"<<ar.arr());
        return o;
    }

    BSONObj MongoDatabaseConnector::CombineQueryAnd(BSONObj q1,BSONObj q2)
    {
        if(!q1.isEmpty() && !q2.isEmpty())
        {
            BSONArrayBuilder ar;
            ar.append(q1);
            ar.append(q2);

            return BSON("$and"<<ar.arr());
        }else if(!q1.isEmpty())
            return q1;
        else if(!q2.isEmpty())
            return q2;
        else
            return BSONObj();

    }

    BSONObj MongoDatabaseConnector::GenerateDatabaseGroupsQuery(DatabaseGroups Groups)
    {
        BSONObj o;
        if(!Groups.IsNull)
        {
            QList<BSONObj> oq;

            while(true)
            {
                if(Groups.GroupIdList.contains("-1") || Groups.GroupIdList.isEmpty())
                    break;


                QStringList groups = Groups.GroupIdList;

                if(groups.contains("-2"))
                {

                    oq.append(BSON("groups" << BSONArray()));
                    groups.removeAll("-2");
                }

                if(!groups.isEmpty())
                {
                    if(groups.size() == 1)
                    {
                        oq.append(BSON("groups" << OID(groups.first().toStdString())));
                    }else
                    {
                        BSONArrayBuilder ar;
                        foreach(QString oid,groups)
                        {
                            ar.append(OID(oid.toStdString()));
                        }
                        oq.append(BSON("groups" << BSON( "$in" << ar.arr())));
                    }
                }

                if(oq.length() == 1)
                {
                    o = oq.first();
                }else if(oq.length() == 2)
                {
                    BSONArrayBuilder ar;
                    ar.append(oq.first());
                    ar.append(oq[1]);
                    o = BSON("$or"<<ar.arr());
                }


                break;
            }

        }
        return o;
    }

    BSONObj MongoDatabaseConnector::GenerateDatabaseItemsQuery(DatabaseItems Items)
    {

        BSONObj o;
        if(!Items.IsNull)
        {
            while(true)
            {
                if(Items.SelectedRows.isEmpty())
                    break;

                BSONArrayBuilder ba;

                foreach(QString oid,Items.SelectedRows)
                {
                    ba.append(OID(oid.toStdString()));
                }

                QString selector;
                if(!Items.IsInverseSelection)
                    selector = "$in";
                else
                    selector = "$nin";

                o = BSON("_id" << BSON(selector.toStdString()<<ba.arr()));

                break;
            }

        }
        return o;
    }

    BSONObj MongoDatabaseConnector::GenerateDatabaseGroupsAndItemsQuery(DatabaseGroups Groups,DatabaseItems Items)
    {

        if(!Items.IsInverseSelection && !Items.SelectedRows.isEmpty())
        {
            return GenerateDatabaseItemsQuery(Items);
        }

        BSONObj o1 = GenerateDatabaseItemsQuery(Items),o2 = GenerateDatabaseGroupsQuery(Groups);
        if(o1.isEmpty())
            return o2;
        else if(o2.isEmpty())
            return o1;
        else
        {
            BSONArrayBuilder ar;
            ar.append(o1);
            ar.append(o2);
            return BSON("$and"<<ar.arr());
        }
        return BSONObj();
    }

    QList<DatabaseItem> MongoDatabaseConnector::Select(DatabaseSelector Selector)
    {
        _WasError = false;

        try
        {

            if(!EnsureIndexTables.contains(Selector.TableId))
            {
                _c.eval(QString::number(Selector.TableId).toStdString(),"db.res.ensureIndex( { groups: 1 } )");
                EnsureIndexTables.insert(Selector.TableId);

            }


            BSONObj o = CombineQueryAnd(GenerateDatabaseGroupsQuery(Selector.Groups), GenerateFilterQuery(Selector.Filter));
            //qDebug()<<o.toString().c_str();
            int limmit = 0;
            int offset = 0;

            if(!Selector.Page.IsNull)
            {
                limmit = Selector.Page.PageSize;
                offset = Selector.Page.PageSize*(Selector.Page.PageNumber-1);
            }

            Query q(o);
            if(!Selector.Sort.IsNull)
            {
                int sort = (Selector.Sort.OrderIsAsc)?1:-1;

                q.sort(QString::number(Selector.Sort.ColumnId).toStdString(),sort);
            }
            std::auto_ptr<DBClientCursor> cursor = _c.query(QString("%1.res").arg(Selector.TableId).toStdString(), q, limmit, offset);
            if(cursor.get() == 0)
            {
                throw std::exception();
            }

            QList<DatabaseItem> res;

            QList<DatabaseColumn> Columns = GetColumns(Selector.TableId);

            while (cursor->more())
            {
               DatabaseItem Item;
               Item.IsNull = false;
               BSONObj obj = cursor->next();

               Item.Id = QString::fromStdString(obj.getField("_id").OID().toString());
               foreach(DatabaseColumn Column,Columns)
               {
                    std::string column = QString::number(Column.Id).toStdString();
                    switch(Column.Type)
                    {
                        case DatabaseColumn::String:
                            if(obj.getField(column).type() == mongo::String)
                                Item.Data[Column.Id] = QString::fromUtf8(obj.getStringField(column));
                            else
                                Item.Data[Column.Id] = QString();
                        break;
                        case DatabaseColumn::Int:
                            if(obj.getField(column).type() == mongo::NumberInt)
                                Item.Data[Column.Id] = obj.getIntField(column);
                            else
                                Item.Data[Column.Id] = 0;

                        break;
                        case DatabaseColumn::Date:

                            if(obj.getField(column).type() == mongo::Date)
                                Item.Data[Column.Id] = QDateTime::fromMSecsSinceEpoch(obj.getField(column).Date().asInt64());
                            else
                                Item.Data[Column.Id] = QDateTime(QDate(2000,1,1));
                        break;
                        case DatabaseColumn::Bool:

                            if(obj.getField(column).type() == mongo::Bool)
                                Item.Data[Column.Id] = obj.getBoolField(column);
                            else
                                Item.Data[Column.Id] = false;
                        break;
                    }
               }

               res.append(Item);


            }
            return res;

        }
        catch( const mongo::DBException &e ) {
            _WasError = true;
            QString error = QString::fromStdString(e.what());
            _ErrorString = tr("Database Error : ") + error;
            qDebug()<<_ErrorString<<e.getCode();
            return QList<DatabaseItem>();
        }catch(...)
        {
            _WasError = true;
            _ErrorString = tr("Database Error");
            qDebug()<<"Database Error";
            return QList<DatabaseItem>();

        }


    }
    QString MongoDatabaseConnector::Insert(DatabaseGroups Groups,DatabaseItem Item, int TableId)
    {

        //QTime t = QTime::currentTime();
        _WasError = false;
        QString OidString;

        try
        {
            OID oid = OID::gen();
            OidString = QString::fromStdString(oid.toString());
            BSONObjBuilder ItemBuild;
            ItemBuild.append("_id", oid);
            QHashIterator<int,QVariant> i(Item.Data);
            while (i.hasNext())
            {
                i.next();
                std::string column = QString::number(i.key()).toStdString();
                switch(i.value().type())
                {
                    case QVariant::Int:
                    {
                        ItemBuild.append(column,i.value().toInt());
                    }break;
                    case QVariant::String:
                    {
                        ItemBuild.append(column,i.value().toString().toStdString());
                    }break;
                    case QVariant::Bool:
                    {
                        ItemBuild.append(column,i.value().toBool());
                    }break;
                    case QVariant::DateTime:
                    {
                        ItemBuild.append(column,Date_t(i.value().toDateTime().toMSecsSinceEpoch()));
                    }break;

                }
            }

            BSONArrayBuilder ar;
            foreach(QString oid,Groups.GroupIdList)
            {
                if(oid!="-2" && oid!="-1")
                    ar.append(OID(oid.toStdString()));
            }
            ItemBuild.append("groups", ar.arr());
            BSONObj o = ItemBuild.obj();
            //qDebug()<<o.toString().c_str();
            _c.insert(QString("%1.res").arg(TableId).toStdString(), o);
        }catch( const mongo::DBException &e ) {
            OidString.clear();
            _WasError = true;
            QString error = QString::fromStdString(e.what());
            _ErrorString = tr("Database Error : ") + error;
            qDebug()<<_ErrorString;
            return OidString;
        }catch(...)
        {
            OidString.clear();
            _WasError = true;
            _ErrorString = tr("Database Error");
            qDebug()<<"Database Error";
            return OidString;

        }
        return OidString;
        //qDebug()<<t.msecsTo(QTime::currentTime());
    }
    int MongoDatabaseConnector::Count(DatabaseSelector Selector)
    {
        _WasError = false;

        try
        {
            BSONObj o = CombineQueryAnd(GenerateDatabaseGroupsQuery(Selector.Groups), GenerateFilterQuery(Selector.Filter));

            return _c.count(QString("%1.res").arg(Selector.TableId).toStdString(),o);
        }catch( const mongo::DBException &e ) {
            _WasError = true;
            QString error = QString::fromStdString(e.what());
            _ErrorString = tr("Database Error : ") + error;
            qDebug()<<_ErrorString;
            return 0;
        }catch(...)
        {
            _WasError = true;
            _ErrorString = tr("Database Error");
            qDebug()<<"Database Error";
            return 0;

        }

    }
    void MongoDatabaseConnector::Delete(DatabaseMassSelector Selector)
    {
        _WasError = false;

        try
        {
            BSONObj o = CombineQueryAnd(GenerateDatabaseGroupsAndItemsQuery(Selector.Groups,Selector.Items),GenerateFilterQuery(Selector.Filters));
            _c.remove(QString("%1.res").arg(Selector.TableId).toStdString(),
                     o
                    );
        }catch( const mongo::DBException &e ) {
            _WasError = true;
            QString error = QString::fromStdString(e.what());
            _ErrorString = tr("Database Error : ") + error;
            qDebug()<<_ErrorString;
            return;
        }catch(...)
        {
            _WasError = true;
            _ErrorString = tr("Database Error");
            qDebug()<<"Database Error";
            return;

        }
    }
    void MongoDatabaseConnector::Update(DatabaseItem Item, int TableId)
    {
        _WasError = false;

        try
        {
            BSONObjBuilder b;
            QHashIterator<int,QVariant> i(Item.Data);
            while (i.hasNext())
            {
                i.next();
                std::string column = QString::number(i.key()).toStdString();
                switch(i.value().type())
                {
                    case QVariant::Int:
                    {
                        b.append(column,i.value().toInt());
                    }break;
                    case QVariant::String:
                    {
                        b.append(column,i.value().toString().toStdString());
                    }break;
                    case QVariant::Bool:
                    {
                        b.append(column,i.value().toBool());
                    }break;
                    case QVariant::DateTime:
                    {
                        b.append(column,Date_t(i.value().toDateTime().toMSecsSinceEpoch()));
                    }break;

                }
            }

            _c.update(QString("%1.res").arg(TableId).toStdString(),
                BSON("_id" << OID(Item.Id.toStdString())),
                BSON("$set" << b.obj())
            );
        }catch( const mongo::DBException &e ) {
            _WasError = true;
            QString error = QString::fromStdString(e.what());
            _ErrorString = tr("Database Error : ") + error;
            qDebug()<<_ErrorString;
            return;
        }catch(...)
        {
            _WasError = true;
            _ErrorString = tr("Database Error");
            qDebug()<<"Database Error";
            return;

        }
    }

    QList<DatabaseGroup> MongoDatabaseConnector::GetGroups(int TableId)
    {
        _WasError = false;

        try
        {
            QList<DatabaseGroup> res;

            {
                DatabaseGroup group;
                group.IsNull = false;
                group.Description = tr("All data in table");
                group.Id = "-1";
                group.Name = tr("All");
                res.append(group);
            }

            {
                DatabaseGroup group;
                group.IsNull = false;
                group.Description = tr("Items, which is not present in any group");
                group.Id = "-2";
                group.Name = tr("Not in groups");
                res.append(group);
            }

            std::auto_ptr<DBClientCursor> cursor = _c.query(QString("%1.groups").arg(TableId).toStdString(), BSONObj());
            if(cursor.get() == 0)
            {
                throw std::exception();
            }

            while (cursor->more())
            {
               BSONObj obj = cursor->next();
               //qDebug()<<obj.toString().c_str();
               DatabaseGroup group;
               group.IsNull = false;
               group.Description = QString::fromUtf8(obj.getStringField("description"));
               group.Id = QString::fromStdString(obj.getField("_id").OID().toString());
               group.Name = QString::fromUtf8(obj.getStringField("name"));
               res.append(group);
            }

            return res;
        }catch( const mongo::DBException &e ) {
            _WasError = true;
            QString error = QString::fromStdString(e.what());
            _ErrorString = tr("Database Error : ") + error;
            qDebug()<<_ErrorString;
            return QList<DatabaseGroup>();
        }catch(...)
        {
            _WasError = true;
            _ErrorString = tr("Database Error");
            qDebug()<<"Database Error";
            return QList<DatabaseGroup>();
        }
    }

    void MongoDatabaseConnector::UpdateGroup(const DatabaseGroup& Group, int TableId)
    {
        _WasError = false;

        try
        {
            _c.update(QString("%1.groups").arg(TableId).toStdString(),
                BSON("_id" << OID(Group.Id.toStdString())),
                BSON("$set" << BSON( "name" << Group.Name.toStdString()<<"description"<<Group.Description.toStdString()))
            );
        }catch( const mongo::DBException &e ) {
            _WasError = true;
            QString error = QString::fromStdString(e.what());
            _ErrorString = tr("Database Error : ") + error;
            qDebug()<<_ErrorString;
            return;
        }catch(...)
        {
            _WasError = true;
            _ErrorString = tr("Database Error");
            qDebug()<<"Database Error";
            return;
        }
        emit GroupManipulated();
    }

    QString MongoDatabaseConnector::InsertGroup(const DatabaseGroup& Group, int TableId)
    {
        _WasError = false;
        QString res;
        try
        {
            OID oid = OID::gen();
            QString OidString = QString::fromStdString(oid.toString());
            BSONObj p = BSONObjBuilder().append("_id", oid).append("name",Group.Name.toStdString()).append("description",Group.Description.toStdString()).obj();
            _c.insert(QString("%1.groups").arg(TableId).toStdString(), p);

            res = OidString;
        }catch( const mongo::DBException &e ) {
            _WasError = true;
            QString error = QString::fromStdString(e.what());
            _ErrorString = tr("Database Error : ") + error;
            qDebug()<<_ErrorString;
            return "";
        }catch(...)
        {
            _WasError = true;
            _ErrorString = tr("Database Error");
            qDebug()<<"Database Error";
            return "";
        }
        emit GroupManipulated();
        return res;
    }

    void MongoDatabaseConnector::MoveToGroup(DatabaseMassSelector Selector, QString NewGroupId)
    {
        MoveToGroup(Selector,  NewGroupId, true);
    }

    void MongoDatabaseConnector::CopyToGroup(DatabaseMassSelector Selector, QString NewGroupId)
    {
        MoveToGroup(Selector,  NewGroupId, false);
    }

    void MongoDatabaseConnector::MoveToGroup(DatabaseMassSelector Selector, QString NewGroupId, bool MoveOrCopy)
    {
        _WasError = false;

        try
        {
            BSONObj o = CombineQueryAnd(GenerateDatabaseGroupsAndItemsQuery(Selector.Groups,Selector.Items),GenerateFilterQuery(Selector.Filters));
            //qDebug()<<o.toString().c_str();
            BSONObj oa;
            if(MoveOrCopy)
            {
                BSONArrayBuilder b;
                b.append(OID(NewGroupId.toStdString()));
                oa = BSON("$set" << BSON("groups" << b.arr()));
            }
            else
            {
                oa = BSON("$addToSet" << BSON("groups" << OID(NewGroupId.toStdString())));
            }

            _c.update(QString("%1.res").arg(Selector.TableId).toStdString(),
                     o,
                     oa,
                     false,
                     true
                    );
        }catch( const mongo::DBException &e ) {
            _WasError = true;
            QString error = QString::fromStdString(e.what());
            _ErrorString = tr("Database Error : ") + error;
            qDebug()<<_ErrorString;
            return;
        }catch(...)
        {
            _WasError = true;
            _ErrorString = tr("Database Error");
            qDebug()<<"Database Error";
            return;
        }
    }
    void MongoDatabaseConnector::DeleteFromAllGroups(DatabaseMassSelector Selector)
    {
        _WasError = false;

        try
        {
            BSONObj o = CombineQueryAnd(GenerateDatabaseGroupsAndItemsQuery(Selector.Groups,Selector.Items),GenerateFilterQuery(Selector.Filters));
            _c.update(QString("%1.res").arg(Selector.TableId).toStdString(),
                     o,
                     BSON("$set" << BSON("groups" << BSONArray())),
                     false,
                     true
                    );
        }catch( const mongo::DBException &e ) {
            _WasError = true;
            QString error = QString::fromStdString(e.what());
            _ErrorString = tr("Database Error : ") + error;
            qDebug()<<_ErrorString;
            return;
        }catch(...)
        {
            _WasError = true;
            _ErrorString = tr("Database Error");
            qDebug()<<"Database Error";
            return;
        }
    }

    void MongoDatabaseConnector::DeleteGroupNoData(DatabaseGroups GroupIds, int TableId)
    {
        _WasError = false;

        try
        {

            BSONArrayBuilder ar,ar2;
            DatabaseGroups GroupIdsCopy = GroupIds;
            GroupIdsCopy.GroupIdList.removeAll("-2");
            GroupIdsCopy.GroupIdList.removeAll("-1");
            foreach(QString oid,GroupIds.GroupIdList)
            {
                if(oid!="-2")
                {
                    ar.append(OID(oid.toStdString()));
                    ar2.append(OID(oid.toStdString()));
                }
            }

            _c.update(QString("%1.res").arg(TableId).toStdString(),
                     GenerateDatabaseGroupsQuery(GroupIdsCopy),
                     BSON("$pull" << BSON("groups" << BSON("$in" << ar2.arr() ))),
                     false,
                     true
                    );

            _c.remove(QString("%1.groups").arg(TableId).toStdString(),
                BSON("_id" << BSON("$in" << ar.arr()))
            );
        }catch( const mongo::DBException &e ) {
            _WasError = true;
            QString error = QString::fromStdString(e.what());
            _ErrorString = tr("Database Error : ") + error;
            qDebug()<<_ErrorString;
            return;
        }catch(...)
        {
            _WasError = true;
            _ErrorString = tr("Database Error");
            qDebug()<<"Database Error";
            return;
        }
        emit GroupManipulated();
    }
    void MongoDatabaseConnector::DeleteGroupWithData(DatabaseGroups GroupIds, int TableId)
    {
        _WasError = false;

        try
        {

            BSONArrayBuilder ar;

            foreach(QString oid,GroupIds.GroupIdList)
            {
                if(oid!="-2")
                {
                    ar.append(OID(oid.toStdString()));
                }
            }

            _c.remove(QString("%1.res").arg(TableId).toStdString(),
                     GenerateDatabaseGroupsQuery(GroupIds)
                    );

            _c.remove(QString("%1.groups").arg(TableId).toStdString(),
                BSON("_id" << BSON("$in" << ar.arr()))
            );
        }catch( const mongo::DBException &e ) {
            _WasError = true;
            QString error = QString::fromStdString(e.what());
            _ErrorString = tr("Database Error : ") + error;
            qDebug()<<_ErrorString;
            return;
        }catch(...)
        {
            _WasError = true;
            _ErrorString = tr("Database Error");
            qDebug()<<"Database Error";
            return;
        }
        emit GroupManipulated();
    }
    void MongoDatabaseConnector::ClearGroup(DatabaseGroups GroupIds, int TableId)
    {
        _WasError = false;

        try
        {
            _c.remove(QString("%1.res").arg(TableId).toStdString(),
                     GenerateDatabaseGroupsQuery(GroupIds)
                    );
        }catch( const mongo::DBException &e ) {
            _WasError = true;
            QString error = QString::fromStdString(e.what());
            _ErrorString = tr("Database Error : ") + error;
            qDebug()<<_ErrorString;
            return;
        }catch(...)
        {
            _WasError = true;
            _ErrorString = tr("Database Error");
            qDebug()<<"Database Error";
            return;
        }
    }
    void MongoDatabaseConnector::DeleteAll()
    {
        _WasError = false;

        try
        {
            foreach(Table t,Schema.Tables)
                _c.dropDatabase(QString::number(t.Id).toStdString());
        }catch( const mongo::DBException &e ) {
            _WasError = true;
            QString error = QString::fromStdString(e.what());
            _ErrorString = tr("Database Error : ") + error;
            qDebug()<<_ErrorString;
            return;
        }catch(...)
        {
            _WasError = true;
            _ErrorString = tr("Database Error");
            qDebug()<<"Database Error";
            return;
        }
    }

    QString MongoDatabaseConnector::CopyGroup(const DatabaseGroup& NewGroup, int TableId, QString OriginalGroupId)
    {
        _WasError = false;

        try
        {
            QString NewGroupId = InsertGroup(NewGroup,TableId);
            DatabaseGroups Groups;
            Groups.IsNull = false;
            Groups.GroupIdList.append(OriginalGroupId);
            QString q = QString::fromStdString(GenerateDatabaseGroupsQuery(Groups).toString());
            q = QString("db.res.find(") + q + QString(").forEach( function(i) { i._id = ObjectId();i.groups=[ObjectId(\"") + QString(NewGroupId) + QString("\")];db.res.insert(i);});");

            _c.eval(QString::number(TableId).toStdString(),q.toStdString());

            return NewGroupId;
        }catch( const mongo::DBException &e ) {
            _WasError = true;
            QString error = QString::fromStdString(e.what());
            _ErrorString = tr("Database Error : ") + error;
            qDebug()<<_ErrorString;
            return QString();
        }catch(...)
        {
            _WasError = true;
            _ErrorString = tr("Database Error");
            qDebug()<<"Database Error";
            return QString();
        }
    }

    bool MongoDatabaseConnector::WasError()
    {
        return _WasError;
    }

    QString MongoDatabaseConnector::GetError()
    {
        return _ErrorString;
    }


    QList<DatabaseTable> MongoDatabaseConnector::GetTables()
    {
        QList<DatabaseTable> res;
        foreach(Table t, Schema.Tables)
        {
            DatabaseTable tr;
            tr.IsNull = false;
            tr.Name = t.Name;
            tr.Description = t.Description;
            tr.Id = t.Id;
            res.append(tr);
        }
        return res;
    }

    QList<DatabaseColumn> MongoDatabaseConnector::GetColumns(int TableId)
    {
        QList<DatabaseColumn> Columns;
        foreach(Table t,Schema.Tables)
        {
            if(t.Id == TableId)
            {
                foreach (Column c, t.Columns) {
                    DatabaseColumn res;
                    res.IsNull = false;
                    res.Description = c.Description;
                    res.Id = c.Id;
                    res.Name = c.Name;
                    switch(c.Type)
                    {
                        case String: res.Type = DatabaseColumn::String; break;
                        case Int: res.Type = DatabaseColumn::Int; break;
                        case Bool: res.Type = DatabaseColumn::Bool; break;
                        case Date: res.Type = DatabaseColumn::Date; break;
                    }
                    Columns.append(res);
                }

                break;
            }
        }
        return Columns;
    }

    void MongoDatabaseConnector::Init(const QString &Lang)
    {
        this->Lang = Lang;
    }

    bool MongoDatabaseConnector::HasDatabase()
    {
        return _HasDatabase;
    }

    void MongoDatabaseConnector::LoadSchema(const QString& SchemaText)
    {
        IsDatabasePresent = !SchemaText.isEmpty();
        Schema.Tables.clear();

        GetPort();
        QXmlStreamReader xmlReader(SchemaText);


        Table t;
        bool first = true;
        while(!xmlReader.atEnd() && !xmlReader.hasError())
        {

            QXmlStreamReader::TokenType token = xmlReader.readNext();
            /*if(xmlReader.name() == "DataBase" && token == QXmlStreamReader::StartElement)
            {
                foreach(QXmlStreamAttribute attr, xmlReader.attributes())
                {
                    if(attr.name() == "port")
                    {
                        Port = attr.value().toInt();
                    }
                }
            }*/

            if(xmlReader.name() == "Table" && token == QXmlStreamReader::StartElement)
            {
                _HasDatabase = true;

                if(!first)
                {
                    Schema.Tables.append(t);
                }
                t.Id = 0;
                t.Description.clear();
                t.Name.clear();
                t.Columns.clear();
                first = false;
                foreach(QXmlStreamAttribute attr, xmlReader.attributes())
                {
                    if(attr.name() == "id")
                    {
                        t.Id = attr.value().toInt();
                    }
                    if(attr.name() == "name")
                    {
                        t.Name = attr.value().toString();
                    }
                    if(attr.name() == (QString("description_") + Lang))
                    {
                        t.Description = attr.value().toString();
                    }

                }
            }
            if(xmlReader.name() == "Column" && token == QXmlStreamReader::StartElement)
            {
                Column c;
                foreach(QXmlStreamAttribute attr, xmlReader.attributes())
                {
                    if(attr.name() == "id")
                    {
                        c.Id = attr.value().toInt();
                    }
                    if(attr.name() == "name")
                    {
                        c.Name = attr.value().toString();
                    }
                    if(attr.name() == (QString("description_") + Lang))
                    {
                        c.Description = attr.value().toString();
                    }
                    if(attr.name() == "type")
                    {
                        QString type = attr.value().toString();

                        if(type == "string")
                        {
                            c.Type = String;
                        }
                        if(type == "int")
                        {
                            c.Type = Int;
                        }
                        if(type == "date")
                        {
                            c.Type = Date;
                        }
                        if(type == "bool")
                        {
                            c.Type = Bool;
                        }
                    }
                }
                t.Columns.append(c);
            }
        }
        if(!xmlReader.hasError())
        {
            Schema.Tables.append(t);
        }
        if(xmlReader.hasError())
        {
            IsDatabasePresent = false;
            _ErrorString = QString("Failed to load schema.xml : ") + xmlReader.errorString();
            return;
        }
        if(Schema.Tables.isEmpty())
        {
            IsDatabasePresent = false;
            _ErrorString = QString("Failed to load schema.xml : it is empty");
            return;
        }

    }

    bool MongoDatabaseConnector::IsConnected()
    {
        bool res = _c.isStillConnected();
        if(!res)
            StartServer();
        return res;
    }

    bool MongoDatabaseConnector::Init()
    {
        return client::initialize().isOK();
    }

    bool MongoDatabaseConnector::TryConnect()
    {
        IsDatabasePresent = false;
        try
        {
            QString ConnectionString;
            if(ConnectionIsRemote)
            {

                ConnectionString += ConnectionServer;
                if(!ConnectionPort.isEmpty())
                {
                    ConnectionString += QString(":");
                    ConnectionString += ConnectionPort;
                }
                ConnectionLog += "Remote Connection String = " + ConnectionString;
                qDebug()<<"RemoteConnectionString"<<ConnectionString;

                if(!ConnectionLogin.isEmpty() && !ConnectionPassword.isEmpty())
                {
                    qDebug()<<"RemoteConnectionLoginAndPass"<<ConnectionLogin<<ConnectionPassword;
                    //_c.connect(ConnectionString.toStdString(),ConnectionLogin.toStdString(),ConnectionPassword.toStdString());
                    _c.connect(ConnectionString.toStdString());
                }else
                {
                    _c.connect(ConnectionString.toStdString());
                }

            }else
            {
                ConnectionString = QString("localhost:%1").arg(QString::number(Port));
                _c.connect(ConnectionString.toStdString());
            }

            IsDatabasePresent = true;
            qDebug()<<"Connected";
        } catch( const DBException &e )
        {
            IsDatabasePresent = false;
            _ErrorString = QString(e.what());
            qDebug()<<"Connection Error"<<_ErrorString;
            ConnectionLog += "\nConnection Error = " + _ErrorString;
        }catch( ... )
        {
            IsDatabasePresent = false;
            _ErrorString = tr("Database error");
            qDebug()<<"Database error";
            ConnectionLog += "\nUnknown database error";
        }

        return IsDatabasePresent;
    }

    bool MongoDatabaseConnector::Start(const QString& SchemaText,const QString& DatabaseId, bool IsRemote, const QString& ConnectionServer, const QString& ConnectionPort, const QString& ConnectionLogin, const QString& ConnectionPassword)
    {
        this->ConnectionIsRemote = IsRemote;
        this->ConnectionServer = ConnectionServer;
        this->ConnectionPort = ConnectionPort;
        this->ConnectionLogin = ConnectionLogin;
        this->ConnectionPassword = ConnectionPassword;

        this->DatabaseId = DatabaseId;
        _WasError = false;
        _ErrorString.clear();

        LoadSchema(SchemaText);

        if(!IsDatabasePresent)
        {
            _WasError = true;
            emit Started();
            return true;
        }

        DatabaseConnectionWindow->Show();

        if(!IsRemote)
        {
            if(TryConnect())
            {
                DatabaseConnectionWindow->Hide();
                return true;
            }


            if(!EnsureDataDirCreated())
            {
                DatabaseConnectionWindow->Failed(tr("Failed to create data dir"));
                return false;
            }

            StartServer();
            return false;
        }
        else
        {
            if(TryConnect())
            {
                DatabaseConnectionWindow->Hide();
                return true;
            }else
            {
                DatabaseConnectionWindow->Failed(QString(tr("Failed to connect to database on server %1")).arg(ConnectionServer));
                return false;
            }
        }


    }

    void MongoDatabaseConnector::StartServer()
    {
        if(!IsBusy)
        {
            IsBusy = true;
            //WriteFirewallException();
            StartMongoProcess();
        }
    }

    bool MongoDatabaseConnector::EnsureDataDirCreated()
    {
        QDir dir(GetDatabaseLocation());
        if(!dir.exists())
        {
            if(!dir.mkpath("."))
                return false;
        }

        QDir dirc(GetDatabaseLocation() + QString("/current"));
        if(!dirc.exists())
        {
            if(!dirc.mkpath("."))
                return false;
        }
        return true;
    }
    void MongoDatabaseConnector::StartMongoProcess()
    {
        qDebug()<<"StartMongoProcess";
        /*if(CurrentNetshProcess->exitCode()!=0)
        {
            IsBusy = false;
            _WasError = true;
            _ErrorString = QString(tr("Failed to add firewall exception with code %1")).arg(QString::number(CurrentNetshProcess->exitCode()));
            emit Started();
        }*/

        MongoOutput.clear();
        CurrentMongoProcess = new QProcess();
        //connect(CurrentMongoProcess,SIGNAL(finished(int)),this,SLOT(MongoProcessTerminate()));
        connect(CurrentMongoProcess,SIGNAL(finished(int)),this,SLOT(MongoServerClosed()));
        //connect(CurrentMongoProcess,SIGNAL(readyRead()),this,SLOT(ProcessReadDebug()));
        connect(CurrentMongoProcess,SIGNAL(readyRead()),this,SLOT(ProcessRead()));
        connect(CurrentMongoProcess,SIGNAL(started()),this,SLOT(SaveMongoPid()));

        connect(CurrentMongoProcess,SIGNAL(destroyed()),this,SLOT(ClosePort()));
        //connect(this,SIGNAL(TerminateProcess()),CurrentMongoProcess,SLOT(terminate()));

        QString exe = "mongod.exe";
        if(QSysInfo::windowsVersion() < QSysInfo::WV_VISTA)
            exe = "mongodxp.exe";
        #ifdef Q_OS_LINUX
            exe = "mongod";
        #endif
        CurrentMongoProcess->setWorkingDirectory(GetDatabaseLocation());
        CurrentMongoProcess->start(exe,QStringList()<<"--dbpath"<<QString("current")<<"--port"<<QString::number(Port)<<"--bind_ip"<<"127.0.0.1"<<"--journal"<<"--smallfiles");
    }

    void MongoDatabaseConnector::MongoServerClosed()
    {
        if(IsBusy)
        {
            TryConnectFinal();
        }else
        {
            StartServer();
        }
    }

    void MongoDatabaseConnector::TryConnectFinal()
    {
        if(TryConnect())
        {
            IsBusy = false;
            if(DatabaseConnectionWindow)
                DatabaseConnectionWindow->Hide();
            return;
        }else
        {
            IsBusy = false;
            if(DatabaseConnectionWindow)
                DatabaseConnectionWindow->Failed(QString(tr("Failed to run database server on port %1. Please check firewall settings, maybe exception should be added. This error may occur if you have less than 4GB free space on hard drive.")).arg(QString::number(Port)));
            return;
        }
    }

    void MongoDatabaseConnector::ProcessRead()
    {

        if(sender() == CurrentMongoProcess)
        {
            QString append = CurrentMongoProcess->readAll();
            MongoOutput.append(append);
            ConnectionLog.append(append);
            qDebug()<<append;
            if(MongoOutput.contains("waiting for connections on port"))
            {
                MongoOutput.clear();
                disconnect(CurrentMongoProcess,SIGNAL(readyRead()),this,SLOT(ProcessRead()));
                TryConnectFinal();
            }else if (MongoOutput.contains("ERROR: listen(): bind() failed"))
            {
                MongoOutput.clear();
                disconnect(CurrentMongoProcess,SIGNAL(readyRead()),this,SLOT(ProcessRead()));
                CurrentMongoProcess->deleteLater();
                CurrentMongoProcess = 0;

                ChangePort();

                IsBusy = false;

            }
        }
    }





    /*void MongoDatabaseConnector::WriteFirewallException()
    {
        QString command = QString("netsh advfirewall firewall show rule name=\"Open mongod port %1\"").arg(QString::number(Port));
        qDebug()<<"WriteFirewallException"<<command;
        CurrentNetshProcess = new QProcess(this);
        connect(CurrentNetshProcess,SIGNAL(finished(int)),CurrentNetshProcess,SLOT(deleteLater()));
        connect(CurrentNetshProcess,SIGNAL(finished(int)),this,SLOT(WriteFirewallException2()));
        connect(CurrentNetshProcess,SIGNAL(destroyed()),CurrentNetshProcess,SLOT(terminate()));
        CurrentNetshProcess->start(command);
    }

    void MongoDatabaseConnector::WriteFirewallException2()
    {
        if(CurrentNetshProcess->exitCode()==0)
        {
            StartMongoProcess();
            return;
        }
        QString command = QString("netsh advfirewall firewall add rule name=\"Open mongod port %1\" dir=in action=allow protocol=TCP localport=%1").arg(QString::number(Port));
        qDebug()<<"WriteFirewallException 2"<<CurrentNetshProcess->exitCode()<<command;
        CurrentNetshProcess = new QProcess(this);
        connect(CurrentNetshProcess,SIGNAL(finished(int)),CurrentNetshProcess,SLOT(deleteLater()));
        connect(CurrentNetshProcess,SIGNAL(finished(int)),this,SLOT(StartMongoProcess()));
        connect(CurrentNetshProcess,SIGNAL(destroyed()),CurrentNetshProcess,SLOT(terminate()));
        CurrentNetshProcess->start(command);
    }*/


    QStringList MongoDatabaseConnector::ShowBackupList()
    {
        _WasError = false;
        QStringList res;
        QDirIterator it(GetDatabaseLocation());
        while (it.hasNext())
        {
            it.next();
            if(it.fileInfo().isDir() && it.fileName() != "." && it.fileName() != ".." && it.fileName() != "current"  )
            {
                 res.append(it.fileName());
            }
        }
        return res;
    }




    void MongoDatabaseConnector::Backup()
    {
        _WasError = false;
        QProcess *Process = new QProcess(this);
        QString res = QDateTime::currentDateTime().toString("dd.MM.yyyy hh.mm.ss");

        connect(Process,SIGNAL(finished(int)),this,SLOT(BackupRestoreFinishedSlot(int)));
        connect(Process,SIGNAL(finished(int)),Process,SLOT(deleteLater()));
        connect(Process,SIGNAL(destroyed()),Process,SLOT(terminate()));

        QString exe = "mongodump.exe";
        if(QSysInfo::windowsVersion() < QSysInfo::WV_VISTA)
            exe = "mongodumpxp.exe";
        Process->start(exe,QStringList()<<"--out"<<GetDatabaseLocation() + res<<"--port"<<QString::number(Port));

    }
    void MongoDatabaseConnector::Restore(const QString& BackupLabel)
    {
        _WasError = false;
        QProcess *Process = new QProcess(this);

        connect(Process,SIGNAL(finished(int)),this,SLOT(BackupRestoreFinishedSlot(int)));
        connect(Process,SIGNAL(finished(int)),Process,SLOT(deleteLater()));
        connect(Process,SIGNAL(destroyed()),Process,SLOT(terminate()));

        QString exe = "mongorestore.exe";
        if(QSysInfo::windowsVersion() < QSysInfo::WV_VISTA)
            exe = "mongorestorexp.exe";
        Process->start(exe,QStringList()<<"--port"<<QString::number(Port)<<QString(GetDatabaseLocation()) + BackupLabel);
    }

    void MongoDatabaseConnector::BackupRestoreFinishedSlot(int res)
    {
        //qDebug()<<"BackupRestoreFinished"<<res;
        emit BackupOrRestoreFinished();
    }

    DatabaseFilters MongoDatabaseConnector::ParseFilter(const QString& JsonFilters)
    {
        DatabaseFilters res;
        QJsonParseError err;

        res.IsNull = true;
        QJsonDocument InputObject = QJsonDocument::fromJson(JsonFilters.toUtf8(),&err);
        if(err.error)
            return res;

        res.IsNull = false;

        for(QJsonValue val:InputObject.array())
        {
            QJsonArray array = val.toArray();
            DatabaseFilter f;

            bool IsString = false;
            bool IsInt = false;
            bool IsValid = true;
            qlonglong IntValue = 0;
            QString StringValue;

            if(array.size()>=3)
            {
                if(array[2].isDouble())
                {
                    IsInt = true;
                    IntValue = array[2].toDouble();
                }
                if(array[2].isString())
                {
                    IsString = true;
                    StringValue = array[2].toString();
                }
            }

            if(array.size()>=2)
            {
                f.ColumnId = array[0].toInt();
                QString type = array[1].toString();

                if(type == "StringNotEmpty")
                    f.Type = DatabaseFilter::StringNotEmpty;

                if(type == "StringEmpty")
                    f.Type = DatabaseFilter::StringEmpty;

                if(type == "StringContains")
                {
                    f.Type = DatabaseFilter::StringContains;
                    if(IsInt)
                    {
                        f.Data = QString::number(IntValue);
                    }else if(IsString)
                    {
                        f.Data = StringValue;
                    }
                    else
                    {
                        IsValid = false;
                    }
                }

                if(type == "IntEquals")
                {
                    f.Type = DatabaseFilter::IntEquals;
                    if(IsInt)
                    {
                        f.Data = IntValue;
                    }else if(IsString)
                    {
                        f.Data = StringValue.toInt();
                    }
                    else
                    {
                        IsValid = false;
                    }
                }

                if(type == "IntNotEquals")
                {
                    f.Type = DatabaseFilter::IntNotEquals;
                    if(IsInt)
                    {
                        f.Data = IntValue;
                    }else if(IsString)
                    {
                        f.Data = StringValue.toInt();
                    }
                    else
                    {
                        IsValid = false;
                    }
                }

                if(type == "IntGreaterOrEqual")
                {
                    f.Type = DatabaseFilter::IntGreaterOrEqual;
                    if(IsInt)
                    {
                        f.Data = IntValue;
                    }else if(IsString)
                    {
                        f.Data = StringValue.toInt();
                    }
                    else
                    {
                        IsValid = false;
                    }
                }

                if(type == "IntGreater")
                {
                    f.Type = DatabaseFilter::IntGreater;
                    if(IsInt)
                    {
                        f.Data = IntValue;
                    }else if(IsString)
                    {
                        f.Data = StringValue.toInt();
                    }
                    else
                    {
                        IsValid = false;
                    }
                }

                if(type == "IntLessThan")
                {
                    f.Type = DatabaseFilter::IntLessThan;
                    if(IsInt)
                    {
                        f.Data = IntValue;
                    }else if(IsString)
                    {
                        f.Data = StringValue.toInt();
                    }
                    else
                    {
                        IsValid = false;
                    }
                }

                if(type == "IntLessThanOrEqual")
                {
                    f.Type = DatabaseFilter::IntLessThanOrEqual;
                    if(IsInt)
                    {
                        f.Data = IntValue;
                    }else if(IsString)
                    {
                        f.Data = StringValue.toInt();
                    }
                    else
                    {
                        IsValid = false;
                    }
                }

                if(type == "BoolIsTrue")
                    f.Type = DatabaseFilter::BoolIsTrue;

                if(type == "BoolIsFalse")
                    f.Type = DatabaseFilter::BoolIsFalse;

                if(type == "DateIsLessThan")
                {
                    f.Type = DatabaseFilter::DateIsLessThan;
                    if(IsInt)
                    {
                        QDateTime timestamp;
                        timestamp.setTime_t(IntValue / 1000);
                        f.Data = timestamp;
                    }
                    else
                    {
                        IsValid = false;
                    }
                }

                if(type == "DateGreaterThan")
                {
                    f.Type = DatabaseFilter::DateGreaterThan;
                    if(IsInt)
                    {
                        QDateTime timestamp;
                        timestamp.setTime_t(IntValue / 1000);
                        f.Data = timestamp;
                    }
                    else
                    {
                        IsValid = false;
                    }
                }

                if(type == "DateIsSameYear")
                {
                    f.Type = DatabaseFilter::DateIsSameYear;
                    if(IsInt)
                    {
                        QDateTime timestamp;
                        timestamp.setTime_t(IntValue / 1000);
                        f.Data = timestamp;
                    }
                    else
                    {
                        IsValid = false;
                    }
                }

                if(type == "DateIsSameMonth")
                {
                    f.Type = DatabaseFilter::DateIsSameMonth;
                    if(IsInt)
                    {
                        QDateTime timestamp;
                        timestamp.setTime_t(IntValue / 1000);
                        f.Data = timestamp;
                    }
                    else
                    {
                        IsValid = false;
                    }
                }

                if(type == "DateIsSameDay")
                {
                    f.Type = DatabaseFilter::DateIsSameDay;
                    if(IsInt)
                    {
                        QDateTime timestamp;
                        timestamp.setTime_t(IntValue / 1000);
                        f.Data = timestamp;
                    }
                    else
                    {
                        IsValid = false;
                    }
                }

                if(type == "DateIsSameHour")
                {
                    f.Type = DatabaseFilter::DateIsSameHour;
                    if(IsInt)
                    {
                        QDateTime timestamp;
                        timestamp.setTime_t(IntValue / 1000);
                        f.Data = timestamp;
                    }
                    else
                    {
                        IsValid = false;
                    }
                }



            }
            if(IsValid)
                res.FilterList.append(f);
        }

        return res;
    }

    void MongoDatabaseConnector::GetPort()
    {
        QSettings Settings(GetDatabaseBaseLocation() + QString("settings.ini"),QSettings::IniFormat);
        if(Settings.value(DatabaseId,"").toString().isEmpty())
        {
            Port = qrand() % 10000 + 10000;
            Settings.setValue(DatabaseId,QString::number(Port) + QString(";") + QString::number(qApp->applicationPid()));
        }else
        {
            QStringList Value = Settings.value(DatabaseId,"").toString().split(";");
            QString PortString = Value.first();
            QStringList Pids = Value.last().split(",");
            if(!Pids.contains(QString::number(qApp->applicationPid())))
            {
                Pids.append(QString::number(qApp->applicationPid()));
                Settings.setValue(DatabaseId,PortString + QString(";") + Pids.join(","));
            }
            Port = PortString.toInt();
        }
    }

    void MongoDatabaseConnector::ChangePort()
    {
        QSettings Settings(GetDatabaseBaseLocation() + QString("settings.ini"),QSettings::IniFormat);
        Port = qrand() % 10000 + 10000;
        Settings.setValue(DatabaseId,QString::number(Port) + QString(";") + QString::number(qApp->applicationPid()));
    }

    BOOL TerminateProcess(DWORD dwProcessId, UINT uExitCode)
    {
        DWORD dwDesiredAccess = PROCESS_TERMINATE;
        BOOL  bInheritHandle  = FALSE;
        HANDLE hProcess = OpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId);
        if (hProcess == NULL)
            return FALSE;

        BOOL result = ::TerminateProcess(hProcess, uExitCode);

        CloseHandle(hProcess);

        return result;
    }

    void MongoDatabaseConnector::ClosePort()
    {
        //qDebug()<<"ClosePort";
        QSettings Settings(GetDatabaseBaseLocation() + QString("settings.ini"),QSettings::IniFormat);
        QStringList Value = Settings.value(DatabaseId,"").toString().split(";");
        if(Settings.value(DatabaseId,"").toString().isEmpty())
        {
            MongoProcessTerminate();
            return;
        }

        QString PortString = Value.first();
        QStringList Pids = Value.last().split(",");
        if(Pids.contains(QString::number(qApp->applicationPid())))
        {
            Pids.removeAll(QString::number(qApp->applicationPid()));
        }

        if(Pids.isEmpty())
        {
            if(CurrentMongoProcess)
            {
                MongoProcessTerminate();
                Settings.remove(DatabaseId);
            }else
            {
                if(Settings.contains(QString("MongoPid") + DatabaseId))
                {
                    TerminateProcess(Settings.value(QString("MongoPid") + DatabaseId,"0").toString().toULongLong(),0);
                    Settings.remove(QString("MongoPid") + DatabaseId);
                    Settings.remove(DatabaseId);
                }
            }
        }else
        {
            Settings.setValue(DatabaseId,PortString + QString(";") + Pids.join(","));
        }

    }

    void MongoDatabaseConnector::SaveMongoPid()
    {
        if(!CurrentMongoProcess)
            return;
        QSettings Settings(GetDatabaseBaseLocation() + QString("settings.ini"),QSettings::IniFormat);
        QString pid = QString::number(CurrentMongoProcess->processId());
        Settings.setValue(QString("MongoPid") + DatabaseId,pid);
    }

    void MongoDatabaseConnector::MongoProcessTerminate()
    {
        //qDebug()<<"MongoProcessTerminate";
        if(CurrentMongoProcess)
        {
            CurrentMongoProcess->deleteLater();
            {
                QSettings Settings(GetDatabaseBaseLocation() + QString("settings.ini"),QSettings::IniFormat);
                Settings.remove(QString("MongoPid") + DatabaseId);
            }

            CurrentMongoProcess->kill();
            CurrentMongoProcess = 0;
        }
    }




}
