CPP_FILES="io.cpp generate.cpp main.cpp merge_sort.cpp"
APP=megaknight

if [ -f $APP ]; then rm $APP
fi

g++ $CPP_FILES -o $APP

./$APP