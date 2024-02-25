#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPrinter>
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include <QApplication>
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

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triiggered();

    void on_actionSave_as_triggered();

    void on_actionPrint_triggered();

    void on_actionPrintPreview_triggered();

    void PrintPreview(QPrinter *);
    void on_actionExport_PDF_triggered();

private:
    Ui::MainWindow *ui;
    QString CurrentFile;
};
#endif // MAINWINDOW_H
