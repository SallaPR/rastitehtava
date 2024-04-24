#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *getManager;
    QNetworkAccessManager *putManager;
    QNetworkAccessManager *postManager;
    QNetworkAccessManager *deleteManager;
    QNetworkReply *getReply;
    QNetworkReply *putReply;
    QNetworkReply *postReply;
    QNetworkReply *deleteReply;
    QByteArray response_data;

private slots:
    void getCarSlot (QNetworkReply *reply);
    void updateCarSlot (QNetworkReply *reply);
    void addCarSlot (QNetworkReply *reply);
    void deleteCarSlot (QNetworkReply *reply);
    void on_btnGetAll_clicked();
    void on_btnUpdateCar_clicked();
    void on_btnAddCar_clicked();
    void on_btnDeleteCar_clicked();
};

#endif // MAINWINDOW_H
