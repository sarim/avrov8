/*
    =============================================================================
    *****************************************************************************
    The contents of this file are subject to the Mozilla Public License
    Version 1.1 (the "License"); you may not use this file except in
    compliance with the License. You may obtain a copy of the License at
    http://www.mozilla.org/MPL/

    Software distributed under the License is distributed on an "AS IS"
    basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See the
    License for the specific language governing rights and limitations
    under the License.

    The Original Code is jsAvroPhonetic

    The Initial Developer of the Original Code is
    Mehdi Hasan Khan <mhasan@omicronlab.com>

    Copyright (C) OmicronLab (http://www.omicronlab.com). All Rights Reserved.


    Contributor(s): ______________________________________.

    *****************************************************************************
    =============================================================================
*/


const sdb = imports.avrodict;
const RegexServer = imports.avroregexlib;
const dbpatterns = imports.patterndict;
const dbwords =  imports.worddict;
//const utfconvs = imports.utf8;

function DBSearch () {
    this._init();
}

DBSearch.prototype = {

	search: function (enText) {
        var queryobject = this._regex.parse(enText);
        queryobject.regex = '^' + queryobject.regex + '$';

        return this._query(queryobject) || [];
  	},


    _query: function(queryobject){
        var wordid = [];

        var startpattern = "^" + queryobject.tokens[0];
        wordid = dbpatterns[startpattern] || [];

        if (queryobject.patterns.length > 1){
          var endpattern = queryobject.tokens[queryobject.patterns.length - 1] + "$";
          var temp = dbpatterns[endpattern] || [];
          wordid = this._arrayIntersection(wordid, temp) || [];
        }

        return this._searchInArray(queryobject.regex, wordid);
     },


     /* Source: http://stackoverflow.com/questions/1885557/ */
     _arrayIntersection: function (a, b){
         var ai=0, bi=0;
          var result = new Array();

          while( ai < a.length && bi < b.length )
          {
             if      (a[ai] < b[bi] ){ ai++; }
             else if (a[ai] > b[bi] ){ bi++; }
             else /* they're equal */
             {
               result.push(a[ai]);
               ai++;
               bi++;
             }
          }

          return result;
    },


  	_searchInArray: function(pattern, wArrayId){
      var retWords = [];
      var re = new RegExp(pattern);
      wArrayId.forEach(function(wordid){
          if (re.test(dbwords[wordid])){
              retWords.push(dbwords[wordid]);
          }
      });

      return retWords;
  	},


	_printWords: function (enText) {
	    var words = this.search(enText);
	    for (w in words){
            print(words[w]);
        }
  	},


	_init: function () {
        this._regex = new RegexServer.AvroRegex();
  	}
}


/* --------- */
/* Test code */
/* --------- */
// var __dbSearch = new DBSearch ();
// __dbSearch._printWords('onirban');

define({"DBSearch" : DBSearch});
