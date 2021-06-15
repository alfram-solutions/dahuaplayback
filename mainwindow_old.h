//#ifndef MAINWINDOW_OLD_H
//#define MAINWINDOW_OLD_H

//#include <QMainWindow>
//#include <qapplication.h>
//#include <qmessagebox.h>
//#include <qtimer.h>
//#include <qlist.h>
//#include <qstring.h>
//#include <string>
//#include <pthread.h>
//#include <stdlib.h>
//#include <QStandardItemModel>
//#include <dhnetsdk.h>
//#include "./utility/dhmutex.h"
//#include "UserDefine.h"
//#include <./utility/Profile.h>



//QT_BEGIN_NAMESPACE
//namespace Ui {
//    class MainWindow;
//}
//QT_END_NAMESPACE

//class MainWindow : public QMainWindow
//{
//    Q_OBJECT

//public:
//    MainWindow(QWidget *parent = nullptr);
//    ~MainWindow();

//public:
//    int LoadConfig(int* nThreadNum);
//    void Logindev(int nThreadNum);
//    QStandardItem* createListModel();
//    void addRowData(QAbstractItemModel* model, QStringList rowDataList);

//protected:
//    bool InitData();
//    bool UnInitData();

//private:
//    pthread_t m_thread;

//    QTimer* m_counter;
//    LLONG m_lLoginHandle;
//    QString m_FileName;
//    QStandardItemModel* standardItemModel;

//private slots:
//    void on_pushButStop_clicked();
//    void on_pushButStopALL_clicked();
//    void on_pushButPlay_clicked();
//    void on_pushButLoad_clicked();
//    void UpdataListview();


//};
//#endif // MAINWINDOW_OLD_H
