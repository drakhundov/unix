#include <stdio.h>

#define IN 1   // in word
#define OUT 0 // out of word

/* counts how much words,
   lines, symbols does user
   entered */

int main() {
	int c, state;
	long nw, nl, nc;

	state = IN;
	nc = nw = nl = 0;

	while(c != EOF) {
		c = getchar();

		if(c == '\n' || c == '\t' || c == ' ') {
			state = OUT;

			if(c == '\n')
                ++nl;

			continue;
		} else if(state == OUT) {
			state = IN;
			++nw;
		}

        if(c != EOF)
            ++nc;
	}

	printf("characters: %ld\n", nc);
	printf("words: %ld\n", nw);
	printf("lines: %ld\n", nl);

	return 0;
}
