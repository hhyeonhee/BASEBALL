#include "widget.h"
#include "ui_widget.h"



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->uiSetting();
    this->connectSetting();
    this->shortcutSetting();
    this->dbSetting();
}

void Widget::dbSetting() {
    this->db.setHostName("10.10.20.95");
    this->db.setDatabaseName("test");
    this->db.setPort(3306);
    this->db.setUserName("test");
    this->db.setPassword("1234");
}

void Widget::uiSetting() {
    this->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int x = screenGeometry.x() + (screenGeometry.width() - this->width()) / 2;
    int y = screenGeometry.y() + (screenGeometry.height() - this->height()) / 2;
    this->move(x, y);
    this->tableWidegtColumnStrech();
    ui->stackedWidget->setCurrentIndex(1);
    this->setMainWidgetSize();
    this->setLvComboBox();
}

void Widget::connectSetting() {
    connect(ui->pushButton_start, &QPushButton::clicked, this, &Widget::toPlayWidget);
    connect(ui->pushButton_score, &QPushButton::clicked, this, &Widget::toScoreWidget);
    connect(ui->pushButton_exit, &QPushButton::clicked, this, &Widget::close);
    connect(ui->pushButton_retire, &QPushButton::clicked, this, &Widget::retireBtnClicked);
    QList<QPushButton*> buttonList = ui->frame_btn->findChildren<QPushButton*>();
    std::sort(buttonList.begin(), buttonList.end(), [](QPushButton *a, QPushButton *b) {return a->objectName() < b->objectName();});
    for (int i=0;i<buttonList.size();i++) {
        connect(buttonList[i], &QPushButton::clicked, this, [this, i](){this->numberBtnClicked(i);});
    }
    connect(ui->textEdit, &QTextEdit::textChanged, this, &Widget::clearCheck);
    connect(ui->pushButton_clear, &QPushButton::clicked, this, &Widget::clearBtnClicked);
    connect(ui->textEdit, &QTextEdit::textChanged, this, &Widget::submitCheck);
    connect(ui->pushButton_submit, &QPushButton::clicked, this, &Widget::submitBtnClicked);
    connect(ui->pushButton_back, &QPushButton::clicked, this, &Widget::backBtnClicked);
    connect(ui->pushButton_search, &QPushButton::clicked, this, &Widget::setScoreTable);
}

void Widget::shortcutSetting() {
    QList<QPushButton*> buttonList = ui->frame_btn->findChildren<QPushButton*>();
    std::sort(buttonList.begin(), buttonList.end(), [](QPushButton *a, QPushButton *b) {return a->objectName() < b->objectName();});
    for (int i=0;i<buttonList.size();i++) {
        buttonList[i]->setShortcut(QString::number(i));
    }
    ui->pushButton_clear->setShortcut(Qt::Key_Backspace);
    ui->pushButton_submit->setShortcut(Qt::Key_Enter);
    ui->pushButton_retire->setShortcut(Qt::Key_Escape);
}

void Widget::setMainWidgetSize() {
    this->setMaximumSize(QSize(MAIN_SIZE));
    this->setMinimumSize(QSize(MAIN_SIZE));
    this->resize(QSize(MAIN_SIZE));
}

void Widget::setPlayWidgetSize() {
    this->setMaximumSize(QSize(PLAY_SIZE));
    this->setMinimumSize(QSize(PLAY_SIZE));
    this->resize(QSize(PLAY_SIZE));
}

void Widget::setScoreWidgetSize() {
    this->setMaximumSize(QSize(SCORE_SIZE));
    this->setMinimumSize(QSize(SCORE_SIZE));
    this->resize(QSize(SCORE_SIZE));
}

void Widget::setLvComboBox() {
    ui->comboBox_level->clear();
    ui->comboBox_level->addItem(QString("Easy(Chance: ") + QString::number(this->levels[0]) + ")");
    ui->comboBox_level->addItem(QString("Normal(Chance: ") + QString::number(this->levels[1]) + ")");
    ui->comboBox_level->addItem(QString("Difficult(Chance: ") + QString::number(this->levels[2]) + ")");
    ui->comboBox_level->addItem(QString("Hell(Chance: ") + QString::number(this->levels[3]) + ")");
}

void Widget::tableWidegtColumnStrech() {
    QHeaderView* header = ui->tableWidget_score->horizontalHeader();
    header->setSectionResizeMode(0, QHeaderView::Stretch);
    for (int i=1;i<4;i++) {
        header->setSectionResizeMode(i, QHeaderView::Fixed);
        ui->tableWidget_score->setColumnWidth(i, 80);
    }

    QHeaderView* header2 = ui->tableWidget_search->horizontalHeader();
    header2->setSectionResizeMode(0, QHeaderView::Stretch);
    header2->setSectionResizeMode(3, QHeaderView::Stretch);
    header2->setSectionResizeMode(4, QHeaderView::Stretch);
    header2->setSectionResizeMode(1, QHeaderView::Fixed);
    ui->tableWidget_search->setColumnWidth(1, 80);
    header2->setSectionResizeMode(2, QHeaderView::Fixed);
    ui->tableWidget_search->setColumnWidth(2, 120);
}

