/**
 * 
 * ---- Software Parameters
 * 
 */

/*jshint esversion: 6 */ 
const HTML_LISTEN_PORT = 80;
const HTML_INDEX = "./ptgmIndex.html";
const CSS_STYLE = "./semantic/dist/semantic.min.css";
const TM4C_IP_ADR = '192.168.2.110';
const TM4C_LISTEN_PORT = 1000;

const convert = require('./scripts/IEEE754_hex2float');

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
			var temp = JSON.stringify(req.post);
			//io.emit('TM4CAnswer', temp);
			console.log('\nReceived Data length: ' + JSON.stringify(temp));
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

    socket.on('newPhaseLimit', function(data){
        setPhaseLimit(data);
    })
	
    socket.on('getPhaseLimit', function(){
        var cmd = new Buffer([0x17, 0x00]); // read direct from outlet 1
        sendToTM4C(cmd);
    });

	//io.emit('TM4CAnswer', temp);
    
});

function setPhaseLimit(data) 
{
    var value = new Buffer(toFloat32(data).toString('16'),'hex');
    var cmdHeader = new Buffer([0x18, 0x00]); // write direct to outlet 1
    var cmd = new Buffer(6);
    cmd = Buffer.concat([cmdHeader, value]);;
    //console.log('cmd: ' + cmd);
    sendToTM4C(cmd);
}


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


/*------------------ TCP/IP Server --------------------------------*/

/**
*
*	Basic TCP Server to test TM4C Protegemed packets
*	
* 	Created by: Julio - julio.ppgca@gmail.com
*	Date: 4/10/2017		
*
*/


// TM4C settings must meet
const PORT = 7891;
const HOST = '192.168.2.151';

/*------------------------------------*/
/*           TCP Server               */
/*------------------------------------*/
net = require('net');

net.createServer(function(sock) {
    
    //console.log('TM4C connected: ' + sock.remoteAddress +':'+ sock.remotePort);
    
	var msg = [];	// to merge all chunks
	var i =0;		// index msg variable

	// new data arrived
    sock.on('data', function(data) {
        
		for(var j=0;j<data.length;j++)
		{
		msg[i++] = data[j];
		}
        //console.log('Received msg from ' + sock.remoteAddress + ' with length: ' + data.length);
        //Write answer or not..
        //sock.write('OK');
        
    });
    
    // connectio closed by TM4C
    sock.on('close', function(data) {
        //console.log('TM4C disconnected: ' + sock.remoteAddress +':'+ sock.remotePort);
		//console.log('Total msg length:' + msg.length + '\n');
		processData(msg);
    });
	
	// log error 
	sock.on('error', err => {
	console.log(err.stack);});
    
}).listen(PORT, HOST);
console.log('Server listening on ' + HOST +':'+ PORT);

