#include <QString>
#include <QtTest>

#include "copyresourcecontroller.h"
#include "resources.h"
#include "resourcemodelfixedstring.h"
#include "resourcemodelfixedinteger.h"
#include "resourcemodelrandominteger.h"
#include "resourcemodelrandomstring.h"
#include "resourcemodelselect.h"
#include "resourcemodelfile.h"
#include "resourcemodelurl.h"
#include "resourcemodeldirectory.h"

using namespace BrowserAutomationStudioFramework;

class CopyResourcesTests : public QObject
{
    Q_OBJECT

public:
    CopyResourcesTests();

private Q_SLOTS:
    void CheckIfTypeIsChangedWhenNeededSelect1();
    void CheckIfTypeIsChangedWhenNeededSelect2();
    void CheckIfTypeIsChangedWhenNeededDirectory();
    void CheckIfTypeIsChangedWhenNeededUrl();
    void CheckIfTypeIsChangedWhenNeededFile();
    void CheckIfTypeIsChangedWhenNeededRandomInteger();
    void CheckIfTypeIsChangedWhenNeededRandomString();
    void CheckIfTypeIsChangedWhenNeededFixedString();
    void CheckIfTypeIsChangedWhenNeededFixedInteger();
    void CheckIfTypeIsNotChangedWhenNoNeededSelect();
    void CheckIfTypeIsNotChangedWhenNoNeededDirectory();
    void CheckIfTypeIsNotChangedWhenNoNeededUrl();
    void CheckIfTypeIsNotChangedWhenNoNeededFile();
    void CheckIfTypeIsNotChangedWhenNoNeededRandomInteger();
    void CheckIfTypeIsNotChangedWhenNoNeededRandomString();
    void CheckIfTypeIsNotChangedWhenNoNeededFixedString();
    void CheckIfTypeIsNotChangedWhenNoNeededFixedInteger();
    void CheckIfValuesAreFromUsersEvenIfDefaultsAreNotSameType();
    void CheckIfNameIsRespected();
    void CheckIfNameIsRespected2();
    void CheckIfTypeIsChangedWhenNeeded();
    void CheckIfTypeIsNotChangedWhenNoNeeded();
    void CheckIfRunsOkIfDefaultTypesAreDifferent();
    void CheckIfFixedIntegerRespectsDefault();
    void CheckIfWorksWithNoDefaultsAndEmptyUserValues();
    void CheckIfWorksWithNoDefaults();
    void CheckIfTypeIsPreserved();
    void CheckIfFixedStringRespectsDefault();
    void CheckIfFixedStringPreservesNotEmpty();
    void CheckIfSomeValuesAreFromDefaultsAndSomeNot();
    void CheckIfFixedStringIsChanged();
    void CheckIfFixedIntegerIsChanged();
    void CheckIfRandomStringIsChanged();
    void CheckIfRandomIntegerIsChanged();
    void CheckIfFileIsChanged();
    void CheckIfUrlIsChanged();
    void CheckIfDirectoryIsChanged();
    void CheckIfSelectIsChanged();



};

CopyResourcesTests::CopyResourcesTests()
{
}


void CopyResourcesTests::CheckIfTypeIsChangedWhenNeededSelect1()
{
    CopyResourceController * _Controller = new CopyResourceController(this);
    _Controller->deleteLater();


    Resources *_ResourcesDeveloper = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDeveloper = _ResourcesDeveloper->GetModelList();

    ResourceModelUrl *Model1 = new ResourceModelUrl(_Controller);
    Model1->SetName("name1");
    Model1->SetUrl("tes1_url1");

    ResourceModelSelect *Model12 = new ResourceModelSelect(_Controller);
    Model12->SetName("name1");
    Model12->SetValues(QStringList()<<"vall1"<<"vall2"<<"vall3");
    Model12->SetSelected(QList<int>()<<0<<1);


    QList<IResourceModel * > ModelsDeveloperDefaults = QList<IResourceModel * >()<<Model12;
    Model1->SetDefaults(ModelsDeveloperDefaults);
    ModelsDeveloper->append(Model1);


    Resources *_ResourcesUser = new Resources(_Controller);
    QList<IResourceModel * >* ModelsUser = _ResourcesUser->GetModelList();

    ResourceModelSelect *Model2 = new ResourceModelSelect(_Controller);
    Model2->SetName("name1");
    Model2->SetValues(QStringList()<<"val1"<<"val2"<<"vall3");
    Model2->SetSelected(QList<int>()<<0<<2);

    ModelsUser->append(Model2);


    Resources *_ResourcesDefault = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDefault = _ResourcesDefault->GetModelList();

    ResourceModelSelect *Model3 = new ResourceModelSelect(_Controller);
    Model3->SetName("name1");
    Model3->SetValues(QStringList()<<"val3"<<"val1"<<"val2");
    Model3->SetSelected(QList<int>()<<1<<2);

    ResourceModelFixedString *Model31 = new ResourceModelFixedString(_Controller);
    Model31->SetName("name1");
    Model31->SetValue("123");

    QList<IResourceModel * > ModelsDefaultDefaults = QList<IResourceModel * >()<<Model31;
    Model3->SetDefaults(ModelsDefaultDefaults);
    ModelsDefault->append(Model3);



    ModelsDefault->append(Model3);


    _Controller->SetDefaults(_ResourcesDefault);
    _Controller->SetResources(_ResourcesUser);
    _Controller->FromViewToModel(_ResourcesDeveloper);


    ModelsDeveloper = _ResourcesDeveloper->GetModelList();
    QCOMPARE(ModelsDeveloper->length(),1);
    IResourceModel * ModelResultInterface = ModelsDeveloper->at(0);
    QCOMPARE(ModelResultInterface->GetTypeId(),QString("Select"));
    ResourceModelSelect * ModelResult = qobject_cast<ResourceModelSelect *>(ModelResultInterface);
    if(ModelResult == 0)
        QFAIL("Object is 0 after cast");


    QCOMPARE(ModelResult->GetDefaults().length(),1);
    IResourceModel * ModelResultDefaultInterface = ModelResult->GetDefaults().at(0);
    QCOMPARE(ModelResultDefaultInterface->GetTypeId(),QString("LinesFromUrl"));
    ResourceModelUrl * ModelResultDefault = qobject_cast<ResourceModelUrl *>(ModelResultDefaultInterface);
    if(ModelResultDefault == 0)
        QFAIL("Object is 0 after cast");

    QStringList l1 = ModelResult->GetValues();
    l1.sort();
    QStringList l2;
    foreach(int i, ModelResult->GetSelected())
    {
        l2.append(QString::number(i));
    }
    l2.sort();

    QCOMPARE(l1.join(","),QString("vall1,vall2,vall3"));
    QCOMPARE(l2.join(","),QString("2"));
    QCOMPARE(ModelResultDefault->GetUrl(),QString("tes1_url1"));

}


void CopyResourcesTests::CheckIfTypeIsChangedWhenNeededSelect2()
{
    CopyResourceController * _Controller = new CopyResourceController(this);
    _Controller->deleteLater();


    Resources *_ResourcesDeveloper = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDeveloper = _ResourcesDeveloper->GetModelList();

    ResourceModelUrl *Model1 = new ResourceModelUrl(_Controller);
    Model1->SetName("name1");
    Model1->SetUrl("tes1_url1");

    ResourceModelSelect *Model12 = new ResourceModelSelect(_Controller);
    Model12->SetName("name1");
    Model12->SetValues(QStringList()<<"vall1"<<"vall2"<<"vall3");
    Model12->SetSelected(QList<int>()<<0<<1);


    QList<IResourceModel * > ModelsDeveloperDefaults = QList<IResourceModel * >()<<Model12;
    Model1->SetDefaults(ModelsDeveloperDefaults);
    ModelsDeveloper->append(Model1);


    Resources *_ResourcesUser = new Resources(_Controller);
    QList<IResourceModel * >* ModelsUser = _ResourcesUser->GetModelList();

    ResourceModelSelect *Model2 = new ResourceModelSelect(_Controller);
    Model2->SetName("name1");
    Model2->SetValues(QStringList()<<"val1"<<"val2"<<"val3");
    Model2->SetSelected(QList<int>()<<0<<2);

    ModelsUser->append(Model2);


    Resources *_ResourcesDefault = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDefault = _ResourcesDefault->GetModelList();

    ResourceModelSelect *Model3 = new ResourceModelSelect(_Controller);
    Model3->SetName("name1");
    Model3->SetValues(QStringList()<<"val3"<<"val1"<<"vall2");
    Model3->SetSelected(QList<int>()<<1<<0);

    ResourceModelFixedString *Model31 = new ResourceModelFixedString(_Controller);
    Model31->SetName("name1");
    Model31->SetValue("123");

    QList<IResourceModel * > ModelsDefaultDefaults = QList<IResourceModel * >()<<Model31;
    Model3->SetDefaults(ModelsDefaultDefaults);
    ModelsDefault->append(Model3);



    ModelsDefault->append(Model3);


    _Controller->SetDefaults(_ResourcesDefault);
    _Controller->SetResources(_ResourcesUser);
    _Controller->FromViewToModel(_ResourcesDeveloper);


    ModelsDeveloper = _ResourcesDeveloper->GetModelList();
    QCOMPARE(ModelsDeveloper->length(),1);
    IResourceModel * ModelResultInterface = ModelsDeveloper->at(0);
    QCOMPARE(ModelResultInterface->GetTypeId(),QString("Select"));
    ResourceModelSelect * ModelResult = qobject_cast<ResourceModelSelect *>(ModelResultInterface);
    if(ModelResult == 0)
        QFAIL("Object is 0 after cast");


    QCOMPARE(ModelResult->GetDefaults().length(),1);
    IResourceModel * ModelResultDefaultInterface = ModelResult->GetDefaults().at(0);
    QCOMPARE(ModelResultDefaultInterface->GetTypeId(),QString("LinesFromUrl"));
    ResourceModelUrl * ModelResultDefault = qobject_cast<ResourceModelUrl *>(ModelResultDefaultInterface);
    if(ModelResultDefault == 0)
        QFAIL("Object is 0 after cast");

    QStringList l1 = ModelResult->GetValues();
    l1.sort();
    QStringList l2;
    foreach(int i, ModelResult->GetSelected())
    {
        l2.append(QString::number(i));
    }
    l2.sort();

    QCOMPARE(l1.join(","),QString("vall1,vall2,vall3"));
    QCOMPARE(l2.join(","),QString("0,1"));
    QCOMPARE(ModelResultDefault->GetUrl(),QString("tes1_url1"));

}


void CopyResourcesTests::CheckIfTypeIsChangedWhenNeededDirectory()
{
    CopyResourceController * _Controller = new CopyResourceController(this);
    _Controller->deleteLater();


    Resources *_ResourcesDeveloper = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDeveloper = _ResourcesDeveloper->GetModelList();

    ResourceModelUrl *Model1 = new ResourceModelUrl(_Controller);
    Model1->SetName("name1");
    Model1->SetUrl("tes1_url1");

    ResourceModelDirectory *Model12 = new ResourceModelDirectory(_Controller);
    Model12->SetName("name1");
    Model12->SetDirectory("file_name1");
    Model12->SetGreedy(true);
    Model12->SetMix(true);
    Model12->SetNumberSimultaneousUse(987);


    QList<IResourceModel * > ModelsDeveloperDefaults = QList<IResourceModel * >()<<Model12;
    Model1->SetDefaults(ModelsDeveloperDefaults);
    ModelsDeveloper->append(Model1);


    Resources *_ResourcesUser = new Resources(_Controller);
    QList<IResourceModel * >* ModelsUser = _ResourcesUser->GetModelList();

    ResourceModelDirectory *Model2 = new ResourceModelDirectory(_Controller);
    Model2->SetName("name1");
    Model2->SetDirectory("file_name2");
    Model2->SetGreedy(false);
    Model2->SetMix(false);
    Model2->SetNumberSimultaneousUse(9871);

    ModelsUser->append(Model2);


    Resources *_ResourcesDefault = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDefault = _ResourcesDefault->GetModelList();

    ResourceModelDirectory *Model3 = new ResourceModelDirectory(_Controller);
    Model3->SetName("name1");
    Model3->SetDirectory("file_name2");
    Model3->SetGreedy(true);
    Model3->SetMix(false);
    Model3->SetNumberSimultaneousUse(9871);

    ResourceModelSelect *Model31 = new ResourceModelSelect(_Controller);
    Model31->SetName("name1");
    Model31->SetValues(QStringList()<<"value1"<<"value2"<<"value3");

    QList<IResourceModel * > ModelsDefaultDefaults = QList<IResourceModel * >()<<Model31;
    Model3->SetDefaults(ModelsDefaultDefaults);
    ModelsDefault->append(Model3);



    ModelsDefault->append(Model3);


    _Controller->SetDefaults(_ResourcesDefault);
    _Controller->SetResources(_ResourcesUser);
    _Controller->FromViewToModel(_ResourcesDeveloper);


    ModelsDeveloper = _ResourcesDeveloper->GetModelList();
    QCOMPARE(ModelsDeveloper->length(),1);
    IResourceModel * ModelResultInterface = ModelsDeveloper->at(0);
    QCOMPARE(ModelResultInterface->GetTypeId(),QString("FilesFromDirectory"));
    ResourceModelDirectory * ModelResult = qobject_cast<ResourceModelDirectory *>(ModelResultInterface);
    if(ModelResult == 0)
        QFAIL("Object is 0 after cast");


    QCOMPARE(ModelResult->GetDefaults().length(),1);
    IResourceModel * ModelResultDefaultInterface = ModelResult->GetDefaults().at(0);
    QCOMPARE(ModelResultDefaultInterface->GetTypeId(),QString("LinesFromUrl"));
    ResourceModelUrl * ModelResultDefault = qobject_cast<ResourceModelUrl *>(ModelResultDefaultInterface);
    if(ModelResultDefault == 0)
        QFAIL("Object is 0 after cast");

    QCOMPARE(ModelResult->GetDirectory(),QString("file_name1"));
    QCOMPARE(ModelResult->GetGreedy(),false);
    QCOMPARE(ModelResult->GetNumberSimultaneousUse(),987);
    QCOMPARE(ModelResultDefault->GetUrl(),QString("tes1_url1"));

}

