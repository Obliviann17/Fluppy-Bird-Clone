#pragma once

#include <memory>
#include <stack>

#include "State.h"

typedef std::unique_ptr<State> StateRef;

class StateMachine
{
public:
	StateMachine();
	~StateMachine();

	void AddState(StateRef newState, bool isReplacing = true);
	void RemoveState();

	void ProcessStateChanges();

	// У твоїй реалізації в GetActiveState() ти без перевірки звертаєшся до this->states.top(). Якщо стек пустий — буде краш програми.
	StateRef& GetActiveState();

private:
	std::stack<StateRef> states;
	StateRef newState;

	bool isRemoving;
	bool isAdding;
	bool isReplacing;
};

