
postfix:
	g++ -std=c++14 -c main.cpp PostfixCalculator.cpp                                                                                                                                                                                                                                                                                                                                                                                                                                                  
	g++ -std=c++14 main.o PostfixCalculator.o -o postfix

clean:
	rm -f *.o postfix