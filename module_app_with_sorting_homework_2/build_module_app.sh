CPP_FILES="generator.cpp show_array.cpp shellSorting.cpp main1.cpp"
APP=bin/example

mkdir -p bin

if [ -f $APP ]; then rm $APP
fi

g++ -Wall $CPP_FILES -o $APP

./$APP