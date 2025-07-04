#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMessageBox>
#include <QTime>
#include <QScreen>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlQuery>

#define MAIN_SIZE 500, 160
#define PLAY_SIZE 780, 460
#define SCORE_SIZE 780, 460
#define MAIN_PAGE 1
#define PLAY_PAGE 0
#define SCORE_PAGE 2
#define EASY_LV 15
#define NORMAL_LV 12
#define DIFFICULT_LV 10
#define HELL_LV 8


QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    QString answer;
    QString com;
    QString user_name;
    int round_chance;
    int round;
    int result[2];
    QList<QStringList> results;
    QList<int> levels = {EASY_LV, NORMAL_LV, DIFFICULT_LV, HELL_LV};
    QTime start_time;
    int playtime;
    void dbSetting();
    void uiSetting();
    void connectSetting();
    void shortcutSetting();
    void setMainWidgetSize();
    void setPlayWidgetSize();
    void setScoreWidgetSize();
    void setLvComboBox();
    void tableWidegtColumnStrech();
    void toMainWidget();
    void toPlayWidget();
    void toScoreWidget();
    void playInitialize();
    void roundInitialize();
    void winLoseCheck();
    void resultToDB(bool wl);
    void setScoreTable();
    void makeResult();
    void setResultToTable();
    void randomCom();
    void checkAnswer();
    bool checkNumber(int num);
    void resetBtn();
    void numberBtnClicked(int num);
    void clearCheck();
    void clearBtnClicked();
    void submitCheck();
    void submitBtnClicked();
    void retireBtnClicked();
    void backBtnClicked();
    ~Widget();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
