#include "UI.h"

//================================================================================
UI::UI(QObject *parent) : QObject(parent)
{

}
//================================================================================
void UI::Init()
{

    //  settings.setValue("DatasetPath", "/home/amin/dataset");
    qDebug()<<"INIT START";
    //    QVariant returnedValue ;
    QMetaObject::invokeMethod((QObject*)RootObject, "qmlFunc",
                              //                              Q_RETURN_ARG(QVariant, returnedValue),
                              Q_ARG(QVariant,"my message")

                              );

    View->show();

    DisplayProgressBar(true, false);
    LoadDefualtSettings();

}
QStringList UI::GetDtatSetFilesList(QString path)
{
    QStringList result;
    QDirIterator directoryIterator(path, QDirIterator::Subdirectories);
    while (directoryIterator.hasNext())
    {
        QString fname= directoryIterator.next();
        if(fname.contains("/."))
            continue;
        result.append(fname);
        _labels.append("NAN");
    }
    return result;
}
//================================================================================
void UI::LoadDefualtSettings()
{
    currentIndex=0;
    DisplayDatasetPath( settings.value("DatasetPath").toString());
    _classifyList= LoadClassifyModel(settings.value("ClassifyList").toString());
    _fileList= GetDtatSetFilesList(settings.value("DatasetPath").toString().remove(0,7));
    DisplayImage(_fileList[currentIndex]);
    ChartAddSeries("NC",100);
    for(int i=0;i<_classifyList.count();i++)
    {
        ChartAddSeries(_classifyList[i],0);

    }
    //
    //    ChartAddSeries("non",80);
}
//================================================================================
void UI::UpdateStatic()
{
    int totalImages=_fileList.count();
    int unclassified=0;
    int totalClassified=0;
    int values[_classifyList.count()];

    for(int i=0;i<_classifyList.count();i++)
        values[i]=0;
    for(int i=0;i<_labels.count();i++)
    {
        for(int j=0;j<_classifyList.count();j++)
        {
            if(_labels[i]==_classifyList[j])
            {
                values[j]++;
                totalClassified++;
            }

        }

    }
    ChartClera();
    for(int i=0;i<_classifyList.count();i++)
    {
        float percentage=values[i]*100;
        percentage/=totalImages;
        ChartAddSeries(_classifyList[i],percentage);
    }
    float percentage=(totalImages-totalClassified)*100;
    percentage/=_fileList.count();

    ChartAddSeries("NC",percentage);

   QString msg="Total="+QString::number(_fileList.count())+"\n";
   for(int i=0;i<_classifyList.count();i++)
   {
       msg+=_classifyList[i]+":"+QString::number(values[i]) +"\t"+QString::number((values[i]*100)/_fileList.count())+"% \n";
   }
 unclassified=totalImages-totalClassified;
   msg+="NC:"+QString::number(unclassified)+"\t";
 msg+=QString::number((unclassified*100)/_fileList.count())+"%";



    ShowChartMetrics(msg);
}
//================================================================================

QStringList UI::LoadClassifyModel(QString settingValue)
{
    QStringList result;
    QStringList splitlis= settingValue.split(',');
    for(int i=0;i<splitlis.count();i++)
    {
        if(!splitlis[i].isEmpty())
        {
            AppendToClassifyModel(splitlis[i]);
            result.append(splitlis[i]);
        }
    }
    return result;
}
//================================================================================

void UI::DisplayImage(QString src)
{
    QMetaObject::invokeMethod((QObject*)RootObject, "displayImage",
                              Q_ARG(QVariant, src)
                              );
}
//================================================================================
void UI::SetImageLabel(QString lable)
{

    QMetaObject::invokeMethod((QObject*)RootObject, "setImageLabel",
                              Q_ARG(QVariant, lable)
                              );
}
//================================================================================
void UI::ChartAddSeries(QString name,float value)

{
    QMetaObject::invokeMethod((QObject*)RootObject, "chartAddSeries",
                              Q_ARG(QVariant, name),
                              Q_ARG(QVariant, value )
                              );
}
//================================================================================

void UI::ChartClera()

{
    QMetaObject::invokeMethod((QObject*)RootObject, "chartClear"
                              );
}

//================================================================================

void UI::AppendToClassifyModel(QString( value))
{

    QMetaObject::invokeMethod((QObject*)RootObject, "addToModel",
                              Q_ARG(QVariant, value)
                              );


}

void UI::ShowChartMetrics(QString metics)
{
    QMetaObject::invokeMethod((QObject*)RootObject, "showChartMetrics",
                              Q_ARG(QVariant, metics)
                              );
}
//================================================================================
void UI::DisplayDatasetPath(QString path)
{
    QMetaObject::invokeMethod((QObject*)RootObject, "setDatasetAddress",
                              Q_ARG(QVariant, path)
                              );
}
//================================================================================
void UI::DisplayDeviceStatus(QString camF, QString camR, QString board)
{

    QMetaObject::invokeMethod((QObject*)RootObject, "displayDeviceStatus",
                              Q_ARG(QVariant, camF),
                              Q_ARG(QVariant, camR),
                              Q_ARG(QVariant, board)
                              );
}
//================================================================================
void UI::DisplayProgressBar(bool status, bool visibility)
{
    QMetaObject::invokeMethod((QObject*)RootObject, "displayProgressBar",
                              Q_ARG(QVariant, status),
                              Q_ARG(QVariant, visibility)
                              );
}
//================================================================================
void UI::uiLog(QString message )
{
    qDebug()<<"we are in UILOG" << message;
    QMetaObject::invokeMethod((QObject*)RootObject, "setText",
                              //                              Q_RETURN_ARG(QVariant, returnedValue),
                              Q_ARG(QVariant,message)
                              );
}
//================================================================================
void UI::btnClicked()
{
    qDebug()<<"clicked c++";
}
//================================================================================
void UI::closeApp()
{
    QCoreApplication::quit();
}

//================================================================================
void UI::keyHandler(int key)
{
    if(16777220==key){//enter

        if(currentIndex<_fileList.count()-1)currentIndex++;

        SetImageLabel(_labels[currentIndex]);
        DisplayImage(_fileList[currentIndex]);
        return;
    }
    if(16777219==key){//backspace
        if(currentIndex>0)currentIndex--;
        SetImageLabel(_labels[currentIndex]);
        DisplayImage(_fileList[currentIndex]);

        return;
    }
    if(key>48 && key<58)
    {
        if((key-49)<_classifyList.count())
        {
            _lastLable=  _classifyList[key-49];
            SetImageLabel(_lastLable);
            _labels[currentIndex]=_lastLable;
        }
        UpdateStatic();

    }

}
//================================================================================

void UI::addClassifyClasses(QString key)
{
    _classifyList.append(key);
    QString strList;
    for(int i=0;i<_classifyList.count();i++)
        strList+=","+_classifyList[i];
    settings.setValue("ClassifyList", strList);

}
//================================================================================

void UI::remveClassifyClasses()
{
    settings.setValue("ClassifyList", "");
}
//================================================================================

void UI::saveResult()
{
    QFile file("result.txt");
    file.open(QFile::ReadWrite);
    for(int i=0;i<_fileList.count();i++)
    {
        QString st=_fileList[i]+" "+_labels[i]+"\n";
        file.write(st.toLatin1());
    }

}
//================================================================================

void UI::classifyButtonClicked(QString name)
{
    SetImageLabel(name);
}
//================================================================================
void UI::setDatasetPath(QString path)
{
    settings.setValue("DatasetPath", path);
}

//================================================================================
