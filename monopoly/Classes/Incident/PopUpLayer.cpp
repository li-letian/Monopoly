#include "PopUpLayer.h"
#include "Common/CommonMethod.h"
#include "Common/CommonConstant.h"

bool PopUpLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	//添加屏蔽层
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [](Touch* touch, Event* event) {
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//添加背景
	auto visible_size = Director::getInstance()->getVisibleSize();
	back_ground_ = Sprite::create("dialog_bg.png");
	back_ground_->setAnchorPoint(Vec2(0.5f, 0.5f));
	back_ground_width_ = back_ground_->getContentSize().width;
	back_ground_height_ = back_ground_->getContentSize().height;
	back_ground_->setPosition(Vec2((visible_size.width - grid_distance * 16) / 2,
		visible_size.height / 2));
	this->addChild(back_ground_);

	return true;
}

void PopUpLayer::setTitle(const std::string& title)
{
	auto title_label = Label::createWithSystemFont(ZH(title), "华文琥珀", 30);
	title_label->setColor(Color3B(0, 0, 0));
	title_label->setAnchorPoint(Vec2(0.5f, 0.5f));
	title_label->setPosition(Vec2(back_ground_width_ / 2, back_ground_height_ - 2 * grid_distance));
	back_ground_->addChild(title_label);
}

void PopUpLayer::setContent(const std::string& content)
{
	auto content_label = Label::createWithSystemFont(ZH(content), "华文琥珀", 20);
	content_label->setColor(Color3B(0, 0, 0));
	content_label->setDimensions(back_ground_width_ - 4 * grid_distance, back_ground_height_ - 10 * grid_distance);
	content_label->setAnchorPoint(Vec2(0.5f, 0.5f));
	content_label->setPosition(Vec2(back_ground_width_ / 2, back_ground_height_ / 2));
	back_ground_->addChild(content_label);
}

void PopUpLayer::setCallBack(std::function<void(Ref * render)> confirm_call_back)
{
	MenuItemFont::setFontName("华文琥珀");
	MenuItemFont::setFontSize(25);
	auto confirm_item = MenuItemFont::create(ZH("确认"), [=](Ref* ref) {
		confirm_call_back(ref);
		this->removeFromParentAndCleanup(true); });
	confirm_item->setColor(Color3B(0, 0, 0));
	confirm_item->setAnchorPoint(Vec2(0.5f, 0));
	confirm_item->setPosition(Vec2(back_ground_width_ / 2, 2 * grid_distance));
	auto menu = Menu::create(confirm_item, nullptr);
	menu->setAnchorPoint(Vec2(0, 0));
	menu->setPosition(Vec2(0, 0));
	back_ground_->addChild(menu);
}

void PopUpLayer::setCallBack(std::function<void(Ref * render)> confirm_call_back, std::function<void(Ref * render)> cancel_call_back)
{
	MenuItemFont::setFontName("华文琥珀");
	MenuItemFont::setFontSize(25);

	auto confirm_item = MenuItemFont::create(ZH("确认"), [=](Ref* ref) {
		confirm_call_back(ref);
		this->removeFromParentAndCleanup(true); });
	confirm_item->setColor(Color3B(0, 0, 0));
	confirm_item->setAnchorPoint(Vec2(0, 0));
	confirm_item->setPosition(Vec2(2 * grid_distance, 2 * grid_distance));

	auto cancel_item = MenuItemFont::create(ZH("取消"), [=](Ref* ref) {
		cancel_call_back(ref);
		this->removeFromParentAndCleanup(true);
	});
	cancel_item->setColor(Color3B(0, 0, 0));
	cancel_item->setAnchorPoint(Vec2(1.0f, 0));
	cancel_item->setPosition(Vec2(back_ground_width_ - 2 * grid_distance, 2 * grid_distance));

	auto menu = Menu::create(confirm_item, cancel_item, nullptr);
	menu->setAnchorPoint(Vec2(0, 0));
	menu->setPosition(Vec2(0,0));
	back_ground_->addChild(menu);
}