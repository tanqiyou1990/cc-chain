# Unit tests

The sources in this directory are unit test cases. Boost includes a
unit testing framework, and since Vircles Core already uses Boost, it makes
sense to simply use this framework rather than require developers to
configure some other framework (we want as few impediments to creating
unit tests as possible).

The build system is set up to compile an executable called `test_vircles`
that runs all of the unit tests. The main source file for the test library is found in
`util/setup_common.cpp`.

### Compiling/running unit tests

Unit tests will be automatically compiled if dependencies were met in `./configure`
and tests weren't explicitly disabled.

After configuring, they can be run with `make check`.

To run the virclesd tests manually, launch `src/test/test_vircles`. To recompile
after a test file was modified, run `make` and then run the test again. If you
modify a non-test file, use `make -C src/test` to recompile only what's needed
to run the virclesd tests.

To add more virclesd tests, add `BOOST_AUTO_TEST_CASE` functions to the existing
.cpp files in the `test/` directory or add new .cpp files that
implement new `BOOST_AUTO_TEST_SUITE` sections.

To run the virlces-qt tests manually, launch `src/qt/test/test_vircles-qt`

To add more virlces-qt tests, add them to the `src/qt/test/` directory and
the `src/qt/test/test_main.cpp` file.

### Running individual tests

test_vircles has some built-in command-line arguments; for
example, to run just the getarg_tests verbosely:

    test_vircles --log_level=all --run_test=getarg_tests

... or to run just the doubledash test:

    test_vircles --run_test=getarg_tests/doubledash

Run `test_vircles --help` for the full list.

### Adding test cases

To add a new unit test file to our test suite you need
to add the file to `src/Makefile.test.include`. The pattern is to create
one test file for each class or source file for which you want to create
unit tests. The file naming convention is `<source_filename>_tests.cpp`
and such files should wrap their tests in a test suite
called `<source_filename>_tests`. For an example of this pattern,
see `uint256_tests.cpp`.

### Logging and debugging in unit tests

To write to logs from unit tests you need to use specific message methods
provided by Boost. The simplest is `BOOST_TEST_MESSAGE`.

For debugging you can launch the test_vircles executable with `gdb`or `lldb` and
start debugging, just like you would with virclesd:

```bash
gdb src/test/test_vircles
```
