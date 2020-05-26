#include "Scene/GameController.h"
#include "Scene/MapScene.h"
#include "Common/CommonConstant.h"

GameController::GameController()
	:map_scene_(NULL)
{

}

bool GameController::init()
{
	//创造map_scene场景并切换
	map_scene_ = MapScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, map_scene_, Color3B(0, 255, 255)));
	
	//添加角色，暂时固定添加2个:初音未来与南小鸟
	addCharacter("miku", miku, 15000, map_scene_->pos_.at(0));
	addCharacter("nanxiaoniao", nanxiaoniao, 15000, map_scene_->pos_.at(1));
	
	whose_turn_ = 0;
	returnToCharacter(characters_.at(whose_turn_)); //回到第一个角色的视角
	addGoButton();									//添加go按钮

	
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

	//经过某种神奇的坐标变换将视角转到角色
	map_scene_->map_->setPosition(
		Vec2(-character->getCurPos().x + visible_size.width / 2,
			tile_size.height * static_cast<float>(100)-character->getCurPos().y+visible_size.height/2));
}

void GameController::addGoButton()
{
	auto visible_size = Director::getInstance()->getVisibleSize();

	//暂时没有找到好的按钮素材，先将按前按后的按钮设为同一张图
	auto go_button = MenuItemImage::create("go.png", "go.png");
	go_button->setCallback([=](Ref* render) {
		//点击后将按钮移设置到可见范围之外
		go_button->setPosition(Vec2(visible_size.width + 1000.0f, 0));
		});
	auto menu = Menu::create(go_button, NULL);

	//设置锚点、初始位置
	menu->setAnchorPoint(Vec2(0.5f, 0.5f));
	menu->setPosition(Vec2(visible_size.width / 2, 3 * visible_size.height / 4));

	map_scene_->addChild(menu,11);
}
