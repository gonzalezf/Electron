var ffi = require('ffi');
var ref = require('ref');
var ArrayType = require('ref-array');
var floatArray = ArrayType(ref.types.float);
// You can also access just functions in the current process by passing a null
var current = ffi.Library("./dll_final", {
   "create_Handler":["pointer",["int","string","string"]],
   "free_Handler": ["void",["pointer"]],
   "getNumData": ["int",["pointer"]],
   "getNumLocations": ["int",["pointer"]],
   "getAllDist": [floatArray,["pointer"]]
});
var magic=current.create_Handler(1,"datos.txt","ubicaciones.txt");
var b= current.getNumLocations(magic);
pez=current.getAllDist(magic)
//var pez=current.getAllDist.async(magic,function(err,res){});
res.length = b;
var primes = pez.toArray().slice(0, b);
primes.forEach(function(element) {
  console.log(element);
  });
console.log(current.getNumData(magic));
console.log(b);
current.free_Handler(magic);
