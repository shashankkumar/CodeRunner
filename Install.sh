rm main
rm Execution
mkdir TestCases
mkdir Logs
mkdir Files
javac GenerateSH.java
java GenerateSH
make
chmod 777 link.sh
chmod 777 CodeRunner.sh
