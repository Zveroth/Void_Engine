#pragma once



class Entity;

class Component
{

	friend class Scene;

public:

	virtual ~Component() {}

	void Init(Entity* OwningEntity);
	virtual void Tick(float DeltaTime) {}
	virtual void OnDestroy() {}

	Scene* GetOwningScene() const;
	Entity* GetOwner() const { return m_Owner; }
	uint32_t GetOwnerID() const { return m_OwnerID; }

	bool CanEverTick() const { return m_bCanEverTick; }

	bool operator==(const Component& other);

	bool operator==(uint32_t ID);

	operator uint32_t() const;

	operator uint32_t();

protected:

	bool m_bCanEverTick = false;

	Entity* m_Owner;
	uint32_t m_OwnerID;
};