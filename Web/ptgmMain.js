/**
 * 
 * ---- Software Parameters
 * 
 */

/*jshint esversion: 6 */ 
const HTML_LISTEN_PORT = 3000;
const HTML_INDEX = "./index.html";
const CSS_STYLE = "./semantic/dist/semantic.min.css";


/**
 * 
 * ---- HTML Server ----
 * 
 */
var http = require('http');	// to mount html server
var   fs = require('fs');	// to read index.html page

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
	
	socket.on('createDataBase', function(data){
    	console.log('Create Data Base:' + data);
    	createDataBase(data);
    });
	
	// io.emit('dataBaseResponse', ("Error creating " + dbObj.dbName + ". < " + err.message + " >"));
    
});


var http = require('http');
var querystring = require('querystring');

function processPost(request, response, callback) {
    var queryData = "";
    if(typeof callback !== 'function') return null;

    if(request.method == 'POST') {
        request.on('data', function(data) {
            queryData += data;
            if(queryData.length > 1e6) {
                queryData = "";
                response.writeHead(413, {'Content-Type': 'text/plain'}).end();
                request.connection.destroy();
            }
        });

        request.on('end', function() {
            request.post = querystring.parse(queryData);
            callback();
        });

    } else {
        response.writeHead(405, {'Content-Type': 'text/plain'});
        response.end();
    }
}

http.createServer(function(request, response) {
    if(request.method == 'POST') {
        processPost(request, response, function() {
            console.log(request.post);
			//console.log('Sin values: ' + getFloat32(request.post.RMS));
			io.emit('TM4CAnswer', request.post.SIN );
            // Use request.post here

            response.writeHead(200, "OK", {'Content-Type': 'text/plain'});
            response.end();
        });
    } else {
        response.writeHead(200, "OK", {'Content-Type': 'text/plain'});
        response.end();
    }

}).listen(80);