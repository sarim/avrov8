#!/bin/bash
closure-compiler --compilation_level SIMPLE_OPTIMIZATIONS --accept_const_keyword --js_output_file=avro.min.utf.js --language_in ECMASCRIPT5 --jscomp_off globalThis --charset UTF-8 avro.final.js
closure-compiler --compilation_level SIMPLE_OPTIMIZATIONS --accept_const_keyword --js_output_file=avro.min.latin.js --language_in ECMASCRIPT5 --jscomp_off globalThis avro.final.js
