#include <stdio.h>
#include <time.h>
#include <string>

#define __MODULE__ "main"

std::string get_time()
{
    time_t t = time(0);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y/%m/%d %X", localtime(&t));
    return std::string(tmp);
}

#define LOG_NOTICE 0
#define LOG_WARNING 1
#define LOG_ERROR 2

#define LOG(LEVEL,fmt,...)\
    do{\
        FILE * fp = fopen("log.txt", "a+");\
        if(fp){\
            if(LOG_NOTICE == LEVEL){\
                fprintf(stdout,"NOTICE:[%s][%s]:[%s:%d]"fmt"\n",get_time().c_str(),__MODULE__,__FILE__,__LINE__,##__VA_ARGS__);\
                fprintf(fp,"NOTICE:[%s][%s]:[%s:%d]"fmt"\n",get_time().c_str(),__MODULE__,__FILE__,__LINE__,##__VA_ARGS__);\
            }\
            if(LOG_WARNING == LEVEL){\
                fprintf(stdout,"WARNING:[%s][%s]:[%s:%d]"fmt"\n",get_time().c_str(),__MODULE__,__FILE__,__LINE__,##__VA_ARGS__);\
                fprintf(fp,"WARNING:[%s][%s]:[%s:%d]"fmt"\n",get_time().c_str(),__MODULE__,__FILE__,__LINE__,##__VA_ARGS__);\
            }\
            if(LOG_ERROR == LEVEL){\
                fprintf(stdout,"ERROR:[%s][%s]:[%s:%d]"fmt"\n",get_time().c_str(),__MODULE__,__FILE__,__LINE__,##__VA_ARGS__);\
                fprintf(fp,"ERROR:[%s][%s]:[%s:%d]"fmt"\n",get_time().c_str(),__MODULE__,__FILE__,__LINE__,##__VA_ARGS__);\
            }\
            fclose(fp);\
        }\
    }while(0)

#define NOTICE(fmt,...) LOG(LOG_NOTICE, fmt, ##__VA_ARGS__)
#define WARNING(fmt,...) LOG(LOG_WARNING, fmt, ##__VA_ARGS__)
#define ERROR(fmt,...) LOG(LOG_ERROR, fmt, ##__VA_ARGS__)

int main()
{
    int i = 2015;
    const char * notice = "Hello World";
    NOTICE(" %s %d", notice, i); // NOTICE:[2015/09/02 22:08:37][main]:[h:\programming\anything\main.cpp:83] Hello World 2015
    return 1;
}