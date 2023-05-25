#pragma once
#include "Contact.h"
#include "Physics/Body.h"
#include <vector>

namespace collision
{
	Contact GenerateContact(Body* bodyA, Body* bodyB);
	void CreateContacts(std::vector<Body*> bodies, std::vector<Contact>& contacts);
	void SeparateContacts(std::vector<Contact>& contacts);
	void ResolveContacts(std::vector<Contact>& contacts);
}