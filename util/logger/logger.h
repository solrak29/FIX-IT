/*
 * Logger.h
 *
 *  Created on: Jun 26, 2017
 *      Author: Carlos
 */

#ifndef UTIL_LOGGER_H_
#define UTIL_LOGGER_H_

//
//  Logger class to provide logging for the application.
//
//  Author: cnegron (solrak29@yahoo.com)
//
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

namespace Util {
class Logger {

public:

	static void init() {
		Logger& l = Logger::getInstance();
		l.initByConfig();
	}
	static void init(const string& logfile) {
	    Logger& l = Logger::getInstance();
	    l.createLog(logfile);
	}
	static void log(const char* function, const string& msg) {
		Logger& l = Logger::getInstance();
		l.logmsg(function, msg);
	}

	static string toString(const int& val) {
		stringstream ss;
		ss << val;
		string str = ss.str();
		return str;
	}

private:

	Logger();
	virtual ~Logger();
	Logger(Logger const&);

	static Logger& getInstance() {
		if ( !pInstance_) {
				static Logger _logger;
				pInstance_ = &_logger;
		}

		return *pInstance_;
	}
	void operator=(Logger const&){};
	void logmsg(const char* func, const string& msg);
	void createLog( const string& filename);
	void initByConfig();

	std::fstream _f;
	bool is_logging;
	static Logger* pInstance_;
};
}

#endif /* UTIL_LOGGER_H_ */
