#!/bin/bash
AVROLIBS="utf8 version suffixdict autocorrect avrodict levenshtein avrolib avroregexlib dbsearch suggestionbuilder"
MYDIR=`pwd`
LIBDIR=$MYDIR"/src"

echo //Shit Starts Here > avro.build.js

cd $LIBDIR

for LIBNAME in $AVROLIBS
do
echo -n \; modulename = \"$LIBNAME\" \; >> $MYDIR/avro.build.js
cat $LIBNAME.js >> $MYDIR/avro.build.js
echo \; >> $MYDIR/avro.build.js
done

cd $MYDIR

echo //Shit Ends Here >> avro.build.js

cat inc/build.1.js > avro.final.js
cat avro.build.js >> avro.final.js
cat inc/build.2.js >> avro.final.js

cat avro.final.js inc/build.3.js > avro.test.js

rm avro.build.js
