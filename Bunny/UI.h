#ifndef UI_H
#define UI_H

#include <QObject>
#include <QDebug>
#include <QSettings>
#include <QMetaObject>
#include <QtQuick/QQuickView>
#include <QApplication>
#include <QDir>
#include <QDirIterator>

#define KEY_ENTER 16777220
#define KEY_BACKSPACE 16777219
class UI : public QObject
{
    Q_OBJECT

    QStringList _classifyList;
    QStringList _fileList;
    QStringList _labels;
    QString _lastLable;
    int _currentIndex=0;

    QSettings settings;
public:
    QQuickItem *RootObject=nullptr;
    QQuickView  *View=nullptr;
    explicit UI(QObject *parent = nullptr);

    Q_INVOKABLE void btnClicked();
    Q_INVOKABLE void keyHandler(int key);
    Q_INVOKABLE void addClassifyClasses(QString key);
    Q_INVOKABLE void remveClassifyClasses();
    Q_INVOKABLE void saveResult();
    Q_INVOKABLE void classifyButtonClicked(QString name);
    Q_INVOKABLE void setDatasetPath(QString path);
    Q_INVOKABLE void closeApp();
    void Init();
    void LoadDefualtSettings();
    void DisplayDatasetPath(QString path);
    void AppendToClassifyModel(QString value);
    QStringList LoadClassifyModel(QString settingValue);
    void DisplayImage(QString src);
    void SetImageLabel(QString lable);
    void ChartAddSeries(QString name, float value);
    QStringList GetDtatSetFilesList(QString path);
    void UpdateStatic();
    void ChartClera();
    void ShowChartMetrics(QString metics);
    bool LoadLabels(QString path);
signals:

public slots:

    void uiLog(QString message);
};


#endif // UI_H
