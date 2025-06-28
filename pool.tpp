#ifndef POOL_TPP
# define POOL_TPP

template<typename TType>
Pool<TType>::Pool() {}

template<typename TType>
Pool<TType>::~Pool() {
	for (size_t i = 0; i < storage_.size(); i++) {
		if (active_[i]) {
			destroyObjectAt(i);
		}
		delete[] reinterpret_cast<unsigned char*>(storage_[i]);
	}
}

template<typename TType>
void Pool<TType>::resize(const size_t& numberOfObjectStored) {
	for (std::size_t i = 0; i < numberOfObjectStored; i++) {
		unsigned char* rawMem = reinterpret_cast<unsigned char*>(new TType());
		storage_.push_back(rawMem);
		freeIndex_.push(i);
		active_.push_back(false);
	}
}

template<typename TType>
template<typename... TArgs>
typename Pool<TType>::Object Pool<TType>::acquire(TArgs&&... args) {
	if (freeIndex_.empty()) {
		throw std::runtime_error("No available objects in the pool.");
	}

	// get one resource at the top
	size_t index = freeIndex_.top();
	freeIndex_.pop();

	// get void* memory pointer
	void *mem = static_cast<void *>(storage_[index]);
	// construct new(placement new) object at adreess mem, initialise TType object with 
	// forwarded args, since the args are passed as temporary instances, use
	// move constructor
	TType *ptr = new (mem) TType(std::forward<TArgs>(args)...);
	active_[index] = true;
	
	return Object(this, index, ptr);
	
}

template<typename TType>
void Pool<TType>::destroyObjectAt(std::size_t index) {
	if (!active_[index]) return ;
	TType* ptr = reinterpret_cast<TType *>(storage_[index]);
	ptr->~TType();
	active_[index] = false;
	freeIndex_.push(index);
}

template<typename TType>
Pool<TType>::Object::Object(Pool* pool, std::size_t index, TType* ptr):
pool_(pool), index_(index), ptr_(ptr), valid_(true) {}

template<typename TType>
Pool<TType>::Object::~Object() {
	if (valid_) {
		pool_->destroyObjectAt(index_);
	}
}

template<typename TType>
TType* Pool<TType>::Object::operator->() {
	return ptr_;
}

template<typename TType>
TType& Pool<TType>::Object::operator*() {
	return *ptr_;
}

template<typename TType>
Pool<TType>::Object::Object(Object&& other): pool_(other.pool_),
	index_(other.index_), ptr_(other.ptr_), valid_(other.valid_) {
	pool_ = nullptr;
	valid_ = false;
}

template<typename TType>
typename Pool<TType>::Object& Pool<TType>::Object::operator=(Object&& other) {
	if (this != &other) {
		if (valid_) {
			pool_->destoryObjectAt(index_);
		}

		pool_ = std::move(other.pool_);
		index_ = std::move(other.index_);
		ptr_ = std::move(other.ptr_);
		valid_ = std::move(other.valid_);
	}
	return *this;
}

#endif