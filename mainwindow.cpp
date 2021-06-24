#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCoreApplication>
#include <random>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateState()));
    connect(ui->card01, SIGNAL(clicked()), this, SLOT(discoverdCard()));
    connect(ui->card02, SIGNAL(clicked()), this, SLOT(discoverdCard()));
    connect(ui->card03, SIGNAL(clicked()), this, SLOT(discoverdCard()));
    connect(ui->card04, SIGNAL(clicked()), this, SLOT(discoverdCard()));
    connect(ui->card05, SIGNAL(clicked()), this, SLOT(discoverdCard()));
    connect(ui->card06, SIGNAL(clicked()), this, SLOT(discoverdCard()));
    connect(ui->card07, SIGNAL(clicked()), this, SLOT(discoverdCard()));
    connect(ui->card08, SIGNAL(clicked()), this, SLOT(discoverdCard()));
    connect(ui->card09, SIGNAL(clicked()), this, SLOT(discoverdCard()));
    connect(ui->card10, SIGNAL(clicked()), this, SLOT(discoverdCard()));
    connect(ui->card11, SIGNAL(clicked()), this, SLOT(discoverdCard()));
    connect(ui->card12, SIGNAL(clicked()), this, SLOT(discoverdCard()));
    initializeGame();
}

void MainWindow::finalResult(){
    msgBox.setWindowTitle("Game finished");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    msgBox.setEscapeButton(QMessageBox::No);

    if(remainingPairs == 0){
        timer->stop();
        msgBox.setText("You win! Final score:" + QString::number(score) + "\nPlay again?");
        if(QMessageBox::Yes == msgBox.exec()){
            initializeGame();
        }
        else{
            QCoreApplication::quit();
        }
    }
    else{
        if(time.toString() == "00:00:00"){
            timer->stop();
            ui->frame->setEnabled(false);
            msgBox.setText("You lose! Play again?");
            if(QMessageBox::Yes == msgBox.exec()){
                initializeGame();
            }
            else{
                QCoreApplication::quit();
            }
        }
    }
}

void MainWindow::initializeGame(){
    init_game = false;
    score = 0;
    ui->lbl_score->setText(QString::number(score));
    remainingPairs = 6;
    time.setHMS(0, 1, 0);
    ui->chrono->setText(time.toString("m:ss"));
    timer->start(1000);
    shuffler();
    distribute();
    ui->frame->setEnabled(true);
    QList<QPushButton*> buttons = ui->centralwidget->findChildren<QPushButton*>();
    foreach(QPushButton* b, buttons){
        b->setEnabled(true);
        b->setStyleSheet("#" + b->objectName() + "{}");
    }
}

void MainWindow::discoverdCard(){
    cardCurr = qobject_cast<QPushButton*>(sender());
    showImage();
    cardCurr->setEnabled(false);

    if(!init_game){
        cardPrev = cardCurr;
        init_game = true;
    }
    else{
        partialResult();
        init_game = false;
    }
}

void MainWindow::showImage(){
    QString card_name = cardCurr->objectName();
    QString img = distribution[card_name];
    cardCurr->setStyleSheet("#" + card_name + "{background-image:url(://" + img + ")}");
}

void MainWindow::partialResult(){
    if(distribution[cardCurr->objectName()] == distribution[cardPrev->objectName()]){
        score += 15;
        ui->lbl_score->setText(QString::number(score));
        remainingPairs--;
        finalResult();
    }
    else{
        score -= 5;
        ui->lbl_score->setText(QString::number(score));
        ui->frame->setEnabled(false);
        QTimer::singleShot(1000, this, SLOT(reinitCard()));
    }
}

void MainWindow::reinitCard(){
    cardCurr->setStyleSheet("#" + cardCurr->objectName() + "{}");
    cardPrev->setStyleSheet("#" + cardPrev->objectName() + "{}");
    cardCurr->setEnabled(true);
    cardPrev->setEnabled(true);
    ui->frame->setEnabled(true);
}

void MainWindow::updateChrono(){
    time = time.addSecs(-1);
    ui->chrono->setText(time.toString("m:ss"));
}

void MainWindow::updateState(){
    updateChrono();
    finalResult();
}

void MainWindow::shuffler(){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(cards.begin(), cards.end(), std::default_random_engine(seed));
}

void MainWindow::distribute(){
    auto iterator = cards.begin();
    for(int i = 1; i <= 6; i++){
        QString file_name = "image" + QString::number(i) + ".png";
        distribution[(*iterator)] = file_name;
        iterator++;
        distribution[(*iterator)] = file_name;
        iterator++;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

