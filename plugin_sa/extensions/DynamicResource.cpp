#include "DynamicResource.h"

using namespace plugin;

std::vector<DynamicResource*> DynamicResource::resourcesList;

DynamicResource::DynamicResource() {
    resourcesList.push_back(this);
}

DynamicResource::~DynamicResource() {
    resourcesList.erase(std::remove(resourcesList.begin(), resourcesList.end(), this), resourcesList.end());
}

void DynamicResource::ReleaseAllDynamicResources() {
    for (auto res : resourcesList) { res->Unload(); }
}

void DynamicResource::RecreateAllDynamicResources() {
    for (auto res : resourcesList) { res->Load(); }
}

void DynamicResource::InitDynamicResourceSystem() {
    plugin::Events::d3dLostEvent += ReleaseAllDynamicResources;
    plugin::Events::d3dResetEvent += RecreateAllDynamicResources;
}