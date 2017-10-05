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
    
    console.log('TM4C connected: ' + sock.remoteAddress +':'+ sock.remotePort);
    
	var msg = [];	// to merge all chunks
	var i =0;		// index msg variable

	// new data arrived
    sock.on('data', function(data) {
        
		for(var j=0;j<data.length;j++)
		{
		msg[i++] = data[j];
		}
        console.log('Received msg from ' + sock.remoteAddress + ' with length: ' + data.length);
        //Write answer or not..
        //sock.write('OK');
        
    });
    
    // connectio closed by TM4C
    sock.on('close', function(data) {
        console.log('TM4C disconnected: ' + sock.remoteAddress +':'+ sock.remotePort);
		console.log('Total msg length:' + msg.length + '\n');
		processData(msg);
    });
    
}).listen(PORT, HOST);

console.log('Server listening on ' + HOST +':'+ PORT);

/*------------------------------------*/
/*        Msg data process            */
/*------------------------------------*/
function processData(msg)
{	
/*
*			Message structure
*	
*  [  Header  ][     Data    ]
*     20bytes      3840bytes
*
*	Header[0]: outlet LSB \
*   Header[1]: outlet MSB / int16 data type
*   Header[2]: event Id   / int8 data type
*   header[4..19]: Reserved for future use  
*
*   Data[20...3859]: 	Phase current samples
*   Data[3860...7699]: 	Differential current samples
*   Data[7700...11539]: Phase Voltage samples
*   Data[11540...15379]:Earth leakage current samples
*
*   Obs.: Data samples must be unmerged because each sample is shared between
*         two bytes.
*        Eg.:  
*			Sample1 = 0x0f12  //int16 data type
*			Sample2 = 0x0e37  //int16 data type
*			Merged into: 0xf12e37 //int32 data type
*			Will result:
*			   Data[0] = 0xf1  // Sample1 part 1
*			   Data[1] = 0x2e  // Sample1 part 2 and Sample3 part1
*			   Data[3] = 0x37  // Sample2 part 2
*              
*
*/
	
const HEADER_SIZE = 20;	 	 //header bytes lenght
const DATA_SIZE	  = 15360;   //data size in bytes
const TOTAL_SIZE  = 15380;   //expected msg size in bytes

const SAMPLES_OFFSET = 3840; // interval 

var header=[];
var data=[];

// extract header
for(var i=0; i < HEADER_SIZE ;i++)
{
	header[i] = msg[i]; 
}

// extract data
for(var i=HEADER_SIZE; i < DATA_SIZE ;i++)
{
	data[i-HEADER_SIZE] = msg[i]; 
}

// print msgs size
console.log('\tHeader size: ' + header.length);	
console.log('\tData size: ' + data.length);	


// object to access data header
var objHeader = {Outlet:0,Event:0,Reserved:0};
var eventEnum = ['unknow','Off','Turns On','Turns Off', 'On' ];
// unpack data header
objHeader.Outlet = header[1]<<8 | header[0];
objHeader.Event = header[2];
objHeader.Resever = 0;
// log to console
console.log('\nNew message at ' + timeStamp());
console.log('\tOutlet Number: ' +  objHeader.Outlet + 1);
console.log('\tOutlet Event: ' +  eventEnum[objHeader.Event]);

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

// export to csv file
toCSV('phase.csv',JSON.stringify(objSamples.phase));
toCSV('diff.csv',JSON.stringify(objSamples.diff));
toCSV('voltage.csv',JSON.stringify(objSamples.voltage));
toCSV('leakage.csv',JSON.stringify(objSamples.leakage));
}


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