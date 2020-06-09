#include "Car.h"
#include "Character/Character.h"
#include "Incident/Staff.h"

void Car::work(Character* player) {

	SetFlyingShoes(player);

}
std::string Car::getItemName() {
	return name_;
}

Car* Car::create() {
	Car* car = new Car();
	return car;
}
std::string Car::getContent() {
	return content_;
}