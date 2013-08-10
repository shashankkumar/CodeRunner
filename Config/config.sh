#appends `#define ABSOLUTE_PATH` in config.h
echo "#define ABSOLUTE_PATH \""$PWD"/\"" >> $1/$2
echo "\n#endif" >> $1/$2
