all: clean
	gcc -I/usr/local/include/opus -L/usr/local/lib -lopus -o main main.c && \
	echo "---" && ./main

clean:
	rm -fv main

deps:
	apt-get update && \
	apt-get install -y gcc libopus-dev