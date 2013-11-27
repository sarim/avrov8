
        var sb = new imports.suggestionbuilder.SuggestionBuilder();
        
        var y = function(word){
                return sb.suggest(word);
        }
        
        var z = function(word, candidate){
                sb.stringCommitted(word, candidate);
        }
        
        return {suggest: y, commit: z};
    }
    
    return new sandbox();
}

