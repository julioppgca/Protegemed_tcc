%% Matlab script for testing TCP/IP communication with matlab
%% This script is the receiver part
%% Written by Philippe Lucidarme
%% http://www.lucidarme.me

%% TCP/IP Receiver

% Clear console and workspace
close all;
clear all;
clc;

% Configuration and connection
disp ('Receiver started');
t=tcpip('192.168.2.151', 7891,'NetworkRole','server');

% Wait for connection
disp('Waiting for connection');
fopen(t);
disp('Connection OK');

% Read data from the socket
for i=0:10
    DataReceived=fread(t,2)
end