void Widget::toMainWidget() {
    this->setMainWidgetSize();
    ui->stackedWidget->setCurrentIndex(MAIN_PAGE);
}

void Widget::toPlayWidget() {
    this->setPlayWidgetSize();
    ui->stackedWidget->setCurrentIndex(PLAY_PAGE);
    this->playInitialize();
}

void Widget::toScoreWidget() {
    this->setScoreWidgetSize();
    ui->stackedWidget->setCurrentIndex(SCORE_PAGE);
    this->setScoreTable();
}

void Widget::playInitialize() {
    if (ui->lineEdit->text() != "") {
        this->user_name = ui->lineEdit->text();
    } else {
        this->user_name = "Player_Unknown";
        ui->lineEdit->setText("Player_Unknown");
    }
    this->round_chance = levels[ui->comboBox_level->currentIndex()];
    this->round = 1;
    this->randomCom();
    this->result[0] = 0;
    this->result[1] = 0;
    this->start_time = QTime::currentTime();
    ui->textEdit->setPlaceholderText(QString::number(this->round_chance) + "Left");
    ui->pushButton_clear->setDisabled(true);
    ui->pushButton_submit->setDisabled(true);
    ui->tableWidget_score->clearContents();
}

void Widget::roundInitialize() {
    this->checkAnswer();
    this->makeResult();
    this->setResultToTable();
    ui->textEdit->setPlaceholderText(QString::number(this->round_chance - this->round) + "Laft");
    this->round++;
    this->winLoseCheck();
    this->result[0] = 0;
    this->result[1] = 0;
}

void Widget::randomCom() {
    while (this->com.size() < 3) {
        int num = rand() % 10;
        QString num_ = QString::number(num);
        if (!this->com.contains(num_)) this->com.append(num_);
    }
}

void Widget::checkAnswer() {
    for (int i=0;i<3;i++) {
        if (this->com.contains(this->answer[i])) {
            if (this->com[i] == this->answer[i]) {
                this->result[0]++;
                continue;
            }
            this->result[1]++;
        }
    }
}

void Widget::winLoseCheck() {
    this->playtime = this->start_time.secsTo(QTime::currentTime());
    if (this->result[0] == 3) {
        QMessageBox::information(this, "Win!", "You're Win! Collect Answer is '" + this->com + "'!!");
        this->resultToDB(1);
        this->toMainWidget();
    } else if ((this->result[0] == 0) && (this->result[1] == 0)) {
        QMessageBox::information(this, "result", "Out!!!");
    } else {
        QString msg = "";
        if (this->result[0] >= 1) {
            msg += QString::number(this->result[0]) + " Strike!! ";
        }
        if (this->result[1] >= 1) {
            msg += QString::number(this->result[1]) + " Ball!!";
        }
        QMessageBox::information(this, "result", msg);
    }
    if (this->round > this->round_chance) {
        QMessageBox::critical(this, "Lose...", "You're Lose... Collect Answer is '" + this->com + "'...");
        this->resultToDB(0);
        this->toMainWidget();
    }
}

void Widget::resultToDB(bool wl) {
    db.open();
    QTime duration(0, 0, 0);
    duration = duration.addSecs(this->playtime);

    // QSqlQuery를 통한 삽입
    QSqlQuery query(db);
    query.prepare(R"(
    INSERT INTO baseball_result (user, win_lose, lv, start_time, play_time)
    VALUES (:name, :win, :lv, :start_time, :duration))");

    query.bindValue(":name", this->user_name);
    query.bindValue(":win", wl);
    query.bindValue(":lv", ui->comboBox_level->currentIndex());
    query.bindValue(":start_time", QDateTime::currentDateTime());
    query.bindValue(":duration", duration.toString("HH:mm:ss"));

    query.exec();
    db.close();
}

