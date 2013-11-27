This is just a initial step of cleaning up js library.

TESTING:
Running build.sh will combine the library files inside a closure with some glue code. avro.final.js can be tested from test.html. avro.test.js can be run by node.
compiler.sh will minify/compile js file to both utf and latin encoding.

TODO:

need to move sh files into one makefile.

a good test.html page.


DONE:
external load and save function interface.


NOTE:
i put the localStorage.js in plugings folder. There can be other implementations, like IndexedDB, or Some cloud saving thing, browser extension data save interface bla bla bla.


