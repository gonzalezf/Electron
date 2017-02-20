const electron = require('electron')
// Module to control application life.
const app = electron.app
// Module to create native browser window.
const BrowserWindow = electron.BrowserWindow

var express	=	require("express");
var multer	=	require('multer');
//var rainfall = require("../ng2-electron-master/node_modules/file_upload/build/Release/file_upload");


// Keep a global reference of the window object, if you don't, the window will
// be closed automatically when the JavaScript object is garbage collected.
let mainWindow

function createWindow () {
  // Create the browser window.
  mainWindow = new BrowserWindow({width: 800, height: 600})

  // and load the index.html of the app.
  mainWindow.loadURL(`file://${__dirname}/index.html`)

  // Open the DevTools.
  // mainWindow.webContents.openDevTools()

  // Emitted when the window is closed.
  mainWindow.on('closed', function () {
    // Dereference the window object, usually you would store windows
    // in an array if your app supports multi windows, this is the time
    // when you should delete the corresponding element.
    mainWindow = null
  })
}

// This method will be called when Electron has finished
// initialization and is ready to create browser windows.
// Some APIs can only be used after this event occurs.
app.on('ready', createWindow)

// Quit when all windows are closed.
app.on('window-all-closed', function () {
  // On OS X it is common for applications and their menu bar
  // to stay active until the user quits explicitly with Cmd + Q
  if (process.platform !== 'darwin') {
    app.quit()
  }
})

app.on('activate', function () {
  // On OS X it's common to re-create a window in the app when the
  // dock icon is clicked and there are no other windows open.
  if (mainWindow === null) {
    createWindow()
  }
})
/**code example append**/
//inclusion de las librerias
var ffi = require('ffi');
var ref = require('ref');
var ArrayType = require('ref-array');
//defincion de la estructura de un arreglo de float
var floatArray = ArrayType(ref.types.float);
//inlcusion del dll, se debe aseugar que se entrega la ruta correcta
var Handler = ffi.Library("../example/Release/dllexample", {
  //definicion de la firma de las funciones
  //el primer elemento es el nombre de la funcion,
  //el segundo elemento es una lista con el output y input
  //se debe definir la clase del output y de cada output dentro de la lista
   "create_Handler":["pointer",[]],
   "free_Handler": ["void",["pointer"]],
   "calc_fibonnacci":["int",["pointer","int"]],
   "bobo_sort":["void",["pointer",floatArray,"int"]],
   "load_points":["void",["pointer","string"]],
   "get_point":[floatArray,["pointer","int"]],
   "get_dimension_points":[floatArray,["pointer","int"]],
   "hello_string":["int",["pointer",ref.refType(ref.types.char),"string","int"]],

});
console.log(" ");
console.log(" ");
//se genera un objeto de classe basic Handler
var myHandlerObj=Handler.create_Handler();
//se genera un arreglo con elementos tipo float
var array = new floatArray([1.2,7 ,2, 0.2, 1, 0]);
//se hace llamada de la funcion de la libreria
Handler.bobo_sort(myHandlerObj,array,array.length);
//Se imprime los datos por consola
for (var i = 0; i < array.length; i++) {
  console.log(" "+  array[i]);
}
//se genera un buffer de tamaño de 10 char en el cual
var my_str= new Buffer(10*ref.sizeof.char);
//se setea el tipo de elementos dentro de buffer como char
my_str.type= ref.types.char;
console.log(" **");
//se llama a la funcion de la liberia
Handler.hello_string(myHandlerObj,my_str,"toby",my_str.length);
//se imprime por pantalla, el metodo toString convierte el buffer en un string
console.log(" "+my_str.toString());
//se llama a la funcion de la libreria que carga los datos desde un archivo a una
//estrucutura dentro del objeto
console.log(" **");
Handler.load_points(myHandlerObj,"a.txt");
//se llama a la funcion de la liberia
var aux1=Handler.get_dimension_points(myHandlerObj,1);
//se setea el tamaño del arreglo en 3
aux1.length=3;
//se pasa de un arreglo de "C" aun arreglo javaScript
//esto genera una copia local de los datos
var aux1_array = aux1.toArray().slice(0, 3);
//se imprimen los datos
aux1_array.forEach(function(element) {
  console.log(" "+element);
  });
console.log(" **");
console.log(" "+Handler.calc_fibonnacci(myHandlerObj,20));
Handler.free_Handler.async(myHandlerObj, function (err, res) {});
// In this file you can include the rest of your app's specific main process
// code. You can also put them in separate files and require them here.