void CopyResourcesTests::CheckIfTypeIsChangedWhenNeededUrl()
{
    CopyResourceController * _Controller = new CopyResourceController(this);
    _Controller->deleteLater();


    Resources *_ResourcesDeveloper = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDeveloper = _ResourcesDeveloper->GetModelList();

    ResourceModelFile *Model1 = new ResourceModelFile(_Controller);
    Model1->SetName("name1");
    Model1->SetFilename("tes1_filennn1");

    ResourceModelUrl *Model12 = new ResourceModelUrl(_Controller);
    Model12->SetName("name1");
    Model12->SetUrl("url1");
    Model12->SetGreedy(true);
    Model12->SetMix(true);
    Model12->SetNumberSimultaneousUse(987);


    QList<IResourceModel * > ModelsDeveloperDefaults = QList<IResourceModel * >()<<Model12;
    Model1->SetDefaults(ModelsDeveloperDefaults);
    ModelsDeveloper->append(Model1);


    Resources *_ResourcesUser = new Resources(_Controller);
    QList<IResourceModel * >* ModelsUser = _ResourcesUser->GetModelList();

    ResourceModelUrl *Model2 = new ResourceModelUrl(_Controller);
    Model2->SetName("name1");
    Model2->SetUrl("url2");
    Model2->SetGreedy(false);
    Model2->SetMix(false);
    Model2->SetNumberSimultaneousUse(9871);

    ModelsUser->append(Model2);


    Resources *_ResourcesDefault = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDefault = _ResourcesDefault->GetModelList();

    ResourceModelUrl *Model3 = new ResourceModelUrl(_Controller);
    Model3->SetName("name1");
    Model3->SetUrl("url2");
    Model3->SetGreedy(true);
    Model3->SetMix(false);
    Model3->SetNumberSimultaneousUse(9871);

    ResourceModelSelect *Model31 = new ResourceModelSelect(_Controller);
    Model31->SetName("name1");
    Model31->SetValues(QStringList()<<"value1"<<"value2"<<"value3");

    QList<IResourceModel * > ModelsDefaultDefaults = QList<IResourceModel * >()<<Model31;
    Model3->SetDefaults(ModelsDefaultDefaults);
    ModelsDefault->append(Model3);



    ModelsDefault->append(Model3);


    _Controller->SetDefaults(_ResourcesDefault);
    _Controller->SetResources(_ResourcesUser);
    _Controller->FromViewToModel(_ResourcesDeveloper);


    ModelsDeveloper = _ResourcesDeveloper->GetModelList();
    QCOMPARE(ModelsDeveloper->length(),1);
    IResourceModel * ModelResultInterface = ModelsDeveloper->at(0);
    QCOMPARE(ModelResultInterface->GetTypeId(),QString("LinesFromUrl"));
    ResourceModelUrl * ModelResult = qobject_cast<ResourceModelUrl *>(ModelResultInterface);
    if(ModelResult == 0)
        QFAIL("Object is 0 after cast");


    QCOMPARE(ModelResult->GetDefaults().length(),1);
    IResourceModel * ModelResultDefaultInterface = ModelResult->GetDefaults().at(0);
    QCOMPARE(ModelResultDefaultInterface->GetTypeId(),QString("LinesFromFile"));
    ResourceModelFile * ModelResultDefault = qobject_cast<ResourceModelFile *>(ModelResultDefaultInterface);
    if(ModelResultDefault == 0)
        QFAIL("Object is 0 after cast");

    QCOMPARE(ModelResult->GetUrl(),QString("url1"));
    QCOMPARE(ModelResult->GetGreedy(),false);
    QCOMPARE(ModelResult->GetNumberSimultaneousUse(),987);
    QCOMPARE(ModelResultDefault->GetFilename(),QString("tes1_filennn1"));

}


void CopyResourcesTests::CheckIfTypeIsChangedWhenNeededFile()
{
    CopyResourceController * _Controller = new CopyResourceController(this);
    _Controller->deleteLater();


    Resources *_ResourcesDeveloper = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDeveloper = _ResourcesDeveloper->GetModelList();

    ResourceModelUrl *Model1 = new ResourceModelUrl(_Controller);
    Model1->SetName("name1");
    Model1->SetUrl("tes1_url1");

    ResourceModelFile *Model12 = new ResourceModelFile(_Controller);
    Model12->SetName("name1");
    Model12->SetFilename("file_name1");
    Model12->SetGreedy(false);
    Model12->SetMix(true);
    Model12->SetNumberSimultaneousUse(987);


    QList<IResourceModel * > ModelsDeveloperDefaults = QList<IResourceModel * >()<<Model12;
    Model1->SetDefaults(ModelsDeveloperDefaults);
    ModelsDeveloper->append(Model1);


    Resources *_ResourcesUser = new Resources(_Controller);
    QList<IResourceModel * >* ModelsUser = _ResourcesUser->GetModelList();

    ResourceModelFile *Model2 = new ResourceModelFile(_Controller);
    Model2->SetName("name1");
    Model2->SetFilename("file_name2");
    Model2->SetGreedy(true);
    Model2->SetMix(false);
    Model2->SetNumberSimultaneousUse(9871);

    ModelsUser->append(Model2);


    Resources *_ResourcesDefault = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDefault = _ResourcesDefault->GetModelList();

    ResourceModelFile *Model3 = new ResourceModelFile(_Controller);
    Model3->SetName("name1");
    Model3->SetFilename("file_name2");
    Model3->SetGreedy(false);
    Model3->SetMix(false);
    Model3->SetNumberSimultaneousUse(9871);

    ResourceModelSelect *Model31 = new ResourceModelSelect(_Controller);
    Model31->SetName("name1");
    Model31->SetValues(QStringList()<<"value1"<<"value2"<<"value3");

    QList<IResourceModel * > ModelsDefaultDefaults = QList<IResourceModel * >()<<Model31;
    Model3->SetDefaults(ModelsDefaultDefaults);
    ModelsDefault->append(Model3);



    ModelsDefault->append(Model3);


    _Controller->SetDefaults(_ResourcesDefault);
    _Controller->SetResources(_ResourcesUser);
    _Controller->FromViewToModel(_ResourcesDeveloper);


    ModelsDeveloper = _ResourcesDeveloper->GetModelList();
    QCOMPARE(ModelsDeveloper->length(),1);
    IResourceModel * ModelResultInterface = ModelsDeveloper->at(0);
    QCOMPARE(ModelResultInterface->GetTypeId(),QString("LinesFromFile"));
    ResourceModelFile * ModelResult = qobject_cast<ResourceModelFile *>(ModelResultInterface);
    if(ModelResult == 0)
        QFAIL("Object is 0 after cast");


    QCOMPARE(ModelResult->GetDefaults().length(),1);
    IResourceModel * ModelResultDefaultInterface = ModelResult->GetDefaults().at(0);
    QCOMPARE(ModelResultDefaultInterface->GetTypeId(),QString("LinesFromUrl"));
    ResourceModelUrl * ModelResultDefault = qobject_cast<ResourceModelUrl *>(ModelResultDefaultInterface);
    if(ModelResultDefault == 0)
        QFAIL("Object is 0 after cast");

    QCOMPARE(ModelResult->GetFilename(),QString("file_name1"));
    QCOMPARE(ModelResult->GetGreedy(),true);
    QCOMPARE(ModelResult->GetNumberSimultaneousUse(),987);
    QCOMPARE(ModelResultDefault->GetUrl(),QString("tes1_url1"));

}

void CopyResourcesTests::CheckIfTypeIsChangedWhenNeededRandomInteger()
{
    CopyResourceController * _Controller = new CopyResourceController(this);
    _Controller->deleteLater();


    Resources *_ResourcesDeveloper = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDeveloper = _ResourcesDeveloper->GetModelList();

    ResourceModelUrl *Model1 = new ResourceModelUrl(_Controller);
    Model1->SetName("name1");
    Model1->SetUrl("tes1_url1");

    ResourceModelRandomInteger *Model12 = new ResourceModelRandomInteger(_Controller);
    Model12->SetName("name1");
    Model12->SetMaxUserValue(199);
    Model12->SetMinUserValue(159);

    QList<IResourceModel * > ModelsDeveloperDefaults = QList<IResourceModel * >()<<Model12;
    Model1->SetDefaults(ModelsDeveloperDefaults);
    ModelsDeveloper->append(Model1);


    Resources *_ResourcesUser = new Resources(_Controller);
    QList<IResourceModel * >* ModelsUser = _ResourcesUser->GetModelList();

    ResourceModelRandomInteger *Model2 = new ResourceModelRandomInteger(_Controller);
    Model2->SetName("name1");
    Model2->SetMaxUserValue(99);
    Model2->SetMinUserValue(49);

    ModelsUser->append(Model2);


    Resources *_ResourcesDefault = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDefault = _ResourcesDefault->GetModelList();

    ResourceModelRandomInteger *Model3 = new ResourceModelRandomInteger(_Controller);
    Model3->SetName("name1");
    Model3->SetMaxUserValue(99);
    Model3->SetMinUserValue(59);

    ResourceModelSelect *Model31 = new ResourceModelSelect(_Controller);
    Model31->SetName("name1");
    Model31->SetValues(QStringList()<<"value1"<<"value2"<<"value3");

    QList<IResourceModel * > ModelsDefaultDefaults = QList<IResourceModel * >()<<Model31;
    Model3->SetDefaults(ModelsDefaultDefaults);
    ModelsDefault->append(Model3);



    ModelsDefault->append(Model3);


    _Controller->SetDefaults(_ResourcesDefault);
    _Controller->SetResources(_ResourcesUser);
    _Controller->FromViewToModel(_ResourcesDeveloper);


    ModelsDeveloper = _ResourcesDeveloper->GetModelList();
    QCOMPARE(ModelsDeveloper->length(),1);
    IResourceModel * ModelResultInterface = ModelsDeveloper->at(0);
    QCOMPARE(ModelResultInterface->GetTypeId(),QString("RandomInteger"));
    ResourceModelRandomInteger * ModelResult = qobject_cast<ResourceModelRandomInteger *>(ModelResultInterface);
    if(ModelResult == 0)
        QFAIL("Object is 0 after cast");


    QCOMPARE(ModelResult->GetDefaults().length(),1);
    IResourceModel * ModelResultDefaultInterface = ModelResult->GetDefaults().at(0);
    QCOMPARE(ModelResultDefaultInterface->GetTypeId(),QString("LinesFromUrl"));
    ResourceModelUrl * ModelResultDefault = qobject_cast<ResourceModelUrl *>(ModelResultDefaultInterface);
    if(ModelResultDefault == 0)
        QFAIL("Object is 0 after cast");

    QCOMPARE(ModelResult->GetMaxUserValue(),199);
    QCOMPARE(ModelResult->GetMinUserValue(),49);
    QCOMPARE(ModelResultDefault->GetUrl(),QString("tes1_url1"));

}

void CopyResourcesTests::CheckIfTypeIsChangedWhenNeededFixedString()
{
    CopyResourceController * _Controller = new CopyResourceController(this);
    _Controller->deleteLater();


    Resources *_ResourcesDeveloper = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDeveloper = _ResourcesDeveloper->GetModelList();

    ResourceModelUrl *Model1 = new ResourceModelUrl(_Controller);
    Model1->SetName("name1");
    Model1->SetUrl("tes1_url1");

    ResourceModelFixedString *Model12 = new ResourceModelFixedString(_Controller);
    Model12->SetName("name1");
    Model12->SetValue("test_value_2");

    QList<IResourceModel * > ModelsDeveloperDefaults = QList<IResourceModel * >()<<Model12;
    Model1->SetDefaults(ModelsDeveloperDefaults);
    ModelsDeveloper->append(Model1);


    Resources *_ResourcesUser = new Resources(_Controller);
    QList<IResourceModel * >* ModelsUser = _ResourcesUser->GetModelList();

    ResourceModelFixedString *Model2 = new ResourceModelFixedString(_Controller);
    Model2->SetName("name1");
    Model2->SetValue("test_value_3");

    ModelsUser->append(Model2);


    Resources *_ResourcesDefault = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDefault = _ResourcesDefault->GetModelList();

    ResourceModelFixedString *Model3 = new ResourceModelFixedString(_Controller);
    Model3->SetName("name1");
    Model3->SetValue("test_value_1");

    ResourceModelSelect *Model31 = new ResourceModelSelect(_Controller);
    Model31->SetName("name1");
    Model31->SetValues(QStringList()<<"value1"<<"value2"<<"value3");

    QList<IResourceModel * > ModelsDefaultDefaults = QList<IResourceModel * >()<<Model31;
    Model3->SetDefaults(ModelsDefaultDefaults);
    ModelsDefault->append(Model3);



    ModelsDefault->append(Model3);


    _Controller->SetDefaults(_ResourcesDefault);
    _Controller->SetResources(_ResourcesUser);
    _Controller->FromViewToModel(_ResourcesDeveloper);


    ModelsDeveloper = _ResourcesDeveloper->GetModelList();
    QCOMPARE(ModelsDeveloper->length(),1);
    IResourceModel * ModelResultInterface = ModelsDeveloper->at(0);
    QCOMPARE(ModelResultInterface->GetTypeId(),QString("FixedString"));
    ResourceModelFixedString * ModelResult = qobject_cast<ResourceModelFixedString *>(ModelResultInterface);
    if(ModelResult == 0)
        QFAIL("Object is 0 after cast");


    QCOMPARE(ModelResult->GetDefaults().length(),1);
    IResourceModel * ModelResultDefaultInterface = ModelResult->GetDefaults().at(0);
    QCOMPARE(ModelResultDefaultInterface->GetTypeId(),QString("LinesFromUrl"));
    ResourceModelUrl * ModelResultDefault = qobject_cast<ResourceModelUrl *>(ModelResultDefaultInterface);
    if(ModelResultDefault == 0)
        QFAIL("Object is 0 after cast");

    QCOMPARE(ModelResult->GetValue(),QString("test_value_3"));
    QCOMPARE(ModelResultDefault->GetUrl(),QString("tes1_url1"));

}


