#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix(":/resources/images/beergame.png");
    QPixmap cover(":/resources/images/cover.png");
    ui->label_logo->setPixmap(pix.scaled(200,180, Qt::KeepAspectRatio));
    ui->label_cover->setPixmap(cover.scaled(820,820, Qt::KeepAspectRatio));
    ui->lineEdit_useremail->setText("test");
    ui->lineEdit_password->setText("1234");
    // ui->checkBox_isInstructor->setCheckState(Qt::Checked);
}

MainWindow::~MainWindow()
{
    delete ui;
}
/*
void MainWindow::playerGame()
{

    Game* newgame = new Game(1,1,1,1,1,1,1);

    Player* retailer = new Player(newgame, RETAILER);

    newgame->addPlayer(retailer);

    // Creating the player dialogs for the ui
    std::vector<Player*> allPlayers {retailer};//, retailer, wholesaler, distributor, factory};

    myplayer = new PlayerDialog(this, *newgame, retailer);
    myplayer->move(1000,0);
    myplayer->show();
    PlayerDialog* R = new PlayerDialog(this, *newgame, allPlayers);
  PlayerDialog* W = new PlayerDialog(this,*newgame, allPlayers);
  PlayerDialog* D = new PlayerDialog(this,*newgame, allPlayers);
  PlayerDialog* F = new PlayerDialog(this,*newgame, allPlayers);


  W->move(1000,0);



}
*/

void MainWindow::on_pushButton_Login_clicked()
{
    QString username = ui->lineEdit_useremail->text();
    QString password = ui->lineEdit_password->text();
    bool isInstructor = ui->checkBox_isInstructor->checkState();
    bool isPlayer = ui->checkBox_isPlayer->checkState();

    if ((isInstructor && isPlayer) || (!isInstructor && !isPlayer))
    {
        QMessageBox::warning(this, "Only one option", "Please check exactly one option");
        return;
    }

    if(username == "test" && password =="1234" && isInstructor){
        QMessageBox::information(this,"Instructor Login", "Username and Password is correct");
        hide();
        Instructor *instructor = new Instructor();
        /*
        instructor->setInstrEmail(username);
        instructor->setInstrPassword(password);
        */
        id = new InstructorDialog(this, instructor);
        id->show();
        id->move(0,0);
    }else if (username == "test" && password =="1234" && isPlayer){
        // QMessageBox::information(this,"Player Login", "Try as a instructor. Player login under construction");
        hide();
        Player *player = new Player();

        cr = new ClientRequest(this, player);
        cr->show();
        cr->move(0,0);       
    }else
    {
        QMessageBox::warning(this,"Login", "Username and password is not correct");
    }
}
