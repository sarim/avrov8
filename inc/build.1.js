var AvroPhonetic = function(){
    var sandbox = function(){
        
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
        
        
