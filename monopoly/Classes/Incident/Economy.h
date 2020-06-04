#ifndef _ECONOMY_H_
#define _ECONOMY_H_

#include "Character/Character.h"
#include "Scene/StorkScene.h"
//政府征收所得税、地产税、股票税
//最好将所有人的税同时都收了
//函数的返回值为征收的数目
int LevyIncomeTax(Character* character);
int LevyEstateTax(Character* character);
int LevyStockTax(Character* character, StockScene* stock_scene);

Character* GetMostEstate(const Vector<Character*>& characters); //得知地产最多者是谁
Character* GetLeastEstate(const Vector<Character*>& characters);//得知地产最少者是谁
Character* GetMostStock(const Vector<Character*>& characters,StockScene*stock_scene);//得知股票最多者是谁
void RewardMostEstate(Character*character);	//奖励地产最多者
void HelpLeastEstate(Character* character);	//补助地产最少者
void RewardMostStock(Character* character); //奖励股票拥有最多者

#endif
