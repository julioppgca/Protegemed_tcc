const net = require('net');

const PORT = 7891;
const ADDRESS = '192.168.2.151';

let server = net.createServer(onClientConnected);
server.listen(PORT, ADDRESS);

console.log(`Server started at: ${ADDRESS}:${PORT}`);

var msgCount=1;
var tmpMsg=0;

function onClientConnected(socket) {

  // Giving a name to this client
  let clientName = `${socket.remoteAddress}:${socket.remotePort}`;

  // Logging the message on the server
  // console.log(`${clientName} connected.`);

  // Triggered on data received by this client
  socket.on('data', (data) => { 

    // getting the string message and also trimming
    // new line characters [\r or \n]
    let m = data.toString().replace(/[\n\r]*$/, '');

    // Logging the message on the server
    // console.log(`${clientName} said: ${m}`);
	// console.log('Msg size: ' + m.length + ' Msg Id: ' + msgCount++ );

	if(m.length == 4200) console.log(' Msg Id: ' + msgCount++ );
	if(m.length < 4200)
	{
		tmpMsg = tmpMsg + m.length;
		if(tmpMsg == 4200) 
		{
			console.log(' Msg Id (S): ' + msgCount++ );
			tmpMsg = 0;
		}
	}
	
	
    // notifing the client
    // socket.write(`We got your message (${m}). Thanks!\n`);
  });
  
  // Triggered when this client disconnects
  socket.on('end', () => {
    // Logging this message on the server
    // console.log(`${clientName} disconnected.`);
	//msgCount=0;
  });
}