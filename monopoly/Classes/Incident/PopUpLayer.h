#ifndef _POP_UP_LAYER_H_
#define _POP_UP_LAYER_H_

#include <functional>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Common/CommonConstant.h"
USING_NS_CC;

//PopUpLayerʹ��ʾ��
	/*
	auto pop = PopUpLayer::create();
	pop->setTitle("���Ա���");
	pop->setContent("����һ���ı���ʾ�������Լ������ӻ᲻���Զ������Է�ֹ����Ļ��,����ֻ��Ϊ����һ���������Ե���΢��һ�����");
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

	//���ñ���������
	void setTitle(const std::string& title);
	void setContent(const std::string& content);

	//���ûص���������ֻ����ȷ�ϰ�ťҲ������ȷ�ϰ�ť��ȡ����ť
	void setCallBack(std::function<void(Ref * render)> confirm_call_back);
	void setCallBack(std::function<void(Ref * render)> confirm_call_back, std::function<void(Ref * render)> cancel_call_back);

private:
	Sprite* back_ground_ = nullptr;
	float back_ground_width_ = 0;
	float back_ground_height_ = 0;
};

#endif