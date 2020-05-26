#include "Scene/GameController.h"
#include "Scene/MapScene.h"
#include "Common/CommonConstant.h"

GameController::GameController()
	:map_scene_(NULL)
{

}

bool GameController::init()
{
	//����map_scene�������л�
	map_scene_ = MapScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, map_scene_, Color3B(0, 255, 255)));
	
	//��ӽ�ɫ����ʱ�̶����2��:����δ������С��
	addCharacter("miku", miku, 15000, map_scene_->pos_.at(0));
	addCharacter("nanxiaoniao", nanxiaoniao, 15000, map_scene_->pos_.at(1));
	
	whose_turn_ = 0;
	returnToCharacter(characters_.at(whose_turn_)); //�ص���һ����ɫ���ӽ�
	addGoButton();									//���go��ť

	
	return true;
}

void GameController::addCharacter(const std::string&name,int tag,int money,Vec2 start_pos)
{
	auto character = Character::create(name, tag, money, start_pos);
	characters_.pushBack(character);
	character->setPosition(start_pos);
	map_scene_->map_->addChild(character,10);
}

void GameController::returnToCharacter(Character* character)
{
	auto visible_size = Director::getInstance()->getVisibleSize();
	auto tile_size = map_scene_->map_->getTileSize();

	//����ĳ�����������任���ӽ�ת����ɫ
	map_scene_->map_->setPosition(
		Vec2(-character->getCurPos().x + visible_size.width / 2,
			tile_size.height * static_cast<float>(100)-character->getCurPos().y+visible_size.height/2));
}

void GameController::addGoButton()
{
	auto visible_size = Director::getInstance()->getVisibleSize();

	//��ʱû���ҵ��õİ�ť�زģ��Ƚ���ǰ����İ�ť��Ϊͬһ��ͼ
	auto go_button = MenuItemImage::create("go.png", "go.png");
	go_button->setCallback([=](Ref* render) {
		//����󽫰�ť�����õ��ɼ���Χ֮��
		go_button->setPosition(Vec2(visible_size.width + 1000.0f, 0));
		});
	auto menu = Menu::create(go_button, NULL);

	//����ê�㡢��ʼλ��
	menu->setAnchorPoint(Vec2(0.5f, 0.5f));
	menu->setPosition(Vec2(visible_size.width / 2, 3 * visible_size.height / 4));

	map_scene_->addChild(menu,11);
}
