#include "Motor.h"
#include "Character/Character.h"
#include "Incident/Staff.h"

void Motor::work(Character* player) {

	SetSpeedShoes(player);

}
std::string Motor::getItemName() {
	return name_;
}

Motor* Motor::create() {
	Motor* motor = new Motor();
	return motor;
}
std::string Motor::getContent() {
	return content_;
}