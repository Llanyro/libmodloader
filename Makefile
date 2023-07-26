
## Project: LlanyModLib by git@llanyro
## Makefile created by Francisco Julio Ruiz Fernandez

all: make_lib
project: make_lib

TARGETDIR_PROJECT=output

COMPILE.cpp = g++ -std=c++17 -fPIC -g -c -O2 -Wall -Wno-unknown-pragmas
LINK.cpp = g++ -std=c++17 -shared -g

LIBS_PROJECT = \
	-ldl

OBJS_PROJECT = \
	$(TARGETDIR_PROJECT)/ModLoader.o \
	$(TARGETDIR_PROJECT)/ModObject.o \
	$(TARGETDIR_PROJECT)/ModInfo.o \
	$(TARGETDIR_PROJECT)/ModData.o \
	$(TARGETDIR_PROJECT)/ModCore.o \
	$(TARGETDIR_PROJECT)/ModBasicData.o \
	$(TARGETDIR_PROJECT)/ModInfoExtra.o


# Link or archive
make_lib: $(OBJS_PROJECT) 
	$(LINK.cpp) -o $(TARGETDIR_PROJECT)/libmod.so $(OBJS_PROJECT) $(LIBS_PROJECT)

# Compile source files into .o's
$(TARGETDIR_PROJECT)/ModLoader.o: ModLoader.cpp
	$(COMPILE.cpp) -o $(TARGETDIR_PROJECT)/ModLoader.o ModLoader.cpp

# Objects
$(TARGETDIR_PROJECT)/ModObject.o: objects/ModObject.cpp
	$(COMPILE.cpp) -o $(TARGETDIR_PROJECT)/ModObject.o objects/ModObject.cpp
$(TARGETDIR_PROJECT)/ModInfo.o: objects/ModInfo.cpp
	$(COMPILE.cpp) -o $(TARGETDIR_PROJECT)/ModInfo.o objects/ModInfo.cpp
$(TARGETDIR_PROJECT)/ModData.o: objects/ModData.cpp
	$(COMPILE.cpp) -o $(TARGETDIR_PROJECT)/ModData.o objects/ModData.cpp
$(TARGETDIR_PROJECT)/ModCore.o: objects/ModCore.cpp
	$(COMPILE.cpp) -o $(TARGETDIR_PROJECT)/ModCore.o objects/ModCore.cpp
$(TARGETDIR_PROJECT)/ModBasicData.o: objects/ModBasicData.cpp
	$(COMPILE.cpp) -o $(TARGETDIR_PROJECT)/ModBasicData.o objects/ModBasicData.cpp
$(TARGETDIR_PROJECT)/ModInfoExtra.o: objects/ModInfoExtra.cpp
	$(COMPILE.cpp) -o $(TARGETDIR_PROJECT)/ModInfoExtra.o objects/ModInfoExtra.cpp


###### clean target: deletes generated files ######
clean:
	$(RM) \
	$(TARGETDIR_PROJECT)/libmod.so \
	$(OBJS_PROJECT)
