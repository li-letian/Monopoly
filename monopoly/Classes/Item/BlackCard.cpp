#include "BlackCard.h"
#include "Character/Character.h"
#include "Incident/Staff.h"

void BlackCard::work(Character* player) {

	UseBlackCard(player);

}
std::string BlackCard::getItemName() {
	return name_;
}

BlackCard* BlackCard::create() {
	BlackCard* black_card = new BlackCard();
	return black_card;
}
std::string BlackCard::getContent() {
	return content_;
}