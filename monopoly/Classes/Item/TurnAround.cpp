#include "TurnAround.h"
#include "Character/Character.h"
#include "Incident/Staff.h"

void TurnAround::work(Character* player) {

	UseTurnAroundCard(player);

}
std::string TurnAround::getItemName() {
	return name_;
}

TurnAround* TurnAround::create() {
	TurnAround* turn_around = new TurnAround();
	return turn_around;
}
std::string TurnAround::getContent() {
	return content_;
}