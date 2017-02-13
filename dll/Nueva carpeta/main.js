const electron = require('electron')
var ffi = require('ffi');
var ref = require('ref');
var ArrayType = require('ref-array');
var floatArray = ArrayType(ref.types.float);
// You can also access just functions in the current process by passing a null
var Handler = ffi.Library("../example/dllexample", {
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
Handler.load_points(myHandlerObj,"../example/a.txt");
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

// In this file you can include the rest of your app's specific main process
// code. You can also put them in separate files and require them here.
