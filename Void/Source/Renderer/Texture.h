#pragma once

#include "Void/Core/Core.h"


class Texture
{

public:

	virtual ~Texture() {}

	virtual uint32_t GetWidth() const = 0;
	virtual uint32_t GetHeight() const = 0;

	virtual void Bind(unsigned int Slot = 0) const = 0;

	virtual void SetData(void* Data, uint32_t size) = 0;
};

class Texture2D : public Texture
{

public:

	static Ref<Texture2D> Create(const std::string& path);
	static Ref<Texture2D> Create(uint32_t Width, uint32_t Height, void* Data = nullptr);
};