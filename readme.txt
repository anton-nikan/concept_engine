

Drawbacks:
---------
1. The need to represent the scene as a collection requires adding run-time polymorphism to object (virtual function calls).
2. Handle-Body forces to use indirect call (through unique_ptr).
3. Handle-Body requires pointer to implementation (body) so objects can be scattered in memory (while processing is sequential).
4. Context always copies along drawing sequence (to not allow backward influence though).
5. Operation is performed over the context (operator +, copy) to move to more local context even if nothing has changed.
6. Render stream gets filled with anonymous calls from objects and contexts on every loop (hard to optimize for updates on demand).


TODO:
----
- moving stringstream as batch should be possible / object_t does not support moving now.
- action should be applied to both context and data in animate() / polymorphism doesn't allow to get to the data.
- transformation type is deeper containing details: position, rotation, scale / manipulation now happens on transformation_t directly.
- namespacing.
- move_to has a problem with implicit conversion (when using double it can't accept an int as 'to' parameter).
- rendering concept is now operator << which probably is not good.
- then() idiom for manipulators has a problem of actions changed (or applied) during animation (i.e. going through loop, 
calling actions, nulling them, etc.) so then() considered dangerous.


8.10.2012:
---------
+ immediate move_to version.
+ would be cool to chain manipulations (then()? or chain semantics?)
-> then() idiom for animated and immediate move_to manipulator (has problems with actions applied during animation).


7.10.2012:
---------
+ concepts.hpp should be included to check for available specializations / it all goes using empty implementations now.
-> concepts have no implementation so you get linking error when concept declaration used but your implementation not found.


before 7.10.2012:
----------------
+ future-based loading concept.
+ independent datatypes (parametrized through templates).
+ static scene initialization.
+ manipulation and manipulators with both instant and animated effect.
+ animation concept and actions to apply (lambda-based).
+ drawing concept and context for drawing.
+ basic types with value semantics and concept-based polymorphism.
+ (drawbacks#7) Complex dependencies between elements (will be hard to put apart).
