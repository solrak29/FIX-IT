/*
 * WinServiceapp.cpp
 *
 *  Created on: Jul 31, 2017
 *      Author: Carlos
 */

#include <windows.h>
#include "winserviceapp.h"
#include "logger.h"

namespace Util {

WinServiceApp::WinServiceApp(const string& appname) {
	// TODO Auto-generated constructor stub
	Logger::log(__func__, "");
	_hStatus = 0;
}

void
WinServiceApp::start(SERVICE_STATUS_HANDLE& h)
{
	Logger::log(__func__, "");
	 _hStatus = h;
	 SERVICE_STATUS ServiceStatus;
	 ServiceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	 ServiceStatus.dwCurrentState = SERVICE_START_PENDING;
	 ServiceStatus.dwControlsAccepted   = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;
	 ServiceStatus.dwWin32ExitCode = 0;
	 ServiceStatus.dwServiceSpecificExitCode = 0;
	 ServiceStatus.dwCheckPoint = 30000;
	 ServiceStatus.dwWaitHint = 50000;
	 Logger::log(__func__, "Setting pending start status");
	 SetServiceStatus (_hStatus, &ServiceStatus);
	 _terminateEvent = CreateEvent(0, TRUE, FALSE,0);
	 if ( !_terminateEvent) {
		 Logger::log(__func__, "Can't create terminate event object");
	 } else {
	     Logger::log(__func__, "Calling run...");
     	 ServiceStatus.dwCurrentState = SERVICE_RUNNING;
     	 SetServiceStatus (_hStatus, &ServiceStatus);
    	 run(); // should run indef; on return we presume it has stopped.
    	 WaitForSingleObject(_terminateEvent, INFINITE);
         ServiceStatus.dwWin32ExitCode = 0;
         ServiceStatus.dwCurrentState = SERVICE_STOPPED;
         SetServiceStatus (_hStatus, &ServiceStatus);
	 }
	 // We report the running status to SCM.
	 Logger::log(__func__, "returning...");
}

void
WinServiceApp::shutdown()
{
	stop(); // tell the derived classed that we are stopping
    CloseHandle(_terminateEvent);
}

WinServiceApp::~WinServiceApp() {
	// TODO Auto-generated destructor stub
}

} /* namespace Util */
