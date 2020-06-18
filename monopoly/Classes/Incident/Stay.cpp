#include "Incident/PopUpLayer.h"
#include "Incident/Incident.h"
#include "Character/Character.h"
#include "Scene/ItemScene.h"

#include "Item/AngelCard.h"
#include "Item/ControlDice.h"
#include "Item/HouseChange.h"
#include "Item/Item.h"
#include "Item/Pray.h"
#include "Item/RidHospital.h"
#include "Item/Sleep.h"
#include "Item/Turtle.h"
#include "Item/Average.h"
#include "Item/DevilCard.h"
#include "Item/HouseDestory.h"
#include "Item/Mine.h"
#include "Item/RedCard.h"
#include "Item/RidJail.h"
#include "Item/Stop.h"
#include "Item/Sleep.h"
#include "Item/Worker.h"
#include "Item/BlackCard.h"
#include "Item/Escape.h"
#include "Item/HouseExchange.h"
#include "Item/Missile.h"
#include "Item/Revenge.h"
#include "Item/RisePrice.h"
#include "Item/Transmit.h"
#include "Item/Car.h"
#include "Item/Frame.h"
#include "Item/Impute.h"
#include "Item/Motor.h"
#include "Item/RidGod.h"
#include "Item/Robot.h"
#include "Item/TurnAround.h"

#include "Stay.h"

void GetRandomItem(Character* standing)
{
	auto item_scene = GetItemScene();
	auto temp = rand() % 29;
	log("item get case%d", temp);
	switch (temp)
	{
	case	0:	item_scene->addItem(standing, AngelCard::create());	break;
	case	1:	item_scene->addItem(standing, ControlDice::create());	break;
	case	2:	item_scene->addItem(standing, HouseChange::create());	break;
	case	3:	item_scene->addItem(standing, Pray::create());	break;
	case	4:	item_scene->addItem(standing, RidHospital::create());	break;
	case	5:	item_scene->addItem(standing, Sleep::create());	break;
	case	6:	item_scene->addItem(standing, Turtle::create());	break;
	case	7:	item_scene->addItem(standing, Average::create());	break;
	case	8:	item_scene->addItem(standing, DevilCard::create());	break;
	case	9:	item_scene->addItem(standing, HouseDestory::create());	break;
	case	10:	item_scene->addItem(standing, Mine::create());	break;
	case	11:	item_scene->addItem(standing, RedCard::create());	break;
	case	12:	item_scene->addItem(standing, RidJail::create());	break;
	case	13:	item_scene->addItem(standing, Stop::create());	break;
	case	14:	item_scene->addItem(standing, Worker::create());	break;
	case	15:	item_scene->addItem(standing, BlackCard::create());	break;
	case	16:	item_scene->addItem(standing, Escape::create());	break;
	case	17:	item_scene->addItem(standing, HouseExchange::create());	break;
	case	18:	item_scene->addItem(standing, Missile::create());	break;
	case	19:	item_scene->addItem(standing, Revenge::create());	break;
	case	20:	item_scene->addItem(standing, RisePrice::create());	break;
	case	21:	item_scene->addItem(standing, Transmit::create());	break;
	case	22:	item_scene->addItem(standing, Car::create());	break;
	case	23:	item_scene->addItem(standing, Frame::create());	break;
	case	24:	item_scene->addItem(standing, Impute::create());	break;
	case	25:	item_scene->addItem(standing, Motor::create());	break;
	case	26:	item_scene->addItem(standing, RidGod::create());	break;
	case	27:	item_scene->addItem(standing, Robot::create());	break;
	case	28:	item_scene->addItem(standing, TurnAround::create());	break;
	default:
		break;
	}
}

void GetRandomItem(Character* standing,ItemScene* item_scene)
{
	auto temp = rand() % 29;
	log("item get case%d", temp);
	switch (temp)
	{
	case	0:	item_scene->addItem(standing, AngelCard::create());	break;
	case	1:	item_scene->addItem(standing, ControlDice::create());	break;
	case	2:	item_scene->addItem(standing, HouseChange::create());	break;
	case	3:	item_scene->addItem(standing, Pray::create());	break;
	case	4:	item_scene->addItem(standing, RidHospital::create());	break;
	case	5:	item_scene->addItem(standing, Sleep::create());	break;
	case	6:	item_scene->addItem(standing, Turtle::create());	break;
	case	7:	item_scene->addItem(standing, Average::create());	break;
	case	8:	item_scene->addItem(standing, DevilCard::create());	break;
	case	9:	item_scene->addItem(standing, HouseDestory::create());	break;
	case	10:	item_scene->addItem(standing, Mine::create());	break;
	case	11:	item_scene->addItem(standing, RedCard::create());	break;
	case	12:	item_scene->addItem(standing, RidJail::create());	break;
	case	13:	item_scene->addItem(standing, Stop::create());	break;
	case	14:	item_scene->addItem(standing, Worker::create());	break;
	case	15:	item_scene->addItem(standing, BlackCard::create());	break;
	case	16:	item_scene->addItem(standing, Escape::create());	break;
	case	17:	item_scene->addItem(standing, HouseExchange::create());	break;
	case	18:	item_scene->addItem(standing, Missile::create());	break;
	case	19:	item_scene->addItem(standing, Revenge::create());	break;
	case	20:	item_scene->addItem(standing, RisePrice::create());	break;
	case	21:	item_scene->addItem(standing, Transmit::create());	break;
	case	22:	item_scene->addItem(standing, Car::create());	break;
	case	23:	item_scene->addItem(standing, Frame::create());	break;
	case	24:	item_scene->addItem(standing, Impute::create());	break;
	case	25:	item_scene->addItem(standing, Motor::create());	break;
	case	26:	item_scene->addItem(standing, RidGod::create());	break;
	case	27:	item_scene->addItem(standing, Robot::create());	break;
	case	28:	item_scene->addItem(standing, TurnAround::create());	break;
	default:
		break;
	}
}