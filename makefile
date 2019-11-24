CC = gcc
CFLAGS = -Iheaders -Isrc
DEPS = fileloader.h gamemap.h buildingrelationgraph.h mesinkar.h mapmatrix.h buildingarray.h building.h point.h buildinglist.h player.h skillqueue.h skill.h
OBJ = main.o fileloader.o gamemap.o buildingrelationgraph.o mesinkar.o mapmatrix.o buildingarray.o building.o point.o buildinglist.o player.o skillqueue.o skill.o

%.o: %.c $(DEPS)
		$(CC) $(CFLAGS) -c -o $@ $<

main: $(OBJ)
		gcc $(CFLAGS) -o $@ $^