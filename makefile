PREFIX =.
IDIR =.
CC=gcc 
CFLAGS=-g -fPIC -Wall -I$(IDIR)
LIBSONAME=libpregalla.so

ODIR=.
LDIR =./lib
LDIR2 = /lib64

LIBS=-lm

src = $(wildcard *.c)
obj = $(src:.c=.o)
dep = $(obj:.o=.d)  # one dependency file for each source


LDFLAGS = -lGL -lglut -lpng -lz -lm


all: $(obj)
	gcc -shared -o $(LIBSONAME) $(obj)

-include $(dep)   # include all dep files in the makefile
# rule to generate a dep file by using the C preprocessor
# (see man cpp for details on the -MM and -MT options)
%.d: %.c
	@$(CC) $(CFLAGS) $< -MM -MT $(@:.d=.o) >$@

%.o: %.c 
#$(CC) -o $@ -c $< $(CFLAGS)
#@$(CC) $(CFLAGS) $< -MM -MT $(@:.d=.o) >$@
#$(CC) -MM $(CFLAGS) $*.c > $*.d
	$(CC) -c $(CFLAGS) $*.c -o $*.o





.PHONY: clean
clean:
	rm -f $(ODIR)/*.o *.d
	mv $(LIBSONAME) old_libs/$(LIBSONAME)-`date +"%F-%T"`

.PHONY: cleandep
cleandep:
	rm -f $(dep)

#%.o: %.c $(dep)
#	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: install
install: all
	mkdir -p $(DESTDIR)$(PREFIX)/lib
	cp $(LIBSONAME) $(DESTDIR)$(PREFIX)/lib/$(LIBSONAME)
	mv ./lib/$(LIBSONAME) old_libs/$(LIBSONAME)-`date +"%F-%T"`-from_lib
	sudo cp $(LIBSONAME) $(LDIR2)/$(LIBSONAME)
	sudo ldconfig

.PHONY: uninstall
uninstall:
	rm -f $(DESTDIR)$(PREFIX)/lib/$(LIBSONAME)




