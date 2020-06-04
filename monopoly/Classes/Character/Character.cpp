#include "Character/Character.h"
#include "Common/CommonConstant.h"
#include "Common/CommonMethod.h"
USING_NS_CC;

Character::Character()
	:character_anim_down_(nullptr),
	character_anim_left_(nullptr),
	character_anim_right_(nullptr),
	character_anim_up_(nullptr),
	character_frame_cache_(nullptr),
	name_(),
	money_(150000),
	cur_pos_(0),
	steps_scope_(walk_steps),
	stop_times_(0),
	condition_(0),
	estate_value_(0)
{
	this->setTag(0);
}

Character::~Character()
{
	//释放先前retain的动画对象
	character_anim_down_->release();
	character_anim_left_->release();
	character_anim_right_->release();
	character_anim_up_->release();
}


bool Character::init(const std::string& name, int tag, int money, int cur_pos)
{
	if (!Sprite::init())
	{
		return false;
	}

	//设置一些基本属性
	name_ = name;
	this->setTag(tag);
	money_ = money;
	cur_pos_ = cur_pos;

	initAnimate();	//初始化动画对象
	initSprite();	//设置人物初始形象
	
	return true;
}

void Character::initAnimate()
{
	character_frame_cache_ = SpriteFrameCache::getInstance();
	character_frame_cache_->addSpriteFramesWithFile(StringUtils::format("%s.plist", name_.c_str()), StringUtils::format("%s.png", name_.c_str()));

	Vector<SpriteFrame*>character_anim_down_vec;
	Vector<SpriteFrame*>character_anim_left_vec;
	Vector<SpriteFrame*>character_anim_right_vec;
	Vector<SpriteFrame*>character_anim_up_vec;

	for (int i = 0; i < 4; ++i)
	{
		auto frame = character_frame_cache_->getSpriteFrameByName(StringUtils::format("%s-%d.png", name_.c_str(), i));
		character_anim_down_vec.pushBack(frame);
	}
	for (int i = 4; i < 8; ++i)
	{
		auto frame = character_frame_cache_->getSpriteFrameByName(StringUtils::format("%s-%d.png", name_.c_str(), i));
		character_anim_left_vec.pushBack(frame);
	}
	for (int i = 8; i < 12; ++i)
	{
		auto frame = character_frame_cache_->getSpriteFrameByName(StringUtils::format("%s-%d.png", name_.c_str(), i));
		character_anim_right_vec.pushBack(frame);
	}
	for (int i = 12; i < 16; ++i)
	{
		auto frame = character_frame_cache_->getSpriteFrameByName(StringUtils::format("%s-%d.png", name_.c_str(), i));
		character_anim_up_vec.pushBack(frame);
	}
	
	character_anim_down_ = Animate::create(Animation::createWithSpriteFrames(character_anim_down_vec, character_walk_delay_time));
	character_anim_left_ = Animate::create(Animation::createWithSpriteFrames(character_anim_left_vec, character_walk_delay_time));
	character_anim_right_ = Animate::create(Animation::createWithSpriteFrames(character_anim_right_vec, character_walk_delay_time));
	character_anim_up_ = Animate::create(Animation::createWithSpriteFrames(character_anim_up_vec, character_walk_delay_time));

	//暂时不添加到父节点中，retain以防止被autorelease
	character_anim_down_->retain();
	character_anim_left_->retain();
	character_anim_right_->retain();
	character_anim_up_->retain();
}

void Character::initSprite()
{
	auto spf = character_frame_cache_->getSpriteFrameByName(StringUtils::format("%s-4.png", name_.c_str()));
	this->initWithSpriteFrame(spf);
	this->setAnchorPoint(Vec2(0.5f, 0.15f));
}

void Information::updateInformation(Character* player) {
	
	this->removeAllChildren();
	
	int tag = player->getTag();
	Size visible_size = Director::getInstance()->getVisibleSize();
	
	
	Value val_cash,val_cash_pre,val_cash_label;
	val_cash_pre = Value(ZH("现金: "));
	int money = player->getMoney();
	val_cash = Value(money);
	val_cash_label = val_cash_pre.asString() + val_cash.asString().c_str();
	auto label_cash = Label::createWithSystemFont(val_cash_label.asString().c_str(), "fonts/arial.ttf", 30);
	label_cash->setTextColor(Color4B::BLACK);
	label_cash->setAnchorPoint(Vec2(0, 0.5));
	label_cash->setPosition(Vec2(810, visible_size.height - 370));
	this->addChild(label_cash,25);                                                      //现金标签
	
	if (tag == 1) {
		auto sprite_head = Sprite::create("miku_avatar.png");
		sprite_head->setPosition(Vec2(847, visible_size.height - 290));
		this->addChild(sprite_head, 25);

		auto sprite_color = Sprite::create("character_avatar1.png");
		sprite_color->setPosition(Vec2(940, visible_size.height - 290));
		this->addChild(sprite_color, 25);

		
	}
	else if (tag == 2) {
		auto sprite_head = Sprite::create("kotori_avatar.png");
		sprite_head->setPosition(Vec2(847, visible_size.height - 290));
		this->addChild(sprite_head, 25);

		auto sprite_color = Sprite::create("character_avatar2.png");
		sprite_color->setPosition(Vec2(940, visible_size.height - 290));
		this->addChild(sprite_color, 25);
		day_++;
		
	}
	Value val_year(ZH("年")), val_mon(ZH("月")), val_day(ZH("日")),val_date;
	if (day_ >= 31) {
		day_ = 1;
		month_++;
	}
	if (month_ >= 12) {
		month_ = 1;
		year_++;
	}
	val_date = Value(year_).asString().c_str() + val_year.asString() + Value(month_).asString().c_str() +
		val_mon.asString() + Value(day_).asString().c_str() + val_day.asString();
	auto label_date=Label::createWithSystemFont(val_date.asString().c_str(), "fonts/arial.ttf", 30);
	label_date->setTextColor(Color4B::BLACK);
	label_date->setAnchorPoint(Vec2(0, 0.5));
	label_date->setPosition(Vec2(800, visible_size.height - 200));
	this->addChild(label_date, 25);
	
    

}
bool Information::init() {
	if (!Layer::init()) {
		return false;
	}
	
	
	return true;
}

Information* Information::createScene(MapScene* map_scene) {
	auto information_layer= Information::create();
	information_layer->map_scene_ = map_scene;
	information_layer->map_scene_->addChild(information_layer,30);
	return  information_layer;
	
}