void Widget::setScoreTable() {
    db.open();
    QSqlQuery query;
    if (ui->lineEdit_search->text() == "") {
        query = QSqlQuery("SELECT * FROM baseball_result", db);
    } else {
        QString q = "SELECT * FROM baseball_result where user like '%" + ui->lineEdit_search->text() + "%'";
        query = QSqlQuery(q, db);
    }

    ui->tableWidget_search->clearContents();
    ui->tableWidget_search->setRowCount(0);
    ui->tableWidget_search->setColumnCount(query.record().count()-1);

    int row = 0;
    while (query.next()) {
        ui->tableWidget_search->insertRow(row);

        QString name = query.value("user").toString();
        bool win = query.value("win_lose").toBool();
        int lv = query.value("lv").toInt();
        QDateTime start = query.value("start_time").toDateTime();
        QString duration = query.value("play_time").toString();  // TIME 형은 문자열로 처리됨

        QTableWidgetItem* tmp_name = new QTableWidgetItem(name);
        tmp_name->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_search->setItem(row, 0, tmp_name);

        QTableWidgetItem* tmp_win_lose = new QTableWidgetItem(win ? "Win" : "Lose");
        tmp_win_lose->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_search->setItem(row, 2, tmp_win_lose);

        QTableWidgetItem* tmp_lv;
        switch (lv) {
            case 0:
                tmp_lv = new QTableWidgetItem("Easy");
                break;
            case 1:
                tmp_lv = new QTableWidgetItem("Normal");
                break;
            case 2:
                tmp_lv = new QTableWidgetItem("Difficult");
                break;
            case 3:
                tmp_lv = new QTableWidgetItem("Hell");
                break;
        }
        tmp_lv->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_search->setItem(row, 1, tmp_lv);

        QTableWidgetItem* tmp_start = new QTableWidgetItem(start.toString("yyyy-MM-dd HH:mm:ss"));
        tmp_start->setTextAlignment(Qt::AlignCenter);

        ui->tableWidget_search->setItem(row, 3, tmp_start);

        QTableWidgetItem* tmp_play = new QTableWidgetItem(duration);
        tmp_play->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_search->setItem(row, 4, tmp_play);

        row++;
    }
    db.close();
}

void Widget::makeResult() {
    QStringList tmp;
    if ((this->result[0] == 0) && (this->result[1] == 0)) {
        tmp.append(this->answer);
        tmp.append("-");
        tmp.append("-");
        tmp.append("out!");
    } else {
        tmp.append(this->answer);
        tmp.append(QString::number(this->result[0]));
        tmp.append(QString::number(this->result[1]));
        tmp.append("-");
    }
    this->results.append(tmp);
}

void Widget::setResultToTable() {
    ui->tableWidget_score->clearContents();
    ui->tableWidget_score->setRowCount(this->results.size());
    ui->tableWidget_score->setColumnCount(this->results.first().size());

    for (int i = 0; i < this->results.size(); i++) {
        const QStringList &row = this->results[i];
        for (int col = 0; col < row.size(); ++col) {
            QTableWidgetItem* it = new QTableWidgetItem(row[col]);
            it->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_score->setItem(i, col, it);
        }
    }
}

bool Widget::checkNumber(int num) {
    if (this->answer.size() < 3) {
        if (this->answer.contains(QString::number(num))) return false;
        else return true;
    }
    return false;
}

void Widget::resetBtn() {
    QList<QPushButton*> buttonList = ui->frame_btn->findChildren<QPushButton*>();
    std::sort(buttonList.begin(), buttonList.end(), [](QPushButton *a, QPushButton *b) {
        return a->objectName() < b->objectName();
    });
    for (int i=0;i<buttonList.size();i++) {
        buttonList[i]->setEnabled(1);
    }
}

void Widget::numberBtnClicked(int num) {
    if (this->checkNumber(num)) {
        this->answer += QString::number(num);
        ui->textEdit->setText(this->answer);
        QObject *obj = sender();
        QPushButton *btn = qobject_cast<QPushButton*>(obj);
        btn->setDisabled(1);
    }
}

void Widget::clearCheck() {
    if (ui->textEdit->toPlainText().size() == 0) {
        ui->pushButton_clear->setDisabled(true);
    } else ui->pushButton_clear->setEnabled(true);
}

void Widget::clearBtnClicked() {
    this->answer.clear();
    ui->textEdit->setText(this->answer);
    this->resetBtn();
}

void Widget::submitCheck() {
    if (ui->textEdit->toPlainText().size() < 3) {
        ui->pushButton_submit->setDisabled(true);
    } else{
        for (int i=0;i<this->results.size();i++) {
            if (this->results[i][0] == ui->textEdit->toPlainText()) {
                return;
            }
        }
        ui->pushButton_submit->setEnabled(true);
    }
}

void Widget::submitBtnClicked() {
    this->roundInitialize();
    this->answer.clear();
    ui->textEdit->setText(this->answer);
    this->resetBtn();
}

void Widget::retireBtnClicked() {
    QMessageBox::StandardButton re;
    re = QMessageBox::question(this, "Confirm", "Are you really giving up? This round will be recorded as a loss.",
                                  QMessageBox::Yes | QMessageBox::No);
    if (re == QMessageBox::Yes) {
        this->resultToDB(0);
        this->toMainWidget();
    }
}

void Widget::backBtnClicked() {
    this->toMainWidget();
}

Widget::~Widget()
{
    delete ui;
}
