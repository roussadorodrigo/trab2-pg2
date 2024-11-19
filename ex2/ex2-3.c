int collAddBook(const char * line, void * context){
	BookData * b;
	
	//verificar se há espaço para o novo elemento
	if(context->count == MAX_BOOKS)return 0;
	
	//verificar se a informação é válida (e preencher a nova estrutura)
	if(fillBookData(b, line) == 0)return 0;
	
	//preencher a estrutura com o novo elemento
	context->books[context->count] = *b;
	context->refs[context->count] = NULL;
	count++;

	return 1;
}
