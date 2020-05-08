#include "gamescreen.h"
#include "ui_gamescreen.h"
#include <QMessageBox>

GameScreen::GameScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameScreen)
{
    ui->setupUi(this);
player_role = this->windowTitle();
    if (player_role == "RETAILER"){
    ui->incomingOrder->setText("4");}
    else
    {
        ui->incomingOrder->setText("6");
    }
    ui->inventory->setText(initial_inventory_ui);
}

GameScreen::GameScreen(QWidget *parent, Game *g, Player *p, ClientRequest *client) :
    QDialog(parent),
    ui(new Ui::GameScreen),
    my_game(g),
    my_player(p),
    client_socket(client)
{

    ui->setupUi(this);
    player_role = this->windowTitle();

    if (player_role == "RETAILER"){
    ui->incomingOrder->setText("4");}
    else
    {
        ui->incomingOrder->setText("6");
    }

ui->week->setText("1");
ui->incomingShipment->setText("0");
QString initial_inventory = QString::number(my_game->getStartingInventory());

ui->inventory->setText(initial_inventory);
ui->outgoingShipment->setText("0");
ui->backLog->setText("0");
ui->weekCost->setText("0.0");
ui->totalCost->setText("0.0");

}

GameScreen::~GameScreen()
{
    delete ui;
}

void GameScreen::on_player_order_clicked()
{


    bool ok;
    //Factory's input, place it orders
    //ui->enterOrder->setValidator(new QIntValidator(0, 100, this)); //validation
    QString orderText = ui->order_amount->text();

    QRegExp re("\\d*"); // a digit (\d), zero or more times (*)

    if ((orderText.isEmpty() == true) || (!re.exactMatch(orderText)) || (orderText.toInt(&ok, 10) < 0))
    {
        QMessageBox::information(this, "Empty Order", "Please enter a valid number");

    }
    else
    {
        //int outgoing_order = orderText.toInt(nullptr, 10);
        QString week_s = QString::number(player_week_in_game);
        client_socket->send_order(orderText, week_s);

        ui->player_order->setDisabled(true);


    }
}

Ui::GameScreen *GameScreen::getUi() const
{
    return ui;
}

void GameScreen::setUi(Ui::GameScreen *value)
{
    ui = value;
}

void GameScreen::setInitialInventory(QString inv)
{
    initial_inventory_ui = inv;
}

void GameScreen::enable_order_button()
{
    ui->player_order->setEnabled(true);
}

void GameScreen::update_ui_parameters(int inventory, int backlog, int incoming_order, int i_delivered, double week_cost, int i_received)
{
inventories.push_back(inventory);
backlogs.push_back(backlog);
demands.push_back(incoming_order);
delivered.push_back(i_delivered);
costs.push_back(week_cost);
total_cost += week_cost;
received.push_back(i_received);

QString inv, back, dem, del, cost, week, total_cost_s, received_s;
inv = QString::number(inventory);
back = QString::number(backlog);
dem = QString::number(incoming_order);
del = QString::number(i_delivered);
cost = QString::number(week_cost);
week = QString::number(player_week_in_game+1);
received_s = QString::number(i_received);
total_cost_s = QString::number(total_cost);

ui->inventory->setText(inv);
ui->backLog->setText(back);
ui->incomingOrder->setText(dem);
ui->outgoingShipment->setText(del);
ui->weekCost->setText(cost);
ui->week->setText(week);
ui->totalCost->setText(total_cost_s);
ui->incomingShipment->setText(received_s);

}

void GameScreen::set_vectors(vector<int> i_inventories, vector<int> i_backlogs, vector<int> i_demands, vector<int> i_delivered, vector<double> i_costs)
{
    inventories = i_inventories;
    backlogs = i_backlogs;
    demands = i_demands;
    delivered = i_delivered;
    costs = i_costs;


}

int GameScreen::getPlayer_week_in_game() const
{
    return player_week_in_game;
}

void GameScreen::setPlayer_week_in_game(int value)
{
    player_week_in_game = value;
}
