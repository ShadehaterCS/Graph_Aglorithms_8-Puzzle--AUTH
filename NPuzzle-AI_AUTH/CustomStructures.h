#pragma once
#include <queue>
#include "State.h"

namespace shd {
	class Queue : public std::queue<State> {
	public:
		State top() {
			return front();
		}
	};
}
