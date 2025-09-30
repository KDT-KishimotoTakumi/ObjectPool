#pragma once
#include <stdexcept>
#include "ObjectPool.h"

//	�O���錾
template <typename T>
class ObjectPool;

//	�v�[���n���h���N���X
template <typename T>
class PoolHandle {
	//	ObjectPool����̂ݐ����\�ɂ���
	friend class ObjectPool<T>;
	//	�����t���̃R���X�g���N�^
	//	�ÖٓI�Ȍ^�ϊ��̖h�~�̂���explicit�w��
	explicit PoolHandle(T* obj, ObjectPool<T>* pool)
		: obj_(obj), pool_(pool) {
	}
public:
	//	�R�s�[�֎~
	PoolHandle(const PoolHandle&) = delete;
	//	���[�u�֎~
	PoolHandle(PoolHandle&& other) noexcept
		: obj_(other.obj_), pool_(other.pool_) {
		other.obj_ = nullptr;
		other.pool_ = nullptr;
	}
	//	�f�X�g���N�^
	~PoolHandle() {
		if (obj_ && pool_) {
			pool_->Release(obj_);
		}
	}
	//	�A�N�Z�X���Z�q
	T* operator->() { return obj_; }
	T& operator*() { return *obj_; }

private:
	//	�e���v���[�g�^�̃|�C���^
	T* obj_;
	//	�v�[���̃|�C���^
	ObjectPool<T>* pool_;
};