#include "HouseChange.h"
#include "Character/Character.h"
#include "Incident/Staff.h"

void HouseChange::work(Character* player) {

	UseHouseBuy(player);

}
std::string HouseChange::getItemName() {
	return name_;
}

HouseChange* HouseChange::create() {
	HouseChange* house_change = new HouseChange();
	return house_change;
}
std::string HouseChange::getContent() {
	return content_;
}