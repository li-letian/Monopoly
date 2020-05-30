#ifndef _COMMON_METHOD_H_
#define _COMMON_METHOD_H_

#include <cstdlib>
#include<string>

#define random(x) (rand()%x)

std::string ZH(const std::string& str);

void sendMsg(int msg);
#endif // !_COMMON_METHOD_H_
