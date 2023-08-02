
## Project: LlanyModLib by git@llanyro
## Makefile created by Francisco Julio Ruiz Fernandez

all: make_lib
project: make_lib

TARGETDIR_PROJECT=output

COMPILE.cpp = g++ -std=c++17 -fPIC -c -O2 -Wall -Wno-unknown-pragmas
LINK.cpp = g++ -std=c++17 -shared

LIBS_PROJECT = \
	-ldl

OBJS_PROJECT = \
	$(TARGETDIR_PROJECT)/ModBasicData.o \
	$(TARGETDIR_PROJECT)/ModCore.o \
	$(TARGETDIR_PROJECT)/ModData.o \

	$(TARGETDIR_PROJECT)/ModInfo.o \
	$(TARGETDIR_PROJECT)/ModInfoExtra.o \
	$(TARGETDIR_PROJECT)/ModLoader.o \

	$(TARGETDIR_PROJECT)/ModObject.o


# Link or archive
make_lib: $(OBJS_PROJECT) 
	$(LINK.cpp) -o $(TARGETDIR_PROJECT)/libmod.so $(OBJS_PROJECT) $(LIBS_PROJECT)

# Compile source files into .o's
$(TARGETDIR_PROJECT)/ModBasicData.o: v4/mod/ModBasicData.cpp
	$(COMPILE.cpp) -o $(TARGETDIR_PROJECT)/ModBasicData.o v4/mod/ModBasicData.cpp
$(TARGETDIR_PROJECT)/ModCore.o: v4/mod/ModCore.cpp
	$(COMPILE.cpp) -o $(TARGETDIR_PROJECT)/ModCore.o v4/mod/ModCore.cpp
$(TARGETDIR_PROJECT)/ModData.o: v4/mod/ModData.cpp
	$(COMPILE.cpp) -o $(TARGETDIR_PROJECT)/ModData.o v4/mod/ModData.cpp

$(TARGETDIR_PROJECT)/ModInfo.o: v4/modloader/ModInfo.cpp
	$(COMPILE.cpp) -o $(TARGETDIR_PROJECT)/ModInfo.o v4/modloader/ModInfo.cpp
$(TARGETDIR_PROJECT)/ModInfoExtra.o: v4/modloader/ModInfoExtra.cpp
	$(COMPILE.cpp) -o $(TARGETDIR_PROJECT)/ModInfoExtra.o v4/modloader/ModInfoExtra.cpp
$(TARGETDIR_PROJECT)/ModLoader.o: v4/modloader/ModLoader.cpp
	$(COMPILE.cpp) -o $(TARGETDIR_PROJECT)/ModLoader.o v4/modloader/ModLoader.cpp

$(TARGETDIR_PROJECT)/ModObject.o: v4/test/ModObject.cpp
	$(COMPILE.cpp) -o $(TARGETDIR_PROJECT)/ModObject.o v4/test/ModObject.cpp


###### clean target: deletes generated files ######
clean:
	$(RM) \
	$(TARGETDIR_PROJECT)/libmod.so \
	$(OBJS_PROJECT)
