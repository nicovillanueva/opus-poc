all: clean
	gcc `pkg-config --cflags --libs opus` -o main main.c && \
	echo "---" && ./main

clean:
	rm -fv main

deps:
	apt-get update && \
	apt-get install -y gcc pkg-config libopus-dev