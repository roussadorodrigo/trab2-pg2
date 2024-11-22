#ifndef BOOKS_H
#define BOOKS_H

#define LINE_LEN 512

#define MAX_BOOKS 310 //MAX_BOOKS coincide com o número máximo de linhas!
#define MAX_LINE_WIDTH 450
#define MAX_TITLE 220
#define SIZE_ISBN 20
#define MAX_AUTHORS 100
#define MAX_PUB_NAME 70

typedef struct book { 
 char title[MAX_TITLE]; 
 char isbn[SIZE_ISBN]; 
 char authors[MAX_AUTHORS]; 
 char publisher[MAX_PUB_NAME]; 
} BookData; 
 
typedef struct{ 
 BookData books[MAX_BOOKS]; 
 BookData *refs[MAX_BOOKS]; 
 int count; 			//quantidade de elementos preenchidos em books 
} Collection;

/***FUNCOES SE1***/
static char *splitField(char *str);
static int lenght(const char *str);
int strcmp_ic(const char *str1, const char *str2);
void separatorUnify(char str[]);
/******/

static int title_cmp(const BookData * b1, const BookData * b2);
static int isbn_cmp(const BookData * b1, const BookData * b2);

int processFile(const char * filename, int (*action)(const char * line, void * context), void * context);
int linePrintRaw(const char * line, void * context);
int lineFilterPrint(const char * line, void * context);
int fillBookData(BookData * b, const char * line);
int collAddBook(const char * line, void * context);
void collSortTitle(Collection * col);
void collSortRefIsbn(Collection * col);
int bookContainsAuthor(BookData * b, const char * word);

#endif
