#ifndef THREADS_H
#define THREADS_H

#include <commons/log.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <pthread.h>
#include <strings.h>
#include <semaphore.h>

sem_t producer;
sem_t consumer;

void process_user_msgs(void);
void create_backup(void);

#endif