void CopyResourcesTests::CheckIfTypeIsChangedWhenNeededFixedInteger()
{
    CopyResourceController * _Controller = new CopyResourceController(this);
    _Controller->deleteLater();


    Resources *_ResourcesDeveloper = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDeveloper = _ResourcesDeveloper->GetModelList();

    ResourceModelUrl *Model1 = new ResourceModelUrl(_Controller);
    Model1->SetName("name1");
    Model1->SetUrl("tes1_url1");

    ResourceModelFixedInteger *Model12 = new ResourceModelFixedInteger(_Controller);
    Model12->SetName("name1");
    Model12->SetValue(999);

    QList<IResourceModel * > ModelsDeveloperDefaults = QList<IResourceModel * >()<<Model12;
    Model1->SetDefaults(ModelsDeveloperDefaults);
    ModelsDeveloper->append(Model1);


    Resources *_ResourcesUser = new Resources(_Controller);
    QList<IResourceModel * >* ModelsUser = _ResourcesUser->GetModelList();

    ResourceModelFixedInteger *Model2 = new ResourceModelFixedInteger(_Controller);
    Model2->SetName("name1");
    Model2->SetValue(9999);

    ModelsUser->append(Model2);


    Resources *_ResourcesDefault = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDefault = _ResourcesDefault->GetModelList();

    ResourceModelFixedInteger *Model3 = new ResourceModelFixedInteger(_Controller);
    Model3->SetName("name1");
    Model3->SetValue(99);

    ResourceModelSelect *Model31 = new ResourceModelSelect(_Controller);
    Model31->SetName("name1");
    Model31->SetValues(QStringList()<<"value1"<<"value2"<<"value3");

    QList<IResourceModel * > ModelsDefaultDefaults = QList<IResourceModel * >()<<Model31;
    Model3->SetDefaults(ModelsDefaultDefaults);
    ModelsDefault->append(Model3);



    ModelsDefault->append(Model3);


    _Controller->SetDefaults(_ResourcesDefault);
    _Controller->SetResources(_ResourcesUser);
    _Controller->FromViewToModel(_ResourcesDeveloper);


    ModelsDeveloper = _ResourcesDeveloper->GetModelList();
    QCOMPARE(ModelsDeveloper->length(),1);
    IResourceModel * ModelResultInterface = ModelsDeveloper->at(0);
    QCOMPARE(ModelResultInterface->GetTypeId(),QString("FixedInteger"));
    ResourceModelFixedInteger * ModelResult = qobject_cast<ResourceModelFixedInteger *>(ModelResultInterface);
    if(ModelResult == 0)
        QFAIL("Object is 0 after cast");


    QCOMPARE(ModelResult->GetDefaults().length(),1);
    IResourceModel * ModelResultDefaultInterface = ModelResult->GetDefaults().at(0);
    QCOMPARE(ModelResultDefaultInterface->GetTypeId(),QString("LinesFromUrl"));
    ResourceModelUrl * ModelResultDefault = qobject_cast<ResourceModelUrl *>(ModelResultDefaultInterface);
    if(ModelResultDefault == 0)
        QFAIL("Object is 0 after cast");

    QCOMPARE(ModelResult->GetValue(),9999);
    QCOMPARE(ModelResultDefault->GetUrl(),QString("tes1_url1"));

}


void CopyResourcesTests::CheckIfTypeIsChangedWhenNeededRandomString()
{
    CopyResourceController * _Controller = new CopyResourceController(this);
    _Controller->deleteLater();


    Resources *_ResourcesDeveloper = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDeveloper = _ResourcesDeveloper->GetModelList();

    ResourceModelUrl *Model1 = new ResourceModelUrl(_Controller);
    Model1->SetName("name1");
    Model1->SetUrl("tes1_url1");

    ResourceModelRandomString *Model12 = new ResourceModelRandomString(_Controller);
    Model12->SetName("name1");
    Model12->SetValue("test2");

    QList<IResourceModel * > ModelsDeveloperDefaults = QList<IResourceModel * >()<<Model12;
    Model1->SetDefaults(ModelsDeveloperDefaults);
    ModelsDeveloper->append(Model1);


    Resources *_ResourcesUser = new Resources(_Controller);
    QList<IResourceModel * >* ModelsUser = _ResourcesUser->GetModelList();

    ResourceModelRandomString *Model2 = new ResourceModelRandomString(_Controller);
    Model2->SetName("name1");
    Model2->SetValue("test3");

    ModelsUser->append(Model2);


    Resources *_ResourcesDefault = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDefault = _ResourcesDefault->GetModelList();

    ResourceModelRandomString *Model3 = new ResourceModelRandomString(_Controller);
    Model3->SetName("name1");
    Model3->SetValue("test1");

    ResourceModelSelect *Model31 = new ResourceModelSelect(_Controller);
    Model31->SetName("name1");
    Model31->SetValues(QStringList()<<"value1"<<"value2"<<"value3");

    QList<IResourceModel * > ModelsDefaultDefaults = QList<IResourceModel * >()<<Model31;
    Model3->SetDefaults(ModelsDefaultDefaults);
    ModelsDefault->append(Model3);



    ModelsDefault->append(Model3);


    _Controller->SetDefaults(_ResourcesDefault);
    _Controller->SetResources(_ResourcesUser);
    _Controller->FromViewToModel(_ResourcesDeveloper);


    ModelsDeveloper = _ResourcesDeveloper->GetModelList();
    QCOMPARE(ModelsDeveloper->length(),1);
    IResourceModel * ModelResultInterface = ModelsDeveloper->at(0);
    QCOMPARE(ModelResultInterface->GetTypeId(),QString("RandomString"));
    ResourceModelRandomString * ModelResult = qobject_cast<ResourceModelRandomString *>(ModelResultInterface);
    if(ModelResult == 0)
        QFAIL("Object is 0 after cast");


    QCOMPARE(ModelResult->GetDefaults().length(),1);
    IResourceModel * ModelResultDefaultInterface = ModelResult->GetDefaults().at(0);
    QCOMPARE(ModelResultDefaultInterface->GetTypeId(),QString("LinesFromUrl"));
    ResourceModelUrl * ModelResultDefault = qobject_cast<ResourceModelUrl *>(ModelResultDefaultInterface);
    if(ModelResultDefault == 0)
        QFAIL("Object is 0 after cast");

    QCOMPARE(ModelResult->GetValue(),QString("test3"));
    QCOMPARE(ModelResultDefault->GetUrl(),QString("tes1_url1"));

}


void CopyResourcesTests::CheckIfTypeIsNotChangedWhenNoNeededSelect()
{
    CopyResourceController * _Controller = new CopyResourceController(this);
    _Controller->deleteLater();


    Resources *_ResourcesDeveloper = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDeveloper = _ResourcesDeveloper->GetModelList();

    ResourceModelUrl *Model1 = new ResourceModelUrl(_Controller);
    Model1->SetName("name1");
    Model1->SetUrl("tes1_url1");

    ResourceModelSelect *Model12 = new ResourceModelSelect(_Controller);
    Model12->SetName("name1");
    Model12->SetValues(QStringList()<<"vall1"<<"vall2"<<"vall3");
    Model12->SetSelected(QList<int>()<<0<<1);


    QList<IResourceModel * > ModelsDeveloperDefaults = QList<IResourceModel * >()<<Model12;
    Model1->SetDefaults(ModelsDeveloperDefaults);
    ModelsDeveloper->append(Model1);


    Resources *_ResourcesUser = new Resources(_Controller);
    QList<IResourceModel * >* ModelsUser = _ResourcesUser->GetModelList();

    ResourceModelSelect *Model2 = new ResourceModelSelect(_Controller);
    Model2->SetName("name1");
    Model2->SetValues(QStringList()<<"val1"<<"val2"<<"val3");
    Model2->SetSelected(QList<int>()<<0<<2);

    ModelsUser->append(Model2);


    Resources *_ResourcesDefault = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDefault = _ResourcesDefault->GetModelList();

    ResourceModelSelect *Model3 = new ResourceModelSelect(_Controller);
    Model3->SetName("name1");
    Model3->SetValues(QStringList()<<"val3"<<"val1"<<"val2");
    Model3->SetSelected(QList<int>()<<1<<0);

    ResourceModelFixedString *Model31 = new ResourceModelFixedString(_Controller);
    Model31->SetName("name1");
    Model31->SetValue("123");

    QList<IResourceModel * > ModelsDefaultDefaults = QList<IResourceModel * >()<<Model31;
    Model3->SetDefaults(ModelsDefaultDefaults);
    ModelsDefault->append(Model3);



    ModelsDefault->append(Model3);


    _Controller->SetDefaults(_ResourcesDefault);
    _Controller->SetResources(_ResourcesUser);
    _Controller->FromViewToModel(_ResourcesDeveloper);


    ModelsDeveloper = _ResourcesDeveloper->GetModelList();
    QCOMPARE(ModelsDeveloper->length(),1);
    IResourceModel * ModelResultInterface = ModelsDeveloper->at(0);
    QCOMPARE(ModelResultInterface->GetTypeId(),QString("LinesFromUrl"));
    ResourceModelUrl * ModelResult = qobject_cast<ResourceModelUrl *>(ModelResultInterface);
    if(ModelResult == 0)
        QFAIL("Object is 0 after cast");


    QCOMPARE(ModelResult->GetDefaults().length(),1);
    IResourceModel * ModelResultDefaultInterface = ModelResult->GetDefaults().at(0);
    QCOMPARE(ModelResultDefaultInterface->GetTypeId(),QString("Select"));
    ResourceModelSelect * ModelResultDefault = qobject_cast<ResourceModelSelect *>(ModelResultDefaultInterface);
    if(ModelResultDefault == 0)
        QFAIL("Object is 0 after cast");

    QStringList l1 = ModelResultDefault->GetValues();
    l1.sort();
    QStringList l2;
    foreach(int i, ModelResultDefault->GetSelected())
    {
        l2.append(QString::number(i));
    }
    l2.sort();

    QCOMPARE(l1.join(","),QString("vall1,vall2,vall3"));
    QCOMPARE(l2.join(","),QString("0,1"));
    QCOMPARE(ModelResult->GetUrl(),QString("tes1_url1"));

}


void CopyResourcesTests::CheckIfTypeIsNotChangedWhenNoNeededDirectory()
{
    CopyResourceController * _Controller = new CopyResourceController(this);
    _Controller->deleteLater();


    Resources *_ResourcesDeveloper = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDeveloper = _ResourcesDeveloper->GetModelList();

    ResourceModelUrl *Model1 = new ResourceModelUrl(_Controller);
    Model1->SetName("name1");
    Model1->SetUrl("tes1_url1");

    ResourceModelDirectory *Model12 = new ResourceModelDirectory(_Controller);
    Model12->SetName("name1");
    Model12->SetDirectory("file_name1");
    Model12->SetGreedy(false);
    Model12->SetMix(true);
    Model12->SetNumberSimultaneousUse(987);


    QList<IResourceModel * > ModelsDeveloperDefaults = QList<IResourceModel * >()<<Model12;
    Model1->SetDefaults(ModelsDeveloperDefaults);
    ModelsDeveloper->append(Model1);


    Resources *_ResourcesUser = new Resources(_Controller);
    QList<IResourceModel * >* ModelsUser = _ResourcesUser->GetModelList();

    ResourceModelDirectory *Model2 = new ResourceModelDirectory(_Controller);
    Model2->SetName("name1");
    Model2->SetDirectory("file_name2");
    Model2->SetGreedy(true);
    Model2->SetMix(false);
    Model2->SetNumberSimultaneousUse(9871);

    ModelsUser->append(Model2);


    Resources *_ResourcesDefault = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDefault = _ResourcesDefault->GetModelList();

    ResourceModelDirectory *Model3 = new ResourceModelDirectory(_Controller);
    Model3->SetName("name1");
    Model3->SetDirectory("file_name2");
    Model3->SetGreedy(true);
    Model3->SetMix(false);
    Model3->SetNumberSimultaneousUse(9871);

    ResourceModelSelect *Model31 = new ResourceModelSelect(_Controller);
    Model31->SetName("name1");
    Model31->SetValues(QStringList()<<"value1"<<"value2"<<"value3");

    QList<IResourceModel * > ModelsDefaultDefaults = QList<IResourceModel * >()<<Model31;
    Model3->SetDefaults(ModelsDefaultDefaults);
    ModelsDefault->append(Model3);



    ModelsDefault->append(Model3);


    _Controller->SetDefaults(_ResourcesDefault);
    _Controller->SetResources(_ResourcesUser);
    _Controller->FromViewToModel(_ResourcesDeveloper);


    ModelsDeveloper = _ResourcesDeveloper->GetModelList();
    QCOMPARE(ModelsDeveloper->length(),1);
    IResourceModel * ModelResultInterface = ModelsDeveloper->at(0);
    QCOMPARE(ModelResultInterface->GetTypeId(),QString("LinesFromUrl"));
    ResourceModelUrl * ModelResult = qobject_cast<ResourceModelUrl *>(ModelResultInterface);
    if(ModelResult == 0)
        QFAIL("Object is 0 after cast");


    QCOMPARE(ModelResult->GetDefaults().length(),1);
    IResourceModel * ModelResultDefaultInterface = ModelResult->GetDefaults().at(0);
    QCOMPARE(ModelResultDefaultInterface->GetTypeId(),QString("FilesFromDirectory"));
    ResourceModelDirectory * ModelResultDefault = qobject_cast<ResourceModelDirectory *>(ModelResultDefaultInterface);
    if(ModelResultDefault == 0)
        QFAIL("Object is 0 after cast");

    QCOMPARE(ModelResultDefault->GetDirectory(),QString("file_name1"));
    QCOMPARE(ModelResult->GetUrl(),QString("tes1_url1"));

}

