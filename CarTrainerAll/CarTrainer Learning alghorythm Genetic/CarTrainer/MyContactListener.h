#pragma once
class MyContactListner : public b2ContactListener
{
	BoxObject *finish;
public:
	void SetFinish(BoxObject *_finish)
	{
		finish = _finish;
	}

	// Called when two fixtures begin to touch
	virtual void BeginContact(b2Contact* contact)
	{
		//BoxObject *bo = static_cast<BoxObject*>(contact->GetFixtureA()->GetBody()->GetUserData());
		//if(bo)cout << bo->userData << endl;
	}

	// Called when two fixtures cease to touch
	virtual void EndContact(b2Contact* contact)
	{

	}


	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
	{
		// Set two fixtures of the same name cannot collide
		if (contact->GetFixtureA()->GetBody()->GetUserData() ==
			contact->GetFixtureB()->GetBody()->GetUserData())
			contact->SetEnabled(false);
	}
};