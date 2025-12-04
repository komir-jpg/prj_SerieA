CC := cc
# CFLAGS_COMMON contiene i flag di base (include, warning, debug, sanitize)
CFLAGS_COMMON := -Iinclude -Iinclude/backend -Iinclude/gui -Wall -Wextra -g -fsanitize=address

# GTK4_CFLAGS ottiene i flag di compilazione da pkg-config
GTK4_CFLAGS := $(shell pkg-config --cflags gtk4)
# GTK4_LDFLAGS ottiene le librerie per il linking da pkg-config
GTK4_LDFLAGS := $(shell pkg-config --libs gtk4)

# CFLAGS finale combina i flag comuni e quelli di GTK4
CFLAGS := $(CFLAGS_COMMON) $(GTK4_CFLAGS)

# LDFLAGS finale combina le librerie di sistema e quelle di GTK4
LDFLAGS := -lcurl -lcjson -fsanitize=address $(GTK4_LDFLAGS)

OBJDIR := objects
GUI_OBJDIR := $(OBJDIR)/gui
BACKEND_OBJDIR := $(OBJDIR)/backend
LSAN_SUPP := lsan.supp

# Crea le directory degli oggetti necessarie
$(shell mkdir -p $(BACKEND_OBJDIR))
$(shell mkdir -p $(GUI_OBJDIR))


SRCDIR = src

# Sorgenti
BACKEND_SOURCES = $(wildcard $(SRCDIR)/backend/*.c)
GUI_SOURCES = $(wildcard $(SRCDIR)/gui/*.c)
SOURCES = $(BACKEND_SOURCES) $(GUI_SOURCES)

# Oggetti
BACKEND_OBJS := $(patsubst $(SRCDIR)/backend/%.c,$(BACKEND_OBJDIR)/%.o,$(BACKEND_SOURCES))
GUI_OBJS := $(patsubst $(SRCDIR)/gui/%.c,$(GUI_OBJDIR)/%.o,$(GUI_SOURCES))
OBJS := $(BACKEND_OBJS) $(GUI_OBJS)

TARGET = main
GUI_TARGET = gui_test # Nome del target solo GUI, utile per test veloci

.PHONY: all clean gui run debug

# Regola Principale: Compila tutto (Backend + GUI)
all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET)

# Regola Compilazione Solo GUI
# Usa solo gli oggetti GUI e linka con gli LDFLAGS_GTK4
gui : $(GUI_TARGET)

$(GUI_TARGET) : $(GUI_OBJS)
	$(CC) $(GUI_OBJS) -lcurl -lcjson $(GTK4_LDFLAGS) -o $(GUI_TARGET)

# --- Regole Pattern di Compilazione ---

# Regola per i file backend
$(BACKEND_OBJDIR)/%.o : $(SRCDIR)/backend/%.c | $(BACKEND_OBJDIR)
	$(CC) $(CFLAGS_COMMON) -c $< -o $@

# Regola per i file GUI
$(GUI_OBJDIR)/%.o : $(SRCDIR)/gui/%.c | $(GUI_OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# --- Regole Utility ---

run: $(TARGET)
	@LSAN_OPTIONS=suppressions=$(LSAN_SUPP) ./$(TARGET)

debug: $(TARGET)
	@LSAN_OPTIONS=suppressions=$(LSAN_SUPP) gdb ./$(TARGET)

clean :
	rm -rf $(OBJDIR) $(TARGET) $(GUI_TARGET)
