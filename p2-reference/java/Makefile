all: logserver log b64hash

logserver: LogServer.class
	echo '#!/bin/bash\nCLASSPATH=. java LogServer "$$@"' >logserver
	chmod 755 logserver

log: Log.class
	echo '#!/bin/bash\nCLASSPATH=. java Log "$$@"' >log
	chmod 755 log

b64hash: b64hash.class
	echo '#!/bin/bash\nCLASSPATH=. java b64hash "$$@"' >b64hash
	chmod 755 b64hash

%.class: %.java
	CLASSPATH=. javac $<

clean:
	rm -f log.txt loghead.txt
	rm -f *.class logserver log b64hash
