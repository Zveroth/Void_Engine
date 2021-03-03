#pragma once
#include "Void/Containers/SegmentedArray.h"
#include "Void/Core/Log.h"



class IObjectStorageHandle
{

public:

	virtual ~IObjectStorageHandle() {}

	virtual void DeleteObject(void* Object) = 0;

	virtual void Each(const std::function<void(void*)>& Function) = 0;

	virtual void Each(const std::function<void(void*, BitArray::BitRef)>& Function) = 0;
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
	ControlledPointer<T> Create(Args &&... args)
	{
		return m_Objects.Create(std::forward<Args>(args)...);
	}

	ControlledPointer<T> Get(int32_t At) const
	{
		return m_Objects.Get(At);
	}

	std::vector<ControlledPointer<T>> GetAll() const
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
		for (ControlledPointer<T> Object : GetAll())
			if (Object)
				Function((void*)Object.Get());
	}

	virtual void Each(const std::function<void(void*, BitArray::BitRef)>& Function) override
	{
		for (ControlledPointer<T> Object : GetAll())
				Function((void*)Object.Get(), Object.GetBit());
	}

private:

	SegmentedArray<T> m_Objects;
};