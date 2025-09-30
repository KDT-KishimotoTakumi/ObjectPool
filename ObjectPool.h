#pragma once
#include <memory>
#include <stack>
#include <vector>
#include "PoolHandle.h"

//	‘O•ûéŒ¾
template <typename T>
class PoolHandle;

template <typename T>
class ObjectPool {
	//	PoolHandle‚©‚ç‚Ì‚İ¶¬‰Â”\‚É‚·‚é
	friend class PoolHandle<T>;
public:
	explicit ObjectPool(size_t capacity) {
		objects_.reserve(capacity);
		for (size_t i = 0; i < capacity; ++i) {
			objects_.emplace_back(std::make_unique<T>());
			free_.push(objects_.back().get());
		}
	}
	PoolHandle<T> Acquire() {
		if (free_.empty()) throw std::runtime_error("empty");
		T* obj = free_.top();
		free_.pop();
		return PoolHandle<T>(obj, this);
	}
private:
	void Release(T* obj) { free_.push(obj); }
	std::vector<std::unique_ptr<T>> objects_;
	std::stack<T*> free_;
};