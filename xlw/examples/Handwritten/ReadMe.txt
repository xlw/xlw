Xlw Handwritten example
=======================

This example shows how to do various things talking to the low level Excel api directly.

In this example there is no interface generation and it is intended for anybody looking to 
understand more deeply the way Xlw works internally or require the extra performance that
copme from avoiding copying.

Each of the cpp files is stand alone and can be used as a basis for your own projects.

The example is split into the following files which are located in the common_source 
sub-directory

1) xlwExample.cpp - simple examples using the XlfOper structure
2) xlwAsynchExample.cpp - demonstrates how to use Excel 2010's new
   Asychronous function capability
3) xlwMatrixTest - Some performance test functions
4) xlwCommands - demonstrates how to run code when add-in is loaded and unloaded as well as
   adding a simple menu
5) xlwXlmMacros.cpp - gives a simple example of using XLM macro function sfrom within a function

