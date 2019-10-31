all : $(patsubst %.vala,%.c,$(wildcard *.vala))

%.c: %.vala
	valac --ccode $^ -o $@

clean:
	rm *.c
