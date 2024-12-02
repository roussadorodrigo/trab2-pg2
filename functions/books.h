#ifndef BOOKS_H
#define BOOKS_H

#define LINE_LEN 512

#define MAX_BOOKS 296 //MAX_BOOKS coincide com o número máximo de linhas!
#define MAX_LINE_WIDTH 435+1
#define MAX_TITLE 200+1
#define SIZE_ISBN 10+1
#define MAX_AUTHORS 92+1
#define MAX_PUB_NAME 51+1

/**
 * @struct
 * 
 */
typedef struct book { 
 char title[MAX_TITLE]; 
 char isbn[SIZE_ISBN]; 
 char authors[MAX_AUTHORS]; 
 char publisher[MAX_PUB_NAME]; 
} BookData; 

/**
 * @struct
 * 
 */
typedef struct{ 
 BookData books[MAX_BOOKS]; 
 BookData *refs[MAX_BOOKS]; 
 int count; 			//quantidade de elementos preenchidos em books 
} Collection;

/**<Funções usadas na SP1 - as suas descrições podem ser aí encontradas*/
static char *splitField(char *str);
int lenght(const char *str);
int strcmp_ic(const char *str1, const char *str2);
void separatorUnify(char str[]);


/** 
 * 
 * @brief função que compara alfabeticamente os campos "title" indicadas pelos pointers passados como parâmetros
 * 
 * @param const BookData * b1 e b2: pointers para as estruturas BookData cujos títulos vão ser comparados
 * 
 * @return int: retorna um valor inteiro maior que zero se a estrutura apontada por b1 for alfabeticamente maior que a apontada por
 *              b2, menor que zero se o contrário se verificar ou ainda zero, caso os títulos sejam iguais 
 * 
 * @note esta função baseia-se na strcmp_ic (SE1), visto que, na realidade, estamos a comparar duas strings
*/
static int title_cmp(const BookData * b1, const BookData * b2);


/**
 * 
 * @brief função que compara alfabeticamente os campos "isbn" indicadas pelos pointers passados como parâmetros
 * 
 * @param const BookData * b1 e b2: pointers para as estruturas BookData cujos isbn vão ser comparados
 * 
 * @return int: retorna um valor inteiro maior que zero se a estrutura apontada por b1 tiver um isbn superior que a apontada por
 *              b2, menor que zero se o contrário se verificar ou ainda zero, caso os isbn sejam iguais 
 * 
 * @note esta função baseia-se na strcmp_ic (SE1), visto que, na realidade, estamos a comparar duas strings
*/
int isbn_cmp(const BookData * b1, const BookData * b2);


/**
 * 
 * @brief função que, dado um isbn, procura o livro a que este corresponde
 * 
 * @param const char *search_isbn: string que contém o isbn pelo qual se pretende procurar
 * @param Collection *col: collection onde vai ser procurado o livro
 * 
 * @return BookData *: ponteiro para a estrutura BookData a que corresponde o isbn passado no primeiro parâmetro (ou NULL, caso este
 *                     não seja encontrado)
 * 
 * @note esta função baseia-se nafunção bsearch da biblioteca standard, logo, o array de procura tem de estar organizado por isbn
*/
BookData *find_book_by_isbn(const char *search_isbn, Collection *col);


/**
 * 
 * @brief função que abre um ficheiro em modo de leitura e, a cada linha, aplica a função passada como parâmetro
 * 
 * @param const char *filename: nome do ficheiro a abrir (tem de incluir a extensão)
 * @param int (*action)(const char * line, void * context), void * context: função que vai ser aplicada a cada linha
 * 
 * @return int: soma dos retornos das sucessivas chamadas à função action, ou -1 caso haja algum erro
 * 
 * @note quando se verifica um erro de abertura do ficheiro, a função escreve uma mensagem de erro no standard output
*/
int processFile(const char * filename, int (*action)(const char * line, void * context), void * context);


