var dummyLoader = function() {
    console.log("Dummy Loader");
    return {'kak':  "কাঁক"}
}

var dummySaver = function(a) {
    console.log("Dummy Save, not really saving ;)");
    console.log(a);
}

var megusta = new AvroPhonetic(dummyLoader, dummySaver);
console.log( megusta.suggest("kak") );