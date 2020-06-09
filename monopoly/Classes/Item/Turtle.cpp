#include "Turtle.h"
#include "Character/Character.h"
#include "Incident/Staff.h"

void Turtle::work(Character* player) {

	SetTurtle(player);

}
std::string Turtle::getItemName() {
	return name_;
}

Turtle* Turtle::create() {
	Turtle* turtle = new Turtle();
	return turtle;
}
std::string Turtle::getContent() {
	return content_;
}