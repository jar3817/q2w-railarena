#CFLAGS = -ffast-math -O3 -w -DGAME_INCLUDE -DLINUX -fPIC
GLIB_CFLAGS = -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include
GLIB_LIBS = -lglib-2.0
CFLAGS = -std=c99 -pipe -g -O2 $(GLIB_CFLAGS)
LDFLAGS = -S
#ORIGDIR=src

OBJS = g_main.o

game.so: $(OBJS)
	ld -lm -shared -o $@ $(OBJS) $(LDFLAGS)
	chmod 0755 $@
	ldd $@

clean:
	/bin/rm -f $(OBJS) game.so

$*.o: $*.c
	$(CC) $(CFLAGS) -c $*.c

#$*.c: $*.c
#        tr -d '\015' < $*.c > $*.c

#$*.h: $*.h
#        tr -d '\015' < $(ORIGDIR)/$*.h > $*.h

# DO NOT DELETE

#fopen.o: g_local.h q_shared.h game.h
g_main.o: g_local.h g_types.h game.h

