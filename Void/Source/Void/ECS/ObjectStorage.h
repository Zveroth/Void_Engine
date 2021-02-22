#pragma once
#include "Void/Containers/SegmentedArray.h"
#include "Void/Core/Log.h"



class IObjectStorageHandle
{

public:

	virtual ~IObjectStorageHandle() {}

	virtual void DeleteObject(void* Object) = 0;

	virtual void Each(const std::function<void(void*)>& Function) = 0;

	//virtual size_t Num() const = 0;
};

template<typename T>
class TObjectStorage : public IObjectStorageHandle
{

public:

	TObjectStorage()
	{
		VD_CORE_TRACE("Creating storage for {0}", typeid(T).name());
	}

	virtual ~TObjectStorage()
	{
		VD_CORE_TRACE("Destroying storage for {0}", typeid(T).name());
	}

	template<typename... Args>
	T* Create(Args &&... args)
	{
		return m_Objects.Create(std::forward<Args>(args)...);
	}

	T* Get(int32_t At) const
	{
		return m_Objects.Get(At);
	}

	std::vector<T*> GetAll() const
	{
		return m_Objects.GetAll();
	}

	void Delete(T* Object)
	{
		m_Objects.Remove(Object);
	}

	void DeleteObject(void* Object) override
	{
		Delete((T*)Object);
	}

	virtual void Each(const std::function<void(void*)>& Function) override
	{
		for (T* Object : GetAll())
			Function((void*)Object);
	}

	//virtual size_t Num() const override
	//{
	//	return m_Objects.Num();
	//}

private:

	SegmentedArray<T> m_Objects;
};