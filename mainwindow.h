#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QMessageBox>
#include <QVector>
#include <QHash>
#include <QString>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTimer *timer = new QTimer();
    QTime time;
    int remainingPairs;
    QMessageBox msgBox;
    QVector<QString> cards{"card01", "card02", "card03",
                           "card04", "card05", "card06",
                           "card07", "card08", "card09",
                           "card10", "card11", "card12"};
    QHash<QString, QString> distribution;
    int score;
    bool init_game;
    QPushButton* cardPrev;
    QPushButton* cardCurr;

private slots:
    void updateState();
    void updateChrono();
    void finalResult();
    void partialResult();
    void initializeGame();
    void discoverdCard();
    void shuffler();
    void distribute();
    void showImage();
    void reinitCard();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
