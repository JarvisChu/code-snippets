#include <stdio.h>
#include <stdlib.h>


// 判断是否是回文数
// 思路：分解，然后重组数字
int isPalindrome(int x){
    if (x < 0) return 0;
    
    long reverse = 0; 
    int n = x;
    while(n > 0) {                      // 分解，step1
        int digit = n % 10;             // 分解，step2
        n /= 10;                        // 分解，step3
        reverse = reverse * 10 + digit; // 重组
    }

    return x == reverse;
}


int main()
{
    printf("%d \n", isPalindrome(121) );
    printf("%d \n", isPalindrome(-121) );
    printf("%d \n", isPalindrome(10) );
    printf("%d \n", isPalindrome(123454321) );
    return 0;
}