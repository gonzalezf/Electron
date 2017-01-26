var express	=	require("express");
var multer	=	require('multer');
var app	=	express();
var rainfall = require("../file_upload/build/Release/file_upload");

fs = require('fs');
const util = require('util')
const readline = require('readline');
var lineReader = require('readline').createInterface({
  input: require('fs').createReadStream('../file_upload/uploads/userPhoto.txt')
});
var http = require('http');


var storage	=	multer.diskStorage({
  destination: function (req, file, callback) {
    callback(null, './uploads');
  },
  filename: function (req, file, callback) {
    callback(null, file.fieldname+'.txt');
  }
});
var upload = multer({ storage : storage}).single('userPhoto');

app.get('/',function(req,res){
      res.sendFile(__dirname + "/index.html");

});

app.post('/api/photo',function(req,res){
  //res.sendFile(__dirname + "/results.html");

	upload(req,res,function(err) {
		if(err) {
			return res.end("Error uploading file.");
		}
		res.end("File is uploaded");
	});
  var primes = rainfall2();
  console.log("PRIMES = "+primes);

});

function rainfall2(){

  function print_rain_results (results,locations) {
           var primes = new Array();
           var i = 0;


           results.forEach(function(result){

               console.log("Result for Location " + i);
               console.log("--------------------------");
               console.log("\tLatitude:         " + locations[i].latitude.toFixed(2));
               console.log("\tLongitude:        " + locations[i].longitude.toFixed(2));
               console.log("\tMean Rainfall:    " + result.mean.toFixed(2) + "cm");
               console.log("\tMedian Rainfall:  " + result.median.toFixed(2) + "cm");
               console.log("\tStandard Dev.:    " + result.standard_deviation.toFixed(2) + "cm");
               console.log("\tNumber Samples:   " + result.n);
               console.log();

               //Agregar valores a la pila para poder
               primes.push(locations[i].latitude.toFixed(2));

               primes.push(locations[i].longitude.toFixed(2));
               primes.push(result.mean.toFixed(2));
               primes.push(result.median.toFixed(2));
               primes.push(result.standard_deviation.toFixed(2));
               primes.push(result.n);
               i++;

           });
          return primes;
         }
         var makeup = function(max) {
             return Math.round(max * Math.random() * 100)/100;
         }


         fs.readFile('../file_upload/uploads/userPhoto.txt', 'utf8', function (err,data) {
            var locations = []

            if (err) {
              return console.log(err);
            }

            //console.log(data); Imprime el archivo de manera completa
            const input = readline.createInterface({
              input: fs.createReadStream('../file_upload/uploads/userPhoto.txt')
            });
            var count2 = 0;
            var count = 0;
            input.on('line', function (line) { // Leer archivo linea x linea
              //console.log('Line from file: - '+count+'-', line);
              if(count == 0){
                var lat = line;
              }
              if(count == 1){
                var lon = line;
              }
              count++;
              count2++;

              if(count == 2){
                var loc = {
                    latitude: makeup(180),
                    longitude: makeup(180),
                    samples : [
                        {date: "2015-07-20", rainfall: makeup(3)},
                        {date: "2015-07-21", rainfall: makeup(3)},
                        {date: "2015-07-22", rainfall: makeup(3)},
                        {date: "2015-07-23", rainfall: makeup(3)}
                    ]
                };
                locations.push(loc);
                count = 0;
              } // fin del count == 2

              if(count2 ==6){
                var results = rainfall.calculate_results(locations);
                var primes = print_rain_results(results,locations);
                console.log("Primes count = "+primes);
                var n= 5;
                var http = require('http');

                http.createServer(function (req, res) {
                  res.write('<html><head>  <meta charset="UTF-8"></head><body>');
                  res.write('<h1>Resultados</h1>');
                  for(var contador = 0; contador < 3; contador++){
                    res.write('<h4><br> Resultados para locacion:'+contador+'</br></h4>')
                    res.write('<p> Latitud: '+primes[contador]+'</p>')
                    res.write('<p> Longitud: '+primes[contador+1]+'</p>')
                    res.write('<p> Promedio:'+primes[contador+2]+'</p>')
                    res.write('<p> Mediana:'+primes[contador+3]+'</p>')
                    res.write('<p> Desviación Estandar:'+primes[contador+4]+'</p>')
                    res.write('<p> Número de samples:'+primes[contador+5]+'</p>')

                  }
                  res.end('</body></html>');
                }).listen(3001);
                return primes;
              }
            });
         });
};






app.listen(3000,function(){
    console.log("Working on port 3000");
});
