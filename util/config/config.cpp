/*
 * Config.cpp
 *
 *  Created on: Aug 2, 2017
 *      Author: Carlos
 */

#include "config.h"
#include <string>
#include <cstdio>
#include <exception>
#include "logger.h"

using namespace std;

namespace Util {

Config::Config() {
	// TODO Auto-generated constructor stub
	// check that the environment variables are setup
	char* configlocation = getenv("CONFIG_DAT");
	if ( configlocation ) {
	    _configdir = configlocation;
	} else {
	    cerr << "Environment not set for config" << endl;
	    throw ConfigException("No env defined");
	}

}

Config::~Config() {
	// TODO Auto-generated destructor stub
}


int
Config::callback(void* notused, int argc, char**argv, char** azColName) {
	int i;
for(i=0; i<argc; i++){
printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
}
printf("\n");
return 0;
}

void
Config::getConfig(string context, string configitem, char* results) {

	sqlite3 *db = NULL;
	try {
	    db = _contextmap.at(context);
	} catch (const out_of_range &ex) {
		cout << "Caught exception; getting context again " << ex.what() << endl;
		getConfigContext( context);
	}

	int delimloc = configitem.find(":");
	if ( delimloc == string::npos ) {
		cout << "Error in getting config bad format" << configitem << endl;
		results = NULL;
		return;
	} else {
        string tablename = configitem.substr(0, delimloc);
        string item = configitem.substr(delimloc+1, configitem.length());
        string sql = "select " + item + " from " + tablename;
        cout << "Running query " << sql << endl;

	    sqlite3_stmt *stmt = NULL;
	    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
	    if (rc != SQLITE_OK) {
	    	cout << "Error in preparing statement for sql" << endl;
	        results = NULL;
	        return;
	    }

	    int rowCount = 0;
	    rc = sqlite3_step(stmt);
	    while (rc != SQLITE_DONE && rc != SQLITE_OK)
	    {
	        rowCount++;
	        int colCount = sqlite3_column_count(stmt);
	        for (int colIndex = 0; colIndex < colCount; colIndex++)
	        {
	            int type = sqlite3_column_type(stmt, colIndex);
	            const char * columnName = sqlite3_column_name(stmt, colIndex);
	            if (type == SQLITE_INTEGER)
	            {
	                int valInt = sqlite3_column_int(stmt, colIndex);
	                printf("columnName = %s, Integer val = %d", columnName, valInt);
	            }
	            else if (type == SQLITE_FLOAT)
	            {
	                double valDouble = sqlite3_column_double(stmt, colIndex);
	                printf("columnName = %s,Double val = %f", columnName, valDouble);
	            }
	            else if (type == SQLITE_TEXT)
	            {
	                const unsigned char* valChar = sqlite3_column_text(stmt, colIndex);
	                results = new char[strlen((const char*)valChar)];
	                strcpy(results, (const char*)valChar);
	                printf("columnName = %s,Text val = %s", columnName, valChar);
	                delete [] (valChar);
	                return;
	            }
	            else if (type == SQLITE_BLOB)
	            {
	                printf("columnName = %s,BLOB", columnName);
	            }
	            else if (type == SQLITE_NULL)
	            {
	                printf("columnName = %s,NULL", columnName);
	            }
	        }
	        printf("Line %d, rowCount = %d", rowCount, colCount);

	        rc = sqlite3_step(stmt);
	    }

	    rc = sqlite3_finalize(stmt);
	}
}

void
Config::getConfigContext(string config){

	sqlite3* db = NULL;
	int rc = sqlite3_open(config.c_str(), &db);
	if ( rc ) {
		cout << "Failed to open db" << endl;
	} else {
		_contextmap[config] = db;
		cout << "Opened db added to context list" << endl;
	}
}

} /* namespace Util */
