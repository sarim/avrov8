sb = new imports.suggestionbuilder.SuggestionBuilder();
print("init sb");
function testfunc(a){
	k =  JSON.stringify(sb.suggest(a));
	return k;
}

function word_committed(word, candidate){
	print("requested to commit " + word + ":" + candidate);
	sb.stringCommitted(word, candidate);
}