void CopyResourcesTests::CheckIfTypeIsNotChangedWhenNoNeededUrl()
{
    CopyResourceController * _Controller = new CopyResourceController(this);
    _Controller->deleteLater();


    Resources *_ResourcesDeveloper = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDeveloper = _ResourcesDeveloper->GetModelList();

    ResourceModelFile *Model1 = new ResourceModelFile(_Controller);
    Model1->SetName("name1");
    Model1->SetFilename("tes1_filennn1");

    ResourceModelUrl *Model12 = new ResourceModelUrl(_Controller);
    Model12->SetName("name1");
    Model12->SetUrl("url1");
    Model12->SetGreedy(false);
    Model12->SetMix(true);
    Model12->SetNumberSimultaneousUse(987);


    QList<IResourceModel * > ModelsDeveloperDefaults = QList<IResourceModel * >()<<Model12;
    Model1->SetDefaults(ModelsDeveloperDefaults);
    ModelsDeveloper->append(Model1);


    Resources *_ResourcesUser = new Resources(_Controller);
    QList<IResourceModel * >* ModelsUser = _ResourcesUser->GetModelList();

    ResourceModelUrl *Model2 = new ResourceModelUrl(_Controller);
    Model2->SetName("name1");
    Model2->SetUrl("url2");
    Model2->SetGreedy(true);
    Model2->SetMix(false);
    Model2->SetNumberSimultaneousUse(9871);

    ModelsUser->append(Model2);


    Resources *_ResourcesDefault = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDefault = _ResourcesDefault->GetModelList();

    ResourceModelUrl *Model3 = new ResourceModelUrl(_Controller);
    Model3->SetName("name1");
    Model3->SetUrl("url2");
    Model3->SetGreedy(true);
    Model3->SetMix(false);
    Model3->SetNumberSimultaneousUse(9871);

    ResourceModelSelect *Model31 = new ResourceModelSelect(_Controller);
    Model31->SetName("name1");
    Model31->SetValues(QStringList()<<"value1"<<"value2"<<"value3");

    QList<IResourceModel * > ModelsDefaultDefaults = QList<IResourceModel * >()<<Model31;
    Model3->SetDefaults(ModelsDefaultDefaults);
    ModelsDefault->append(Model3);



    ModelsDefault->append(Model3);


    _Controller->SetDefaults(_ResourcesDefault);
    _Controller->SetResources(_ResourcesUser);
    _Controller->FromViewToModel(_ResourcesDeveloper);


    ModelsDeveloper = _ResourcesDeveloper->GetModelList();
    QCOMPARE(ModelsDeveloper->length(),1);
    IResourceModel * ModelResultInterface = ModelsDeveloper->at(0);
    QCOMPARE(ModelResultInterface->GetTypeId(),QString("LinesFromFile"));
    ResourceModelFile * ModelResult = qobject_cast<ResourceModelFile *>(ModelResultInterface);
    if(ModelResult == 0)
        QFAIL("Object is 0 after cast");


    QCOMPARE(ModelResult->GetDefaults().length(),1);
    IResourceModel * ModelResultDefaultInterface = ModelResult->GetDefaults().at(0);
    QCOMPARE(ModelResultDefaultInterface->GetTypeId(),QString("LinesFromUrl"));
    ResourceModelUrl * ModelResultDefault = qobject_cast<ResourceModelUrl *>(ModelResultDefaultInterface);
    if(ModelResultDefault == 0)
        QFAIL("Object is 0 after cast");

    QCOMPARE(ModelResultDefault->GetUrl(),QString("url1"));
    QCOMPARE(ModelResult->GetFilename(),QString("tes1_filennn1"));

}


void CopyResourcesTests::CheckIfTypeIsNotChangedWhenNoNeededFile()
{
    CopyResourceController * _Controller = new CopyResourceController(this);
    _Controller->deleteLater();


    Resources *_ResourcesDeveloper = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDeveloper = _ResourcesDeveloper->GetModelList();

    ResourceModelUrl *Model1 = new ResourceModelUrl(_Controller);
    Model1->SetName("name1");
    Model1->SetUrl("tes1_url1");

    ResourceModelFile *Model12 = new ResourceModelFile(_Controller);
    Model12->SetName("name1");
    Model12->SetFilename("file_name1");
    Model12->SetGreedy(false);
    Model12->SetMix(true);
    Model12->SetNumberSimultaneousUse(987);


    QList<IResourceModel * > ModelsDeveloperDefaults = QList<IResourceModel * >()<<Model12;
    Model1->SetDefaults(ModelsDeveloperDefaults);
    ModelsDeveloper->append(Model1);


    Resources *_ResourcesUser = new Resources(_Controller);
    QList<IResourceModel * >* ModelsUser = _ResourcesUser->GetModelList();

    ResourceModelFile *Model2 = new ResourceModelFile(_Controller);
    Model2->SetName("name1");
    Model2->SetFilename("file_name2");
    Model2->SetGreedy(true);
    Model2->SetMix(false);
    Model2->SetNumberSimultaneousUse(9871);

    ModelsUser->append(Model2);


    Resources *_ResourcesDefault = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDefault = _ResourcesDefault->GetModelList();

    ResourceModelFile *Model3 = new ResourceModelFile(_Controller);
    Model3->SetName("name1");
    Model3->SetFilename("file_name2");
    Model3->SetGreedy(true);
    Model3->SetMix(false);
    Model3->SetNumberSimultaneousUse(9871);

    ResourceModelSelect *Model31 = new ResourceModelSelect(_Controller);
    Model31->SetName("name1");
    Model31->SetValues(QStringList()<<"value1"<<"value2"<<"value3");

    QList<IResourceModel * > ModelsDefaultDefaults = QList<IResourceModel * >()<<Model31;
    Model3->SetDefaults(ModelsDefaultDefaults);
    ModelsDefault->append(Model3);



    ModelsDefault->append(Model3);


    _Controller->SetDefaults(_ResourcesDefault);
    _Controller->SetResources(_ResourcesUser);
    _Controller->FromViewToModel(_ResourcesDeveloper);


    ModelsDeveloper = _ResourcesDeveloper->GetModelList();
    QCOMPARE(ModelsDeveloper->length(),1);
    IResourceModel * ModelResultInterface = ModelsDeveloper->at(0);
    QCOMPARE(ModelResultInterface->GetTypeId(),QString("LinesFromUrl"));
    ResourceModelUrl * ModelResult = qobject_cast<ResourceModelUrl *>(ModelResultInterface);
    if(ModelResult == 0)
        QFAIL("Object is 0 after cast");


    QCOMPARE(ModelResult->GetDefaults().length(),1);
    IResourceModel * ModelResultDefaultInterface = ModelResult->GetDefaults().at(0);
    QCOMPARE(ModelResultDefaultInterface->GetTypeId(),QString("LinesFromFile"));
    ResourceModelFile * ModelResultDefault = qobject_cast<ResourceModelFile *>(ModelResultDefaultInterface);
    if(ModelResultDefault == 0)
        QFAIL("Object is 0 after cast");

    QCOMPARE(ModelResultDefault->GetFilename(),QString("file_name1"));
    QCOMPARE(ModelResult->GetUrl(),QString("tes1_url1"));

}

void CopyResourcesTests::CheckIfTypeIsNotChangedWhenNoNeededRandomInteger()
{
    CopyResourceController * _Controller = new CopyResourceController(this);
    _Controller->deleteLater();


    Resources *_ResourcesDeveloper = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDeveloper = _ResourcesDeveloper->GetModelList();

    ResourceModelUrl *Model1 = new ResourceModelUrl(_Controller);
    Model1->SetName("name1");
    Model1->SetUrl("tes1_url1");

    ResourceModelRandomInteger *Model12 = new ResourceModelRandomInteger(_Controller);
    Model12->SetName("name1");
    Model12->SetMaxUserValue(199);
    Model12->SetMinUserValue(159);

    QList<IResourceModel * > ModelsDeveloperDefaults = QList<IResourceModel * >()<<Model12;
    Model1->SetDefaults(ModelsDeveloperDefaults);
    ModelsDeveloper->append(Model1);


    Resources *_ResourcesUser = new Resources(_Controller);
    QList<IResourceModel * >* ModelsUser = _ResourcesUser->GetModelList();

    ResourceModelRandomInteger *Model2 = new ResourceModelRandomInteger(_Controller);
    Model2->SetName("name1");
    Model2->SetMaxUserValue(99);
    Model2->SetMinUserValue(59);

    ModelsUser->append(Model2);


    Resources *_ResourcesDefault = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDefault = _ResourcesDefault->GetModelList();

    ResourceModelRandomInteger *Model3 = new ResourceModelRandomInteger(_Controller);
    Model3->SetName("name1");
    Model3->SetMaxUserValue(99);
    Model3->SetMinUserValue(59);

    ResourceModelSelect *Model31 = new ResourceModelSelect(_Controller);
    Model31->SetName("name1");
    Model31->SetValues(QStringList()<<"value1"<<"value2"<<"value3");

    QList<IResourceModel * > ModelsDefaultDefaults = QList<IResourceModel * >()<<Model31;
    Model3->SetDefaults(ModelsDefaultDefaults);
    ModelsDefault->append(Model3);



    ModelsDefault->append(Model3);


    _Controller->SetDefaults(_ResourcesDefault);
    _Controller->SetResources(_ResourcesUser);
    _Controller->FromViewToModel(_ResourcesDeveloper);


    ModelsDeveloper = _ResourcesDeveloper->GetModelList();
    QCOMPARE(ModelsDeveloper->length(),1);
    IResourceModel * ModelResultInterface = ModelsDeveloper->at(0);
    QCOMPARE(ModelResultInterface->GetTypeId(),QString("LinesFromUrl"));
    ResourceModelUrl * ModelResult = qobject_cast<ResourceModelUrl *>(ModelResultInterface);
    if(ModelResult == 0)
        QFAIL("Object is 0 after cast");


    QCOMPARE(ModelResult->GetDefaults().length(),1);
    IResourceModel * ModelResultDefaultInterface = ModelResult->GetDefaults().at(0);
    QCOMPARE(ModelResultDefaultInterface->GetTypeId(),QString("RandomInteger"));
    ResourceModelRandomInteger * ModelResultDefault = qobject_cast<ResourceModelRandomInteger *>(ModelResultDefaultInterface);
    if(ModelResultDefault == 0)
        QFAIL("Object is 0 after cast");

    QCOMPARE(ModelResultDefault->GetMaxUserValue(),199);
    QCOMPARE(ModelResultDefault->GetMinUserValue(),159);
    QCOMPARE(ModelResult->GetUrl(),QString("tes1_url1"));

}

void CopyResourcesTests::CheckIfTypeIsNotChangedWhenNoNeededFixedString()
{
    CopyResourceController * _Controller = new CopyResourceController(this);
    _Controller->deleteLater();


    Resources *_ResourcesDeveloper = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDeveloper = _ResourcesDeveloper->GetModelList();

    ResourceModelUrl *Model1 = new ResourceModelUrl(_Controller);
    Model1->SetName("name1");
    Model1->SetUrl("tes1_url1");

    ResourceModelFixedString *Model12 = new ResourceModelFixedString(_Controller);
    Model12->SetName("name1");
    Model12->SetValue("test_value_2");

    QList<IResourceModel * > ModelsDeveloperDefaults = QList<IResourceModel * >()<<Model12;
    Model1->SetDefaults(ModelsDeveloperDefaults);
    ModelsDeveloper->append(Model1);


    Resources *_ResourcesUser = new Resources(_Controller);
    QList<IResourceModel * >* ModelsUser = _ResourcesUser->GetModelList();

    ResourceModelFixedString *Model2 = new ResourceModelFixedString(_Controller);
    Model2->SetName("name1");
    Model2->SetValue("test_value_1");

    ModelsUser->append(Model2);


    Resources *_ResourcesDefault = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDefault = _ResourcesDefault->GetModelList();

    ResourceModelFixedString *Model3 = new ResourceModelFixedString(_Controller);
    Model3->SetName("name1");
    Model3->SetValue("test_value_1");

    ResourceModelSelect *Model31 = new ResourceModelSelect(_Controller);
    Model31->SetName("name1");
    Model31->SetValues(QStringList()<<"value1"<<"value2"<<"value3");

    QList<IResourceModel * > ModelsDefaultDefaults = QList<IResourceModel * >()<<Model31;
    Model3->SetDefaults(ModelsDefaultDefaults);
    ModelsDefault->append(Model3);



    ModelsDefault->append(Model3);


    _Controller->SetDefaults(_ResourcesDefault);
    _Controller->SetResources(_ResourcesUser);
    _Controller->FromViewToModel(_ResourcesDeveloper);


    ModelsDeveloper = _ResourcesDeveloper->GetModelList();
    QCOMPARE(ModelsDeveloper->length(),1);
    IResourceModel * ModelResultInterface = ModelsDeveloper->at(0);
    QCOMPARE(ModelResultInterface->GetTypeId(),QString("LinesFromUrl"));
    ResourceModelUrl * ModelResult = qobject_cast<ResourceModelUrl *>(ModelResultInterface);
    if(ModelResult == 0)
        QFAIL("Object is 0 after cast");


    QCOMPARE(ModelResult->GetDefaults().length(),1);
    IResourceModel * ModelResultDefaultInterface = ModelResult->GetDefaults().at(0);
    QCOMPARE(ModelResultDefaultInterface->GetTypeId(),QString("FixedString"));
    ResourceModelFixedString * ModelResultDefault = qobject_cast<ResourceModelFixedString *>(ModelResultDefaultInterface);
    if(ModelResultDefault == 0)
        QFAIL("Object is 0 after cast");

    QCOMPARE(ModelResultDefault->GetValue(),QString("test_value_2"));
    QCOMPARE(ModelResult->GetUrl(),QString("tes1_url1"));

}


