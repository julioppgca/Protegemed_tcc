/**
 * 
 * ---- Software Parameters
 * 
 */

/*jshint esversion: 6 */ 
const HTML_LISTEN_PORT = 80;
const HTML_INDEX = "./index.html";
const CSS_STYLE = "./semantic/dist/semantic.min.css";
const TM4C_IP_ADR = '192.168.2.110';

//var fftData = {sine:[], cosine:[]};	// Object to save fftData received from TM4C html POST
var outlet = {id:[],fftData:{sine:[], cosine:[]}};

/**
 * 
 * ---- HTML Server ----
 * 
 */
var http = require('http');	// to mount html server
var   fs = require('fs');	// to read index.html page
const getPost = require('./scripts/capturePOST');

// from pg. 16 of 'Node.js by example' book
var app = http.createServer(function(req, res) {
	"use strict";
	var content = '';
    var type = '';
    if(req.url === '/') {
       content = fs.readFileSync(HTML_INDEX); 	// load html
       type = 'text/html';
    }else if(req.url === '/semantic/dist/semantic.min.css') {
       content = fs.readFileSync(CSS_STYLE);	// load css
       type = 'text/css';
    }else if(req.url === '/semantic/dist/icon.min.css') {
       content = fs.readFileSync("./semantic/dist/icon.min.css");	// load css
       type = 'text/css';
    }else if (req.url === '/node_modules/chart.js/samples/utils.js') {
        res.writeHead(200, {'Content-Type': 'application/javascript'});
        fs.createReadStream('node_modules/chart.js/samples/utils.js').pipe(res);
        return;
    }else if (req.url === '/node_modules/chart.js/dist/Chart.bundle.js') {
        res.writeHead(200, {'Content-Type': 'application/javascript'});
        fs.createReadStream('node_modules/chart.js/dist/Chart.bundle.js').pipe(res);
        return;
    }else if (req.url === '/node_modules/jquery/dist/jquery.min.js') {
        res.writeHead(200, {'Content-Type': 'application/javascript'});
        fs.createReadStream('node_modules/jquery/dist/jquery.min.js').pipe(res);
        return;
    }else if (req.url === '/semantic/dist/semantic.min.js') {
        res.writeHead(200, {'Content-Type': 'application/javascript'});
        fs.createReadStream('semantic/dist/semantic.min.js').pipe(res);
        return;
    }
	/* Process POST from TM4C */
	if (req.method === 'POST'){
		getPost.processPost(req, res, function() {
            console.log(req.post);
            // extract sine and cosine data from TM4C Post
			//outlet.id = req.post.OUTLET;
			//outlet.fftData.sine = req.post.SIN.split(';');
			//outlet.fftData.cosine = req.post.COS.split(';');
			var temp = JSON.stringify(req.post);
			io.emit('TM4CAnswer', temp);
			console.log('\nfftData: ' + JSON.stringify(temp));//+ JSON.stringify(outlet)); // + sine.length );
            res.writeHead(200, "OK", {'Content-Type': 'text/plain'});
            res.end();
        });
    }
		
    res.writeHead(200, {'Content-Type': type});
    res.end(content + '\n');
 
}).listen(HTML_LISTEN_PORT);


/**
 * 
 * ---- Socket.io HTML Interface ----
 * 
 */
var io = require('socket.io').listen(app);
io.on('connection', function(socket) {
	"use strict";
	
	socket.on('TM4CDeadAlive', function(){
    	//console.log('Html Request: TM4CDeadAlive ');
    	TM4CDeadAlive();
	});
	
	socket.on('GenerateFail', function(){
		//setTimeout(function(){
			for(var i=0;i<100;i++)
				writeSerial(FAIL_COMMAND);
		//},500);
		setTimeout(function(){
			for(var i=0;i<100;i++)
				writeSerial(NO_FAIL_COMMAND);
		},2000);
		
		
	});
	
	//io.emit('TM4CAnswer', temp);
    
});


/* Alive Signal */
var ping = require ("net-ping");
var session = ping.createSession ();

function TM4CDeadAlive()
{
	session.pingHost (TM4C_IP_ADR, function (error, target) {	
    if (error)
    		{
        		//console.log (target + ": " + error.toString ());
    			io.emit('aliveFromTM4C', 'Dead');
    		}
    else
    		{
        		//console.log (target + ": Alive");
    			io.emit('aliveFromTM4C', 'Alive');
    		}
	});
	
	
}



var SerialPort = require('serialport');
var serialPort = new SerialPort('COM2', {baudRate: 115200});
const FAIL_COMMAND =  new Buffer([0x53,200,20,230,230,0x45]); 
const NO_FAIL_COMMAND =  new Buffer([0x53,1,20,230,230,0x45]);


// sends data to the connected device via serial port
function writeSerial(data) {
	// write/send data to serial port
	serialPort.write(data, function (error) {
		if ( error ) {
		console.log('Failed to write serial port. \n\t' + error + '\n\n');
	}else{
		//console.log(data);
	}
	});
	
}
