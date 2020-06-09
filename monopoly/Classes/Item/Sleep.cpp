#include "Sleep.h"
#include "Character/Character.h"
#include "Incident/Staff.h"

void HolidayCard::work(Character* player) {

	UseHolidayCard(player);

}
std::string HolidayCard::getItemName() {
	return name_;
}

HolidayCard* HolidayCard::create() {
	HolidayCard* holiday_card = new HolidayCard();
	return holiday_card;
}
std::string HolidayCard::getContent() {
	return content_;
}