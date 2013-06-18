#Script to add the required directories and create link.sh and codeRunner.sh and to run the makefile

rm main
rm Execution
mkdir TestCases
mkdir Logs
mkdir Files
javac GenerateSH.java
java GenerateSH
cp sample.config.h config.h
make
chmod 755 link.sh
chmod 755 CodeRunner.sh