/*------------------------------------*/
/*        Msg data process            */
/*------------------------------------*/
function processData(msg)
{	
/**
 *              Message constructor
 *
 * [                Message Frame                   ]
 * [                 15.400 bytes                   ]
 * [      HEADER      ][            DATA            ]
 * [      40bytes     ][          15360bytes        ]
 *
 *
 * HEADER:
 *  [00]    = Net protocol version (actual 0x01)
 *  [01]    = Outlet Number MSB \ Eg. 0x07A3 -> 0x07
 *  [02]    = Outlet Number LSB /            -> 0xA3
 *  [03]    = Event identifier
 *  [04]    = Channel Offset: Outlet phase current  MSB
 *  [05]    = Channel Offset: Outlet phase current  LSB
 *  [06]    = Channel Offset: Outlet diff current   MSB
 *  [07]    = Channel Offset: Outlet diff current   LSB
 *  [08]    = Channel Offset: Panel voltage to the specific outlet MSB  (Voltage 1 to outlets 0,1,2 or Voltage 2 to outlets 3,4,5)
 *  [09]    = Channel Offset: Panel voltage to the specific outlet LSB
 *  [10]    = Channel Offset: Panel earth leakage MSB
 *  [11]    = Channel Offset: Panel earth leakage LSB
 *  [12]    = Channel Gain: Outlet phase current  IEEE-754 Floating Point format MSB
 *  [13]    = Channel Gain: Outlet phase current  IEEE-754 Floating Point format
 *  [14]    = Channel Gain: Outlet phase current  IEEE-754 Floating Point format
 *  [15]    = Channel Gain: Outlet phase current  IEEE-754 Floating Point format LSB
 *  [16]    = Channel Gain: Outlet diff current  IEEE-754 Floating Point format MSB
 *  [17]    = Channel Gain: Outlet diff current  IEEE-754 Floating Point format
 *  [18]    = Channel Gain: Outlet diff current  IEEE-754 Floating Point format
 *  [19]    = Channel Gain: Outlet diff current  IEEE-754 Floating Point format LSB
 *  [20]    = Channel Gain: Panel voltage to the specific outlet  IEEE-754 Floating Point format MSB
 *  [21]    = Channel Gain: Panel voltage to the specific outlet  IEEE-754 Floating Point format
 *  [22]    = Channel Gain: Panel voltage to the specific outlet  IEEE-754 Floating Point format
 *  [23]    = Channel Gain: Panel voltage to the specific outlet  IEEE-754 Floating Point format LSB
 *  [24]    = Channel Gain: Panel earth leakage IEEE-754 Floating Point format MSB
 *  [25]    = Channel Gain: Panel earth leakage IEEE-754 Floating Point format
 *  [26]    = Channel Gain: Panel earth leakage IEEE-754 Floating Point format
 *  [27]    = Channel Gain: Panel earth leakage IEEE-754 Floating Point format LSB
 *  [28]    = RFID MSB ( ASCII Data format)
 *  [29]    = RFID
 *  [30]    = RFID
 *  [31]    = RFID
 *  [32]    = RFID
 *  [33]    = RFID
 *  [34]    = RFID
 *  [35]    = RFID LSB
 *  [36..39]= Reserved.
 *
 * DATA:
 *  [00040...03879]  = Raw Data: Phase Samples +merged format
 *  [03880...07719]  = Raw Data: Diff  Samples +merged format
 *  [07720...11559]  = Raw Data: Voltage Samples +merged format
 *  [11560...15399]  = Raw Data: Earth Leakage Samples +merged format
 *
 *  + Merged Format:
 *      Merge two int16 data into 3 int8 data, this can be done because ADC converter had a 12bit resolution.
 *      ADC maximum value is 0x0FFF (4095) therefore its possible to use the highest nibble together with the next sample value.
 *        Eg.:
 *           Sample1 = 0x0f12  //int16 data type
 *           Sample2 = 0x0e37  //int16 data type
 *           Merged into: f1 2e 37
 *           Will result:
 *              Data[0] = 0xf1  // Sample1 part 1
 *              Data[1] = 0x2e  // Sample1 part 2 and Sample2 part1
 *              Data[2] = 0x37  // Sample2 part 2
 *
 */
	
const HEADER_SIZE = 40;	 	 				//header bytes lenght
const DATA_SIZE	  = 15360;   				//data size in bytes
const TOTAL_SIZE  = HEADER_SIZE + DATA_SIZE;//expected msg size in bytes
const SAMPLES_OFFSET = 3840; 				//interval among sampled block raw data

var header=[];
var data=[];

// extract header
for(var i=0; i < HEADER_SIZE ;i++)
{
	header[i] = msg[i]; 
}

// extract data
for(var i=HEADER_SIZE; i < TOTAL_SIZE ;i++)
{
	data[i-HEADER_SIZE] = msg[i]; 
}

// print msgs size
// console.log('\tMessage size: ' + msg.length);
// console.log('\tHeader size: ' + header.length);	
// console.log('\tData size: ' + data.length);	

// object to access data header
var objHeader = {netVersion:0,Outlet:0,Event:0, 
				phaseOffset:0, diffOffset:0, voltageOffset:0,leakageOffset:0,
				phaseGain:0, diffGain:0, voltageGain:0, leakageGain:0, RFID:'',Reserved:0};
var eventEnum = ['unknow','Off','Turns On','Turns Off', 'On' ];
// unpack data header
objHeader.Outlet = parseInt(header[1]<<8 | header[2]);
objHeader.Event = header[3];

objHeader.phaseOffset 	= parseInt(header[4]<<8  | header[5]);
objHeader.diffOffset 	= parseInt(header[6]<<8  | header[7]);
objHeader.voltageOffset = parseInt(header[8]<<8  | header[9]);
objHeader.leakageOffset = parseInt(header[10]<<8 | header[11]);

objHeader.phaseGain 	= convert.hex2float(parseInt(header[12]<<24 | header[13]<<16 | header[14]<<8 | header[15]));
objHeader.diffGain 		= convert.hex2float(parseInt(header[16]<<24 | header[17]<<16 | header[18]<<8 | header[19]));
objHeader.voltageGain 	= convert.hex2float(parseInt(header[20]<<24 | header[21]<<16 | header[22]<<8 | header[23]));
objHeader.leakageGain 	= convert.hex2float(parseInt(header[24]<<24 | header[25]<<16 | header[26]<<8 | header[27]));

objHeader.RFID = String.fromCharCode(header[28]) + String.fromCharCode(header[29]) + 
				 String.fromCharCode(header[30]) + String.fromCharCode(header[31]) + 
				 String.fromCharCode(header[32]) + String.fromCharCode(header[33]) + 
				 String.fromCharCode(header[34]) + String.fromCharCode(header[35]) ;
				 
objHeader.Reseverd = 0;
// log to console
console.log('\nNew message at ' + timeStamp());
console.log('\tOutlet Number: ' +  objHeader.Outlet);
console.log('\tOutlet Event: ' +  eventEnum[objHeader.Event]);
console.log('\tPhase Offset: ' + objHeader.phaseOffset);
console.log('\tPhase Gain: ' + objHeader.phaseGain);
console.log('\tDiff Offset: ' + objHeader.diffOffset);
console.log('\tDiff Gain: ' + objHeader.diffGain);
console.log('\tVoltage Offset: ' + objHeader.voltageOffset);
console.log('\tVoltage Gain: ' + objHeader.voltageGain);
console.log('\tLeakage Offset: ' + objHeader.leakageOffset);
console.log('\tLeakage Gain: ' + objHeader.leakageGain);
console.log('\tRFID: ' + objHeader.RFID);

// object to access data Samples
var objSamples = {phase:[],diff:[],voltage:[],leakage:[]};

// logging for debug purpose only
// console.log('data0: ' + data[0]);	
// console.log('data1: ' + data[1]);
// console.log('data2: ' + data[2]);
// console.log('Sample0: ' + parseInt(data[0]<<4 | data[1]>>4));	
// console.log('Sample1: ' + parseInt(parseInt((data[1]<<8 & 0x0FFF)) | data[2]));


// unmerge phase current  
for(var i=0, j=0; j<SAMPLES_OFFSET; i=i+2, j=j+3)
{
	objSamples.phase[i]= parseInt(data[j]<<4 | data[j+1]>>4);
	objSamples.phase[i + 1] = parseInt(parseInt((data[j+1]<<8 & 0x0FFF)) | data[j+2]);
}

//unmerge diff current
for(var i=0, j=SAMPLES_OFFSET; j<2*SAMPLES_OFFSET; i=i+2, j=j+3)
{
	objSamples.diff[i]= parseInt(data[j]<<4 | data[j+1]>>4);
	objSamples.diff[i + 1] = parseInt(parseInt((data[j+1]<<8 & 0x0FFF)) | data[j+2]);
}

//unmerge voltage
for(var i=0, j=2*SAMPLES_OFFSET; j<3*SAMPLES_OFFSET; i=i+2, j=j+3)
{
	objSamples.voltage[i]= parseInt(data[j]<<4 | data[j+1]>>4);
	objSamples.voltage[i + 1] = parseInt(parseInt((data[j+1]<<8 & 0x0FFF)) | data[j+2]);
}

//unmerge earth leakage
for(var i=0, j=3*SAMPLES_OFFSET; j<4*SAMPLES_OFFSET; i=i+2, j=j+3)
{
	objSamples.leakage[i]= parseInt(data[j]<<4 | data[j+1]>>4);
	objSamples.leakage[i + 1] = parseInt(parseInt((data[j+1]<<8 & 0x0FFF)) | data[j+2]);
}

// debug returned data
//console.log('obj return: ' + JSON.stringify([objHeader, objSamples]));

// websocket to html page
io.emit('TM4CAnswer', JSON.stringify([objHeader, objSamples]));

// export to csv file
// toCSV('phase.csv',JSON.stringify(objSamples.phase));
// toCSV('diff.csv',JSON.stringify(objSamples.diff));
// toCSV('voltage.csv',JSON.stringify(objSamples.voltage));
// toCSV('leakage.csv',JSON.stringify(objSamples.leakage));
}

