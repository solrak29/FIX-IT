/*
 * WinService.cpp
 *
 *  Created on: Jul 18, 2017
 *      Author: Carlos
 */

#include <windows.h>

#include "winservice.h"
#include "logger.h"
#include "winserviceapp.h"

namespace Util {

WinServiceApp* WinService::_app = 0;
string WinService::_serviceName = "";

WinService::WinService(const string &serviceName, Util::WinServiceApp* app) {

	// TODO Auto-generated constructor stub
	WinService::_app = app;
	WinService::_serviceName = serviceName;
	SERVICE_TABLE_ENTRY ServiceTable[2];
	string tmp = serviceName;
    ServiceTable[0].lpServiceName = const_cast<char*>(tmp.c_str());
    ServiceTable[0].lpServiceProc = (LPSERVICE_MAIN_FUNCTION)WinService::WinServiceMain;
    ServiceTable[1].lpServiceName = NULL;
    ServiceTable[1].lpServiceProc = NULL;
    if ( StartServiceCtrlDispatcher(ServiceTable) ) {
        Logger::log(__func__, "Registered Service Ctrl Complete");
    } else {
    	DWORD code = GetLastError();

    	if ( code == ERROR_FAILED_SERVICE_CONTROLLER_CONNECT )
    	{
     	    Logger::log(__func__, "Failed Service controller connect");

    	} else if ( code == ERROR_INVALID_DATA ) {
     	    Logger::log(__func__, "Invalid Data");

    	} else if ( code == ERROR_SERVICE_ALREADY_RUNNING ) {
     	    Logger::log(__func__, "Service Already Running");

    	} else {
     	    Logger::log(__func__, "Error unknown");
    	}
    }
}

void
WinService::WinServiceMain( int argc, char ** argv )
{
	Logger::log(__func__, "");

    SERVICE_STATUS_HANDLE hStatus = RegisterServiceCtrlHandler( _serviceName.c_str(),
                                    (LPHANDLER_FUNCTION)WinService::WinControlHandler);

    if (hStatus == (SERVICE_STATUS_HANDLE)0)
    {
    	Logger::log(__func__, " Registered Controll Handler failed");
       // Registering Control Handler failed
       return;
    }
    // Initialize Service
    _app->start(hStatus);

    return;
}

void
WinService::WinControlHandler(DWORD request)
{
	 switch(request)
	   {
	      case SERVICE_CONTROL_STOP:
	    	  WinService::_app->shutdown();
	         break;

	      case SERVICE_CONTROL_SHUTDOWN:
	    	 WinService::_app->shutdown();
	         break;

	      default:
	         break;
	    }

	    // Report current status
	    //SetServiceStatus (hStatus, &ServiceStatus);

	    return;

}

WinService::~WinService() {
	// TODO Auto-generated destructor stub
}

} /* namespace util */
