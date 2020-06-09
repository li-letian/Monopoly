#include "RedCard.h"
#include "Character/Character.h"
#include "Incident/Staff.h"

void RedCard::work(Character* player) {

	UseRedCard(player);

}
std::string RedCard::getItemName() {
	return name_;
}

RedCard* RedCard::create() {
	RedCard* red_card = new RedCard();
	return red_card;
}
std::string RedCard::getContent() {
	return content_;
}