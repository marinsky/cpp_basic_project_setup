# Simple example to demonstrate C++ basic project setup

This C++ project was written in addition to
[this blogpost](https://victormarinsky.com/c-basic-project-setup/), which describes how
important good project setup is.

The repository has a simple "business-logic" file. It sets warning level to
maximum, treats all warnings as errors, uses code style analyzer and unit tests,
all of which were configured from the very beginning (before writing any code).

Repo shows how to integrate googletest and Google's cpplint into the build using cmake.
It also has a simple example of Google Test and Goolge Mock usage and how to configure
Google's cpplint.


## Dependencies

* CMake
* Python (path to `python2.7` should be in your env vars)


## Usage

```
git clone --recursive git@github.com:marinsky/cpp_basic_project_setup.git
cd cpp_basic_project_setup
cmake .
make
make tests
```

It works with clang and gcc, probably will work under cygwin as well.
