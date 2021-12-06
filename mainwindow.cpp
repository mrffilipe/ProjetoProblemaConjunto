#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,  ca(0)
    ,  cb(0)
{
    ui->setupUi(this);

    ui->lineEditConjuntoA->setEnabled(false);
    ui->lineEditConjuntoB->setEnabled(false);
    ui->lineEditElementoA->setEnabled(false);
    ui->pushButtonIncluirA->setEnabled(false);
    ui->pushButtonIncluirB->setEnabled(false);
    ui->lineEditElementoB->setEnabled(false);
}

MainWindow::~MainWindow()
{
    if(ca) delete ca;
    if(cb) delete cb;
    delete ui;
}

/*
* RASCUNHO QTableWidget
    itens = "É idêntico";
    item1 = new QTableWidgetItem(itens);
    linha = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(linha);
    ui->tableWidget->setItem(linha,0,item1);
*/

void MainWindow::setGridBool(QString nomeItem, bool conjA, bool conjB){
    QString strCA = "false";
    if(QString::number(conjA) == "1") strCA = "true";

    QString strCB = "false";
    if(QString::number(conjB) == "1") strCB = "true";

    QString vet[3] = {nomeItem, strCA, strCB};

    int linha = ui->tableWidgetGrid->rowCount();
    ui->tableWidgetGrid->insertRow(linha);

    for(int i = 0; i < 3; i++){
        QTableWidgetItem *item = 0;
        item = new QTableWidgetItem(vet[i]);
        ui->tableWidgetGrid->setItem(linha, i, item);
    } // *dúvida: deletar ponteiro? // *dúvida: trycatch?
}

void MainWindow::setGridNumber(QString nomeItem, float conjA, float conjB){
    QString strCA = QString::number(conjA);
    QString strCB = QString::number(conjB);

    QString vet[3] = {nomeItem, strCA, strCB};

    int linha = ui->tableWidgetGrid->rowCount();
    ui->tableWidgetGrid->insertRow(linha);

    for(int i = 0; i < 3; i++){
        QTableWidgetItem *item = 0;
        item = new QTableWidgetItem(vet[i]);
        ui->tableWidgetGrid->setItem(linha, i, item);
    } // *dúvida: deletar ponteiro? // *dúvida: trycatch?
}

/*
 * CRIAR A
*/
void MainWindow::on_pushButtonCriarA_clicked()
{
    try {
        int tamanho = ui->lineEditTamanhoA->text().toInt();
        ca = new minhaNamespace::Conjunto(tamanho);

        ui->lineEditTamanhoA->setEnabled(false);
        ui->pushButtonCriarA->setEnabled(false);
        ui->lineEditElementoA->setEnabled(true);
        ui->pushButtonIncluirA->setEnabled(true);
    }  catch (QString &erro) {
        QMessageBox::information(this, "Erro", erro);
        ui->lineEditTamanhoA->clear();
    }  catch (std::bad_alloc const&) {
        QMessageBox::information(this, "Erro", "Erro na alocação de memória!");
    }
}

/*
 * INCLUIR A
*/
void MainWindow::on_pushButtonIncluirA_clicked()
{
    try {
        ui->lineEditTamanhoA->setEnabled(false);
        ui->pushButtonCriarA->setEnabled(false);

        int elemento = ui->lineEditElementoA->text().toInt();
        ca->setElemento(elemento);

        ui->lineEditConjuntoA->setText(ca->getConjunto());

        ui->lineEditElementoA->clear();
    }  catch (QString &erro) {
        QMessageBox::information(this, "Erro", erro);
        ui->lineEditElementoA->clear();
    }
}

/*
 * CRIAR B
*/
void MainWindow::on_pushButtonCriarB_clicked()
{
    try {
        int tamanho = ui->lineEditTamanhoB->text().toInt();
        cb = new minhaNamespace::Conjunto(tamanho);

        ui->lineEditTamanhoB->setEnabled(false);
        ui->pushButtonCriarB->setEnabled(false);
        ui->lineEditElementoB->setEnabled(true);
        ui->pushButtonIncluirB->setEnabled(true);
    }  catch (QString &erro) {
        QMessageBox::information(this, "Erro", erro);
        ui->lineEditTamanhoB->clear();
    }  catch (std::bad_alloc const&) {
        QMessageBox::information(this, "Erro", "Erro na alocação de memória!");
    }
}

/*
 * INCLUIR B
*/
void MainWindow::on_pushButtonIncluirB_clicked()
{
    try {
        ui->lineEditTamanhoB->setEnabled(false);
        ui->pushButtonCriarB->setEnabled(false);

        int elemento = ui->lineEditElementoB->text().toInt();
        cb->setElemento(elemento);

        ui->lineEditConjuntoB->setText(cb->getConjunto());

        ui->lineEditElementoB->clear();
    }  catch (QString &erro) {
        QMessageBox::information(this, "Erro", erro);
        ui->lineEditElementoB->clear();
    }
}

/*
 * UNIÃO
*/
void MainWindow::on_pushButtonUniao_clicked()
{
    try {
        minhaNamespace::Conjunto *aux = ca->uniao(cb);
        ui->lineEditConjuntoResultante->setText(aux->getConjunto());
        delete aux;
    }  catch (QString &erro) {
        QMessageBox::information(this, "Erro", erro);
    }
}

/*
 * INTERSECAO
*/
void MainWindow::on_pushButtonIntersecao_clicked()
{
    try {
        minhaNamespace::Conjunto *aux = ca->intersecao(cb);
        ui->lineEditConjuntoResultante->setText(aux->getConjunto());
        delete aux;
    }  catch (QString &erro) {
        QMessageBox::information(this, "Erro", erro);
    }
}

/*
 * DIFERENCA AB
*/
void MainWindow::on_pushButtonDiferencaAB_clicked()
{
    try {
        minhaNamespace::Conjunto *aux = ca->diferenca(cb);
        ui->lineEditConjuntoResultante->setText(aux->getConjunto());
        delete aux;
    }  catch (QString &erro) {
        QMessageBox::information(this, "Erro", erro);
    }
}

/*
 * DIFERENCA BA
*/
void MainWindow::on_pushButtonDiferencaBA_clicked()
{
    try {
        minhaNamespace::Conjunto *aux = cb->diferenca(ca);
        ui->lineEditConjuntoResultante->setText(aux->getConjunto());
        delete aux;
    }  catch (QString &erro) {
        QMessageBox::information(this, "Erro", erro);
    }
}

/*
 * GRID
*/
void MainWindow::on_pushButtonGrid_clicked()
{
    setGridBool("Vazio", ca->eVazio(), cb->eVazio());
    setGridBool("Sub Conjunto", ca->eSubConjunto(cb), cb->eSubConjunto(ca));
    setGridBool("Idêntico", ca->eIdentico(cb), cb->eIdentico(ca));
    setGridBool("Disjunto", ca->eDisjunto(cb), cb->eDisjunto(ca));
    setGridNumber("Amplitude", ca->calcularAmplitude(), cb->calcularAmplitude());
    setGridNumber("Média aritmética", ca->calcularMediaAritmetica(), cb->calcularMediaAritmetica());
}