void CopyResourcesTests::CheckIfTypeIsNotChangedWhenNoNeededFixedInteger()
{
    CopyResourceController * _Controller = new CopyResourceController(this);
    _Controller->deleteLater();


    Resources *_ResourcesDeveloper = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDeveloper = _ResourcesDeveloper->GetModelList();

    ResourceModelUrl *Model1 = new ResourceModelUrl(_Controller);
    Model1->SetName("name1");
    Model1->SetUrl("tes1_url1");

    ResourceModelFixedInteger *Model12 = new ResourceModelFixedInteger(_Controller);
    Model12->SetName("name1");
    Model12->SetValue(999);

    QList<IResourceModel * > ModelsDeveloperDefaults = QList<IResourceModel * >()<<Model12;
    Model1->SetDefaults(ModelsDeveloperDefaults);
    ModelsDeveloper->append(Model1);


    Resources *_ResourcesUser = new Resources(_Controller);
    QList<IResourceModel * >* ModelsUser = _ResourcesUser->GetModelList();

    ResourceModelFixedInteger *Model2 = new ResourceModelFixedInteger(_Controller);
    Model2->SetName("name1");
    Model2->SetValue(99);

    ModelsUser->append(Model2);


    Resources *_ResourcesDefault = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDefault = _ResourcesDefault->GetModelList();

    ResourceModelFixedInteger *Model3 = new ResourceModelFixedInteger(_Controller);
    Model3->SetName("name1");
    Model3->SetValue(99);

    ResourceModelSelect *Model31 = new ResourceModelSelect(_Controller);
    Model31->SetName("name1");
    Model31->SetValues(QStringList()<<"value1"<<"value2"<<"value3");

    QList<IResourceModel * > ModelsDefaultDefaults = QList<IResourceModel * >()<<Model31;
    Model3->SetDefaults(ModelsDefaultDefaults);
    ModelsDefault->append(Model3);



    ModelsDefault->append(Model3);


    _Controller->SetDefaults(_ResourcesDefault);
    _Controller->SetResources(_ResourcesUser);
    _Controller->FromViewToModel(_ResourcesDeveloper);


    ModelsDeveloper = _ResourcesDeveloper->GetModelList();
    QCOMPARE(ModelsDeveloper->length(),1);
    IResourceModel * ModelResultInterface = ModelsDeveloper->at(0);
    QCOMPARE(ModelResultInterface->GetTypeId(),QString("LinesFromUrl"));
    ResourceModelUrl * ModelResult = qobject_cast<ResourceModelUrl *>(ModelResultInterface);
    if(ModelResult == 0)
        QFAIL("Object is 0 after cast");


    QCOMPARE(ModelResult->GetDefaults().length(),1);
    IResourceModel * ModelResultDefaultInterface = ModelResult->GetDefaults().at(0);
    QCOMPARE(ModelResultDefaultInterface->GetTypeId(),QString("FixedInteger"));
    ResourceModelFixedInteger * ModelResultDefault = qobject_cast<ResourceModelFixedInteger *>(ModelResultDefaultInterface);
    if(ModelResultDefault == 0)
        QFAIL("Object is 0 after cast");

    QCOMPARE(ModelResultDefault->GetValue(),999);
    QCOMPARE(ModelResult->GetUrl(),QString("tes1_url1"));

}


void CopyResourcesTests::CheckIfTypeIsNotChangedWhenNoNeededRandomString()
{
    CopyResourceController * _Controller = new CopyResourceController(this);
    _Controller->deleteLater();


    Resources *_ResourcesDeveloper = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDeveloper = _ResourcesDeveloper->GetModelList();

    ResourceModelUrl *Model1 = new ResourceModelUrl(_Controller);
    Model1->SetName("name1");
    Model1->SetUrl("tes1_url1");

    ResourceModelRandomString *Model12 = new ResourceModelRandomString(_Controller);
    Model12->SetName("name1");
    Model12->SetValue("test2");

    QList<IResourceModel * > ModelsDeveloperDefaults = QList<IResourceModel * >()<<Model12;
    Model1->SetDefaults(ModelsDeveloperDefaults);
    ModelsDeveloper->append(Model1);


    Resources *_ResourcesUser = new Resources(_Controller);
    QList<IResourceModel * >* ModelsUser = _ResourcesUser->GetModelList();

    ResourceModelRandomString *Model2 = new ResourceModelRandomString(_Controller);
    Model2->SetName("name1");
    Model2->SetValue("test1");

    ModelsUser->append(Model2);


    Resources *_ResourcesDefault = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDefault = _ResourcesDefault->GetModelList();

    ResourceModelRandomString *Model3 = new ResourceModelRandomString(_Controller);
    Model3->SetName("name1");
    Model3->SetValue("test1");

    ResourceModelSelect *Model31 = new ResourceModelSelect(_Controller);
    Model31->SetName("name1");
    Model31->SetValues(QStringList()<<"value1"<<"value2"<<"value3");

    QList<IResourceModel * > ModelsDefaultDefaults = QList<IResourceModel * >()<<Model31;
    Model3->SetDefaults(ModelsDefaultDefaults);
    ModelsDefault->append(Model3);



    ModelsDefault->append(Model3);


    _Controller->SetDefaults(_ResourcesDefault);
    _Controller->SetResources(_ResourcesUser);
    _Controller->FromViewToModel(_ResourcesDeveloper);


    ModelsDeveloper = _ResourcesDeveloper->GetModelList();
    QCOMPARE(ModelsDeveloper->length(),1);
    IResourceModel * ModelResultInterface = ModelsDeveloper->at(0);
    QCOMPARE(ModelResultInterface->GetTypeId(),QString("LinesFromUrl"));
    ResourceModelUrl * ModelResult = qobject_cast<ResourceModelUrl *>(ModelResultInterface);
    if(ModelResult == 0)
        QFAIL("Object is 0 after cast");


    QCOMPARE(ModelResult->GetDefaults().length(),1);
    IResourceModel * ModelResultDefaultInterface = ModelResult->GetDefaults().at(0);
    QCOMPARE(ModelResultDefaultInterface->GetTypeId(),QString("RandomString"));
    ResourceModelRandomString * ModelResultDefault = qobject_cast<ResourceModelRandomString *>(ModelResultDefaultInterface);
    if(ModelResultDefault == 0)
        QFAIL("Object is 0 after cast");

    QCOMPARE(ModelResultDefault->GetValue(),QString("test2"));
    QCOMPARE(ModelResult->GetUrl(),QString("tes1_url1"));

}


void CopyResourcesTests::CheckIfNameIsRespected()
{
    CopyResourceController * _Controller = new CopyResourceController(this);
    _Controller->deleteLater();


    Resources *_ResourcesDeveloper = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDeveloper = _ResourcesDeveloper->GetModelList();

    ResourceModelUrl *Model1 = new ResourceModelUrl(_Controller);
    Model1->SetName("name1");
    Model1->SetUrl("tes1_url1");
    ModelsDeveloper->append(Model1);


    Resources *_ResourcesUser = new Resources(_Controller);
    QList<IResourceModel * >* ModelsUser = _ResourcesUser->GetModelList();

    ResourceModelFixedString *Model2 = new ResourceModelFixedString(_Controller);
    Model2->SetName("name");
    Model2->SetValue("test_value_2");
    Model2->SetNotEmpty(true);
    ModelsUser->append(Model2);

    ResourceModelUrl *Model21 = new ResourceModelUrl(_Controller);
    Model21->SetName("name1");
    Model21->SetUrl("tes1_url2");
    ModelsUser->append(Model21);


    Resources *_ResourcesDefault = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDefault = _ResourcesDefault->GetModelList();

    ResourceModelFixedString *Model3 = new ResourceModelFixedString(_Controller);
    Model3->SetName("name");
    Model3->SetValue("test_value_3");
    Model3->SetNotEmpty(true);
    ModelsDefault->append(Model3);

    _Controller->SetDefaults(_ResourcesDefault);
    _Controller->SetResources(_ResourcesUser);
    _Controller->FromViewToModel(_ResourcesDeveloper);


    ModelsDeveloper = _ResourcesDeveloper->GetModelList();
    QCOMPARE(ModelsDeveloper->length(),1);
    IResourceModel * ModelResultInterface = ModelsDeveloper->at(0);
    QCOMPARE(ModelResultInterface->GetTypeId(),QString("LinesFromUrl"));
    ResourceModelUrl * ModelResult = qobject_cast<ResourceModelUrl *>(ModelResultInterface);
    if(ModelResult == 0)
        QFAIL("Object is 0 after cast");

    QCOMPARE(ModelResult->GetUrl(),QString("tes1_url2"));

}


void CopyResourcesTests::CheckIfNameIsRespected2()
{
    CopyResourceController * _Controller = new CopyResourceController(this);
    _Controller->deleteLater();


    Resources *_ResourcesDeveloper = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDeveloper = _ResourcesDeveloper->GetModelList();

    ResourceModelUrl *Model1 = new ResourceModelUrl(_Controller);
    Model1->SetName("name11");
    Model1->SetUrl("tes1_url1");
    ModelsDeveloper->append(Model1);


    Resources *_ResourcesUser = new Resources(_Controller);
    QList<IResourceModel * >* ModelsUser = _ResourcesUser->GetModelList();

    ResourceModelFixedString *Model2 = new ResourceModelFixedString(_Controller);
    Model2->SetName("name");
    Model2->SetValue("test_value_2");
    Model2->SetNotEmpty(true);
    ModelsUser->append(Model2);

    ResourceModelUrl *Model21 = new ResourceModelUrl(_Controller);
    Model21->SetName("name1");
    Model21->SetUrl("tes1_url2");
    ModelsUser->append(Model21);


    Resources *_ResourcesDefault = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDefault = _ResourcesDefault->GetModelList();

    ResourceModelFixedString *Model3 = new ResourceModelFixedString(_Controller);
    Model3->SetName("name");
    Model3->SetValue("test_value_3");
    Model3->SetNotEmpty(true);
    ModelsDefault->append(Model3);

    _Controller->SetDefaults(_ResourcesDefault);
    _Controller->SetResources(_ResourcesUser);
    _Controller->FromViewToModel(_ResourcesDeveloper);


    ModelsDeveloper = _ResourcesDeveloper->GetModelList();
    QCOMPARE(ModelsDeveloper->length(),1);
    IResourceModel * ModelResultInterface = ModelsDeveloper->at(0);
    QCOMPARE(ModelResultInterface->GetTypeId(),QString("LinesFromUrl"));
    ResourceModelUrl * ModelResult = qobject_cast<ResourceModelUrl *>(ModelResultInterface);
    if(ModelResult == 0)
        QFAIL("Object is 0 after cast");

    QCOMPARE(ModelResult->GetUrl(),QString("tes1_url1"));

}


void CopyResourcesTests::CheckIfTypeIsChangedWhenNeeded()
{
    CopyResourceController * _Controller = new CopyResourceController(this);
    _Controller->deleteLater();


    Resources *_ResourcesDeveloper = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDeveloper = _ResourcesDeveloper->GetModelList();

    ResourceModelUrl *Model1 = new ResourceModelUrl(_Controller);
    Model1->SetName("name1");
    Model1->SetUrl("tes1_url1");

    ResourceModelFile *Model11 = new ResourceModelFile(_Controller);
    Model11->SetName("name1");
    Model11->SetFilename("tes1_file1");

    QList<IResourceModel * > ModelsDeveloperDefaults = QList<IResourceModel * >()<<Model11;
    Model1->SetDefaults(ModelsDeveloperDefaults);
    ModelsDeveloper->append(Model1);


    Resources *_ResourcesUser = new Resources(_Controller);
    QList<IResourceModel * >* ModelsUser = _ResourcesUser->GetModelList();

    ResourceModelFile *Model2 = new ResourceModelFile(_Controller);
    Model2->SetName("name1");
    Model2->SetFilename("tes1_file2");


    ResourceModelUrl *Model21 = new ResourceModelUrl(_Controller);
    Model21->SetName("name1");
    Model21->SetUrl("tes1_url2");
    QList<IResourceModel * > ModelsUserDefaults = QList<IResourceModel * >()<<Model21;
    Model2->SetDefaults(ModelsUserDefaults);
    ModelsUser->append(Model2);


    Resources *_ResourcesDefault = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDefault = _ResourcesDefault->GetModelList();

    ResourceModelFile *Model3 = new ResourceModelFile(_Controller);
    Model3->SetName("name1");
    Model3->SetFilename("tes1_file3");


    ResourceModelUrl *Model31 = new ResourceModelUrl(_Controller);
    Model31->SetName("name1");
    Model31->SetUrl("tes1_url3");
    QList<IResourceModel * > ModelsDefaultDefaults = QList<IResourceModel * >()<<Model31;
    Model3->SetDefaults(ModelsDefaultDefaults);
    ModelsDefault->append(Model3);


    _Controller->SetDefaults(_ResourcesDefault);
    _Controller->SetResources(_ResourcesUser);
    _Controller->FromViewToModel(_ResourcesDeveloper);


    ModelsDeveloper = _ResourcesDeveloper->GetModelList();
    QCOMPARE(ModelsDeveloper->length(),1);
    IResourceModel * ModelResultInterface = ModelsDeveloper->at(0);
    QCOMPARE(ModelResultInterface->GetTypeId(),QString("LinesFromFile"));
    ResourceModelFile * ModelResult = qobject_cast<ResourceModelFile *>(ModelResultInterface);
    if(ModelResult == 0)
        QFAIL("Object is 0 after cast");


    QCOMPARE(ModelResult->GetDefaults().length(),1);
    IResourceModel * ModelResultDefaultInterface = ModelResult->GetDefaults().at(0);
    QCOMPARE(ModelResultDefaultInterface->GetTypeId(),QString("LinesFromUrl"));
    ResourceModelUrl * ModelResultDefault = qobject_cast<ResourceModelUrl *>(ModelResultDefaultInterface);
    if(ModelResultDefault == 0)
        QFAIL("Object is 0 after cast");

    QCOMPARE(ModelResultDefault->GetUrl(),QString("tes1_url2"));
    QCOMPARE(ModelResult->GetFilename(),QString("tes1_file2"));

}


