TARGET=../puyo
CC=gcc
CXX=g++
CFLAGS=-g -O2 -w -mwindows
CXXFLAGS=$(CFLAGS)
LDFLAGS=-static-libgcc -static-libstdc++
INCDIR=-I"../DXLib/"
LIBDIR=-L"../DXLib/"
LIBS=-lDxLib -lDxUseCLib -lDxDrawFunc -ljpeg -lpng -lzlib -ltiff -ltheora_static -lvorbis_static\
	 -lvorbisfile_static -logg_static -lbulletdynamics -lbulletcollision -lbulletmath
LIBS+=-lgdi32
OBJS=main.o dxApp.o board.o player.o control.o

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(INCDIR) $(LIBDIR) -o $@ $^ $(LIBS)
clean:
	@rm -fr $(TARGET).exe $(OBJS) *~ *.swp