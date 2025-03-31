CFLAGS = -g
src_files := $(wildcard Form1040/*.c)
obj_files := $(src_files:.c=.o)
hdr_files := $(wildcard Form1040/*.h)

main: $(obj_files)
	$(CC) $(CFLAGS) -o main $(obj_files)

$(obj_files): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm Form1040/*.o
