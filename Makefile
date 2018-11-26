main : main.cpp AnimatedSprite.h AnimatedSprite.o ./InputManager.h ./InputManager.o ./FiniteStateMachine.h ./FiniteStateMachine.o ./State.h ./State.o
	g++ -o main main.cpp InputManager.o FiniteStateMachine.o State.o AnimatedSprite.o

InputManager.o : InputManager.cpp InputManager.h
	g++ -c InputManager.cpp

FiniteStateMachine.o : FiniteStateMachine.cpp FiniteStateMachine.h
	g++ -c FiniteStateMachine.cpp

State.o : State.cpp State.h
	g++ -c State.cpp

clean :
	rm -rf main State.o FiniteStateMachine.o InputManager.o
