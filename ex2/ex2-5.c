void collSortTitle( Collection *col ){
    for(int i = 0; i <= col->count; i++){                    //enquato ir for menor ou i
        qsort(col->books, col->count, sizeof(Bookdata), strcmp_ic);col->books->title[i], col->books->title[i+1]
    }
  
//para usar no programa de teste, parametros de strcmp_ic; // col->books->title[i], col->books->title[i+1] \\
}
