#include "Frame.h"
#include "Character/Character.h"


void Frame::work(Character* player){

	int money = player->getMoney();
	money += 10000;
	player->setMoney(money);

}
std::string Frame::getItemName(){
	return name_;
}

Frame* Frame::create_() {
	Frame* frame = new Frame();
	return frame;
}
std::string Frame::getContent() {
	return content_;
}