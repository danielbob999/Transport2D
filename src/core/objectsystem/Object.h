#pragma once
#include <vector>
#include <string>
#include "../../../includes/box2d/box2d.h"
#include "ComponentScript.h"

namespace core_objectsystem {
	class Object {
	private:
		static int s_nextId;
		static std::vector<Object*> s_objects;

		int m_id;
		std::string m_name;
		bool m_active;
		bool m_shouldRender;
		b2Vec2 m_position;
		std::vector<ComponentScript*> m_components;

	public:
		Object();
		~Object();

		ComponentScript* addComponentScript(ComponentScript*);		// Add a new component script to the Object. If one of the same type exists, return the old one (the new one will not be added)
		ComponentScript* getComponentScript(const std::string&);	// Get a component of the type specified. It one exists, nullptr will be returned
		void removeComponentScript(const std::string&);				// Removes a component of the specified type
		
		b2Vec2& getPosition();										// Gets the current position of the Object
		void setPosition(float, float);								// Sets the current position of the Object
		void setPosition(const b2Vec2&);

		void setActiveStatus(bool);									// Sets whether the Object is active in the game
		bool getActiveStatus();										// Gets the active status of the Object

		void setShouldRenderStatus(bool);							// Sets whether the Object should be rendered
		bool getShouldRenderStatus();								// Gets the render status of the Object

		void setName(std::string);									// Sets the name of this Object
		std::string& getName();										// Gets the name of this Object

		int getId();												// Gets the ID if this Object. The ID is used for Object comparison
		bool equals(const Object*);									// Returns true if the ids are the same (they are the same Object), false otherwise

		static Object* createObject();									// Creates a new Object with the default values
		static Object* createObject(const std::string&, int x, int y);	// Creates a new Object with the supplied values
	};
}
