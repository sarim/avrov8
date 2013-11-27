AVROLIBS="utf8 suffixdict autocorrect avrodict levenshtein avrolib avroregexlib dbsearch gi suggestionbuilder"
MYDIR=`pwd`
LIBDIR="/Users/sarim/ibus-avro/avrov8/lib"

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

cat build.1.js > avro.final.js
cat avro.build.js >> avro.final.js
cat build.2.js >> avro.final.js

cat avro.final.js build.3.js > avro.test.js

rm avro.build.js
