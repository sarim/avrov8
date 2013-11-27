
        var sb = new imports.suggestionbuilder.SuggestionBuilder();
        
        var y = function(a){
                return sb.suggest(a).words;
        }
        
        return y;
    }
    
    return new sandbox();
}

