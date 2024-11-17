#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	size_t capacity;
	char *data;
} sVector;


void svector_init(sVector *this) {
	this->capacity = 0;
	this->data = NULL;

	return;
}

void push_back(sVector *this, char val) {
	if (!this->capacity) {
		this->data = (char*)malloc(sizeof(char));
		this->data[0] = val;
		++this->capacity;
		return;
	}
	
	size_t size = this->capacity;
	this->data = (char*)realloc(this->data, (size + 1) * sizeof(char));
	this->data[size] = val;
	++this->capacity;
	
	return;
}

void destroy_vector(sVector *this) {
	free(this->data);
	this->data = NULL;
	this->capacity = 0;
	return;
}

int main() {
	sVector svec;
	svector_init(&svec);
	FILE *file = fopen("commands.txt", "w+");
	size_t commCnt = 1;
	char *exit = "q\n";
	char command[20];
	size_t length = sizeof(command);
	size_t commNo = 0;
	size_t no = 0;
	int ch;
	char tmp;
	
	while (1) {
		memset(command, 0, length);
		puts("Input command or [q] for exit");
		fgets(command, length, stdin);
		if (!(strcmp(exit, command))) {
			break;
		}
		fprintf(file, "%zu %c %s", commCnt++, '|', command);
	}
	system("clear");
	rewind(file);
	
	puts("Input commands No");
	scanf("%zu", &commNo);
	while (fscanf(file, "%zu", &no) != EOF) {
		if (no == commNo) {
			fseek(file, 3, SEEK_CUR);
			while ((ch = fgetc(file)) != '\n') {
				push_back(&svec, (char)ch);
			}
			system(svec.data);
			break;
		}
		while ((tmp = fgetc(file)) != '\n');
	}

	destroy_vector(&svec);
	fclose(file);

	return 0;
}