//console.log('obj return: ' + JSON.stringify(objSamples));
//io.emit('TM4CAnswer', JSON.stringify(objSamples));

//var dataToWrite;
var fs = require('fs');

function toCSV(fileName, dataToWrite)
{
	fs.writeFile(fileName, dataToWrite, 'utf8', function (err) {
	  if (err) {
		console.log('Some error occured - file either not saved or corrupted file saved.');
	  } else{
		//console.log('It\'s saved!');
	  }
	});
}


/*------------------------------------*/
/*           TCP Client               */
/*------------------------------------*/

var client = new net.Socket(); // client to send/receive commands

/**
*
*		Send new phase limit to Outlet 1 only 
*
* Msg Format:
*	0x18 = Set new phase limit
*	0x?? = ??:Outlet number, 0x00 - outlet 1, 0x01 outlet 2 ...
*   value = IEEE-754 floating point in hex format
*
*/
function sendToTM4C(cmd) {
    "use strict";
    //console.log("cmd: " + cmd + " data: " + data);

    client.connect(TM4C_LISTEN_PORT,TM4C_IP_ADR, function() {
    console.log('Connected');
    client.write(cmd);
    });

}

/**
*
*		Get actual phase limit in Outlet 1
*
*/
client.on('data', function(data){
    var res = JSON.stringify(data);
    console.log('TM4C response: ' + res);
    if((data[0] == 79) & (data[1] == 75))
    {
        console.log('It was ok.');
    }
    else
    {
        var res = JSON.stringify(data);
        res = convert.hex2float(parseInt(data[0]<<24 | data[1]<<16 | data[2]<<8 | data[3]));
        //console.log('Its a number: '+ res);
        io.emit('actualPhaseLimit', res);
    }
})

