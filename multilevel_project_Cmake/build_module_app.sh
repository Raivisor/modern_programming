BUILD_TYPE=Ninja
BUILD_SUFFIX=ninja

BUILD_FOLDER=build_$BUILD_SUFFIX
SOURCE_FOLDER=projects

if [ ! -e $BUILD_FOLDER ]; then
	mkdir $BUILD_FOLDER
fi

cd $BUILD_FOLDER

cmake -G "$BUILD_TYPE" "../$SOURCE_FOLDER"
cmake --build .