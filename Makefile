compile_master :
	gcc -Iinclude apps/master.c src/cb/circular_buffer.c -o master_app

compile_slave :
	gcc -Iinclude apps/slave.c src/cb/circular_buffer.c -o slave_app

create_files :
	echo "sample text" > SharedMem
	echo "sample text" > SharedMemStat

run_master :
	echo "sample text" > SharedMem
	echo "sample text" > SharedMemStat	
	./master_app SharedMemStat SharedMem 

run_slave :	
	./slave_app SharedMemStat SharedMem 

clean :
	rm SharedMem
	rm SharedMemStat
	rm master_app
	rm slave_app

