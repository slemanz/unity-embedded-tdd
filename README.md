# Unity Framework - Test-Driven Development for Embedded Systems

Test-Driven Development (TDD) is a design discipline, not a testing activity.
The tests are a byproduct of letting requirements drive the structure of the
code: you describe a behavior in a failing test, write the minimum code that
makes it pass, and only then clean up. Repeated hundreds of times, that tiny
loop is how complex, robust firmware grows from simple, verifiable steps.

The discipline earns its keep through economics. The cost of a bug that
reaches the customer is exponentially higher than the cost of one caught
during development: a defect found while writing code is trivial to fix,
while the same defect in the field can trigger recalls, mission failures, or
harm to people. TDD attacks this by catching bugs seconds after they are
introduced, by forcing loosely coupled design (code that is hard to test is
usually code that is poorly structured), and by leaving behind a regression
net that makes refactoring safe.

Embedded systems make the practice harder than it is on a desktop. The code
is intimately tied to physical hardware, the targets have little RAM and
flash, and real-time behavior is difficult to replicate in a test. This
repository collects notes and runnable examples on overcoming exactly those
challenges. The sections below summarize the core ideas so this page works as
a refresher long after the details have faded; the links at the end lead to
the full material, and every module with code builds and runs on the host
with a single `make`.

## The Red-Green-Refactor Cycle

The heartbeat of the practice is a three-step loop, and each step has a
distinct mindset.

**Red.** Write a test for code that does not exist yet and watch it fail.
This is the real design phase: writing the test first makes you the first
user of your own code, forcing you to choose the function's name, parameters,
and return type by deciding how you want to call it. The failing test is not
a mistake, it is a victory, because it proves you have described a
requirement the system does not yet meet.

**Green.** Write the absolute minimum code that makes the test pass. If the
test expects five, returning a literal five is allowed; the next test will
force the real logic. Resist overengineering: no future-proofing, no gold
plating, no logic the tests do not explicitly ask for.

**Refactor.** With passing tests as a safety net, improve the code with
complete confidence. If a change breaks something, a test fails immediately,
while the mistake is still small and fresh in your mind.

## What Makes a Good Unit Test

A bad test is worse than no test: it gives false confidence or becomes a
brittle maintenance burden. The acronym **FIRST** captures the qualities that
keep tests valuable. A test should be **Fast**, so the whole suite runs in a
blink and you run it constantly. **Independent**, starting from a clean slate
with no dependence on other tests, which is what setup and teardown exist
for. **Repeatable**, giving the same result in any environment, the core
reason mocks replace unpredictable hardware. **Self-Validating**, deciding
its own pass or fail with no human interpretation. And **Timely**, written
before the production code, which is the definition of TDD itself.

Two naming habits do most of the maintenance work. Mirror production files
with test files (`led_driver.c` gets `test_led_driver.c`), and treat each
test name as documentation: `test_driver_init_enables_the_gpio_clock` tells
you what broke without opening the file, while `test_led_one` tells you
nothing.

## The Unity Framework

Unity is the test runner and referee. It is not installed system-wide; it is
a small set of C files vendored into the project and compiled alongside the
code under test, so a fresh clone builds and tests without any external
setup.

It offers two styles. The core framework (`unity.c`) uses free functions
registered with `RUN_TEST` and global `setUp`/`tearDown` hooks, and suits
small, focused suites. The fixture extension (`unity_fixture.c`) adds named
`TEST_GROUP`s with per-group setup and teardown, and pays off once a suite
grows. The assertion macros behave identically in both; only the organization
changes.

The assertion vocabulary is broad, but a few families cover nearly every
embedded case: boolean and pointer checks, integer and hex equality at exact
widths, bit and bitmask checks (the workhorses of driver tests), relational
and within-tolerance comparisons, string, memory, and array comparisons, and
tolerance-based float checks. Two habits matter in embedded work: prefer the
exact-width variants (`TEST_ASSERT_EQUAL_UINT16` over a generic `EQUAL`) to
avoid integer-promotion surprises, and reach for the `HEX` variants when
checking registers, so failure messages line up with the datasheet.
