#if not defined(ANUT_GPU_RESOURCE_H)
#define ANUT_GPU_RESOURCE_H
#include <list>

namespace anut
{
namespace gl
{
class GpuResource 
{
public:
	static std::list<GpuResource*> allResources;
	
	GpuResource();
	virtual ~GpuResource();
	
	virtual bool init() = 0;
	virtual void shutdown() = 0;
	bool initialized() const;
	unsigned getId() const;
	
protected:
	unsigned __handle;
};

inline bool GpuResource::initialized() const
{
	return __handle != 0;
}

inline unsigned GpuResource::getId() const
{
	return __handle;
}
} // gl namespace
} // anut namespace

#endif
