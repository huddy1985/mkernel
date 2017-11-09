/* String operations header*/
#include "string.h"

int strlen(const char *str)
{
        int cnt;

        asm("cld\n"
                "repnz\n"
            	"scasb" :
            	"=c" (cnt) : "D" (str), "0" (-1), "a" (0));

        return -2 - cnt;
}

int strcmp(const char *__s1, const char *__s2)
{
        register unsigned long int __d0, __d1;
        register int __res;

        __asm__ __volatile__
                ("cld\n"
                 "1:\n\t"
                 "lodsb\n\t"
                 "scasb\n\t"
                 "jne	2f\n\t"
                 "testb	%%al, %%al\n\t"
                 "jne	1b\n\t"
                 "xorl	%%eax, %%eax\n\t"
                 "jmp	3f\n"
                 "2:\n\t"
                 "sbbl	%%eax, %%eax\n\t"
                 "orb	$1, %%al\n"
                 "3:"
                 : "=a" (__res), "=&S" (__d0), "=&D" (__d1)
                 : "1" (__s1), "2" (__s2)
                 : "cc");

        return __res;
}