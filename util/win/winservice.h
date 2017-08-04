/*
 * WinService.h
 *
 *  Created on: Jul 18, 2017
 *      Author: Carlos
 */

#ifndef UTIL_WINSERVICE_H_
#define UTIL_WINSERVICE_H_

#include <windows.h>
#include <string>
using namespace std;


namespace Util {
class WinServiceApp;


class WinService {
public:
	WinService(const string& serviceName, Util::WinServiceApp* app);
	static void WINAPI WinServiceMain(int argc,  char** argv);
	static void WINAPI WinControlHandler(DWORD request);
	virtual ~WinService();
private:
	static WinServiceApp *_app;
	static string _serviceName;
};

} /* namespace util */

#endif /* UTIL_WINSERVICE_H_ */
