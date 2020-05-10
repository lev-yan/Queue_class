all:queue.cpp
	@echo ""
	@./loading.sh
	@g++ -g -pthread queue.cpp -o queue
	@./queue
	@ctags -R

clean:
	rm queue
