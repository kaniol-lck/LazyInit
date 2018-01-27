#ifndef LAZYINIT_HPP
#define LAZYINIT_HPP

#include <memory>
#include <functional>

template<typename T>
class LazyInit
{
public:
	LazyInit() = default;

	template<typename... Args>
	LazyInit(Args&&... args){
		initWith(std::forward<Args>(args)...);
	}

	LazyInit(std::function<const std::shared_ptr<T>()>& initFunc){
		setIniter(initFunc);
	}

//	LazyInit(const LazyInit<T>&) = delete;
//	LazyInit<T>& operator=(const LazyInit<T>&) = delete;

	template<typename... Args>
	void initWith(Args&&... args){
		using FuncType = std::shared_ptr<T>(*)(Args...);
		initFunc_ = std::bind((FuncType)std::make_shared<T>,
							  std::forward<Args>(args)...);
		isFuncInited_ = true;
	}

	void setIniter(std::function<const std::shared_ptr<T>()>& initFunc){
		initFunc_ = initFunc;
	}

	T getValue() const{
		if(!lazyman_)
			lazyman_ = initFunc_();
		return *lazyman_;
	}

private:
	mutable std::shared_ptr<T> lazyman_;

	std::function<std::shared_ptr<T>()> initFunc_;

	bool isFuncInited_ = false;

};

#endif // LAZYINIT_HPP
