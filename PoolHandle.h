#pragma once
#include <stdexcept>
#include "ObjectPool.h"

//	前方宣言
template <typename T>
class ObjectPool;

//	プールハンドルクラス
template <typename T>
class PoolHandle {
	//	ObjectPoolからのみ生成可能にする
	friend class ObjectPool<T>;
	//	引数付きのコンストラクタ
	//	暗黙的な型変換の防止のためexplicit指定
	explicit PoolHandle(T* obj, ObjectPool<T>* pool)
		: obj_(obj), pool_(pool) {
	}
public:
	//	コピー禁止
	PoolHandle(const PoolHandle&) = delete;
	//	ムーブ禁止
	PoolHandle(PoolHandle&& other) noexcept
		: obj_(other.obj_), pool_(other.pool_) {
		other.obj_ = nullptr;
		other.pool_ = nullptr;
	}
	//	デストラクタ
	~PoolHandle() {
		if (obj_ && pool_) {
			pool_->Release(obj_);
		}
	}
	//	アクセス演算子
	T* operator->() { return obj_; }
	T& operator*() { return *obj_; }

private:
	//	テンプレート型のポインタ
	T* obj_;
	//	プールのポインタ
	ObjectPool<T>* pool_;
};