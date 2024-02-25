#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionSave,SIGNAL(triggered(bool)),this,SLOT(on_actionSave_triiggered()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    ui->textEdit->setText(QString());
}


void MainWindow::on_actionOpen_triggered()
{
    QString FileName = QFileDialog::getOpenFileName(this,
                                                    "Open The File");
    CurrentFile = FileName;
    QFile file(FileName);
    QMessageBox open_error;

    if (!file.open(QIODevice::ReadOnly | QFile::Text)){
        open_error.setText("WARNING OPENING FILE");
        open_error.setIcon(QMessageBox::Warning);
        open_error.setInformativeText("NO File opened.");
        open_error.setStyleSheet("color:black;background-color : #C1B2B2");
        open_error.exec();
    }
    setWindowTitle(FileName);
    QTextStream in (&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();

}

void MainWindow::on_actionSave_triiggered()
{
    QString FileName;
    if(CurrentFile.isEmpty())
    {
        FileName= QFileDialog::getSaveFileName(this,"Save File");
        CurrentFile = FileName;
    }
    else{
        FileName = CurrentFile;
    }
    QFile file(FileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)){
        QMessageBox save_file;
        save_file.setText("WARNING SAVING FILE");
        save_file.setWindowTitle(CurrentFile);
        save_file.setIcon(QMessageBox::Warning);
        save_file.setInformativeText("NO File SAVED.");
        save_file.setStyleSheet("color:black;background-color : #C1B2B2");
        save_file.exec();
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}


void MainWindow::on_actionSave_as_triggered()
{
    QString FileName;
        FileName= QFileDialog::getSaveFileName(this,"Save File");
        CurrentFile = FileName;

    QFile file(FileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)){
        QMessageBox save_file;
        save_file.setText("WARNING SAVING FILE");
        save_file.setWindowTitle(CurrentFile);
        save_file.setIcon(QMessageBox::Warning);
        save_file.setInformativeText("NO File SAVED.");
        save_file.setStyleSheet("color:black;background-color : #C1B2B2");
        save_file.exec();
        return;
    }
    CurrentFile = FileName;
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

