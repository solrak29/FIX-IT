/*
 * Logger.cpp
 *
 *  Created on: Jun 26, 2017
 *      Author: Carlos
 */

#include <windows.h>
#include <time.h>
#include <cstdio>
#include "logger.h"
#include "config.h"

namespace Util {

Logger* Logger::pInstance_ = 0;


Logger::Logger() {
	is_logging = false;
	cout << "Initializing logger setting is_logging to " << is_logging << endl;
}

Logger::~Logger() {
	cout << "destroyed" << endl;
}

Logger::Logger(Logger const&) {
	is_logging = false;
	cout << "copying" << endl;
}

void
Logger::initByConfig() {
	// This will init by sqllite db configuration
	// There will be loggerconfig table
	// logerconfig table shall have location.
	// more options to come...
	Config conf;
	conf.getConfigContext("LOGGER");
	//string filename = conf.getConfig("LOGFILE"); // add error checking in case there is no config
	char* results = NULL;
	conf.getConfig("LOGGER","LOGFILE:DIRECTORY", results); // add error checking in case there is no config

	if ( results ) {
	    cout << "results " <<  results << endl;
	} else {
	    cout << "no result" << endl;
	}
//	createLog(filename);
}

void
Logger::createLog(const string& filename) {

	if ( is_logging == true) {
        _f << "Attempt to already open a log file instance" << endl;
	} else {
		_f.open(filename.c_str(), ios::out );
		if (_f.is_open() ) {
			_f << std::unitbuf << "Logger 2017(C) Starting" << endl;
			is_logging = true;
		} else {
	        cout << "failed to open file..." << strerror(errno) << endl;
		}
	}
}

void
Logger::logmsg(const char* function, const string& msg) {
	time_t rawtime;
	struct tm* tinfo;
	time(&rawtime);
	tinfo = localtime(&rawtime);
	char tbuf[80];
	strftime(tbuf,80,"%c",tinfo);
	if ( is_logging == true) {
		_f << tbuf << "[" << function << "]: " << msg << endl;
	} else {
		_f.open("defualt.log", ios::out );
		if (_f.is_open() ) {
			_f << ios::unitbuf << "Logger 2017(C) Starting (" << tbuf << ")" << endl;
			is_logging = true;
			_f << ios::unitbuf <<  tbuf << "[" << function << "]: " << msg << endl;
		} else {
			// we have an error condition
			cout << "failed to open file" << endl;
		}
	}
}

}

