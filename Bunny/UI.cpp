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
    //    uiLog("hello");
    View->show();//showFullScreen();

    DisplayProgressBar(true, false);
    LoadDefualtSettings();

}
//================================================================================
void UI::LoadDefualtSettings()
{
    currentIndex=0;
    SetDatasetPath( settings.value("DatasetPath").toString());
    LoadClassifyModel();
    QString path= settings.value("DatasetPath").toString();

    QDirIterator directoryIterator(settings.value("DatasetPath").toString().remove(0,7), QDirIterator::Subdirectories);
    _fileList.clear();
    qDebug()<<"++++++++++++++++++++++";
    while (directoryIterator.hasNext())
    {
        QString fname= directoryIterator.next();
        if(fname.contains("/."))
            continue;
        qDebug()<<fname;
        _fileList.append(fname);
        _labels.append("NAN");
    }
    DisplayImage(_fileList[currentIndex]);
}
//================================================================================

void UI::LoadClassifyModel()
{

    QStringList classifyList= settings.value("ClassifyList").toString().split(',');
    for(int i=0;i<classifyList.count();i++)
    {
        if(!classifyList[i].isEmpty())
        {
            AppendToClassifyModel(classifyList[i]);
            _classifyList.append(classifyList[i]);
        }
    }



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

void UI::AppendToClassifyModel(QString( value))
{

    QMetaObject::invokeMethod((QObject*)RootObject, "addToModel",
                              Q_ARG(QVariant, value)
                              );


}
//================================================================================
void UI::SetDatasetPath(QString path)
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
        _labels[currentIndex]=_lastLable;
        if(currentIndex<_fileList.count()-1)currentIndex++;

        SetImageLabel(_labels[currentIndex]);
        DisplayImage(_fileList[currentIndex]);
        qDebug()<<"index:"<<currentIndex;
        return;
    }
    if(16777219==key){//backspace
        if(currentIndex>0)currentIndex--;
         SetImageLabel(_labels[currentIndex]);
        DisplayImage(_fileList[currentIndex]);
        qDebug()<<"index:"<<currentIndex;
        return;
    }
    if(key>48 && key<58)
    {
        if((key-49)<_classifyList.count())
        {
            _lastLable=  _classifyList[key-49];
            SetImageLabel(_lastLable);
        }

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
