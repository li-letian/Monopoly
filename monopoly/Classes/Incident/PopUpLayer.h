#ifndef _POP_UP_LAYER_H_
#define _POP_UP_LAYER_H_

#include <functional>
#include "cocos2d.h"

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
	void setCallBack(std::function<void(Ref * render)> confirm_call_back, std::string text = "确认");
	void setCallBack(std::function<void(Ref * render)> confirm_call_back, std::function<void(Ref * render)> cancel_call_back);
	//第一个是文件图片数组，第二个是回调函数数组，一一对应，这个函数会给每个图片创造一个按钮，按下以后执行对应的回调函数，然后退出弹框
	void setMenu(const std::vector< std::string>image, const std::vector<std::function<void(Ref* ref)>>callback);
	//第一个是回调函数数组，第二个是按钮文字数组，一一对应，这个函数会给每个图片创造一个按钮，按下以后执行对应的回调函数，但是不会退出弹框
	void setMenu(const std::vector<std::function<void(Ref* ref)>>callback, const std::vector<std::string>text);
	void setOnScene(int z_order = 50);
private:
	Sprite* back_ground_ = nullptr;
	float back_ground_width_ = 0;
	float back_ground_height_ = 0;
};

#endif