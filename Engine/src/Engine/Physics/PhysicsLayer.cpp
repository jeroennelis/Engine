#include "enpch.h"
#include "PhysicsLayer.h"

Engine::PhysicsLayer::PhysicsLayer()
	:Layer("Physics Layer")
{

}

void Engine::PhysicsLayer::OnAttach()
{
	EN_CORE_INFO("Physics Layer attached");
}

void Engine::PhysicsLayer::OnDetach()
{
	EN_CORE_INFO("Physics Layer detached");
}

void Engine::PhysicsLayer::OnUpdate()
{
}
