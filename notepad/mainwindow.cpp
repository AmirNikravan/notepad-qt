#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionSave,SIGNAL(triggered(bool)),this,SLOT(on_actionSave_triiggered()));
    connect(ui->actionPrint,&QAction::triggered,this,&MainWindow::on_actionPrint_triggered);
    connect(ui->actionPrint_Preview,&QAction::triggered,this,&MainWindow::on_actionPrintPreview_triggered);
    connect(ui->actionExit,&QAction::triggered,this,&QApplication::quit);
    connect(ui->actionExport_PDF,&QAction::triggered,this,&MainWindow::on_actionExport_PDF_triggered);
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

void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;
    QPrintDialog dialog(&printer,this);
    if(dialog.exec() == QDialog::Rejected){
        return;

    }
    ui->textEdit->print(&printer);
}

void MainWindow::on_actionPrintPreview_triggered()
{
    QPrinter printer(QPrinter::HighResolution);
    QPrintPreviewDialog preview(&printer,this);
    preview.setWindowFlags(Qt::Window);
    connect(&preview,SIGNAL(paintRequested(QPrinter*)),SLOT(PrintPreview(QPrinter *)));
    preview.exec();
}

void MainWindow::PrintPreview(QPrinter *printer)
{
    ui->textEdit->print(printer);
}


void MainWindow::on_actionExport_PDF_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this,"export pdf");
    if (filename != ' '){
        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(filename);
        ui->textEdit->document()->print(&printer);
    }
}


void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}


void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}


void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_actionBold_triggered()
{
    QFont font;
    font.setBold(true);
    ui->textEdit->setFont(font);
}


void MainWindow::on_actionItalic_triggered()
{
    QFont font;
    font.setItalic(true);
    ui->textEdit->setFont(font);

}


void MainWindow::on_actionUnderline_triggered()
{
    ui->textEdit->setFontUnderline(true);
}


void MainWindow::on_actionLeft_triggered()
{
    ui->textEdit->setAlignment(Qt::AlignmentFlag::AlignLeft);
}


void MainWindow::on_actionRight_triggered()
{
    ui->textEdit->setAlignment(Qt::AlignmentFlag::AlignRight);
}


void MainWindow::on_actionCenter_triggered()
{
    ui->textEdit->setAlignment(Qt::AlignmentFlag::AlignCenter);
}


void MainWindow::on_actionJustify_triggered()
{
    ui->textEdit->setAlignment(Qt::AlignmentFlag::AlignJustify);
}

