#include "Projectiles.h"
#include "RoomManager.h"

Projectiles::Projectiles(sf::Texture* txt, sf::Vector2i tex_coords, Collision::LAYER l, RoomManager* rm) {
	states.texture = txt;
	texture_coordinates = (sf::Vector2f) tex_coords;
	collisionlayer = l;
	roommanager = rm;
	projectilesize = sf::Vector2f(16, 16);
}

void Projectiles::update(float dt) {
	for (size_t i = 0; i < projectile_vector.size(); i++) {
		if (projectile_vector[i].hitsomething) continue;
		sf::FloatRect mapboundaries;
		mapboundaries.left = roommanager->getCurrentRoom()->getBound(RoomManager::LEFT).left;
		mapboundaries.top = roommanager->getCurrentRoom()->getBound(RoomManager::TOP).top;
		mapboundaries.width = roommanager->MAPSIZE;
		mapboundaries.height = roommanager->MAPSIZE;
		if (!projectile_vector[i].collider.Check_Collision(mapboundaries)) {
			removeArrow(i);
			i--;
			continue;
		}
		sf::Vertex* v = &vertexs[i * 4];
		sf::Vector2f dt_velocity = projectile_vector[i].velocity * dt;
		v[0].position += dt_velocity;
		v[1].position += dt_velocity;
		v[2].position += dt_velocity;
		v[3].position += dt_velocity;
		projectile_vector[i].collider.moveCollision(dt_velocity);

		Collision* collision_hit = nullptr;

		// check game objects collisions
		for (size_t j = 0; j < roommanager->getCurrentRoom()->getGameObjects()->size(); j++) {
			Collision* current_collision = &roommanager->getCurrentRoom()->getGameObjects()->at(j)->collider;
			if (collisionlayer == current_collision->collisionlayer) continue;
			if (current_collision->collisionlayer == Collision::LAYER::NONE) continue;
			sf::FloatRect rect = current_collision->rect;
			if (projectile_vector[i].collider.Check_Collision(rect)) {
				collision_hit = current_collision;
				projectile_vector[i].hitsomething = true;
				projectilestween.push_back(Tweening<float>(255.f, 0.f, 0.f));
				removing_projectiles.push_back({ i });
				roommanager->getCurrentRoom()->getGameObjects()->at(j)->hit(damage);
				break;
			}
		}
		// check tilemap collisions
		for (size_t j = 0; j < roommanager->getCurrentRoom()->getColliders()->size(); j++) {
			Collision* current_collision = roommanager->getCurrentRoom()->getColliders()->at(j);
			if (collisionlayer == current_collision->collisionlayer) continue;
			if (current_collision->collisionlayer == Collision::LAYER::WATER) continue;
			sf::FloatRect rect = current_collision->rect;
			if (projectile_vector[i].collider.Check_Collision(rect)) {
				collision_hit = current_collision;
				projectile_vector[i].hitsomething = true;
				projectilestween.push_back(Tweening<float>(255.f, 0.f, 1.f));
				removing_projectiles.push_back({ i });
				break;
			}
		}

		// if the projectile hit something: check if it's a gameobject
		/*
		if (collision_hit == nullptr) continue;
		for (size_t j = 0; j < roommanager->getCurrentRoom()->getGameObjects()->size(); j++) {
			GameObject* current_gameobject = roommanager->getCurrentRoom()->getGameObjects()->at(j);
			if (&current_gameobject->collider == collision_hit) {
				projectilestween.back().setTotalTime(0.f);
				current_gameobject->hit(damage);
				break;
			}
		}
		*/
	}

	for (size_t i = 0; i < removing_projectiles.size(); i++) {
		projectilestween[i].update(dt);
		size_t k = removing_projectiles[i].positioninarray * 4;
		for (size_t j = 0; j < 4; j++) {
			vertexs[k + j].color = sf::Color(255, 255, 255, projectilestween[i].getValue());
		}
		if (projectilestween[i].isfinished()) {
			removeArrow(removing_projectiles[i].positioninarray);
			i--;
		}
	}
}

void Projectiles::shoot(sf::Transform transform) {
	singleprojectile newprojectile;
	sf::Vertex vertex[4];

	transform.translate(sf::Vector2f(-projectilehitbox.width / 2, -projectilehitbox.height / 2));

	newprojectile.position = sf::Vector2f(transform.getMatrix()[12], transform.getMatrix()[13]);
	newprojectile.velocity = sf::Vector2f(0, 0);
	newprojectile.velocity = transform.transformPoint(orientation * speed);
	newprojectile.velocity -= newprojectile.position;
	sf::Vector2f center = sf::Vector2f(projectilehitbox.left + projectilehitbox.width / 2, projectilehitbox.top + projectilehitbox.height / 2);
	sf::Vector2f centerofcollision = transform.transformPoint(center);
	newprojectile.collider = Collision( centerofcollision.x - projectilehitbox.width / 2,
										centerofcollision.y - projectilehitbox.height / 2,
										projectilehitbox.width,
										projectilehitbox.height,
										collisionlayer);
	projectile_vector.push_back(newprojectile);

	vertex[0].position = transform.transformPoint(sf::Vector2f());
	vertex[1].position = transform.transformPoint(sf::Vector2f(projectilesize.x, 0));
	vertex[2].position = transform.transformPoint(sf::Vector2f(projectilesize.x, projectilesize.y));
	vertex[3].position = transform.transformPoint(sf::Vector2f(0, projectilesize.y));

	vertex[0].texCoords = texture_coordinates;
	vertex[1].texCoords = texture_coordinates + sf::Vector2f(projectilesize.x, 0);
	vertex[2].texCoords = texture_coordinates + sf::Vector2f(projectilesize.x, projectilesize.y);
	vertex[3].texCoords = texture_coordinates + sf::Vector2f(0, projectilesize.y);

	for (size_t i = 0; i < 4; i++) vertexs.push_back(vertex[i]);

}

void Projectiles::removeArrow(size_t n) {
	size_t vn = n * 4;
	vertexs.erase(vertexs.begin() + vn, vertexs.begin() + vn + 4);
	projectile_vector.erase(projectile_vector.begin() + n);
	
	for (size_t i = 0; i < removing_projectiles.size(); i++) {
		if (removing_projectiles[i].positioninarray == n) {
			projectilestween.erase(projectilestween.begin() + i);
			removing_projectiles.erase(removing_projectiles.begin() + i);
			i--;
			continue;
		}
		if (removing_projectiles[i].positioninarray > n) removing_projectiles[i].positioninarray--;
	}
	
}