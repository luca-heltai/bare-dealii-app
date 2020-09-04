Bare template for deal.II Application
=====================================

[![Build Status](https://travis-ci.org/luca-heltai/bare-dealii-app.svg)](https://travis-ci.org/luca-heltai/bare-dealii-app)

[![Build Status](https://gitlab.com/luca-heltai/bare-dealii-app/badges/master/build.svg)](https://gitlab.com/luca-heltai/bare-dealii-app/commits/master)


A bare deal.II application, with directory structure, a testsuite, and unittest
block based on google tests.

This repository can be used to bootstrap your own deal.II
application. The structure of the directory is the following:

	./source
	./include
	./tests
	./gtests

The directories contain a minimal working application (identical to step-4, 
where source and include have been separated) which solves the Poisson problem
on a square, a test directory that uses deal.II style testing, and a test 
directory that uses google tests.

The CMakeLists.txt will generate both an executable and a library
containing all cc files **except** source/main.cc. This library is
added to the running tests, so that you can make tests on your
application just as you would do with the deal.II library.

Modify the TARGET variable in the CMakeLists.txt to your application
name. Two libraries named ./tests/${TARGET}lib and ./tests/${TARGET}lib.g 
will be generated together with one executable per dimension, per build type.

After you have compiled your application, you can run 

	make test

or
	
	ctest 

to start the testsuite.

Take a look at
https://www.dealii.org/developer/developers/testsuite.html for more
information on how to create tests and add categories of tests.

Both `.travis.yml` and `.gitlab-ci.yml` files are provided that 
build the application and run the tests in the tests directory using
ctest, in continuous integration, by running under docker with the 
image provided on dockerhub.com: `dealii/dealii:master-focal`.

Licence
=======

See the file ./LICENSE for details
