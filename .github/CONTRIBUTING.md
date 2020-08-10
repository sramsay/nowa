# How to contribute

Forthcoming . . .

## Bugs, Feature Requests, and Other Issues

First, check to make sure that your issue isn't [already addressed](https://github.com/sramsay/temper/issues/) somewhere.  If you're reasonably confident that it isn't, [create an issue](https://github.com/sramsay/temper/issues/new/choose).  Please note that you need a [GitHub account](https://github.com/signup/free) in order to do this.

## Describe your issue

Try to describe your issue as clearly as possible.

    - If it is a bug, please describe how to **reproduce** it. If possible, attach a complete example which demonstrates the error. Please also state what you **expected** to happen instead of the error.

    - If you propose a change or addition, try to give an **example** how the improved code might look or how to use it.

    - If you found a compilation error, please tell us which **compiler** (version and operating system) you used and paste the (relevant part of) the error messages to the ticket.


<!--
If you add or change a feature, please also add an appropriate test.  The testing framework uses [Catch2](https://github.com/catchorg/Catch2) for unit testing, and [Bats](https://github.com/sstephenson/bats) for testing command-line inputs.  You can compile and run the existing tests with:

  cd test
  make check

The check target runs scripts/run-tests.sh, does something like the following:

  $ meson build
  $ ninja -C build # to create the temper-test
  $ build/temper-test # unit testing
  $ cd scripts
  $ bats temper_cli_tests

I've encountered what appears to a bug that prevents "check" from being a ninja target in meson.  When that is resolved, I will probably get rid of the Makefile.  But the basic principle will stay the same.

-->

## Processes

I generally test all code using the latest stable versions of clang and gcc, and do my best to keep up with the latest versions of all dependencies.  I also run *clang_tidy* using the *.clang_tidy* config in the root directory of the project and run valgrind on the resulting binary with various options.  Code that produces issues with either static analyzer that cannot be satisfactorily resolved is very unlikely to be merged.

I am not particularly interested in code that is meant to run on ancient compilers or incarnations of the C standard (though the project does use [travis-ci](https:://travis-ci.org) for continuous integration, and not all compilers tested are absolutely cutting edge).  If you are interested in getting nowa to run with older toolchains or on more exotic platforms, you are welcome to fork the project.  I say this without the least bit of sarcasm.  In fact, if you do fork the project for these reasons, please let me know so I can link to it!
