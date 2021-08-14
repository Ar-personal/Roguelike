#pragma once
#include <cstdint>
#include <bitset>

#include <cassert>
#include <unordered_map>
#include <set>
#include <memory>
#include <array>
#include <queue>




// The one instance of virtual inheritance in the entire implementation.
// An interface is needed so that the ComponentManager (seen later)
// can tell a generic ComponentArray that an entity has been destroyed
// and that it needs to update its array mappings.









