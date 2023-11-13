# Design Patterns in C++: State

This project is a example for the _State_ design pattern. This pattern is explained in the book _Design Patterns_ by the gang of four and is explained on [Refactoring Guru](https://refactoring.guru/design-patterns/state). It is a behaviourial design pattern and is used when a object has to change it's behaviour in a specific state. To the calling code, it appears as if the object has changed, but the object just uses a different object to delegate it's work too. On the [Refactoring Guru](https://refactoring.guru/design-patterns/state) page you can find a great explanation of the pattern.

## The example code

The example code defines a post from a blog website that can be in three stages:

-   Draft
-   Published
-   Archived

The blogpost contains a list for history of the post; when a post gets edited in Published state, the history gets updated. When edited in Draft state, the history doesn't get updated. The blogpost also contains a list for comments. When in published state, comments can be added. In Draft or Archived state, that is not possible.

The example shows how the behaviour of the blogpost changes when the state is updated:

-   In draft state:
    -   The text can be updated, but the history won't be updated
    -   It is impossible to add comments
    -   It is impossible to transition to archived state
    -   It is impossible to unarchive the post
    -   It is possible to transition to published state by using the `publish()` method
-   In published state:
    -   The text can be updated and the history gets updated too
    -   Comments can be added
    -   The post can be archived
    -   It is impossible to unarchive the post since it is not archived
    -   It is possible to transfer to archived state by using the `archive()` method
-   In archived state:
    -   The text cannot be edited anymore
    -   It is impossible to add comments
    -   It is impossible to transition to archived state
    -   It is possible remove the post from archive by using the `unarchive()` method

When a behaviour is used that is not possible, a exception is thrown (`BlogPostStateException`). The calling code can catch this exception to handle it by using a `try...catch` block.

## How does it work

Objects of the `BlogPost` class have a variable called `_state`. This is a pointer of type `BlogPostState`. When the object is created, a object of the `BlogPostStateDraft` class is initiated for this pointer. All operations on the `BlogPost` object are delegated to the object in the `_state` variable.

The `BlogPostState` object has a reference to the `BlogPost` object. When a `BlogPostState` object wants to transition the `BlogPost` object to a new state, it does this by calling the `__transition` method of the `BlogPost` object. This way, the `BlogPostState` object decides what transitions are possible.

## Running the code

The code can be ran by compiling the source code:

```bash
cd src/
g++ *.cpp -o ../build/app
../build/app
```
