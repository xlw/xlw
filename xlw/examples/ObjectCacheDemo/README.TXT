

It has been asked several times on a number of forums and mailing lists how to implement the feature of persistent objects in XLW. 
The standard response from the XLW developers, and rightly so, is to use ObjectHandler. However sometimes what is required is a very small and
an extremely light-weight solution and some other times just a demonstration of how it could possibly be done. For these requests I have
coded a VERY simple implementation of the feature just to illustrate the concept.

This example consists of 2 Excel functions CreateObject and RetrieveObject.

CreateObject: Takes 2 parameters. The first is the name of the object and the second is a range in Excel (xlw::CellMatrix) which is the object to be stored
It returns the name of the object appended with '#n' where n is a number (explained later).

RetrieveObject : Takes the name of the object to be retrieved and returns it. If given the string 'matrix#100' as the name, then the function will actualy 
consider the  name of the object to be 'matrix'. Everything after the '#' is ignored.

What's with the '#' ?
Consider a function foo which takes as a parameter an object name and then internally retrieves that object and acts on it. If the object is a range of cells
on your spreadsheet then since foo only takes the name of the object as an input it will never know if you change anyone of those cells. If however 
the CreateObject function, used to create an object from those cells, always returns 'name#N', where N is incremented everytime it is called then foo will
think it's input has changed. ('name#97' goes to 'name#98') and it will be forced to re-compute. Internally howevere the '#N' will be ignored. So it's
a trick to force a function to calculate which needs to re-calculate but wouldn't given Excels behaviour.

  
 
The Demo addin provided is far from an industrial quality, as said before is purpose is to be only illustrative. Moreover their has no consideration has been
given to thread-safety, object types, clearing the cache and lot's of other important features that would be desireable.

The objects that you create on the spreadsheet with the function CreateObject are then persistent in memory for that instance of Excel. If you create an object
on a spreadsheet then close that spreadsheet (not Excel itself) then that object will be retrievable ( hence useable) in any other spreadsheet you open.


Narinder Claire 03/2011


Copyright (C) 2009 2010 2011 Narinder S Claire


 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.