#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnGetAll_clicked()
{
    QString site_url="http://localhost:3000/car";
    QNetworkRequest request((site_url));
    getManager = new QNetworkAccessManager(this);

    connect(getManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getCarSlot(QNetworkReply*)));

    getReply = getManager->get(request);
}

void MainWindow::getCarSlot (QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();

    QStandardItemModel *model = new QStandardItemModel(json_array.size(), 3, this);
    model->setHorizontalHeaderLabels(QStringList() << "ID" << "Brand" << "Model");

    int row = 0;
    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        QString id = QString::number(json_obj["id_car"].toInt());
        QString brand = json_obj["brand"].toString();
        QString carmodel = json_obj["model"].toString();

        model->setItem(row, 0, new QStandardItem(id));
        model->setItem(row, 1, new QStandardItem(brand));
        model->setItem(row, 2, new QStandardItem(carmodel));

        row++;
    }

    ui->tableCar->setModel(model);
    ui->tableCar->verticalHeader()->hide();

    reply->deleteLater();
    getManager->deleteLater();
}

void MainWindow::on_btnUpdateCar_clicked()
{
    QString carId = ui->txtUpdateCarId->text();
    QString carBrand = ui->txtUpdateCarBrand->text();
    QString carModel = ui->txtUpdateCarModel->text();

    QJsonObject jsonObj;
    jsonObj.insert("id_car", carId);
    jsonObj.insert("brand", carBrand);
    jsonObj.insert("model", carModel);

    QString site_url="http://localhost:3000/car/" +carId;
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    putManager = new QNetworkAccessManager(this);
    connect(putManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(updateCarSlot(QNetworkReply*)));

    putReply = putManager->put(request, QJsonDocument(jsonObj).toJson());

    ui->txtUpdateCarId->clear();
    ui->txtUpdateCarBrand->clear();
    ui->txtUpdateCarModel->clear();
}

void MainWindow::updateCarSlot (QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    reply->deleteLater();
    putManager->deleteLater();
}

void MainWindow::on_btnAddCar_clicked()
{
    QString carBrand = ui->txtAddCarBrand->text();
    QString carModel = ui->txtAddCarModel->text();

    QJsonObject jsonObj;
    jsonObj.insert("brand", carBrand);
    jsonObj.insert("model", carModel);

    QString site_url="http://localhost:3000/car";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    postManager = new QNetworkAccessManager(this);
    connect(postManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(addCarSlot(QNetworkReply*)));

    postReply = postManager->post(request, QJsonDocument(jsonObj).toJson());

    ui->txtAddCarBrand->clear();
    ui->txtAddCarModel->clear();
}

void MainWindow::addCarSlot (QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    reply->deleteLater();
    postManager->deleteLater();
}

void MainWindow::on_btnDeleteCar_clicked()
{
    QString carId = ui->txtDeleteCarId->text();

    QJsonObject jsonObj;
    jsonObj.insert("id_car", carId);

    QString site_url="http://localhost:3000/car/" +carId;
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    deleteManager = new QNetworkAccessManager(this);
    connect(deleteManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(deleteCarSlot(QNetworkReply*)));

    deleteReply = deleteManager->deleteResource(request);

    ui->txtDeleteCarId->clear();
}

void MainWindow::deleteCarSlot (QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    reply->deleteLater();
    deleteManager->deleteLater();
}