/**
 * 
 * @brief função que mostra no standard output o conteúdo integral do parâmetro line (sem alterações)
 * 
 * @param const char *line: linha de texto
 * @param void *context: não usado nesta função (mantido por razões de igualdade entre as funções destinadas a serem
 *                       passadas como parâmetros a processFile)
 * 
 * @return int: retorna 1
 * 
 * @note esta função destina-se a ser passada como parâmetro a processFile de forma a mostrar no standard output o
 *       conteúdo integral do ficheiro e permitir que esta possa retornar o valor total de linhas apresentadas
*/
int linePrintRaw(const char * line, void * context);


/**
 * 
 * @brief função que mostra no standard output o conteúdo integral do parâmetro line (sem alterações), se o primeiro
 *        campo deste (primeira palavra) for igual à string passada no parâmetro context
 * 
 * @param const char *line: linha de texto
 * @param void *context: string que vai ser comparada com o primeiro campo de cada linha
 * 
 * @return int: retorna 1 se a linha for mostrada no standard output (o primeiro campo de line for igual a context) ou 
 *              0 caso não seja (o primeiro campo de line for diferente de context)
 * 
 * @note esta função destina-se a ser passada como parâmetro a processFile de forma a mostrar no standard output o
 *       conteúdo das linhas que corrrespondem aos critérios acima descritos, permitindo a esta que possa retornar o
 *       número de linhas mostradas
*/
int lineFilterPrint(const char * line, void * context);


/**
 * 
 * @brief função que, dada uma linha de texto (em formato csv), preenche uma estrutura BookData com os respetivos campos
 * 
 * @param BookData *b: ponteiro para a estrutura BookData que vai ser preenchida com os dados da linha de texto
 * @param const char *line: linha que contém os dados para preencher a estrutura
 * 
 * @return int: retorna 1 se a estrutura for preenchida ou 0 caso contrário (erro de preenchimento)
*/
int fillBookData(BookData * b, const char * line);


/**
 * 
 * @brief função que, dada uma estrutura BookData, a preenche e adiciona a uma estrutura Collection
 * 
 * @param const char *line: linha de texto
 * @param void *context: ponteiro para a estrutura Collection à qual a estrutura BookData vai ser adicionada
 * 
 * @return int: retorna 1 se a estrutura for adicionada com sucesso à Collection ou 0 se isto não for possível
 *              (por esta estar cheia, por exemplo)
 * 
 * @note esta função não inicializa o campo refs relativo à estrutura BookData; usa a função fillBookData para preencher 
 *       a estrutura
*/
int collAddBook(const char * line, void * context);


/**
 * 
 * @brief função que, dada uma estrutura Collection, ordena o conteúdo do campo books por ordem alfabética
 * 
 * @param Collection *col: ponteiro para a estrutura Collection cujo campo "books" vai ser ordenado
 * 
 * @return não tem return
*/
void collSortTitle(Collection * col);


/**
 * 
 * @brief função que, dada uma estrutura Collection, ordena o conteúdo do campo refs por ordem de isbn
 * 
 * @param Collection *col: ponteiro para a estrutura Collection cujo campo "refs" vai ser ordenado
 * 
 * @return não tem return
 * 
 * @note esta função, antes de ordenar o array refs, inicia-o com a mesma ordem do array "books"
*/
void collSortRefIsbn(Collection * col);


/**
 * 
 * @brief função que procura o nome passado como parâmetro no campo de autores da estrutura passada como
 *        parâmetro
 * 
 * @param BookData *b: estrutura book data cujo campo "authors" vai ser alvo de busca
 * @param consta char *word: nome a procurar
 * 
 * @return 1 se o nome for encontrado e 0 se não for
 * 
 * @note esta função apenas pesquisa um dos nomes, ou seja, "parte" o campo authors sempre que há um espaço
 *       o que só permite que se faça busca por um único nome
*/
int bookContainsAuthor(BookData * b, const char * word);
#endif
