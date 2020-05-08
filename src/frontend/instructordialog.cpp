#include "instructordialog.h"
#include "ui_instructordialog.h"

#include "../backend/game.h"
#include "../backend/player.h"
#include "playerdialog.h"
#include "../backend/instructor.h"
#include "chooseserver.h"

#include <QDoubleValidator>
#include <QIntValidator>
#include <QPixmap>
#include <QMessageBox>

InstructorDialog::InstructorDialog(QWidget *parent, Instructor *instructor) :
    QDialog(parent),
    ui(new Ui::InstructorDialog),
    instructor(instructor)
{
    ui->setupUi(this);
    this->parent = parent;
    
    ui->instructor_backlogCost->setValidator(new QDoubleValidator(0, 100, 2, this));
    ui->instructor_holdingCost->setValidator(new QDoubleValidator(0, 100, 2, this));
    ui->instructor_orderDelay->setValidator(new QIntValidator(1,100,this));
    ui->instructor_totalWeeks->setValidator(new QIntValidator(1,80,this));
    ui->instructor_startInventory->setValidator(new QIntValidator(1,1000,this));
    ui->instructor_factoryDelay->setValidator(new QIntValidator(1,100,this));
}

InstructorDialog::~InstructorDialog()
{
    delete ui;
}


bool InstructorDialog::validation_check()
{
    bool validation_successful;
    QRegExp re("\\d*");


    if ((!re.exactMatch(ui->instructor_orderDelay->text())) || (!re.exactMatch(ui->instructor_shipmentDelay->text()))|| (!re.exactMatch(ui->instructor_startInventory->text())) || (!re.exactMatch(ui->instructor_totalWeeks->text()) || (!re.exactMatch(ui->instructor_factoryDelay->text()))))
    {

        QMessageBox::warning(this, "Invalid Input", "Please enter only integers");

        return false;
    }

    ui->instructor_holdingCost->text().toDouble(&validation_successful);

    if (validation_successful == false)
    {
        QMessageBox::warning(this, "Invalid Input", "Please enter positive double for holding cost");
        return false;
    }

    ui->instructor_backlogCost->text().toDouble(&validation_successful);
    if (validation_successful == false)
    {
        QMessageBox::warning(this, "Invalid Input", "Please enter positive double for backlog cost");
        return false;
    }


    double backlogCost = ui->instructor_backlogCost->text().toDouble();
    double holdingCost = ui->instructor_holdingCost->text().toDouble();
    int orderDelay = ui->instructor_orderDelay->text().toInt();
    int totalWeeks = ui->instructor_totalWeeks->text().toInt();
    int startInventory = ui->instructor_startInventory->text().toInt();
    int factoryDelay = ui->instructor_factoryDelay->text().toInt();
int shipmentDelay = ui->instructor_shipmentDelay->text().toInt();

    if (totalWeeks < 0)
    {
        QMessageBox::warning(this, "Invalid Input", "Total weeks should be positive integer");
        return false;
    }
    if ((orderDelay < 0) || (orderDelay > totalWeeks))
    {
        QMessageBox::warning(this, "Invalid Input", "Order delay should be: 0 < order delay < Total Game Weeks");
        return false;
    }
            if ((shipmentDelay < 0) || (shipmentDelay > totalWeeks))
            {
                QMessageBox::warning(this, "Invalid Input", "Shipment delay should be: 0 < shipment delay < Total Game Weeks");
                return false;
            }

    if ((factoryDelay < 0) || (factoryDelay > totalWeeks))
    {

        QMessageBox::warning(this, "Invalid Input", "Factory delay should be: 0 < factory delay < Total Game Weeks");
        return false;
    }

    if ((holdingCost < 0) || (backlogCost < 0) || (startInventory < 0))
    {
        QMessageBox::warning(this, "Invalid Input", "Please enter positive integers");
        return false;
    }

    return true;

}

void InstructorDialog::on_createGame_clicked()
{
    bool validation_successful = validation_check();
    if (validation_successful == false)
    {
        return;
    }
    double backlogCost = ui->instructor_backlogCost->text().toDouble();
    double holdingCost = ui->instructor_holdingCost->text().toDouble();
    int orderDelay = ui->instructor_orderDelay->text().toInt();
    int totalWeeks = ui->instructor_totalWeeks->text().toInt();
    int startInventory = ui->instructor_startInventory->text().toInt();
    int factoryDelay = ui->instructor_factoryDelay->text().toInt();
    int shipmentDelay = ui->instructor_shipmentDelay->text().toInt();

    Game* newgame = new Game(instructor->getInstrId(),
                             backlogCost,
                             holdingCost,
                             orderDelay,
                             totalWeeks,
                             startInventory,
                             factoryDelay);
    newgame->setShipmentDelay(shipmentDelay);

    chooseServer* server = new chooseServer(this, newgame);

    //instructor->createGame();


    server->show();

    server->move(0,0);

    ui->createGame->setDisabled(true);
    
    //this->hide();
}


void InstructorDialog::on_exit_clicked()
{
    this->close();
}

void InstructorDialog::on_resetdef_clicked()
{
    ui->instructor_backlogCost->setText("1.0");
    ui->instructor_holdingCost->setText("0.5");
    ui->instructor_orderDelay->setText("2");
    ui->instructor_totalWeeks->setText("26");
    ui->instructor_startInventory->setText("12");
    ui->instructor_factoryDelay->setText("1");
}
