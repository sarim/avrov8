imports = {};
define = function(a){
	modulename = get_module_name();
	imports[modulename] = {};
	for (dkeys in a){
		imports[modulename][dkeys] = a[dkeys];
	}	
}
