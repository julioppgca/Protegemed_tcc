function mrgData = mergaData(in)
%% merge two uint16 into 24 bytes
mrgData= uint16(zeros(1,L*0.75));
k=1;
for j=1:L/2+1
    mrgData(k) = int8(bitand(inData(i),hex2dec('FF')));
    mrgData(k+1) = int8(bitand(bitshift(inData(i),-4),hex2dec('F0')));
    mrgData(k+1) = bitor(mrgData(k+1), int8(bitand(bitshift(inData(i+1),-8),hex2dec('0F'))));
    mrgData(k+2) = int8(bitand(inData(i+1),hex2dec('FF')));
end
end

