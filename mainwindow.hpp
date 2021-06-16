#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <qapplication.h>
#include <qmessagebox.h>
#include <qtimer.h>
#include <qlist.h>
#include <qstring.h>
#include <string>
#include <pthread.h>
#include <stdlib.h>
#include <QStandardItemModel>
#include <dhnetsdk.h>
#include "./utility/dhmutex.h"
#include "UserDefine.h"
#include <./utility/Profile.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    int LoadConfig(int* nThreadNum);
    void Logindev(int nThreadNum);
    QStandardItemModel* createListModel();
    void addRowData(QAbstractItemModel* model, QStringList rowDataList);

protected:
    bool InitData();
    bool UnInitData();

private:
    pthread_t m_thread;

    QTimer* m_counter;
    LLONG m_lLoginHandle;
    QString m_FileName;
    QStandardItemModel* standardItemModel;


private:
    Ui::MainWindow *ui;


private slots:
    void on_pushButStop_clicked();
    void on_pushButStopALL_clicked();
    void on_pushButPlay_clicked();
    void on_pushButLoad_clicked();
    void UpdataListview();

};

#endif // MAINWINDOW_HPP
