hello.exe:main.o
	gcc  $^  -o  $@
%.o:../%.c
	gcc -c  $<  -o  $@
    
.PHYONE:clean
clean:
	rm -rf *.o  hello.exe