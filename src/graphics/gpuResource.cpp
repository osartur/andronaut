#include "graphics/gpuResource.h"

namespace anut
{
std::list<GPUResource*> GPUResource::allResources{};

GPUResource::GPUResource()
{
	allResources.push_back(this);
	handle = 0;
}

GPUResource::~GPUResource()
{
	allResources.remove(this);
}
	
} // anut namespace
