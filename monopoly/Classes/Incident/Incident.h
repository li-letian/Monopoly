#ifndef _INCIDENT_H_
#define _INCIDENT_H_
#endif
class Incident :public Node {
public:
	void FinanceGain(Character* player);
	void FinanceLost(Character* player);
	void Medical(Character* player);
	void Criminal(Character* player);
	void Holiday(Character* player);
	void EconomyUp();
	void EconomyDown();


};