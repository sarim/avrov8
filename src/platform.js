imports = {};
define = function(a){
	imports[modulename] = {};
	for (dkeys in a){
		imports[modulename][dkeys] = a[dkeys];
	}	
}
