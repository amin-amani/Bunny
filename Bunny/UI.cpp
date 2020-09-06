#include "UI.h"



UI::UI(QObject *parent) : QObject(parent)
{

}

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
    DisplayDeviceStatus("Loading...", "Loading...", "Loading...");
    DisplayProgressBar(true, false);
    LoadDefualtSettings();
}

void UI::LoadDefualtSettings()
{

    SetDatasetPath( settings.value("DatasetPath").toString());

}
void UI::SetDatasetPath(QString path)
{
    QMetaObject::invokeMethod((QObject*)RootObject, "setDatasetAddress",
                              Q_ARG(QVariant, path)
                              );
}



void UI::DisplayDeviceStatus(QString camF, QString camR, QString board)
{

    QMetaObject::invokeMethod((QObject*)RootObject, "displayDeviceStatus",
                              Q_ARG(QVariant, camF),
                              Q_ARG(QVariant, camR),
                              Q_ARG(QVariant, board)
                              );
}

void UI::DisplayProgressBar(bool status, bool visibility)
{

    QMetaObject::invokeMethod((QObject*)RootObject, "displayProgressBar",
                              Q_ARG(QVariant, status),
                              Q_ARG(QVariant, visibility)
                              );
}



void UI::uiLog(QString message )
{
    qDebug()<<"we are in UILOG" << message;
    QMetaObject::invokeMethod((QObject*)RootObject, "setText",
                              //                              Q_RETURN_ARG(QVariant, returnedValue),
                              Q_ARG(QVariant,message)

                              );
}

void UI::btnClicked()
{
    qDebug()<<"clicked c++";

    //Init();
}

void UI::closeApp()
{
    QCoreApplication::quit();
}

void UI::startBtnClicked()
{
    qDebug()<<"startBtnClicked";
    emit StartSorting();
}

void UI::stopBtnClicked()
{
    qDebug()<<"stopBtnClicked";
    return;
}

void UI::keyHandler(int key)
{
    qDebug()<<"clicked:"<<key;
}

void UI::RearCameraReady()
{
    //    qDebug()<<"==================================>INJA";
    rearStatus="Connected!";
    DisplayDeviceStatus(frontStatus,rearStatus,"Connected!");
}

void UI::FrontCameraReady()
{
    //    qDebug()<<"==================================>INJA2";
    frontStatus="Connected!";
    DisplayDeviceStatus(frontStatus,rearStatus,"Connected!");
}

