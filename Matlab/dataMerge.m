function mrgData = mergaData(inData)
%% merge two int16 into 24 bytes

%% signal length
L = length(inData);

%% merge identification
MERGE = uint8(2);

mrgData= uint8(zeros(1,L*0.75));
mrgData(1)=MERGE;
k=2;

for j=1:2:L
    mrgData(k) = uint8(bitand(inData(j),hex2dec('FF')));
    mrgData(k+1) = uint8(bitand(bitshift(inData(j),-4),hex2dec('F0')));
    mrgData(k+1) = bitor(uint8(mrgData(k+1)), uint8(bitand(bitshift(inData(j+1),-8),hex2dec('0F'))));
    mrgData(k+2) = uint8(bitand(inData(j+1),hex2dec('FF')));
    k=k+3;
end

end
