#include "UI.h"
//================================================================================
UI::UI(QObject *parent) : QObject(parent)
{

}
//================================================================================
void UI::Init()
{
    //View->setMaximumSize(QSize(800,600));
    View->setFlag(Qt::WindowCloseButtonHint);
    View->showNormal();


    LoadDefualtSettings();
}
//================================================================================
QStringList UI::GetDtatSetFilesList(QString path)
{
    QStringList result;
    QStringList filters={".jpg",".png",".bmp",".jpeg"};
    QDirIterator directoryIterator(path, QDirIterator::Subdirectories);
    while (directoryIterator.hasNext())
    {
        QString fname= directoryIterator.next();
        if(fname.contains("/."))
            continue;

        for(int i=0;i<filters.count();i++)
        {
                   qDebug()<<filters[i];
            if(fname.endsWith(filters[i]))
            {
                result.append(fname);
                qDebug()<<"fn:"<<fname;
                _labels.append("NC");
                    break;
            }

        }
    }
    return result;
}
//================================================================================
bool UI::LoadLabels(QString path)
{

    QFile file(path);
    //qDebug()<<path;
    if(!QFile::exists(path))return false ;
    if(!file.open(QFile::ReadWrite))return false;
    qDebug()<<"path open ok";
    _fileList.clear();
    _labels.clear();
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList str = line.split('\t');
        if(str.count()<2)return false;
        _fileList.append(QString(str[0]).trimmed() );
        _labels.append(QString(str[1]).trimmed() );
    }


    file.close();

    return true;

}
//================================================================================
void UI::LoadDefualtSettings()
{
    _currentIndex=0;
    DisplayDatasetPath( settings.value("DatasetPath").toString());
      if(!LoadLabels( settings.value("DatasetPath").toString()+"/result.txt"))
    {

        _fileList= GetDtatSetFilesList(settings.value("DatasetPath").toString());
    }
      else{

              ShowToast("previuse dataset loaded ",3000);

      }


    _classifyList= LoadClassifyModel(settings.value("ClassifyList").toString());

    if(_fileList.count()<1)return;
    DisplayImage(_fileList[_currentIndex]);
    ChartAddSeries("NC",100);

    for(int i=0;i<_classifyList.count();i++)
    {
        ChartAddSeries(_classifyList[i],0);
    }
    UpdateStatic();
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
    SetImageLabel(_labels[_currentIndex]);
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

void UI::ShowToast(QString text,int delay)
{
    QMetaObject::invokeMethod((QObject*)RootObject, "showToast",
                                  Q_ARG(QVariant, text),
                                          Q_ARG(QVariant, delay)
                              );
}



//================================================================================
void UI::AppendToClassifyModel(QString( value))
{

    QMetaObject::invokeMethod((QObject*)RootObject, "addToModel",
                              Q_ARG(QVariant, value)
                              );


}
//================================================================================
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
    if(KEY_ENTER==key){//enter

        if(_currentIndex<_fileList.count()-1)_currentIndex++;

        SetImageLabel(_labels[_currentIndex]);
        DisplayImage(_fileList[_currentIndex]);
        return;
    }
    if(KEY_BACKSPACE==key){
        if(_currentIndex>0)_currentIndex--;
        SetImageLabel(_labels[_currentIndex]);
        DisplayImage(_fileList[_currentIndex]);

        return;
    }
    if(key>48 && key<58)
    {
        if((key-49)<_classifyList.count())
        {
            _lastLable=  _classifyList[key-49];
            SetImageLabel(_lastLable);
            _labels[_currentIndex]=_lastLable;
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
    QFile file(settings.value("DatasetPath").toString()+"/result.txt");
    if(!file.open(QFile::ReadWrite))return;
    for(int i=0;i<_fileList.count();i++)
    {
        QString st=_fileList[i]+"\t"+_labels[i]+"\n";
        file.write(st.toLatin1());
    }
    file.close();
}
//================================================================================
void UI::classifyButtonClicked(QString name)
{
    SetImageLabel(name);
}
//================================================================================
void UI::setDatasetPath(QString path)
{
    path=path.remove(0,7);
    settings.setValue("DatasetPath", path);
    qDebug()<<"c++"<<path;
    _fileList= GetDtatSetFilesList(path);
    DisplayImage(_fileList[_currentIndex]);

    DisplayDatasetPath(path);
    UpdateStatic();
}
//================================================================================
