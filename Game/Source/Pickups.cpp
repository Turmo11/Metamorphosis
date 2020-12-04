#include "Defs.h"
#include "Log.h"
#include "Application.h"
#include "Render.h"
#include "Map.h"
#include "Collisions.h"
#include "Pickups.h"
#include "Scene.h"
//#include "WalkingEnemy.h"
#include "Audio.h"


Pickups::Pickups() : Module()
{
	name.Create("pickups");
}


// Destructor
Pickups::~Pickups()
{}

bool Pickups::Start()
{
	return true;
}

bool Pickups::PreUpdate()
{
	return true;
}

bool Pickups::Update(float dt)
{
	DrawAnimations();
	UpdateGoal();

	return true;
}

bool Pickups::PostUpdate()
{
	return true;
}

bool Pickups::CleanUp()
{
	// Remove pickups
	ListItem<Pickup*>* item;
	item = pickupList.start;

	while (item != NULL)
	{
		RELEASE(item->data);
		item = item->next;
	}
	pickupList.clear();

	// Remove goals
	ListItem<Goal*>* item2;
	item2 = goalList.start;

	while (item2 != NULL)
	{
		RELEASE(item2->data);
		item2 = item2->next;
	}
	goalList.clear();

	return true;
}

void Pickups::CreatePickup(SString name, iPoint position)
{
	Pickup* new_pickup = new Pickup;

	new_pickup->name = name;
	new_pickup->position = position;

	new_pickup->pickupHitbox.x = position.x;
	new_pickup->pickupHitbox.y = position.y;
	new_pickup->pickupHitbox.w = 32;
	new_pickup->pickupHitbox.h = 32;

	new_pickup->pickupCollider = app->collisions->AddCollider(new_pickup->pickupHitbox, ObjectType::LETTER, this);

	new_pickup->collected = false;

	pickupList.add(new_pickup);
}

void Pickups::DrawAnimations()
{
	ListItem<Pickup*>* pickupIterator = pickupList.start;

	while (pickupIterator != NULL)
	{
		if (!pickupIterator->data->collected)
		{
			app->map->DrawStaticAnimation(pickupIterator->data->name.GetString(), "letter_tileset", pickupIterator->data->position, &pickupIterator->data->animInfo);

		}
		pickupIterator = pickupIterator->next;
	}
}

void Pickups::OnCollision(Collider* A, Collider* B)
{
	if (A->type == ObjectType::LETTER && B->type == ObjectType::PLAYER)
	{
		A->toDelete = true;
		GetCollected();
		app->scene->CheckLevelProgress();

	}
}

void Pickups::GetCollected()
{
	ListItem<Pickup*>* pickupIterator = pickupList.start;

	while (pickupIterator != NULL)
	{
		if (pickupIterator->data->pickupCollider->toDelete)
		{
			pickupIterator->data->collected = true;
			LOG("Collected %s", pickupIterator->data->name.GetString());
		}
		pickupIterator = pickupIterator->next;
	}
}

void Pickups::DebugCollectAll()
{
	ListItem<Pickup*>* pickupIterator = pickupList.start;

	while (pickupIterator != NULL)
	{
		pickupIterator->data->collected = true;
		pickupIterator = pickupIterator->next;
	}

	app->scene->CheckLevelProgress();
}


void Pickups::SetGoal(iPoint position)
{
	Goal* left_goal = new Goal;
	Goal* right_goal = new Goal;

	left_goal->position = position;

	right_goal->position.x = position.x + 192;
	right_goal->position.y = position.y;

	goalList.add(left_goal);
	goalList.add(right_goal);
}

void Pickups::UpdateGoal()
{
	ListItem<Goal*>* goal_iterator = goalList.start;

	while (goal_iterator != NULL)
	{
		if (app->scene->levelCompleted)
		{
			app->map->DrawStaticAnimation("goal", "goal", goal_iterator->data->position, &goal_iterator->data->animInfo);

		}
		goal_iterator = goal_iterator->next;
	}
}


