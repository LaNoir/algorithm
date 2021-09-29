
#include <string.h>
#include <stdio.h>
using namespace std;

char buf[210], * words[110];
int wcnt;

void split() {
	char* token = strtok(buf, " ");
	while (token) {
		words[wcnt++] = token;
		token = (strtok(NULL, " "));
	}
}

void insertionSort() {
	int i, j;
	for (i = 1; i < wcnt; ++i) {
		char* tp = words[i];
		for (j = i - 1; j >= 0; --j) {
			if (strcmp(words[j], tp) > 0) {
				words[j + 1] = words[j];
			}
			else break;
		}
		words[j + 1] = tp;
	}
}

void output() {
	int i, cnt = 1;
	for (i = 1; i < wcnt; ++i) {
		if (strcmp(words[i - 1], words[i]) == 0) {
			cnt++;
		}
		else {
			printf("%s : %d\n", words[i - 1],cnt);
			cnt = 1;
		}
	}
	printf("%s : %d\n", words[i - 1], cnt);
}

int main() {
	
	//freopen("input.txt", "r", stdin);
	while (scanf(" %[^\r\n]s", buf)) {
		if (strcmp(buf, "END") == 0) break;
		wcnt = 0;
		split();
		insertionSort();
		output();
	}
	
}