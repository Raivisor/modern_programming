#!/bin/bash

CPP_FILES="main.cpp define_menu_items.cpp menu_item_function.cpp"
APP=dominator
FOLDER=bin

mkdir -p $FOLDER

if [ -f "$FOLDER/$APP" ]; then 
    rm "$FOLDER/$APP"
fi

g++ -I. $CPP_FILES -o $FOLDER/$APP

if [ -f "$FOLDER/$APP" ]; then
    ./$FOLDER/$APP
else
    echo "GG - Good Game"
    exit 1
fi