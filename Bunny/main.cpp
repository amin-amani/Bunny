//#include <QGuiApplication>
//#include <QQmlApplicationEngine>

//int main(int argc, char *argv[])
//{
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

//    QGuiApplication app(argc, argv);

//    QQmlApplicationEngine engine;
//    const QUrl url(QStringLiteral("qrc:/main.qml"));
//    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
//                     &app, [url](QObject *obj, const QUrl &objUrl) {
//        if (!obj && url == objUrl)
//            QCoreApplication::exit(-1);
//    }, Qt::QueuedConnection);
//    engine.load(url);

//    return app.exec();
//}
//#include <torch/script.h>
#include <QApplication>
#include <QObject>


#include <QDir>

#include <QGuiApplication>
#include <qquickview.h>
#include <QQmlEngine>
#include <QQmlContext>
#include "UI.h"
int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    a.setOrganizationName("nojan");
    a.setOrganizationDomain("tehran");
    /////// UI PART
     UI *ui=new UI();

     QQuickView *view=new QQuickView();
     view->engine()->rootContext()->setContextProperty("processManager", ui);
     view->setSource(QUrl(QLatin1String("/home/amin/Bunny/Bunny/main.qml")));
     ui->RootObject=view->rootObject();
     ui->View=view;
     ui->Init();

    return a.exec();
}
