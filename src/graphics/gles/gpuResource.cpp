#include "graphics/gles/gpuResource.h"

namespace anut
{
namespace gl 
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
} // gl namespace	
} // anut namespace
