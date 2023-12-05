all: sum_rows sum_cols

sum_rows: sum.c 
	gcc -DSUM_ROWS -o sum_rows sum.c 

sum_cols: sum.c 
	gcc -DSUM_COLS -o sum_cols sum.c 

clean:
	rm -f sum_rows sum_cols