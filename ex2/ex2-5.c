void collSortTitle( Collection *col ){
        qsort(col->books, col->count, sizeof(Bookdata), title_cmp);
    }

//for(int i = 0; i <= col->count; i++){                    //enquato ir for menor ou i
//para usar no programa de teste, parametros de strcmp_ic; // col->books->title[i], col->books->title[i+1] \\
