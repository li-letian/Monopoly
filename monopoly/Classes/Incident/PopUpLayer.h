#ifndef _POP_UP_LAYER_H_
#define _POP_UP_LAYER_H_

#include <functional>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Common/CommonConstant.h"
USING_NS_CC;

//PopUpLayer使用示例
	/*
	auto pop = PopUpLayer::create();
	pop->setTitle("测试标题");
	pop->setContent("测试一下文本显示正常，以及长句子会不会自动换行以防止到屏幕外,以下只是为了让一条长句子显得稍微长一点而已");
	pop->setCallBack([=](Ref* sender) {
		log("confirm button ok");
		});


	pop->setPosition(Vec2(0, 0));
	map_scene_->addChild(pop,50);
	*/
class PopUpLayer:public Layer
{
public:
	CREATE_FUNC(PopUpLayer);
	virtual bool init();

	//设置标题与内容
	void setTitle(const std::string& title);
	void setContent(const std::string& content);

	//设置回调函数，可只设置确认按钮也可设置确认按钮与取消按钮
	void setCallBack(std::function<void(Ref * render)> confirm_call_back);
	void setCallBack(std::function<void(Ref * render)> confirm_call_back, std::function<void(Ref * render)> cancel_call_back);

private:
	Sprite* back_ground_ = nullptr;
	float back_ground_width_ = 0;
	float back_ground_height_ = 0;
};

#endif