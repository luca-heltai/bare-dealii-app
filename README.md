Bare template for deal.II Application
=====================================

[![Build Status](https://travis-ci.org/luca-heltai/bare-dealii-app.svg)](https://travis-ci.org/luca-heltai/bare-dealii-app)

A bare deal.II application, with directory structure, and private
testsuite.

This repository can be used to bootstrap your own deal.II
application. The structure of the directory is the following:

	./source
	./include
	./tests

The directories contain a minimal working application (deal.II hello
world) which does nothing at all, except showing a reasonable
structure for large projects.

The CMakeLists.txt will generate both an executable and a library
containing all cc files **except** source/main.cc. This library is
added to the running tests, so that you can make tests on your
application just as you would do with the deal.II library.

Make sure you have dealii-sak installed, and that you export the 
environment variable DEAL_II_SAK to point to the location of 
dealii-sak installation. If you don't want to add that to your 
environment, just add -DDEAL_II_SAK=/path/to/installation to 
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

Licence
=======

Please see the file ./LICENSE for details



