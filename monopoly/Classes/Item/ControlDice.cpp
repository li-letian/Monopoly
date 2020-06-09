#include "ControlDice.h"
#include "Character/Character.h"
#include "Incident/Staff.h"

void ControlDice::work(Character* player) {

	//UseControlDice(player);

}
std::string ControlDice::getItemName() {
	return name_;
}

ControlDice* ControlDice::create() {
	ControlDice* control_dice = new ControlDice();
	return control_dice;
}
std::string ControlDice::getContent() {
	return content_;
}