
        var sb = new imports.suggestionbuilder.SuggestionBuilder(loadFunc, saveFunc, options);
        
        var y = function(word){
                return sb.suggest(word);
        }
        
        var z = function(word, candidate){
                sb.updateCandidateSelection(word, candidate);
                sb.stringCommitted(word, candidate);
        }
        
        var n = function(word){
            return sb._candidateSelections[word];
        }
        
        return {suggest: y, commit: z, candidate: n, version: "" + imports.version};
    }
    
    return new sandbox(loadFunc, saveFunc, options);
}

