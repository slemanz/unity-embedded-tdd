# The Unity Framework

The previous module established the **why**: the professional and financial
reasons for building robust firmware. This module is about the **how**. It is
where the Red-Green-Refactor cycle stops being a theoretical concept and starts
becoming muscle memory.

The goal is to make the cycle so second nature that you begin to think in terms of
a single question: *what is my next failing test?* Everything that follows is
practice toward that habit.

## Red: Design Before You Implement

The cycle begins with a failing test, and it helps to treat this as the most
important design phase, not a formality you rush through before the real work.

Writing the test first forces you to become the **first user of your own code**.
Before any production code exists, you have to answer concrete questions:

- What should this function be called?
- What information does it need to receive?
- What should it give back?

In other words, you are designing the public interface, its name, its parameters,
and its return type, by deciding how you want to call it. You even get to ask the
most useful question of all: is this API actually pleasant to use? It is far
cheaper to answer that now than after the implementation is written.

Then you run the test and watch it fail. **This is not a mistake, it is a
victory.** A failing test proves you have correctly described a requirement the
system does not yet meet. It sounds counterintuitive, but it is the point: you
write just enough test code to trigger a compiler error or a red bar, and that red
bar is your clearly defined goal.

## Green: The Simplest Thing That Works

Once you have a failing test, you enter the green phase, and here the goal is
singular: move the bar from red to green as quickly as possible.

You do that by writing the simplest, most direct code imaginable. If the test
expects the number five, you are allowed to literally return five. That feels
wrong at first, and learning to be comfortable with it is part of the discipline.
It guarantees that your production code is driven only by the requirements the
tests actually specify.

We are not aiming for beautiful code at this stage, we are aiming for a working
system and a stable, passing state. That means you must **resist overengineering**.
Add no logic the test does not explicitly ask for: no future-proofing, no gold
plating. The only key action here is to write production code until the bar turns
from red to green, and no further.

## Refactor: Earn the Right to Improve

With a full suite of passing tests acting as a safety net, you have earned the
right to refactor. Now you put on your software architect hat.

You look at the simple code you just wrote and ask how it can be made better: more
readable, more efficient, more maintainable. Because the tests are green, you can
make these changes with complete confidence. If a refactor breaks something, a
test fails and you know instantly, while the mistake is still small and fresh in
your mind. This is the phase that turns a functional but messy codebase into a
genuinely professional one.

The key action at this stage is to improve the production code, the test code, or
both, running your tests after every small change.

## The Loop

Red defines the goal, green reaches it the fastest way possible, and refactor
makes the result something you would be proud to ship. Then the cycle begins again
with the next failing test. Repeat it enough times and it stops being a procedure
you follow and becomes the way you think.
