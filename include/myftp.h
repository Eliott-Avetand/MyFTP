/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** myftp.h
*/
#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <sys/select.h>

// Clients
enum transfer {
    NONE,
    PASSIVE,
    ACTIVE
};

typedef struct client_s {
    int fd;
    int data_fd;
    int host_port;
    char *username;
    char *path;
    bool password;
    bool logged_in;
    bool is_connected;
    enum transfer mode;
    struct client_s *next;
} client_t;

typedef struct server_s {
    int fd;
    int nfds;
    fd_set main_set;
    fd_set tmp_set;
    char *path;
} server_t;

int handle_errors(char *port, char *path);
void my_ftp(int port, char *path);
int create_socket(void);
void configure_socket(int sfd, int port);

// commands
enum Mode {
    HELP,
    COMMAND
};

void middleware(char *input, client_t *client);
void pass(char **words, client_t *client, enum Mode mode);
void user(char **words, client_t *client, enum Mode mode);
void cwd(char **words, client_t *client, enum Mode mode);
void cdup(char **words, client_t *client, enum Mode mode);
void quit(char **words, client_t *client, enum Mode mode);
void dele(char **words, client_t *client, enum Mode mode);
void pwd(char **words, client_t *client, enum Mode mode);
void pasv(char **words, client_t *client, enum Mode mode);
void port(char **words, client_t *client, enum Mode mode);
void help(char **words, client_t *client, enum Mode mode);
void noop(char **words, client_t *client, enum Mode mode);
void retr(char **words, client_t *client, enum Mode mode);
void stor(char **words, client_t *client, enum Mode mode);
void list(char **words, client_t *client, enum Mode mode);

typedef struct func_s {
    char *name;
    void (*func)(char **, client_t *client, enum Mode mode);
} func_t;

static const func_t commands_s[14] = {
    {"CWD", cwd},
    {"CDUP", cdup},
    {"DELE", dele},
    {"PWD", pwd},
    {"PASV", pasv},
    {"PORT", port},
    {"HELP", help},
    {"NOOP", noop},
    {"RETR", retr},
    {"STOR", stor},
    {"LIST", list},
    {"QUIT", quit},
    {"USER", user},
    {"PASS", pass}
};

// utils functions
bool is_number(char *str);
void clean_str(char *input);
char **my_str_to_word_array(char *str);
void clean_loop(char **commands, char *command);
void new_client(client_t **clients, int fd, char *path);
void client_leave(client_t **clients, int fd);
client_t *get_client(client_t **clients, int fd);
int double_array_len(char **array);
void free_double_array(char **array);
