#include "xsqlib.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
  int i =0;
  for (;i<argc;){
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    i++;
  }
  printf("\n");
  return 0;
}

void xs_init(char db_file[25]){
  strcpy(xs_db_file, db_file);
  return;
}

void xs_open(){
  xs_rc = sqlite3_open(xs_db_file, &xs_db);
  return;
}

void xs_close(){
  sqlite3_close(xs_db);
  return;
}

const char *xs_get_text(char *cmd){
  xs_rc = sqlite3_prepare_v2(xs_db, cmd, -1, &xs_stmt, 0);
  xs_rc = sqlite3_step(xs_stmt);
  const char *return_value = sqlite3_column_text(xs_stmt, 0);
  return return_value;
}

const int xs_get_int(char *cmd){
  xs_rc = sqlite3_prepare_v2(xs_db, cmd, -1, &xs_stmt, 0);
  xs_rc = sqlite3_step(xs_stmt);
  const int return_value = sqlite3_column_int(xs_stmt, 0);
  return 0;
}

const char *xs_sqlite_version(){
  return xs_get_text("SELECT SQLITE_VERSION()");
}

void xs_info(){
  printf("%s (%s) | %s\n", APP_TITLE, APP_ID, GIT_PAGE);
  int loop_value = strlen(APP_TITLE) + strlen(APP_ID) + strlen(GIT_PAGE) + 6;
  for (int i=0; i<loop_value; i++){
    printf("=");
  }
  printf("\n");
  printf(" -> xsqli3 version: %s\n", XSQLI3_VERSION);
  printf(" -> sqlite version: %s\n", xs_sqlite_version());
  return;
}

void xs_execute(char *cmd){
  char *zErrMsg;
  xs_rc = sqlite3_exec(xs_db, cmd, callback, 0, &zErrMsg);
  if (xs_rc != SQLITE_OK){
    printf("[!] ERROR: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  } else {
    printf("[OK]\n");
  }
  return;
}

// it's not recommended
// using main function
int main(int argc, char *argv[]){
  xs_init("my.db");
  xs_open();
  //xs_info();
  char *command = "CREATE TABLE COMPANY("	\
    "ID INT PRIMARY KEY     NOT NULL,"		\
    "NAME           TEXT    NOT NULL,"		\
    "AGE            INT     NOT NULL,"		\
    "ADDRESS        CHAR(50),"			\
    "SALARY         REAL );";
  xs_execute(command);
  xs_close();
  return 0;
}
