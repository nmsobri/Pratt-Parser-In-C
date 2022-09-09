cc = gcc
src = $(wildcard *.c)
obj = $(src:.c=.o)
exe = main

$(exe):$(obj)
	@$(cc) -g $^ -o $@

$(obj):%.o:%.c
	@$(cc) -c -g $< -o $@

run:$(exe)
	@./$< ||:

clean:
	@rm -rf *.o *.exe $(exe); clear