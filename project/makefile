CC := cc
CFLAGS := -Iinclude -Wall -Wextra -g -fsanitize=address
LDFLAGS := -lncurses -lcurl -lcjson -lncurses -lpanel -lmenu -fsanitize=address
OBJDIR := objects
LSAN_SUPP := lsan.supp
$(shell mkdir -p $(OBJDIR))

SRCDIR = src
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

TARGET = main

.PHONY: all clean

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET)

$(OBJDIR)/%.o : $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	@LSAN_OPTIONS=suppressions=$(LSAN_SUPP) ./$(TARGET)

debug: $(TARGET)
	@LSAN_OPTIONS=suppressions=$(LSAN_SUPP) gdb ./$(TARGET)

clean :
	rm -rf $(OBJDIR) $(TARGET)


