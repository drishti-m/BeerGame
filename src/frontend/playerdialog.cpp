#include "../backend/player.h"

#include "playerdialog.h"
#include "ui_playerdialog.h"
#include "clientrequest.h"
#include <QMessageBox>
#include <QPixmap>
#include <string>

#define RETAILER 1
#define WHOLESALER 2
#define DISTRIBUTOR 3
#define FACTORY 4
void PlayerDialog::setChooseImages()
{

    QPixmap retailer(":/resources/images/retailer.png");
    ui->label_retailer->setPixmap(retailer.scaled(100, 100, Qt::KeepAspectRatio));

    QPixmap wholesaler(":/resources/images/wholesaler.png");
    ui->label_wholesaler->setPixmap(wholesaler.scaled(100, 100, Qt::KeepAspectRatio));

    QPixmap distributor(":/resources/images/distributor.png");
    ui->label_distributor->setPixmap(distributor.scaled(100, 100, Qt::KeepAspectRatio));

    QPixmap factory(":/resources/images/factory.png");
    ui->label_factory->setPixmap(factory.scaled(100, 100, Qt::KeepAspectRatio));
}

ClientRequest *PlayerDialog::getClient() const
{
    return client;
}

void PlayerDialog::setClient(ClientRequest *value)
{
    client = value;
}

void PlayerDialog::show_messageBox_to_Player(QString title, QString body)
{
    QMessageBox::information(this, title, body);
}

void PlayerDialog::enable_role_buttons(bool val)
{
    if (val == true)
    {
        ui->retailer_btn->setEnabled(true);
        ui->wholesaler_btn->setEnabled(true);
        ui->distributor_btn->setEnabled(true);
        ui->factory_btn->setEnabled(true);
    }
    else
    {
        ui->retailer_btn->setEnabled(false);
        ui->wholesaler_btn->setEnabled(false);
        ui->distributor_btn->setEnabled(false);
        ui->factory_btn->setEnabled(false);
    }
}

PlayerDialog::PlayerDialog(QWidget *parent, Game &game, Player *player) : QDialog(parent),
                                                                          ui(new Ui::PlayerDialog),
                                                                          game(game),
                                                                          player(player)
{
    ui->setupUi(this);
    //  connect(ui->joinGame, SIGNAL(clicked()), this, SLOT(on_joinGame_clicked()));

    setPlayerUI();
    setChooseImages();
    //ui->stackedWidget->setCurrentIndex(0);
}

PlayerDialog::PlayerDialog(QWidget *parent, Game &game, std::vector<Player *> allPlayers) : QDialog(parent),
                                                                                            ui(new Ui::PlayerDialog),
                                                                                            game(game),
                                                                                            allPlayers(allPlayers)
{

    ui->setupUi(this);

    setChooseImages();
    //ui->stackedWidget->setCurrentIndex(0);
}

PlayerDialog::~PlayerDialog()
{
    delete ui;
}

void PlayerDialog::setPlayerUI()
{
    player->setUi(ui);
}

void PlayerDialog::on_retailer_btn_clicked()
{

    player->setRole(1);
    game.setPRetailerId(1);
    connection = client->getTcpServerConnection();
    connection->write("Retailer chosen");

    /*QMessageBox::information(this, "Wait",
                                 "Waiting for other the Players to join and start the game.");*/

    ui->retailer_btn->setDisabled(true); //1
}

void PlayerDialog::on_wholesaler_btn_clicked()
{

    player->setRole(2);
    game.setPWholesalerId(1);
    QTcpSocket *connection = client->getTcpServerConnection();
    connection->write("Wholesaler chosen");
    /*QMessageBox::information(this, "Wait",
                                 "Waiting for other the Players to join and start the game.");
        ui->retailer_btn->setDisabled(true); //2
        ui->distributor_btn->setDisabled(true); //3
        ui->factory_btn->setDisabled(true); //4 */

    ui->wholesaler_btn->setDisabled(true); //1
}

void PlayerDialog::on_distributor_btn_clicked()
{

    player->setRole(3);
    game.setPDistributorId(1);
    /*
        QMessageBox::information(this, "Wait",
                                 "Waiting for other the Players to join and start the game.");
        ui->retailer_btn->setDisabled(true); //2
        ui->wholesaler_btn->setDisabled(true); //3
        ui->factory_btn->setDisabled(true); //4 */
    QTcpSocket *connection = client->getTcpServerConnection();
    connection->write("Distributor chosen");

    ui->distributor_btn->setDisabled(true); //1
}

void PlayerDialog::on_factory_btn_clicked()
{

    player->setRole(3);
    game.setPFactId(1);

    /*
        QMessageBox::information(this, "Wait",
                                 "Waiting for other the Players to join and start the game.");
        ui->retailer_btn->setDisabled(true); //2
        ui->wholesaler_btn->setDisabled(true); //3
        ui->distributor_btn->setDisabled(true); //4
    */
    QTcpSocket *connection = client->getTcpServerConnection();
    connection->write("Factory chosen");
    ui->factory_btn->setDisabled(true); //1
}
/*
void PlayerDialog::on_player_order_clicked()
{
    QString numberOfBeers = ui-> order_amount->text();
    ui->player_order->setEnabled(false);
    player->placeOrder(numberOfBeers.toInt());
    player->placeShipment(player->getOutgoingShipment());

    //    player->processOrder(numberOfBeers.toInt());

}
*/
Player *PlayerDialog::getPlayer() const
{
    return player;
}

void PlayerDialog::setPlayer(Player *value)
{
    player = value;
}

//for now, client can join the server only once
/*
void PlayerDialog::on_joinGame_clicked()
{

    ui->stackedWidget->setCurrentIndex(0);
    // QMessageBox::information(this,"Choose Game", "Sorry not implemented yet");
    //client = new ClientRequest(this, game, player);
    ui->joinGame->setDisabled(true);

    //client->show();
    //client->move(1000,0);



}*/

Ui::PlayerDialog *PlayerDialog::getUi() const
{
    return ui;
}

void PlayerDialog::setUi(Ui::PlayerDialog *value)
{
    ui = value;
}
