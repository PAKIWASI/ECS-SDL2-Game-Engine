#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>


class Component;
class Entity;
          // for each component, we need Id
using ComponentID = std::size_t; // replaces left side with right side IMP!!!!

// inline size_t getComponentTypeID()
inline ComponentID getComponentTypeID()  // inline func kinda like header file(pastes func where we need it instead of calling) 
{
    static ComponentID lastID = 0; // static size_t lastID
    return lastID++;
}

// template function for each component
template <typename T> 
inline ComponentID getComponentTypeID() noexcept  // each comp will have unique ID
{
    static ComponentID typeID = getComponentTypeID();
    return typeID;
}

constexpr std::size_t maxComponents = 32;
                            //an arr of bits where each bit is a bool
using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>; // arr of comp pointers having maxComp length
/* to check if an entity has got a selection of components, 
we generate a bitset, pass it in, and if it matches, it has all components
index 0 can be position, 1 can pe speed etc....

The getComponentID template function would always return the same value if the type name is the same 
for example getComponentID<Position> would always return 0 or something like that. 
The Bitset stores true and false value, for example, if the position component is added 
it would set the value of the componentID inside bitset to true, then it would 
become much easier to get components and refactor their values. The array is used to store components.

Basically, we got a Manager which holds entities, which are anything drawn in your game.
Each entity has components, which give it functionality.
Each component has it's own class, 
so templates and other fancy stuff are required in order to get and add components.
*/

class Component
{
private:

public:
    Entity* entity = nullptr;
    virtual void init() {}
    virtual void update() {}
    virtual void draw() {}

    virtual ~Component() {}
};

class Entity
{
private:
    bool active = true;
    std::vector<std::unique_ptr<Component>> components; // all comps of an entity stored here

    ComponentArray componentArray; //using ComponentArray = std::array<Component*, maxComponents>; Pointer to each comp
    ComponentBitSet componentBitSet; //using ComponentBitSet = std::bitset<maxComponents>; To see if an Entity has a specific comp
public:
    void update()
    {
        for (auto& c : components) c->update(); 
    }
    void draw()
    {
        for (auto& c : components) c->draw();
    }
    bool isActive() const { return active; }
    void destroy() { active = false; }

    template <typename T> 
    bool hasComponent() const
    {
        return componentBitSet[getComponentTypeID<T>()];  // eg getCompTypeID<Position>() gives index for the position comp, if it is T in bitset then it is present
    }

    template <typename T, typename... TArgs>
    T& addComponent(TArgs&&... mArgs)
    {
        T* c(new T(std::forward<TArgs>(mArgs)...));
        c->entity = this; // E.addComp(a) -> E is the entity, and a is the comp being added
        std::unique_ptr<Component> uPtr{ c };
        components.emplace_back(std::move(uPtr)); // add comp in comp array
                 // each comp will be put in the same pos in array each time
        componentArray[getComponentTypeID<T>()] = c; // each comp has unique ID
        componentBitSet[getComponentTypeID<T>()] = true;  // the index of this comp set to true(present) 

        c->init(); 
        return *c;
    }

    template<typename T> 
    T& getComponent() const
    {
        auto ptr(componentArray[getComponentTypeID<T>()]);// get comp at it's index, store in ptr
        return *static_cast<T*>(ptr);
    }
};


class Manager
{
private:
    std::vector<std::unique_ptr<Entity>> entities; // manager stores all entities in this vector

public:
    void update()
    {
        for (auto& e : entities) e->update();
    }
    void draw()
    {
        for (auto& e : entities) e->draw();
    }
    void refresh()
    {                // remove entites if they are not active
        entities.erase(std::remove_if(std::begin(entities), std::end(entities),
            [](const std::unique_ptr<Entity>& mEntity)
            {
                return !mEntity->isActive();
            }),
            std::end(entities));
    }
    Entity& addEntity()
    {
        Entity* e = new Entity;
        std::unique_ptr<Entity> uPtr{ e } ;
        entities.emplace_back(std::move(uPtr));
        return *e;
    }
};

