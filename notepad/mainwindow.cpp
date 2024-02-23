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
    if (!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"WARNING","<font color = 'black'>CAN NOT OPEN FILE</font>"+file.errorString());
        return;
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
        FileName= QFileDialog::getOpenFileName(this,"Save File");
        CurrentFile = FileName;
    }
    else{
        FileName = CurrentFile;
    }
    QFile file(FileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)){
        QMessageBox an;
        an.setStyleSheet("QPushButton{ color : red; }");
        an.warning(this,"WARNING","<font color = 'blak'>CAN NOT SAVE FILE</font>"+file.errorString());
        // QMessageBox::warning(this,"WARNING","<font color = 'blak'>CAN NOT SAVE FILE</font>"+file.errorString());
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
    if(CurrentFile.isEmpty())
    {
        FileName= QFileDialog::getOpenFileName(this,"Save File");
        CurrentFile = FileName;
    }
    else{
        FileName = CurrentFile;
    }
    QFile file(FileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)){
        QMessageBox an;
        an.setStyleSheet("QPushButton{ color : red; }");
        an.warning(this,"WARNING","<font color = 'blak'>CAN NOT SAVE FILE</font>"+file.errorString());
        // QMessageBox::warning(this,"WARNING","<font color = 'blak'>CAN NOT SAVE FILE</font>"+file.errorString());
        return;
    }
    CurrentFile = FileName;
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

