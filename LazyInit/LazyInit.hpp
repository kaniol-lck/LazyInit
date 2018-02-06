#ifndef LAZYINIT_HPP
#define LAZYINIT_HPP

#include <memory>
#include <functional>
#include <cassert>

template<typename T>
class LazyInit
{
public:
	LazyInit() = default;

	template<typename... Args>
	LazyInit(Args&&... args){
		initWith(std::forward<Args>(args)...);
	}

	template<typename... Args>
	void initWith(Args&&... args){
		initFunc_ = [args...]() -> std::shared_ptr<T>{
					return std::make_shared<T>(args...);
	};
		isFuncInited_ = true;
	}

	void setIniter(std::function<const std::shared_ptr<T>()>& initFunc){
		initFunc_ = initFunc;
	}

	T operator*() const{
		assert(isFuncInited_);
		if(!lazyman_)
			lazyman_ = initFunc_();
		return *lazyman_;
	}
	
	std::shared_ptr<T> operator->() const{
		assert(isFuncInited_);
		if(!lazyman_)
			lazyman_ = initFunc_();
		return lazyman_;
	}

private:
	mutable std::shared_ptr<T> lazyman_;

	std::function<std::shared_ptr<T>()> initFunc_;

	bool isFuncInited_ = false;

};

#endif // LAZYINIT_HPP
