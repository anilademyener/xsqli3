#ifndef XSQLIB_H
#define XSQLIB_H

#define APP_ID "xsqli3"
#define APP_TITLE "XSQLi3"
#define GIT_PAGE "https://github.com/anilademyener/lib-xsqlite3"
#define XSQLI3_VERSION "1.0.0-beta"

#ifdef __linux__
#define OS "linux"
#elif _WIN32
#define OS "windows"
#else
#define OS "other"
#endif

#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

sqlite3 *xs_db;
sqlite3_stmt *xs_stmt;
int xs_rc;
char xs_db_file[25];

void xs_init(char db_file[25]);
void xs_open();
void xs_close();
const char *xs_get_text(char *cmd);
const int xs_get_int(char *cmd);
const char *xs_sqlite_version();
void xs_info();
void xs_execute(char *cmd);
  
#endif // XSQLIB_H
