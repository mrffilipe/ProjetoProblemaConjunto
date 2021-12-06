#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <conjunto.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonCriarA_clicked();

    void on_pushButtonIncluirA_clicked();

    void on_pushButtonCriarB_clicked();

    void on_pushButtonIncluirB_clicked();

    void on_pushButtonUniao_clicked();

    void on_pushButtonIntersecao_clicked();

    void on_pushButtonDiferencaAB_clicked();

    void on_pushButtonDiferencaBA_clicked();

    void on_pushButtonGrid_clicked();

    void setGridNumber(QString nomeItem, float conjA, float conjB);

    void setGridBool(QString nomeItem, bool conjA, bool conjB);

private:
    Ui::MainWindow *ui;
    minhaNamespace::Conjunto *ca;
    minhaNamespace::Conjunto *cb;
};
#endif // MAINWINDOW_H
