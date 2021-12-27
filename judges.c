/*
 * Solution to judges for HSPT online 2019
 * by Jim Geist
 */

#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main()
{
    char line[100];

    int cases;
    scanf("%d\n", &cases);
    for (int c = 1; c <= cases; c++) {
	int n;
	fgets(line, 100, stdin);
	sscanf(line, "%d", &n);

	// each mask contains 1 bit set for the existence of a letter
	// in the corresponding word
	unsigned masks[16];
	
	for (int i = 0; i < n; i++) {
	    masks[i] = 0;

	    int ch;
	    
	    while ((ch = fgetc(stdin)) != -1) {
		if (ch == '\n') {
		    break;
		}
		ch = tolower(ch);
		if (isalpha(ch)) {
		    masks[i] |= (1 << (ch - 'a'));
		}
	    }
	}

	int minSize = 17;
	
	// enumerate all the possible subsets and find the smallest set
	// of words that have all the letters, which corresponds to all
	// bits set in the or of all the word masks
	for (int i = 0; i < (1 << (n + 1)) - 1; i++) {
	    unsigned mask = 0;

	    int setSize = 0;
	    for (int j = 0; j < n; j++) {
		if ((i & (1 << j)) == 0) {
		    continue;
		}
		setSize++;
		mask |= masks[j];
	    }

	    if (mask != ((1 << 26) - 1)) {
		continue;
	    }
	    
	    if (setSize < minSize) {
		minSize = setSize;
	    }
	}
	printf("Judge List #%d: %d\n", c, minSize == 17 ? -1 : minSize);
    }       
}
