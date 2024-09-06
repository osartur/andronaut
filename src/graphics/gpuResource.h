#if not defined(ANUT_GPU_RESOURCE_H)
#define ANUT_GPU_RESOURCE_H
#include <list>

namespace anut
{
class GPUResource 
{
public:
	static std::list<GPUResource*> allResources;
	
	GPUResource();
	virtual ~GPUResource();
	
	virtual bool init() = 0;
	virtual void shutdown() = 0;
	bool initialized() const;
	unsigned getResourceId() const;
	
protected:
	unsigned handle;
};

inline bool GPUResource::initialized() const
{
	return handle != 0;
}

inline unsigned GPUResource::getResourceId() const
{
	return handle;
}
}

#endif
