if [ "$1" == "run" ];then
javac Test.java
#gcc -I /usr/lib/jvm/java-1.7.0-openjdk-amd64/include/ -o c_test c_test.c -L /usr/lib/jvm/java-7-openjdk-amd64/jre/lib/amd64/server -ljvm
#export LD_LIBRARY_PATH=/usr/lib/jvm/java-7-openjdk-amd64/jre/lib/amd64/server 
gcc -I /usr/lib/jvm/java-1.8.0-openjdk-amd64/include/ -I /usr/lib/jvm/java-1.8.0-openjdk-amd64/include/linux -o c_test c_test.c -L /usr/lib/jvm/java-8-openjdk-amd64/jre/lib/amd64/server/ -ljvm
export LD_LIBRARY_PATH=/usr/lib/jvm/java-8-openjdk-amd64/jre/lib/amd64/server/
./c_test
else
javac Test.java
javap -p -s Test.class
fi