void CopyResourcesTests::CheckIfTypeIsNotChangedWhenNoNeeded()
{
    CopyResourceController * _Controller = new CopyResourceController(this);
    _Controller->deleteLater();


    Resources *_ResourcesDeveloper = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDeveloper = _ResourcesDeveloper->GetModelList();

    ResourceModelUrl *Model1 = new ResourceModelUrl(_Controller);
    Model1->SetName("name1");
    Model1->SetUrl("tes1_url1");

    ResourceModelFile *Model11 = new ResourceModelFile(_Controller);
    Model11->SetName("name1");
    Model11->SetFilename("tes1_file1");

    QList<IResourceModel * > ModelsDeveloperDefaults = QList<IResourceModel * >()<<Model11;
    Model1->SetDefaults(ModelsDeveloperDefaults);
    ModelsDeveloper->append(Model1);


    Resources *_ResourcesUser = new Resources(_Controller);
    QList<IResourceModel * >* ModelsUser = _ResourcesUser->GetModelList();

    ResourceModelFile *Model2 = new ResourceModelFile(_Controller);
    Model2->SetName("name1");
    Model2->SetFilename("tes1_file3");


    ResourceModelUrl *Model21 = new ResourceModelUrl(_Controller);
    Model21->SetName("name1");
    Model21->SetUrl("tes1_url3");
    QList<IResourceModel * > ModelsUserDefaults = QList<IResourceModel * >()<<Model21;
    Model2->SetDefaults(ModelsUserDefaults);
    ModelsUser->append(Model2);


    Resources *_ResourcesDefault = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDefault = _ResourcesDefault->GetModelList();

    ResourceModelFile *Model3 = new ResourceModelFile(_Controller);
    Model3->SetName("name1");
    Model3->SetFilename("tes1_file3");


    ResourceModelUrl *Model31 = new ResourceModelUrl(_Controller);
    Model31->SetName("name1");
    Model31->SetUrl("tes1_url3");
    QList<IResourceModel * > ModelsDefaultDefaults = QList<IResourceModel * >()<<Model31;
    Model3->SetDefaults(ModelsDefaultDefaults);
    ModelsDefault->append(Model3);


    _Controller->SetDefaults(_ResourcesDefault);
    _Controller->SetResources(_ResourcesUser);
    _Controller->FromViewToModel(_ResourcesDeveloper);


    ModelsDeveloper = _ResourcesDeveloper->GetModelList();
    QCOMPARE(ModelsDeveloper->length(),1);
    IResourceModel * ModelResultInterface = ModelsDeveloper->at(0);
    QCOMPARE(ModelResultInterface->GetTypeId(),QString("LinesFromUrl"));
    ResourceModelUrl * ModelResult = qobject_cast<ResourceModelUrl *>(ModelResultInterface);
    if(ModelResult == 0)
        QFAIL("Object is 0 after cast");


    QCOMPARE(ModelResult->GetDefaults().length(),1);
    IResourceModel * ModelResultDefaultInterface = ModelResult->GetDefaults().at(0);
    QCOMPARE(ModelResultDefaultInterface->GetTypeId(),QString("LinesFromFile"));
    ResourceModelFile * ModelResultDefault = qobject_cast<ResourceModelFile *>(ModelResultDefaultInterface);
    if(ModelResultDefault == 0)
        QFAIL("Object is 0 after cast");

    QCOMPARE(ModelResult->GetUrl(),QString("tes1_url1"));
    QCOMPARE(ModelResultDefault->GetFilename(),QString("tes1_file1"));

}


void CopyResourcesTests::CheckIfRunsOkIfDefaultTypesAreDifferent()
{
    CopyResourceController * _Controller = new CopyResourceController(this);
    _Controller->deleteLater();


    Resources *_ResourcesDeveloper = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDeveloper = _ResourcesDeveloper->GetModelList();

    ResourceModelUrl *Model1 = new ResourceModelUrl(_Controller);
    Model1->SetName("name1");
    Model1->SetUrl("tes1_url1");

    ResourceModelFile *Model11 = new ResourceModelFile(_Controller);
    Model11->SetName("name1");
    Model11->SetFilename("tes1_file1");

    QList<IResourceModel * > ModelsDeveloperDefaults = QList<IResourceModel * >()<<Model11;
    Model1->SetDefaults(ModelsDeveloperDefaults);
    ModelsDeveloper->append(Model1);


    Resources *_ResourcesUser = new Resources(_Controller);
    QList<IResourceModel * >* ModelsUser = _ResourcesUser->GetModelList();

    ResourceModelSelect *Model2 = new ResourceModelSelect(_Controller);
    Model2->SetName("name1");
    Model2->SetValues(QStringList()<<"value1"<<"value2"<<"value3");


    ResourceModelDirectory *Model21 = new ResourceModelDirectory(_Controller);
    Model21->SetName("name1");
    Model21->SetDirectory("tes1_dir3");
    QList<IResourceModel * > ModelsUserDefaults = QList<IResourceModel * >()<<Model21;
    Model2->SetDefaults(ModelsUserDefaults);
    ModelsUser->append(Model2);


    Resources *_ResourcesDefault = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDefault = _ResourcesDefault->GetModelList();

    ResourceModelFixedInteger *Model3 = new ResourceModelFixedInteger(_Controller);
    Model3->SetName("name1");
    Model3->SetValue(10);


    ResourceModelFixedString *Model31 = new ResourceModelFixedString(_Controller);
    Model31->SetName("name1");
    Model31->SetValue("tes1_str3");
    QList<IResourceModel * > ModelsDefaultDefaults = QList<IResourceModel * >()<<Model31;
    Model3->SetDefaults(ModelsDefaultDefaults);
    ModelsDefault->append(Model3);


    _Controller->SetDefaults(_ResourcesDefault);
    _Controller->SetResources(_ResourcesUser);
    _Controller->FromViewToModel(_ResourcesDeveloper);


    ModelsDeveloper = _ResourcesDeveloper->GetModelList();
    QCOMPARE(ModelsDeveloper->length(),1);
    IResourceModel * ModelResultInterface = ModelsDeveloper->at(0);
    QCOMPARE(ModelResultInterface->GetTypeId(),QString("LinesFromUrl"));
    ResourceModelUrl * ModelResult = qobject_cast<ResourceModelUrl *>(ModelResultInterface);
    if(ModelResult == 0)
        QFAIL("Object is 0 after cast");


    QCOMPARE(ModelResult->GetDefaults().length(),1);
    IResourceModel * ModelResultDefaultInterface = ModelResult->GetDefaults().at(0);
    QCOMPARE(ModelResultDefaultInterface->GetTypeId(),QString("LinesFromFile"));
    ResourceModelFile * ModelResultDefault = qobject_cast<ResourceModelFile *>(ModelResultDefaultInterface);
    if(ModelResultDefault == 0)
        QFAIL("Object is 0 after cast");

    QCOMPARE(ModelResult->GetUrl(),QString("tes1_url1"));
    QCOMPARE(ModelResultDefault->GetFilename(),QString("tes1_file1"));

}



void CopyResourcesTests::CheckIfValuesAreFromUsersEvenIfDefaultsAreNotSameType()
{
    CopyResourceController * _Controller = new CopyResourceController(this);
    _Controller->deleteLater();


    Resources *_ResourcesDeveloper = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDeveloper = _ResourcesDeveloper->GetModelList();

    ResourceModelUrl *Model1 = new ResourceModelUrl(_Controller);
    Model1->SetName("name1");
    Model1->SetUrl("tes1_url1");

    ResourceModelFile *Model11 = new ResourceModelFile(_Controller);
    Model11->SetName("name1");
    Model11->SetFilename("tes1_file1");

    QList<IResourceModel * > ModelsDeveloperDefaults = QList<IResourceModel * >()<<Model11;
    Model1->SetDefaults(ModelsDeveloperDefaults);
    ModelsDeveloper->append(Model1);


    Resources *_ResourcesUser = new Resources(_Controller);
    QList<IResourceModel * >* ModelsUser = _ResourcesUser->GetModelList();

    ResourceModelFile *Model2 = new ResourceModelFile(_Controller);
    Model2->SetName("name1");
    Model2->SetFilename("tes1_file2");


    ResourceModelUrl *Model21 = new ResourceModelUrl(_Controller);
    Model21->SetName("name1");
    Model21->SetUrl("tes1_url2");
    QList<IResourceModel * > ModelsUserDefaults = QList<IResourceModel * >()<<Model21;
    Model2->SetDefaults(ModelsUserDefaults);
    ModelsUser->append(Model2);


    Resources *_ResourcesDefault = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDefault = _ResourcesDefault->GetModelList();

    ResourceModelFixedInteger *Model3 = new ResourceModelFixedInteger(_Controller);
    Model3->SetName("name1");
    Model3->SetValue(10);


    ResourceModelFixedString *Model31 = new ResourceModelFixedString(_Controller);
    Model31->SetName("name1");
    Model31->SetValue("tes1_str3");
    QList<IResourceModel * > ModelsDefaultDefaults = QList<IResourceModel * >()<<Model31;
    Model3->SetDefaults(ModelsDefaultDefaults);
    ModelsDefault->append(Model3);


    _Controller->SetDefaults(_ResourcesDefault);
    _Controller->SetResources(_ResourcesUser);
    _Controller->FromViewToModel(_ResourcesDeveloper);


    ModelsDeveloper = _ResourcesDeveloper->GetModelList();
    QCOMPARE(ModelsDeveloper->length(),1);
    IResourceModel * ModelResultInterface = ModelsDeveloper->at(0);
    QCOMPARE(ModelResultInterface->GetTypeId(),QString("LinesFromFile"));
    ResourceModelFile * ModelResult = qobject_cast<ResourceModelFile *>(ModelResultInterface);
    if(ModelResult == 0)
        QFAIL("Object is 0 after cast");


    QCOMPARE(ModelResult->GetDefaults().length(),1);
    IResourceModel * ModelResultDefaultInterface = ModelResult->GetDefaults().at(0);
    QCOMPARE(ModelResultDefaultInterface->GetTypeId(),QString("LinesFromUrl"));
    ResourceModelUrl * ModelResultDefault = qobject_cast<ResourceModelUrl *>(ModelResultDefaultInterface);
    if(ModelResultDefault == 0)
        QFAIL("Object is 0 after cast");

    QCOMPARE(ModelResultDefault->GetUrl(),QString("tes1_url2"));
    QCOMPARE(ModelResult->GetFilename(),QString("tes1_file2"));

}


void CopyResourcesTests::CheckIfSomeValuesAreFromDefaultsAndSomeNot()
{
    CopyResourceController * _Controller = new CopyResourceController(this);
    _Controller->deleteLater();


    Resources *_ResourcesDeveloper = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDeveloper = _ResourcesDeveloper->GetModelList();

    ResourceModelUrl *Model1 = new ResourceModelUrl(_Controller);
    Model1->SetName("name1");
    Model1->SetUrl("tes1_url1");

    ResourceModelFile *Model11 = new ResourceModelFile(_Controller);
    Model11->SetName("name1");
    Model11->SetFilename("tes1_file1");

    QList<IResourceModel * > ModelsDeveloperDefaults = QList<IResourceModel * >()<<Model11;
    Model1->SetDefaults(ModelsDeveloperDefaults);
    ModelsDeveloper->append(Model1);


    Resources *_ResourcesUser = new Resources(_Controller);
    QList<IResourceModel * >* ModelsUser = _ResourcesUser->GetModelList();

    ResourceModelFile *Model2 = new ResourceModelFile(_Controller);
    Model2->SetName("name1");
    Model2->SetFilename("tes1_file2");


    ResourceModelUrl *Model21 = new ResourceModelUrl(_Controller);
    Model21->SetName("name1");
    Model21->SetUrl("tes1_url2");
    QList<IResourceModel * > ModelsUserDefaults = QList<IResourceModel * >()<<Model21;
    Model2->SetDefaults(ModelsUserDefaults);
    ModelsUser->append(Model2);


    Resources *_ResourcesDefault = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDefault = _ResourcesDefault->GetModelList();

    ResourceModelFixedInteger *Model3 = new ResourceModelFixedInteger(_Controller);
    Model3->SetName("name1");
    Model3->SetValue(10);


    ResourceModelFile *Model31 = new ResourceModelFile(_Controller);
    Model31->SetName("name1");
    Model31->SetFilename("tes1_file2");
    QList<IResourceModel * > ModelsDefaultDefaults = QList<IResourceModel * >()<<Model31;
    Model3->SetDefaults(ModelsDefaultDefaults);
    ModelsDefault->append(Model3);


    _Controller->SetDefaults(_ResourcesDefault);
    _Controller->SetResources(_ResourcesUser);
    _Controller->FromViewToModel(_ResourcesDeveloper);


    ModelsDeveloper = _ResourcesDeveloper->GetModelList();
    QCOMPARE(ModelsDeveloper->length(),1);
    IResourceModel * ModelResultInterface = ModelsDeveloper->at(0);
    QCOMPARE(ModelResultInterface->GetTypeId(),QString("LinesFromFile"));
    ResourceModelFile * ModelResult = qobject_cast<ResourceModelFile *>(ModelResultInterface);
    if(ModelResult == 0)
        QFAIL("Object is 0 after cast");


    QCOMPARE(ModelResult->GetDefaults().length(),1);
    IResourceModel * ModelResultDefaultInterface = ModelResult->GetDefaults().at(0);
    QCOMPARE(ModelResultDefaultInterface->GetTypeId(),QString("LinesFromUrl"));
    ResourceModelUrl * ModelResultDefault = qobject_cast<ResourceModelUrl *>(ModelResultDefaultInterface);
    if(ModelResultDefault == 0)
        QFAIL("Object is 0 after cast");

    QCOMPARE(ModelResultDefault->GetUrl(),QString("tes1_url2"));
    QCOMPARE(ModelResult->GetFilename(),QString("tes1_file1"));

}


void CopyResourcesTests::CheckIfFixedStringIsChanged()
{
    CopyResourceController * _Controller = new CopyResourceController(this);
    _Controller->deleteLater();


    Resources *_ResourcesDeveloper = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDeveloper = _ResourcesDeveloper->GetModelList();

    ResourceModelFixedString *Model1 = new ResourceModelFixedString(_Controller);
    Model1->SetName("name");
    Model1->SetValue("test_value_1");
    Model1->SetNotEmpty(true);
    ModelsDeveloper->append(Model1);


    Resources *_ResourcesUser = new Resources(_Controller);
    QList<IResourceModel * >* ModelsUser = _ResourcesUser->GetModelList();

    ResourceModelFixedString *Model2 = new ResourceModelFixedString(_Controller);
    Model2->SetName("name");
    Model2->SetValue("test_value_2");
    Model2->SetNotEmpty(false);
    ModelsUser->append(Model2);


    Resources *_ResourcesDefault = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDefault = _ResourcesDefault->GetModelList();

    ResourceModelFixedString *Model3 = new ResourceModelFixedString(_Controller);
    Model3->SetName("name");
    Model3->SetValue("test_value_3");
    Model3->SetNotEmpty(true);
    ModelsDefault->append(Model3);

    _Controller->SetDefaults(_ResourcesDefault);
    _Controller->SetResources(_ResourcesUser);
    _Controller->FromViewToModel(_ResourcesDeveloper);


    ModelsDeveloper = _ResourcesDeveloper->GetModelList();
    QCOMPARE(ModelsDeveloper->length(),1);
    IResourceModel * ModelResultInterface = ModelsDeveloper->at(0);
    QCOMPARE(ModelResultInterface->GetTypeId(),QString("FixedString"));
    ResourceModelFixedString * ModelResult = qobject_cast<ResourceModelFixedString *>(ModelResultInterface);
    if(ModelResult == 0)
        QFAIL("Object is 0 after cast");

    QCOMPARE(ModelResult->GetValue(),QString("test_value_2"));
    QCOMPARE(ModelResult->GetNotEmpty(),true);

}

