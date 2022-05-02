#include "threads.h"


void process_user_msgs(void){
    t_log* logger = log_create("messages.log","PROCESS_USER_MSGS",false,LOG_LEVEL_TRACE);
    log_debug(logger,"PROCESS STARTING");
    int msgsc = 0;

    sem_wait(&producer);

    while(1){
        if(msgsc == 10){
            msgsc = 0;
            sem_post(&consumer);
            sem_wait(&producer);
            continue;
        }

        char* user_input = readline("Wite something (Press 'Enter' to finish) >> ");
        if(strcmp(user_input,"") == 0){
            log_debug(logger,"PROCESS FINISHED");
            exit(0);
        }
        log_info(logger,user_input);
        msgsc++;
        
    }

}

void create_backup(void){
    
    /*
        You can uncomment the commented lines to log a message every time
        'create_backup()' function runs
    */
   
    // t_log* logger = log_create(NULL,"BACKUP",true,LOG_LEVEL_TRACE);
    int i = 0;
    while(1){
        sem_wait(&consumer);
        // printf("\n");
        system("mkdir -p backup/");
        system("cp messages.log backup/logs_backup.log");
        // log_trace(logger,"Logs backup done\n");
        sem_post(&producer);
    }
}

int main(void)
{

    pthread_t log_msgs;
    pthread_t folder_managment;

    sem_init(&producer,0,1);
    sem_init(&consumer,0,0);

    pthread_create(&log_msgs,NULL,(void*)process_user_msgs,NULL);
    pthread_create(&folder_managment,NULL,(void*)create_backup,NULL);
    
    pthread_detach(log_msgs);
    pthread_detach(folder_managment);

    while(1){}    

    return EXIT_SUCCESS;
}
