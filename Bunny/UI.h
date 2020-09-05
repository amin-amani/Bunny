#ifndef UI_H
#define UI_H

#include <QObject>
#include <QDebug>
#include <QMetaObject>
#include <QtQuick/QQuickView>
#include <QApplication>


class UI : public QObject
{
    Q_OBJECT
QString frontStatus="Not connected";
QString rearStatus="Not connected";

public:
    QQuickItem *RootObject=nullptr;
    QQuickView  *View=nullptr;
    explicit UI(QObject *parent = nullptr);

    Q_INVOKABLE void btnClicked();
    Q_INVOKABLE void startBtnClicked();
    Q_INVOKABLE void stopBtnClicked();
    Q_INVOKABLE void closeApp();
    void Init();


    void LoadDefualtSettings();
    void SetDatasetPath(QString path);
signals:
void StartSorting();
void StoptSorting();
public slots:
  void RearCameraReady();
  void FrontCameraReady();
  void DisplaySortResults(int Perfect, int garbage, int baste, int total);
  void DisplayDeviceStatus(QString camF, QString camR, QString board);
  void DisplayProgressBar(bool status, bool visibility);
  void uiLog(QString message);
};


#endif // UI_H
