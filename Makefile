CXXFLAGS = -Wall -Wextra -ggdb
LIB = -lallegro_ttf -lallegro_font -lallegro_primitives -lallegro \
			-lallegro_audio -lallegro_acodec -lallegro_image

OBJS = region.o upgrade.o spider_boss.o spider.o seed.o fly.o ant.o enemy.o hero.o entity.o gameclass.o main.o

all: $(OBJS)
	g++ -o main $(OBJS) $(LIB) $(CXXFLAGS)

%.o: %.cpp
	g++ -c -o $@ $< $(CXXFLAGS)

clean:
	rm -f main
	rm -f *.o
