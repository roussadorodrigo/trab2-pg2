int fillBookData(BookData * b, const char * line){
	char unsplit_line[MAX_LINE_WIDTH];
	
	//fazer uma cópia de line
	char line_copy[MAX_LINE_WIDTH];
	for(int i = 0; line[i] != '\0'; i++)
		line_copy[i] = line[i];
	
	
	//copiar informações para a estrutura
	int i = 1;
	while(i <= 6){
		unsplit_line = splitField(line_copy);
		if(unsplit_line == NULL)return 0;
		
		switch(i){
			case 1: 
				b->title = separatorUnify(line_copy);
				break;
				
			case 2:
				b->isbn = separatorUnify(line_copy);
				break;
				
			case 4:
				b->authors = separatorUnify(line_copy);
				break;
				
			case 6:
				b->publisher = separatorUnify(line_copy);
				break;
			}

		line_copy = unsplit_line;
		i++;
	}
	
	return 1;
}