/*
entities.erase takes a first / last pair, and erases all entities in that range(can also function on a single index)

	remove_if iterates over an array or vector, across a range, following a unary predicate. In simpler terms, it goes from a <first> to a <last> index, as passed in, and deletes the entity if it matches <rule>. 



	1. call remove_if on our vector of entities, across the entire list, and delete if if its an element of an array, that we define in-call (aka right fucking now), that is all the entities that have active = false. 

		a. this requires the computer to parse the expression we used to define the nameless array indicated by [], which is any entity where entity-> isActive is false. we flip that becuase we want a true result if the value is false, thus !mEntity->isActive()

		b. this function actually move-erases things, as in, if something needs deleting then it gets swapped to the end of the vector, and all the subsequent items move up a spot this is important because...

		c. the return value is the first address that no longer holds anything important



	2. using the return value from that remove_if, we actually erase the elements no longer needed. this is because remove_if() doesn't remove the index from the list, it just undefines the elements at the end.  Thus, in step 1, the LOGICAL size of the vector is reduces in that

	anything past the new endpoint is undefined, but the actual indexes still exist. After this step, the actual index of the list is removed.
* 
* ////////////////////////////////////////////////////////
* Template<typename T>
* void Print(T value)
* {
*     cout << value;
  }
                                /////// HOW TEMPLATES WORK \\\\\\\
  int main()
  {
    Print<int>(5);
    Print<std::string>("Hello");
  }
  ////////////////////////////////////////////////////////

- These libraries provide essential functionality:
  - `iostream` for basic input-output operations.
  - `vector` to store dynamic lists of objects.
  - `memory` to use `std::unique_ptr` for automatic memory management.
  - `algorithm` for standard algorithms like `std::remove_if`.
  - `bitset` for fixed-size bit manipulation.
  - `array` for fixed-size arrays.


### **3. `using` Aliases
using ComponentID = std::size_t;

- `ComponentID` represents a unique identifier for each component type.
- `std::size_t` is an unsigned integral type, typically used for array indexing and sizes.
- IDs are necessary because components are stored generically, and each type must be uniquely identifiable.


### **4. Unique ID Generator
inline ComponentID getComponentTypeID() 
{
    static ComponentID lastID = 0;
    return lastID++;
}
- `static ComponentID lastID = 0;` ensures that `lastID` is initialized only once.
- `return lastID++;` increments and returns a unique ID every time it is called.
Static variables retain their values between function calls. This behavior ensures that `lastID` consistently increments across all uses of `getComponentTypeID()`.


### **5. Template Version of `getComponentTypeID<T>()`**
template <typename T>
inline ComponentID getComponentTypeID() noexcept
{
    static ComponentID typeID = getComponentTypeID();
    return typeID;
}
```
- **Purpose:** Returns a unique ID for each component type `T`.
- **Usage of `static` inside template functions:** Each template instantiation (e.g., `getComponentTypeID<Position>()`) generates a unique `typeID`.


### **6. Component Count and Data Structures**
constexpr std::size_t maxComponents = 32;
using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

- `maxComponents` defines a fixed number of possible component types.
- **BitSet:** A bitset is a collection of bits used for fast component lookups. Each bit represents whether a component exists.
- **ComponentArray:** A fixed-size array to hold pointers to components.


### **7. Component Base Class**
class Component
{
public:
    virtual void init() {}
    virtual void update() {}
    virtual void draw() {}
    virtual ~Component() {}
};
```
- Base class for all components.
- Declares virtual functions (`init()`, `update()`, and `draw()`) that derived classes override.
- A virtual destructor ensures proper cleanup of derived objects.


### **8. Entity Class**
class Entity
{
private:
    bool active = true;
    std::vector<std::unique_ptr<Component>> components;
    ComponentArray componentArray;
    ComponentBitSet componentBitSet;

- **`bool active`**: Tracks if the entity is still in use.
- **`std::vector<std::unique_ptr<Component>>`**: Stores owned components with automatic memory management.
- **`ComponentArray`**: Provides fast access to components.
- **`ComponentBitSet`**: Tracks which components are present.


#### **Entity Functions**

void update()
{
    for (auto& c : components) c->update();
    for (auto& c : components) c->draw();
}
- Calls `update()` and `draw()` on each component.

bool isActive() const { return active; }
- Returns whether the entity is active.

void destroy() { active = false; }
- Marks the entity as inactive.

template <typename T, typename... TArgs>
T& addComponent(TArgs&&... mArgs)
{
    T* c(new T(std::forward<TArgs>(mArgs)...));
    c->entity = this;
    std::unique_ptr<Component> uPtr{ c };
    components.emplace_back(std::move(uPtr));
    componentArray[getComponentTypeID<T>()] = c;
    componentBitSet[getComponentTypeID<T>()] = true;
    c->init();
    return *c;
}
- **Purpose:** Creates and adds a component of type `T`.
- **Perfect Forwarding (`std::forward<TArgs>(mArgs)`)**: Efficiently passes arguments to the component’s constructor.

##### **Getting Components**     
template<typename T>
T& getComponent() const
{
    auto ptr = componentArray[getComponentTypeID<T>()];
    return *static_cast<T*>(ptr);
}
- Retrieves a reference to a component of type `T`.

##### **Checking Component Existence**
template <typename T>
bool hasComponent() const
{
    return componentBitSet[getComponentTypeID<T>()]; //the func is the index
}
- Checks if the bit for the component type is set.


### **9. Manager Class**
class Manager
{
private:
    std::vector<std::unique_ptr<Entity>> entities;
- Stores all entities in a vector of `unique_ptr`s.

#### **Manager Functions**

void update()
{
    for (auto& e : entities) e->update();
}

- Updates all entities.

void draw()
{
    for (auto& e : entities) e->draw();
}
- Draws all entities.

void refresh()
{
    entities.erase(std::remove_if(std::begin(entities), std::end(entities),
        [](const std::unique_ptr<Entity>& mEntity) {
            return !mEntity->isActive();
        }), std::end(entities));
}

- Removes inactive entities.

Entity& addEntity()
{
    Entity* e = new Entity;
    std::unique_ptr<Entity> uPtr{ e };
    entities.emplace_back(std::move(uPtr));
    return *e;
}
- Creates and returns a new entity.


### **How It All Works Together**
1. **Entities**: Objects in the game world.
2. **Components**: Pieces of functionality that entities can have (like `Position`, `Velocity`).
3. **Manager**: Handles creating, updating, and removing entities.



*/