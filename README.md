Bare template for deal.II Application
=====================================

[![Build Status](https://travis-ci.org/luca-heltai/bare-dealii-app.svg)](https://travis-ci.org/luca-heltai/bare-dealii-app)

[![Build Status](https://gitlab.com/luca-heltai/bare-dealii-app/badges/master/build.svg)](https://gitlab.com/luca-heltai/bare-dealii-app/commits/master)


A bare deal.II application, with directory structure, and private
testsuite.

This repository can be used to bootstrap your own deal.II
application. The structure of the directory is the following:

	./source
	./include
	./tests

The directories contain a minimal working application (deal.II hello
world) which solves the Poisson problem using direct solvers.

The CMakeLists.txt will generate both an executable and a library
containing all cc files **except** source/main.cc. This library is
added to the running tests, so that you can make tests on your
application just as you would do with the deal.II library.

Make sure you have deal2lkit installed, and that you export the 
environment variable D2K_DIR to point to the location of 
deal2lkit installation. If you don't want to add that to your 
environment, just add -DD2K_DIR=/path/to/installation to 
your cmake command.

Modify the TARGET variable in the CMakeLists.txt to your application
name. Two libraries named ./tests/${TARGET}lib and ./tests/${TARGET}lib.g 
will be generated together with the executable when you compile your 
application.

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
image provided on dockerhub.com: `mathlab/deal2lkit:dev-debugrelease`.

Licence
=======

Please see the file ./LICENSE for details