void CopyResourcesTests::CheckIfRandomStringIsChanged()
{
    CopyResourceController * _Controller = new CopyResourceController(this);
    _Controller->deleteLater();


    Resources *_ResourcesDeveloper = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDeveloper = _ResourcesDeveloper->GetModelList();

    ResourceModelRandomString *Model1 = new ResourceModelRandomString(_Controller);
    Model1->SetName("name");
    Model1->SetValue("test_value_1");

    ModelsDeveloper->append(Model1);


    Resources *_ResourcesUser = new Resources(_Controller);
    QList<IResourceModel * >* ModelsUser = _ResourcesUser->GetModelList();

    ResourceModelRandomString *Model2 = new ResourceModelRandomString(_Controller);
    Model2->SetName("name");
    Model2->SetValue("test_value_2");

    ModelsUser->append(Model2);



    _Controller->SetResources(_ResourcesUser);
    _Controller->FromViewToModel(_ResourcesDeveloper);


    ModelsDeveloper = _ResourcesDeveloper->GetModelList();
    QCOMPARE(ModelsDeveloper->length(),1);
    IResourceModel * ModelResultInterface = ModelsDeveloper->at(0);
    QCOMPARE(ModelResultInterface->GetTypeId(),QString("RandomString"));
    ResourceModelRandomString * ModelResult = qobject_cast<ResourceModelRandomString *>(ModelResultInterface);
    if(ModelResult == 0)
        QFAIL("Object is 0 after cast");

    QCOMPARE(ModelResult->GetValue(),QString("test_value_2"));

}

void CopyResourcesTests::CheckIfRandomIntegerIsChanged()
{
    CopyResourceController * _Controller = new CopyResourceController(this);
    _Controller->deleteLater();


    Resources *_ResourcesDeveloper = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDeveloper = _ResourcesDeveloper->GetModelList();

    ResourceModelRandomInteger *Model1 = new ResourceModelRandomInteger(_Controller);
    Model1->SetName("name");
    Model1->SetMinDesignValue(1);
    Model1->SetMaxDesignValue(10);
    Model1->SetMinUserValue(5);
    Model1->SetMaxUserValue(7);

    ModelsDeveloper->append(Model1);


    Resources *_ResourcesUser = new Resources(_Controller);
    QList<IResourceModel * >* ModelsUser = _ResourcesUser->GetModelList();

    ResourceModelRandomInteger *Model2 = new ResourceModelRandomInteger(_Controller);
    Model2->SetName("name");
    Model2->SetMinDesignValue(3);
    Model2->SetMaxDesignValue(9);
    Model2->SetMinUserValue(6);
    Model2->SetMaxUserValue(8);

    ModelsUser->append(Model2);



    _Controller->SetResources(_ResourcesUser);
    _Controller->FromViewToModel(_ResourcesDeveloper);


    ModelsDeveloper = _ResourcesDeveloper->GetModelList();
    QCOMPARE(ModelsDeveloper->length(),1);
    IResourceModel * ModelResultInterface = ModelsDeveloper->at(0);
    QCOMPARE(ModelResultInterface->GetTypeId(),QString("RandomInteger"));
    ResourceModelRandomInteger * ModelResult = qobject_cast<ResourceModelRandomInteger *>(ModelResultInterface);
    if(ModelResult == 0)
        QFAIL("Object is 0 after cast");

    QCOMPARE(ModelResult->GetMinDesignValue(),1);
    QCOMPARE(ModelResult->GetMinUserValue(),6);
    QCOMPARE(ModelResult->GetMaxUserValue(),8);
    QCOMPARE(ModelResult->GetMaxDesignValue(),10);

}

void CopyResourcesTests::CheckIfFileIsChanged()
{
    CopyResourceController * _Controller = new CopyResourceController(this);
    _Controller->deleteLater();


    Resources *_ResourcesDeveloper = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDeveloper = _ResourcesDeveloper->GetModelList();

    ResourceModelFile *Model1 = new ResourceModelFile(_Controller);
    Model1->SetName("name");
    Model1->SetFilename("file1");
    Model1->SetWrite(true);
    Model1->SetMix(true);
    Model1->SetSuccessAttempts(99);
    Model1->SetFailAttempts(999);
    Model1->SetNumberSimultaneousUse(5);
    Model1->SetIntervalBetweenUsage(100);
    Model1->SetLoadInterval(101);
    Model1->SetRenewInterval(102);
    Model1->SetGreedy(true);


    ModelsDeveloper->append(Model1);


    Resources *_ResourcesUser = new Resources(_Controller);
    QList<IResourceModel * >* ModelsUser = _ResourcesUser->GetModelList();

    ResourceModelFile *Model2 = new ResourceModelFile(_Controller);
    Model2->SetName("name");
    Model2->SetFilename("file2");
    Model2->SetWrite(false);
    Model2->SetMix(false);
    Model2->SetSuccessAttempts(991);
    Model2->SetFailAttempts(9919);
    Model2->SetNumberSimultaneousUse(51);
    Model2->SetIntervalBetweenUsage(1001);
    Model2->SetLoadInterval(1011);
    Model2->SetRenewInterval(1012);
    Model2->SetGreedy(false);

    ModelsUser->append(Model2);



    _Controller->SetResources(_ResourcesUser);
    _Controller->FromViewToModel(_ResourcesDeveloper);


    ModelsDeveloper = _ResourcesDeveloper->GetModelList();
    QCOMPARE(ModelsDeveloper->length(),1);
    IResourceModel * ModelResultInterface = ModelsDeveloper->at(0);
    QCOMPARE(ModelResultInterface->GetTypeId(),QString("LinesFromFile"));
    ResourceModelFile * ModelResult = qobject_cast<ResourceModelFile *>(ModelResultInterface);
    if(ModelResult == 0)
        QFAIL("Object is 0 after cast");

    QCOMPARE(ModelResult->GetFilename(),QString("file2"));
    QCOMPARE(ModelResult->GetWrite(),false);
    QCOMPARE(ModelResult->GetMix(),false);
    QCOMPARE(ModelResult->GetSuccessAttempts(),991);
    QCOMPARE(ModelResult->GetFailAttempts(),9919);
    QCOMPARE(ModelResult->GetNumberSimultaneousUse(),51);
    QCOMPARE(ModelResult->GetIntervalBetweenUsage(),1001);
    QCOMPARE(ModelResult->GetLoadInterval(),1011);
    QCOMPARE(ModelResult->GetRenewInterval(),1012);
    QCOMPARE(ModelResult->GetGreedy(),false);

}


void CopyResourcesTests::CheckIfUrlIsChanged()
{
    CopyResourceController * _Controller = new CopyResourceController(this);
    _Controller->deleteLater();


    Resources *_ResourcesDeveloper = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDeveloper = _ResourcesDeveloper->GetModelList();

    ResourceModelUrl *Model1 = new ResourceModelUrl(_Controller);
    Model1->SetName("name");
    Model1->SetUrl("file21");
    Model1->SetMix(true);
    Model1->SetSuccessAttempts(99);
    Model1->SetFailAttempts(999);
    Model1->SetNumberSimultaneousUse(1);
    Model1->SetIntervalBetweenUsage(101);
    Model1->SetLoadInterval(111);
    Model1->SetRenewInterval(112);
    Model1->SetGreedy(true);
    Model1->SetCaptureMethod(ResourceModelUrl::Split);
    Model1->SetCaptureArgument("test_match2");


    ModelsDeveloper->append(Model1);


    Resources *_ResourcesUser = new Resources(_Controller);
    QList<IResourceModel * >* ModelsUser = _ResourcesUser->GetModelList();

    ResourceModelUrl *Model2 = new ResourceModelUrl(_Controller);
    Model2->SetName("name");
    Model2->SetUrl("file2");
    Model2->SetMix(false);
    Model2->SetSuccessAttempts(991);
    Model2->SetFailAttempts(9919);
    Model2->SetNumberSimultaneousUse(51);
    Model2->SetIntervalBetweenUsage(1001);
    Model2->SetLoadInterval(1011);
    Model2->SetRenewInterval(1012);
    Model2->SetGreedy(false);
    Model2->SetCaptureMethod(ResourceModelUrl::Match);
    Model2->SetCaptureArgument("test_match1");

    ModelsUser->append(Model2);



    _Controller->SetResources(_ResourcesUser);
    _Controller->FromViewToModel(_ResourcesDeveloper);


    ModelsDeveloper = _ResourcesDeveloper->GetModelList();
    QCOMPARE(ModelsDeveloper->length(),1);
    IResourceModel * ModelResultInterface = ModelsDeveloper->at(0);
    QCOMPARE(ModelResultInterface->GetTypeId(),QString("LinesFromUrl"));
    ResourceModelUrl * ModelResult = qobject_cast<ResourceModelUrl *>(ModelResultInterface);
    if(ModelResult == 0)
        QFAIL("Object is 0 after cast");

    QCOMPARE(ModelResult->GetUrl(),QString("file2"));
    QCOMPARE(ModelResult->GetMix(),false);
    QCOMPARE(ModelResult->GetSuccessAttempts(),991);
    QCOMPARE(ModelResult->GetFailAttempts(),9919);
    QCOMPARE(ModelResult->GetNumberSimultaneousUse(),51);
    QCOMPARE(ModelResult->GetIntervalBetweenUsage(),1001);
    QCOMPARE(ModelResult->GetLoadInterval(),1011);
    QCOMPARE(ModelResult->GetRenewInterval(),1012);
    QCOMPARE(ModelResult->GetGreedy(),false);
    QCOMPARE(ModelResult->GetCaptureMethod(),ResourceModelUrl::Split);
    QCOMPARE(ModelResult->GetCaptureArgument(),QString("test_match2"));



}

void CopyResourcesTests::CheckIfDirectoryIsChanged()
{
    CopyResourceController * _Controller = new CopyResourceController(this);
    _Controller->deleteLater();


    Resources *_ResourcesDeveloper = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDeveloper = _ResourcesDeveloper->GetModelList();

    ResourceModelDirectory *Model1 = new ResourceModelDirectory(_Controller);
    Model1->SetName("name");
    Model1->SetDirectory("file21");
    Model1->SetWildcard("wildcard1");
    Model1->SetClean(false);
    Model1->SetMix(true);
    Model1->SetSuccessAttempts(99);
    Model1->SetFailAttempts(999);
    Model1->SetNumberSimultaneousUse(1);
    Model1->SetIntervalBetweenUsage(101);
    Model1->SetLoadInterval(111);
    Model1->SetRenewInterval(112);
    Model1->SetGreedy(true);

    ModelsDeveloper->append(Model1);


    Resources *_ResourcesUser = new Resources(_Controller);
    QList<IResourceModel * >* ModelsUser = _ResourcesUser->GetModelList();

    ResourceModelDirectory *Model2 = new ResourceModelDirectory(_Controller);
    Model2->SetName("name");
    Model2->SetDirectory("file2");
    Model2->SetWildcard("wildcard2");
    Model2->SetClean(true);
    Model2->SetMix(false);
    Model2->SetSuccessAttempts(919);
    Model2->SetFailAttempts(1999);
    Model2->SetNumberSimultaneousUse(15);
    Model2->SetIntervalBetweenUsage(108);
    Model2->SetLoadInterval(1161);
    Model2->SetRenewInterval(1142);
    Model2->SetGreedy(false);

    ModelsUser->append(Model2);



    _Controller->SetResources(_ResourcesUser);
    _Controller->FromViewToModel(_ResourcesDeveloper);


    ModelsDeveloper = _ResourcesDeveloper->GetModelList();
    QCOMPARE(ModelsDeveloper->length(),1);
    IResourceModel * ModelResultInterface = ModelsDeveloper->at(0);
    QCOMPARE(ModelResultInterface->GetTypeId(),QString("FilesFromDirectory"));
    ResourceModelDirectory * ModelResult = qobject_cast<ResourceModelDirectory *>(ModelResultInterface);
    if(ModelResult == 0)
        QFAIL("Object is 0 after cast");

    QCOMPARE(ModelResult->GetDirectory(),QString("file2"));
    QCOMPARE(ModelResult->GetWildcard(),QString("wildcard2"));
    QCOMPARE(ModelResult->GetClean(),true);
    QCOMPARE(ModelResult->GetMix(),false);
    QCOMPARE(ModelResult->GetSuccessAttempts(),919);
    QCOMPARE(ModelResult->GetFailAttempts(),1999);
    QCOMPARE(ModelResult->GetNumberSimultaneousUse(),15);
    QCOMPARE(ModelResult->GetIntervalBetweenUsage(),108);
    QCOMPARE(ModelResult->GetLoadInterval(),1161);
    QCOMPARE(ModelResult->GetRenewInterval(),1142);
    QCOMPARE(ModelResult->GetGreedy(),false);


}

