CXXFLAGS = -Wall -Wextra -ggdb
I = -I../Include
LIB = -lallegro_ttf -lallegro_font -lallegro_primitives -lallegro \
			-lallegro_audio -lallegro_acodec -lallegro_image

#PRINTLEVEL=-DPRINT_LEVEL
EXEC = bugboy

OBJS = region.o upgrade.o spider_boss.o spider.o seed.o fly.o ant.o enemy.o hero.o entity.o gameclass.o main.o

all: $(OBJS)
	g++ -o ../$(EXEC) $(OBJS) $(LIB) $(CXXFLAGS) 

%.o: ../Src/%.cpp
	g++ -c -o $@ $< $(CXXFLAGS) $(PRINTLEVEL) $(I)

clean:
	rm -f *.o
	rm -f ../$(EXEC)
