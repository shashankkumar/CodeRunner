#appends `#define ABSOLUTE_PATH` in config.h
cp $2 $1/$3
echo "#define ABSOLUTE_PATH \""$PWD"/\"" >> $1/$2

