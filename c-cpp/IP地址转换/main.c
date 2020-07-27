#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
    // IP地址转换：使用inet_ntoa 整型转字符串 
    //【内部维护了static数组，非线程安全，推荐inet_ntop】

    uint32_t uIP = 2071689994;
    struct in_addr addr;
    addr.s_addr = uIP;
    char * strIP = inet_ntoa(addr);
    printf("uint32_t->string: %u -> %s\n", uIP, strIP);


    // IP地址转换：使用inet_aton 字符串转整型
    const char * strIP1 = "10.123.123.123";
    struct in_addr addr1;
    int ret = inet_aton(strIP1, & addr1);
    if(ret == 0){
        printf("invalid ip address\n");
        return -1;
    }
    printf("string->uint32_t: %s -> %u\n", strIP1, addr1.s_addr);

    // inet_addr 也可以将字符串转整型
    // 【不推荐使用，因为返回值有歧义，当ip地址不合法时，会返回-1， 但-1是一个合法地址（255.255.255.255）。即地址不合法或地址为255.255.255.255 时都会返回-1】
    in_addr_t nIP = inet_addr("10.10.10.10");
    printf("ip=%u\n",nIP);

    return 0;
}