/**
*
*		Timestamp to log incomming messages
*
*/
function timeStamp() {
    var str = "";

    var currentTime = new Date()
    var hours = currentTime.getHours()
    var minutes = currentTime.getMinutes()
    var seconds = currentTime.getSeconds()
	var miliseconds = currentTime.getMilliseconds()

    if (minutes < 10) {
        minutes = "0" + minutes
    }
    if (seconds < 10) {
        seconds = "0" + seconds
    }
    str += hours + ":" + minutes + ":" + seconds + ":" + miliseconds + " ";
    if(hours > 11){
        str += "PM"
    } else {
        str += "AM"
    }
    return str;
}

/**
*
*		Convert Float to byte stream format (float to IEEE-754 hex format)
*
*/
function toFloat32(value) {
    var bytes = 0;
    switch (value) {
        case Number.POSITIVE_INFINITY: bytes = 0x7F800000; break;
        case Number.NEGATIVE_INFINITY: bytes = 0xFF800000; break;
        case +0.0: bytes = 0x40000000; break;
        case -0.0: bytes = 0xC0000000; break;
        default:
            if (Number.isNaN(value)) { bytes = 0x7FC00000; break; }

            if (value <= -0.0) {
                bytes = 0x80000000;
                value = -value;
            }

            var exponent = Math.floor(Math.log(value) / Math.log(2));
            var significand = ((value / Math.pow(2, exponent)) * 0x00800000) | 0;

            exponent += 127;
            if (exponent >= 0xFF) {
                exponent = 0xFF;
                significand = 0;
            } else if (exponent < 0) exponent = 0;

            bytes = bytes | (exponent << 23);
            bytes = bytes | (significand & ~(-1 << 23));
        break;
    }
    return bytes;
};