void CopyResourcesTests::CheckIfSelectIsChanged()
{
    CopyResourceController * _Controller = new CopyResourceController(this);
    _Controller->deleteLater();


    Resources *_ResourcesDeveloper = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDeveloper = _ResourcesDeveloper->GetModelList();

    ResourceModelSelect *Model1 = new ResourceModelSelect(_Controller);
    Model1->SetName("name");
    Model1->SetValues(QStringList()<<"val1"<<"val2"<<"val3");
    Model1->SetSelected(QList<int>()<<0<<2);
    Model1->SetSelectType(ResourceModelSelect::Combo);


    ModelsDeveloper->append(Model1);


    Resources *_ResourcesUser = new Resources(_Controller);
    QList<IResourceModel * >* ModelsUser = _ResourcesUser->GetModelList();

    ResourceModelSelect *Model2 = new ResourceModelSelect(_Controller);
    Model2->SetName("name");
    Model2->SetValues(QStringList()<<"valll1"<<"val242342"<<"val2");
    Model2->SetSelected(QList<int>()<<2);
    Model2->SetSelectType(ResourceModelSelect::Check);


    ModelsUser->append(Model2);



    _Controller->SetResources(_ResourcesUser);
    _Controller->FromViewToModel(_ResourcesDeveloper);


    ModelsDeveloper = _ResourcesDeveloper->GetModelList();
    QCOMPARE(ModelsDeveloper->length(),1);
    IResourceModel * ModelResultInterface = ModelsDeveloper->at(0);
    QCOMPARE(ModelResultInterface->GetTypeId(),QString("Select"));
    ResourceModelSelect * ModelResult = qobject_cast<ResourceModelSelect *>(ModelResultInterface);
    if(ModelResult == 0)
        QFAIL("Object is 0 after cast");

    QStringList j1 = ModelResult->GetValues();
    j1.sort();

    QList<int> i1 = ModelResult->GetSelected();
    QStringList j2;
    foreach(int i,i1)
    {
        j2.append(QString::number(i));
    }
    j2.sort();

    QCOMPARE(j1.join(","),QString("val1,val2,val3"));
    QCOMPARE(j2.join(","),QString("1"));
    QCOMPARE(ModelResult->GetSelectType(),ResourceModelSelect::Combo);


}

void CopyResourcesTests::CheckIfFixedIntegerRespectsDefault()
{
    CopyResourceController * _Controller = new CopyResourceController(this);
    _Controller->deleteLater();


    Resources *_ResourcesDeveloper = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDeveloper = _ResourcesDeveloper->GetModelList();

    ResourceModelFixedInteger *Model1 = new ResourceModelFixedInteger(_Controller);
    Model1->SetName("name");
    Model1->SetValue(999);
    ModelsDeveloper->append(Model1);


    Resources *_ResourcesUser = new Resources(_Controller);
    QList<IResourceModel * >* ModelsUser = _ResourcesUser->GetModelList();

    ResourceModelFixedInteger *Model2 = new ResourceModelFixedInteger(_Controller);
    Model2->SetName("name");
    Model2->SetValue(99);
    ModelsUser->append(Model2);


    Resources *_ResourcesDefault = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDefault = _ResourcesDefault->GetModelList();

    ResourceModelFixedInteger *Model3 = new ResourceModelFixedInteger(_Controller);
    Model3->SetName("name");
    Model3->SetValue(99);
    ModelsDefault->append(Model3);

    _Controller->SetDefaults(_ResourcesDefault);
    _Controller->SetResources(_ResourcesUser);
    _Controller->FromViewToModel(_ResourcesDeveloper);


    ModelsDeveloper = _ResourcesDeveloper->GetModelList();
    QCOMPARE(ModelsDeveloper->length(),1);
    IResourceModel * ModelResultInterface = ModelsDeveloper->at(0);
    QCOMPARE(ModelResultInterface->GetTypeId(),QString("FixedInteger"));
    ResourceModelFixedInteger * ModelResult = qobject_cast<ResourceModelFixedInteger *>(ModelResultInterface);
    if(ModelResult == 0)
        QFAIL("Object is 0 after cast");

    QCOMPARE(ModelResult->GetValue(),999);
}

void CopyResourcesTests::CheckIfFixedIntegerIsChanged()
{
    CopyResourceController * _Controller = new CopyResourceController(this);
    _Controller->deleteLater();


    Resources *_ResourcesDeveloper = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDeveloper = _ResourcesDeveloper->GetModelList();

    ResourceModelFixedInteger *Model1 = new ResourceModelFixedInteger(_Controller);
    Model1->SetName("name");
    Model1->SetValue(999);
    ModelsDeveloper->append(Model1);


    Resources *_ResourcesUser = new Resources(_Controller);
    QList<IResourceModel * >* ModelsUser = _ResourcesUser->GetModelList();

    ResourceModelFixedInteger *Model2 = new ResourceModelFixedInteger(_Controller);
    Model2->SetName("name");
    Model2->SetValue(99);
    ModelsUser->append(Model2);


    Resources *_ResourcesDefault = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDefault = _ResourcesDefault->GetModelList();

    ResourceModelFixedInteger *Model3 = new ResourceModelFixedInteger(_Controller);
    Model3->SetName("name");
    Model3->SetValue(9);
    ModelsDefault->append(Model3);

    _Controller->SetDefaults(_ResourcesDefault);
    _Controller->SetResources(_ResourcesUser);
    _Controller->FromViewToModel(_ResourcesDeveloper);


    ModelsDeveloper = _ResourcesDeveloper->GetModelList();
    QCOMPARE(ModelsDeveloper->length(),1);
    IResourceModel * ModelResultInterface = ModelsDeveloper->at(0);
    QCOMPARE(ModelResultInterface->GetTypeId(),QString("FixedInteger"));
    ResourceModelFixedInteger * ModelResult = qobject_cast<ResourceModelFixedInteger *>(ModelResultInterface);
    if(ModelResult == 0)
        QFAIL("Object is 0 after cast");

    QCOMPARE(ModelResult->GetValue(),99);

}

void CopyResourcesTests::CheckIfWorksWithNoDefaultsAndEmptyUserValues()
{
    CopyResourceController * _Controller = new CopyResourceController(this);
    _Controller->deleteLater();


    Resources *_ResourcesDeveloper = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDeveloper = _ResourcesDeveloper->GetModelList();

    ResourceModelFixedString *Model1 = new ResourceModelFixedString(_Controller);
    Model1->SetName("name");
    Model1->SetValue("test_value_1");
    Model1->SetNotEmpty(true);
    ModelsDeveloper->append(Model1);


    Resources *_ResourcesUser = new Resources(_Controller);



    _Controller->SetResources(_ResourcesUser);
    _Controller->FromViewToModel(_ResourcesDeveloper);


    ModelsDeveloper = _ResourcesDeveloper->GetModelList();
    QCOMPARE(ModelsDeveloper->length(),1);
    IResourceModel * ModelResultInterface = ModelsDeveloper->at(0);
    QCOMPARE(ModelResultInterface->GetTypeId(),QString("FixedString"));
    ResourceModelFixedString * ModelResult = qobject_cast<ResourceModelFixedString *>(ModelResultInterface);
    if(ModelResult == 0)
        QFAIL("Object is 0 after cast");

    QCOMPARE(ModelResult->GetValue(),QString("test_value_1"));
    QCOMPARE(ModelResult->GetNotEmpty(),true);

}

void CopyResourcesTests::CheckIfWorksWithNoDefaults()
{
    CopyResourceController * _Controller = new CopyResourceController(this);
    _Controller->deleteLater();


    Resources *_ResourcesDeveloper = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDeveloper = _ResourcesDeveloper->GetModelList();

    ResourceModelFixedString *Model1 = new ResourceModelFixedString(_Controller);
    Model1->SetName("name");
    Model1->SetValue("test_value_1");
    Model1->SetNotEmpty(true);
    ModelsDeveloper->append(Model1);


    Resources *_ResourcesUser = new Resources(_Controller);
    QList<IResourceModel * >* ModelsUser = _ResourcesUser->GetModelList();

    ResourceModelFixedString *Model2 = new ResourceModelFixedString(_Controller);
    Model2->SetName("name");
    Model2->SetValue("test_value_2");
    Model2->SetNotEmpty(true);
    ModelsUser->append(Model2);



    _Controller->SetResources(_ResourcesUser);
    _Controller->FromViewToModel(_ResourcesDeveloper);


    ModelsDeveloper = _ResourcesDeveloper->GetModelList();
    QCOMPARE(ModelsDeveloper->length(),1);
    IResourceModel * ModelResultInterface = ModelsDeveloper->at(0);
    QCOMPARE(ModelResultInterface->GetTypeId(),QString("FixedString"));
    ResourceModelFixedString * ModelResult = qobject_cast<ResourceModelFixedString *>(ModelResultInterface);
    if(ModelResult == 0)
        QFAIL("Object is 0 after cast");

    QCOMPARE(ModelResult->GetValue(),QString("test_value_2"));
    QCOMPARE(ModelResult->GetNotEmpty(),true);

}

void CopyResourcesTests::CheckIfTypeIsPreserved()
{
    CopyResourceController * _Controller = new CopyResourceController(this);
    _Controller->deleteLater();


    Resources *_ResourcesDeveloper = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDeveloper = _ResourcesDeveloper->GetModelList();

    ResourceModelFixedString *Model1 = new ResourceModelFixedString(_Controller);
    Model1->SetName("name");
    Model1->SetValue("test_value_1");
    Model1->SetNotEmpty(true);
    ModelsDeveloper->append(Model1);


    Resources *_ResourcesUser = new Resources(_Controller);
    QList<IResourceModel * >* ModelsUser = _ResourcesUser->GetModelList();

    ResourceModelFixedInteger *Model2 = new ResourceModelFixedInteger(_Controller);
    Model2->SetName("name");
    Model2->SetValue(99);
    ModelsUser->append(Model2);


    Resources *_ResourcesDefault = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDefault = _ResourcesDefault->GetModelList();

    ResourceModelFixedInteger *Model3 = new ResourceModelFixedInteger(_Controller);
    Model3->SetName("name");
    Model3->SetValue(999);
    ModelsDefault->append(Model3);

    _Controller->SetDefaults(_ResourcesDefault);
    _Controller->SetResources(_ResourcesUser);
    _Controller->FromViewToModel(_ResourcesDeveloper);


    ModelsDeveloper = _ResourcesDeveloper->GetModelList();
    QCOMPARE(ModelsDeveloper->length(),1);
    IResourceModel * ModelResultInterface = ModelsDeveloper->at(0);
    QCOMPARE(ModelResultInterface->GetTypeId(),QString("FixedString"));
    ResourceModelFixedString * ModelResult = qobject_cast<ResourceModelFixedString *>(ModelResultInterface);
    if(ModelResult == 0)
        QFAIL("Object is 0 after cast");

    QCOMPARE(ModelResult->GetValue(),QString("test_value_1"));
    QCOMPARE(ModelResult->GetNotEmpty(),true);

}




void CopyResourcesTests::CheckIfFixedStringRespectsDefault()
{
    CopyResourceController * _Controller = new CopyResourceController(this);
    _Controller->deleteLater();


    Resources *_ResourcesDeveloper = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDeveloper = _ResourcesDeveloper->GetModelList();

    ResourceModelFixedString *Model1 = new ResourceModelFixedString(_Controller);
    Model1->SetName("name");
    Model1->SetValue("test_value_1");
    Model1->SetNotEmpty(true);
    ModelsDeveloper->append(Model1);


    Resources *_ResourcesUser = new Resources(_Controller);
    QList<IResourceModel * >* ModelsUser = _ResourcesUser->GetModelList();

    ResourceModelFixedString *Model2 = new ResourceModelFixedString(_Controller);
    Model2->SetName("name");
    Model2->SetValue("test_value_3");
    Model2->SetNotEmpty(true);
    ModelsUser->append(Model2);


    Resources *_ResourcesDefault = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDefault = _ResourcesDefault->GetModelList();

    ResourceModelFixedString *Model3 = new ResourceModelFixedString(_Controller);
    Model3->SetName("name");
    Model3->SetValue("test_value_3");
    Model3->SetNotEmpty(true);
    ModelsDefault->append(Model3);

    _Controller->SetDefaults(_ResourcesDefault);
    _Controller->SetResources(_ResourcesUser);
    _Controller->FromViewToModel(_ResourcesDeveloper);


    ModelsDeveloper = _ResourcesDeveloper->GetModelList();
    QCOMPARE(ModelsDeveloper->length(),1);
    IResourceModel * ModelResultInterface = ModelsDeveloper->at(0);
    QCOMPARE(ModelResultInterface->GetTypeId(),QString("FixedString"));
    ResourceModelFixedString * ModelResult = qobject_cast<ResourceModelFixedString *>(ModelResultInterface);
    if(ModelResult == 0)
        QFAIL("Object is 0 after cast");

    QCOMPARE(ModelResult->GetValue(),QString("test_value_1"));
    QCOMPARE(ModelResult->GetNotEmpty(),true);

}


void CopyResourcesTests::CheckIfFixedStringPreservesNotEmpty()
{
    CopyResourceController * _Controller = new CopyResourceController(this);
    _Controller->deleteLater();


    Resources *_ResourcesDeveloper = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDeveloper = _ResourcesDeveloper->GetModelList();

    ResourceModelFixedString *Model1 = new ResourceModelFixedString(_Controller);
    Model1->SetName("name");
    Model1->SetValue("test_value_1");
    Model1->SetNotEmpty(false);
    ModelsDeveloper->append(Model1);


    Resources *_ResourcesUser = new Resources(_Controller);
    QList<IResourceModel * >* ModelsUser = _ResourcesUser->GetModelList();

    ResourceModelFixedString *Model2 = new ResourceModelFixedString(_Controller);
    Model2->SetName("name");
    Model2->SetValue("test_value_2");
    Model2->SetNotEmpty(true);
    ModelsUser->append(Model2);


    Resources *_ResourcesDefault = new Resources(_Controller);
    QList<IResourceModel * >* ModelsDefault = _ResourcesDefault->GetModelList();

    ResourceModelFixedString *Model3 = new ResourceModelFixedString(_Controller);
    Model3->SetName("name");
    Model3->SetValue("test_value_3");
    Model3->SetNotEmpty(true);
    ModelsDefault->append(Model3);

    _Controller->SetDefaults(_ResourcesDefault);
    _Controller->SetResources(_ResourcesUser);
    _Controller->FromViewToModel(_ResourcesDeveloper);


    ModelsDeveloper = _ResourcesDeveloper->GetModelList();
    QCOMPARE(ModelsDeveloper->length(),1);
    IResourceModel * ModelResultInterface = ModelsDeveloper->at(0);
    QCOMPARE(ModelResultInterface->GetTypeId(),QString("FixedString"));
    ResourceModelFixedString * ModelResult = qobject_cast<ResourceModelFixedString *>(ModelResultInterface);
    if(ModelResult == 0)
        QFAIL("Object is 0 after cast");

    QCOMPARE(ModelResult->GetValue(),QString("test_value_2"));
    QCOMPARE(ModelResult->GetNotEmpty(),false);

}





QTEST_APPLESS_MAIN(CopyResourcesTests)

#include "tst_copyresourcestests.moc"
