#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::on_lineEdit_editingFinished()
{
    // 命令行示例：https://fasttext.cc/docs/en/cheatsheet.html
}

void MainWindow::on_pushButton_clicked()
{
    FastTextCmd::exec(ui->lineEdit->text().trimmed());
}

void MainWindow::on_pushButton_2_clicked()
{
    FastTextUtil* ft = new FastTextUtil(this);
    connect(ft, &FastTextUtil::signalTrainFinished, this, [=]{
        qDebug() << "模型训练结束";
    });
    ft->train("train.txt", "model");
}

void MainWindow::on_pushButton_3_clicked()
{
    FastTextUtil* ft = new FastTextUtil(this);
    connect(ft, &FastTextUtil::signalPredictsFinished, this, [=](QList<QStringList> result){
        qDebug() << "预测结束，结果:" << result;
    });
    ft->predict("text.txt", "model", 2);
}

void MainWindow::on_pushButton_4_clicked()
{
    FastTextUtil* ft = new FastTextUtil(this);
    connect(ft, &FastTextUtil::signalQuantizeFinished, this, [=] {
        qDebug() << "量化结束";
    });
    ft->quantize("model");
}

void MainWindow::on_pushButton_5_clicked()
{
    FastTextUtil* ft = new FastTextUtil(this);
    connect(ft, &FastTextUtil::signalPredictOneFinished, this, [=](QString result){
        qDebug() << "预测结束，结果:" << result;
    });
    ft->predictOne(ui->lineEdit_2->text(), "model");
}

void MainWindow::on_pushButton_6_clicked()
{
    FastTextUtil* ft = new FastTextUtil(this);
    connect(ft, &FastTextUtil::signalPredictFinished, this, [=](QStringList result){
        qDebug() << "预测结束，结果:" << result;
    });
    ft->predict("text.txt", "model");
}
