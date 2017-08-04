/*
 * Config.h
 *
 *  Created on: Aug 2, 2017
 *      Author: Carlos solrak29@yahoo.com
 *
 *      config class that will sqllite config.
 *      in the future we will abstract this.
 */

#ifndef UTIL_CONFIG_H_
#define UTIL_CONFIG_H_

#include "..\lib\sqlite3.h"
#include <string>
#include <map>
#include <exception>

using namespace std;

namespace Util {

class ConfigException: public exception {

public:
	ConfigException(string errmsg): err(errmsg){};

	virtual const char* what() const throw() {
        return err.c_str();
    }

private:
    string err;
};

class Config {
public:
	Config();
	void getConfigContext(string context);
	void getConfig(string context, string configitem, char* results);
	static int callback(void* notused, int argc, char**argv, char** azColName);
	virtual ~Config();

private:

	map<string, sqlite3*> _contextmap;
	string _configdir;
};

} /* namespace Util */

#endif /* UTIL_CONFIG_H_ */
