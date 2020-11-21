main: main.cpp menu.h end.h title.h player.h gameManager.h common.h
        g++ -I ~/local/include -I ~/local/include/ncursestw -L ~/local/lib -o main main.cpp -lncursestw -ldl -pthread
        
clean:
	rm -f main

.PHONY: clean
