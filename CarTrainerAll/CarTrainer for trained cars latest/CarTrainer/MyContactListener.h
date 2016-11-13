#pragma once

class MyContactListner : public b2ContactListener
{
public:
	// Called when two fixtures begin to touch
	virtual void BeginContact(b2Contact* contact)
	{

	}

	// Called when two fixtures cease to touch
	virtual void EndContact(b2Contact* contact)
	{

	}

	// Called when two AABB's collide
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
	{
		// Set two fixtures of the same name cannot collide
		if (contact->GetFixtureA()->GetBody()->GetUserData() ==
			contact->GetFixtureB()->GetBody()->GetUserData())
			contact->SetEnabled(false);
	}
};