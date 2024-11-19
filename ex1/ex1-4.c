int lineFilterPrint(const char * line, void * context){
	//guardar o conteúdo de line sem alterações
	char line_copy[LINE_LEN];
	for(int i = 0; line[i] != '\0'; i++)line_copy[i] = line[i];
	
	//obter o primeiro campo de line
	splitField(line_copy);
	
	//uniformizar o campo
	separatorUnify(line_copy);
	
	//comparar strings e retornar
	if(strcmp(line_copy, context) == 0){
		printf("%s", line);
		return 1;
	}
	
	return 0;
}
