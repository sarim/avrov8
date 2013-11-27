var AvroPhonetic = function(loadFunc, saveFunc, options){
    var sandbox = function(loadFunc, saveFunc, options){
        
        var imports = {};
        var modulename;
        var define = function(a){
                imports[modulename] = {};
                for (dkeys in a){
                        imports[modulename][dkeys] = a[dkeys];
                }
        }
        
        var print = function(a){
            console.log(a);
        }
        
        
