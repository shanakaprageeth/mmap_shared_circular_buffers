compile_master :
	gcc master/main.c circular_buffer.c -o master_exe

compile_slave :
	gcc slave/main.c circular_buffer.c -o slave_exe

create_files :
	echo "sample text" > SharedMem
	echo "sample text" > SharedMemStat

run_master :
	echo "sample text" > SharedMem
	echo "sample text" > SharedMemStat	
	./master_exe SharedMemStat SharedMem 

run_slave :	
	./slave_exe SharedMemStat SharedMem 

clean :
	rm SharedMem
	rm SharedMemStat
	rm master_exe
	rm slave_exe

