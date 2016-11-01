
OBJS= main.o futils.o mutils.o mdialog.o savescreen.o\
gamelogic00.o gamelogic01.o gamelogic02.o gamelogic03.o\
gamelogic04.o mapdata.o actionstate.o statefile.o
CFLAGS=
CC= gcc
INCLUDES=
LIBS= -lcurses -lm

HQWA: ${OBJS}
	${CC} ${CFLAGS} ${INCLUDES} -o $@ ${OBJS} ${LIBS}

main.o: main.c common.h gamelogic.h mapdata.h actionstate.h
	${CC} ${CFLAGS} -c main.c

futils.o: futils.c common.h
	${CC} ${CFLAGS} -c futils.c

mutils.o: mutils.c common.h
	${CC} ${CFLAGS} -c mutils.c

mdialog.o: mdialog.c common.h
	${CC} ${CFLAGS} -c mdialog.c

savescreen.o: savescreen.c common.h gamelogic.h mapdata.h actionstate.h
	${CC} ${CFLAGS} -c savescreen.c

gamelogic00.o: gamelogic00.c common.h gamelogic.h
	${CC} ${CFLAGS} -c gamelogic00.c

gamelogic01.o: gamelogic01.c common.h gamelogic.h mapdata.h actionstate.h
	${CC} ${CFLAGS} -c gamelogic01.c

gamelogic02.o: gamelogic02.c common.h gamelogic.h mapdata.h actionstate.h
	${CC} ${CFLAGS} -c gamelogic02.c

gamelogic03.o: gamelogic03.c common.h gamelogic.h actionstate.h
	${CC} ${CFLAGS} -c gamelogic03.c

gamelogic04.o: gamelogic04.c common.h gamelogic.h actionstate.h
	${CC} ${CFLAGS} -c gamelogic04.c

mapdata.o: mapdata.c common.h gamelogic.h mapdata.h
	${CC} ${CFLAGS} -c mapdata.c

actionstate.o: actionstate.c common.h gamelogic.h actionstate.h
	${CC} ${CFLAGS} -c actionstate.c

statefile.o: statefile.c common.h gamelogic.h mapdata.h actionstate.h
	${CC} ${CFLAGS} -c statefile.c



