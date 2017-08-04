/*
 * WinServiceapp.h
 *
 *  Created on: Jul 31, 2017
 *      Author: Carlos
 */

#ifndef UTIL_WINSERVICEAPP_H_
#define UTIL_WINSERVICEAPP_H_

#include <string>
#include "winservice.h"

using namespace std;
namespace Util {
class WinServiceApp {
public:
	WinServiceApp(const string& servicename);
	virtual ~WinServiceApp();
	virtual void run() = 0; // tell the derived application to run
	virtual void start(SERVICE_STATUS_HANDLE &h);
	virtual void shutdown();
	virtual void stop() = 0; // tell the derived application to stop running
private:
	SERVICE_STATUS_HANDLE _hStatus;
	HANDLE _terminateEvent;
protected:
	WinService* _service;
};

} /* namespace Util */

#endif /* UTIL_WINSERVICEAPP_H_ */
