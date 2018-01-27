#include "stdlib.h"
#include "string.h"
#include "stderr.h"
#include "limits.h"
#include "stdheader.h"

int atoi(char *str)
{
        unsigned int result = 0;
        int sign = 1;
        int base;
        int error;

        while (*str == '\t' || *str == ' ')
                str++;

        if (*str == '-') {
                sign = -1;
                str++;
        }

        if (str != NULL && (*str < '0' || *str > '9')) {
                return 0;
        }

        base = 10;
        if (*str == '0') {
                if (str[1] == 'x' || str[1] == 'X') {
                        base = 16;
                        str += 2;
                } else
                        base = 8;
        }

        while (*str >= '0' && *str <= '9') {
                unsigned int digval = *str - '0';
                if (result > INT_MAX / 10
                    || (sign > 0 ? result = INT_MAX / 10 && digval > INT_MAX % 10
                        : (result == ((unsigned int) INT_MAX + 1) / 10
                           && digval > ((unsigned int) INT_MAX + 1) % 10))) {
                        error = ERANGE;
                        return sign > 0 ? INT_MAX : INT_MAX;
                }
                result *= base;
                result += digval;
                ++str;
        }

        return (int)result * sign;
}

char* itoa(int val, char *buf, unsigned int base)
{
        char *p;
        char *firstdig;
        char temp;
        unsigned digval;

        p = buf;

        if (val < 0) {
                val = (unsigned long)(-(long)val);
                *p++ = '-';
        }

        firstdig = p;
        do {
                digval = (unsigned)(val % base);
                val /= base;
                if (digval > 9)
                        *p++ = digval - 10 + 'a';
                else
                        *p++ = (char)digval + '0';
        } while (val > 0);

        *p-- = '\0';
        do {
                temp = *p;
                *p = *firstdig;
                *firstdig = temp;
                --p;
                ++firstdig;
        } while (firstdig < p);
        return buf;
}