TARGET := yoshistore
BUILD := build
SOURCES := source
DATA := data
ROMFS := romfs

APP_TITLE := Yoshi HB Store
APP_AUTHOR := Você
APP_DESCRIPTION := Loja de Homebrew

LIBS := -lctru -lm -lcurl

include $(DEVKITPRO)/3ds_rules
