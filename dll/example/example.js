var ffi = require('ffi');
var ref = require('ref');
var ArrayType = require('ref-array');
var floatArray = ArrayType(ref.types.float);
// You can also access just functions in the current process by passing a null
var Handler = ffi.Library("./dllexample", {
   "create_Handler":["pointer",[]],
   "free_Handler": ["void",["pointer"]],
   "calc_fibonnacci":["int",["pointer","int"]],
   "bobo_sort":["void",["pointer",floatArray,"int"]],
   "load_points":["void",["pointer","string"]],
   "get_point":[floatArray,["pointer","int"]],
   "get_dimension_points":[floatArray,["pointer","int"]],
   "hello_string":["int",["pointer",ref.refType(ref.types.char),"string","int"]],

});
var buf = new Buffer(100);
buf.type = ref.types.char;
var myHandlerObj=Handler.create_Handler();
console.log(Handler.calc_fibonnacci(myHandlerObj,20));
console.log("***")
Handler.load_points(myHandlerObj,"a.txt");
var aux1=Handler.get_dimension_points(myHandlerObj,1);
aux1.length=3;
var aux1_array = aux1.toArray().slice(0, 3);
var aux2=Handler.get_dimension_points(myHandlerObj,2);
aux2.length=3;
var aux2_array = aux2.toArray().slice(0, 3);
aux1_array.forEach(function(element) {
  console.log(element);
  });
  console.log("***")
aux2_array.forEach(function(element) {
  console.log(element);
});
console.log("***");
var b = new floatArray([1.2,7 ,2, 0.2, 1, 0]);
Handler.bobo_sort(myHandlerObj,b,b.length);
for (var i = 0; i < b.length; i++) {
  console.log(b[i]);
}
var pez= new Buffer(10*ref.sizeof.char);
pez.type= ref.types.char;
console.log("**");
Handler.hello_string(myHandlerObj,pez,"toby",pez.length);
console.log(pez.toString());
console.log("***");


Handler.free_Handler(myHandlerObj);
