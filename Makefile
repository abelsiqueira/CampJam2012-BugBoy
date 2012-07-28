CXXFLAGS = -Wall -Wextra -ggdb
LIB = -lallegro_ttf -lallegro_font -lallegro_primitives -lallegro \
			-lallegro_audio -lallegro_acodec -lallegro_image

OBJS = hero.o entity.o gameclass.o main.o

all: clean $(OBJS)
	g++ -o main $(OBJS) $(LIB) $(CXXFLAGS)

%.o: %.cpp
	g++ -c -o $@ $< $(CXXFLAGS)

clean:
	rm -f main
	rm -f *.o
