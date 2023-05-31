#include "Collision.h"
#include "Physics/CircleShape.h"
#include "Engine/Random.h"

namespace collision
{
    Contact GenerateContact(Body* bodyA, Body* bodyB)
    {
        Contact contact;

        contact.bodyA = bodyA;
        contact.bodyB = bodyB;

        glm::vec2 direction = bodyA->m_position - bodyB->m_position;
        float distance = glm::length(direction);
        if (distance == 0)
        {
            direction = { randomf(-0.05f, 0.05f), randomf(-0.05f, 0.05f) };
        }

        float radius = dynamic_cast<CircleShape*>(bodyA->m_shape)->radius + dynamic_cast<CircleShape*>(bodyB->m_shape)->radius;
        contact.depth = radius - distance;

        contact.normal = glm::normalize(direction);

        contact.restitution = (bodyA->m_restitution + bodyB->m_restitution) * 0.5f;

        return contact;
    }

    void CreateContacts(std::vector<Body*> bodies, std::vector<Contact>& contacts)
    {
        for (size_t i = 0; i < bodies.size() - 1; i++)
        {
            for (size_t j = i + 1; j < bodies.size(); j++)
            {
                Body* bodyA = bodies[i];
                Body* bodyB = bodies[j];

                // contact needs at least one dynamic body
                if (bodyA->type != Body::DYNAMIC && bodyB->type != Body::DYNAMIC) continue;

                // check for intersection between bodies
                if (bodyA->Intersects(bodyB))
                {
                    // create contact
                    Contact contact = GenerateContact(bodyA, bodyB);
                    contacts.push_back(contact);
                }
            }
        }
    }

    void SeparateContacts(std::vector<Contact>& contacts)
    {
        for (auto& contact : contacts)
        {
            float totalInvMass = contact.bodyA->m_invMass + contact.bodyB->m_invMass;
            glm::vec2 separation = contact.normal * (contact.depth / totalInvMass);

            contact.bodyA->m_position += separation * contact.bodyA->m_invMass;
            contact.bodyB->m_position -= separation * contact.bodyB->m_invMass;
        }
    }

    void ResolveContacts(std::vector<Contact>& contacts)
    {
        for (auto& contact : contacts)
        {
            glm::vec2 relativeVelocity = contact.bodyA->m_velocity - contact.bodyB->m_velocity;
            float normalVelocity = glm::dot(relativeVelocity, contact.normal);

            if (normalVelocity > 0) continue;

            float totalInvMass = contact.bodyA->m_invMass + contact.bodyB->m_invMass;
            float impulseMagnitude = -(1.0f + contact.restitution) * normalVelocity / totalInvMass;

            glm::vec2 impulse = contact.normal * impulseMagnitude;

            contact.bodyA->m_velocity += (impulse * contact.bodyA->m_invMass);
            contact.bodyB->m_velocity -= (impulse * contact.bodyB->m_invMass);
        }
    }

}
