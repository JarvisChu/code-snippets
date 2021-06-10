/*
 * 字节序：CPU存储数据时候的字节顺序
 * 比如：0x12345678
 * 大端：【低字节在高地址】地址由低到高依次存储为 0x12 0x34 0x56 0x78 
 * 小端：【低字节在低地址】地址由低到高依次存储为 0x78 0x56 0x34 0x12 
 * 
 * Intel x86/AMD 小端
 * ARM MIPS 大端
 * 
 * 网络上传输数据普遍采用的都是大端
 */

#include <stdio.h>

/* IsBigEndian: check system endian
 */
bool IsBigEndian()
{
    short n = 1;
    if( ((unsigned char*) &n)[0] == 1 ){
        return false;
    }
    return true;
}

/* SwapEndian: convert a little endian int16 to a big endian int16 or vica verca
 * vec: int16 array
 * len: length of vec
 */
void SwapEndian(short vec[],int len)
{
    for(int i = 0; i < len; i++){
        short tmp = vec[i];
        unsigned char *p1 = (unsigned char *) &vec[i]; 
        unsigned char *p2 = (unsigned char *) &tmp;
        p1[0] = p2[1]; 
        p1[1] = p2[0];
    }
}

void Short2LittleEndianBytes(short st, unsigned char bs[2])
{
    // change to little endian
    if( IsBigEndian()){
        SwapEndian(&st, 1);
    }

    bs[0] = ((unsigned char*)&st)[0];
    bs[1] = ((unsigned char*)&st)[1];
}

short LittleEndianBytes2Short(unsigned char low, unsigned char high)
{
    short st = 0;
    ((unsigned char*)&st)[0] = low;
    ((unsigned char*)&st)[1] = high;

    if(IsBigEndian()){
        SwapEndian(&st,1);
    }

    return st;
}

int main()
{
    printf("Current System Endian is: %s endian\n", IsBigEndian() ? "big":"little");

    short st = 0x0102;
    unsigned char bytes[2];
    Short2LittleEndianBytes(st, bytes);
    printf("Short2LittleEndianBytes: short: 0x%x, byte0:0x%x, byte1:0x%x\n", st, bytes[0], bytes[1]);

    printf("LittleEndianBytes2Short: 0x%x\n", LittleEndianBytes2Short(bytes[0], bytes[1]));

    return 0;
}