#include <stdio.h>
#include <string.h>

#define MAX_LINE 256
#define REDUCTION_FACTOR 3

void chop(char *line)
{
	size_t len;
	len = strlen(line);
	if (len > 0) {
		line[len - 1] = '\0';
	}
}

void reduceLine(char *line, char *reducedLine)
{
	size_t i;
	size_t len;
	size_t charCount = 0;

	len = strlen(line);

	for (i = 0; i < len; i++) {
		if (i % REDUCTION_FACTOR != 0) {
			reducedLine[charCount++] = line[i];
		}
	}
	reducedLine[charCount] = '\0';
}

void reduce(const char *name)
{
	FILE *f;
	char line[MAX_LINE];
	char reducedLine[MAX_LINE];
	size_t lineCount = 0;

	f = fopen(name, "r");
	if (f == NULL) {
		perror(name);
		return;
	}

	while ((fgets(line, MAX_LINE, f)) != NULL) {
		lineCount++;
		chop(line);
		if (lineCount % REDUCTION_FACTOR != 0) {
			reduceLine(line, reducedLine);
			printf("%s\n", reducedLine);
		}
	}
	fclose(f);
}

int main(int argc, char *argv[])
{
	int i;

	for (i = 1; i < argc; i++) {
		reduce(argv[i]);
	}
}
