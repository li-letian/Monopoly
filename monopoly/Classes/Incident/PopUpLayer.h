#ifndef _POP_UP_LAYER_H_
#define _POP_UP_LAYER_H_

#include <functional>
#include "cocos2d.h"

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
	void setCallBack(std::function<void(Ref * render)> confirm_call_back, std::string text = "ȷ��");
	void setCallBack(std::function<void(Ref * render)> confirm_call_back, std::function<void(Ref * render)> cancel_call_back);
	//��һ�����ļ�ͼƬ���飬�ڶ����ǻص��������飬һһ��Ӧ������������ÿ��ͼƬ����һ����ť�������Ժ�ִ�ж�Ӧ�Ļص�������Ȼ���˳�����
	void setMenu(const std::vector< std::string>image, const std::vector<std::function<void(Ref* ref)>>callback);
	//��һ���ǻص��������飬�ڶ����ǰ�ť�������飬һһ��Ӧ������������ÿ��ͼƬ����һ����ť�������Ժ�ִ�ж�Ӧ�Ļص����������ǲ����˳�����
	void setMenu(const std::vector<std::function<void(Ref* ref)>>callback, const std::vector<std::string>text);
	void setOnScene(int z_order = 50);
private:
	Sprite* back_ground_ = nullptr;
	float back_ground_width_ = 0;
	float back_ground_height_ = 0;
};

#endif