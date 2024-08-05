#include <stdio.h>
#include <stdlib.h>

#define BUFLEN 1000
#define N 10 // last N chars will be printed

int _getline(char *, int);

int main(int argc, char *argv[]) {
    char buf[BUFLEN], *bp;
    int n = N, len;

    buf[BUFLEN - 1] = '\0';

    bp = buf;

    while((len = _getline(bp, BUFLEN)) > 0) {
        bp += len;
    }
    
    if(argc > 1 && argv[1][0] == '-') {
        argv[1] += 1;
        n = atoi(argv[1]);
    }

    while(n-- > 0) {
        printf("%c", *(bp - n - 1));
    }

    putchar('\n');

    return 0;
}

int _getline(char *s, int max) {
    int i, c;

    i = 0;
    while(i < max) {
        c = getchar();
        
        if(c == '\n') {
            break;
        } else if(c == EOF) {
            return 0;
        } else {
            s[i++] = c;
        }
    }

    return i;
}
