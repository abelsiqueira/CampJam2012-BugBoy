CXXFLAGS = -Wall -Wextra -Werror -ggdb
I = -I../Include
LIB = -lallegro_ttf -lallegro_font -lallegro_primitives -lallegro \
			-lallegro_audio -lallegro_acodec -lallegro_image

#PRINTLEVEL=-DPRINT_LEVEL
MUTE=-DMUTE
EXEC = bugboy

ENEMIES = cricket_boss.o spider_boss.o cricket.o spider.o fly.o ant.o enemy.o 
GAMECLASS = gameclass_update.o gameclass_keyboard.o gameclass_draw.o gameclass.o
OBJS = region.o upgrade.o seed.o $(ENEMIES) hero.o entity.o $(GAMECLASS) main.o

all: $(OBJS)
	g++ -o ../$(EXEC) $(OBJS) $(LIB) $(CXXFLAGS) 

%.o: ../Src/%.cpp
	g++ -c -o $@ $< $(CXXFLAGS) $(PRINTLEVEL) $(I) $(MUTE)

clean:
	rm -f *.o

purge: clean
	rm -f ../$(EXEC)
