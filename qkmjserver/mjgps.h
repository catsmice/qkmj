#ifndef __MJGPS_H__
#define __MJGPS_H__

#define DEFAULT_GPS_PORT 7001
#define DEFAULT_GPS_IP "0.0.0.0"
#define MAX_PLAYER 500
#define LOGIN_LIMIT 200
#define ASK_MODE 1
#define CMD_MODE 2

/*
 * Data-file paths are built at runtime from the data directory:
 * $QKMJ_DATA_DIR if set, otherwise $HOME/.qkmj (auto-created on startup).
 * See init_data_dir() in mjgps.c.
 */
extern char RECORD_FILE[];
extern char INDEX_FILE[];
extern char NEWS_FILE[];
extern char BADUSER_FILE[];
extern char LOG_FILE[];
extern char GAME_FILE[];

#define DEFAULT_RECORD_FILE "qkmj.rec"  /* mjrec default; pass full path as argv[1], e.g. ~/.qkmj/qkmj.rec */
#define DEFAULT_MONEY 40000


struct player_record
{
    unsigned int id;
    char name[20];
    char password[15];
    long money;
    int level;
    int login_count;
    int game_count;
    long regist_time;
    long last_login_time;
    char last_login_from[60];
};

struct player_info
{
    int sockfd;
    int login;
    unsigned int id;
    char name[20];
    char username[30];
    long money;
    int serv;
    int join;
    int type;
    char note[80];
    int input_mode;
    int prev_request;
    struct sockaddr_in addr;
    int port;
    char version[10];
};

struct record_index_type
{
    char name[20];
    unsigned int id;
};

struct ask_mode_info
{
    int question;
    int answer_ok;
    char *answer;
};

char *lookup (struct sockaddr_in *);
char *genpasswd (char *);
int checkpasswd (char *, char *);

int check_user (int);
void write_record ();
void close_id (int);
void close_connection (int);
void shutdown_server ();


#endif
