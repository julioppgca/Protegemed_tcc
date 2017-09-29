function [ pkgData ] = dataDiff( inData )

%% signal length
L = length(inData);

%% difference identification
DIFF = int8(1);

%% Difference method
pkgData = zeros(1,L);

%% first element is the reference value
pkgData(1)=inData(1);

%% loop elements
for i=2:L
    pkgData(i) = inData(i-1)-inData(i);
end

%% limit test
if(max(pkgData(2:L)) > 127)   % exceed max diffefence value?
    pkgData = int8(-1);
else                          % pack into diference
    pkgData = [DIFF ...                                   % used algorithm
               int8(bitand(pkgData(1),hex2dec('0F'))) ... % ref value L
               int8(bitand(bitshift(pkgData(1),-4),hex2dec('0F'))) ... % ref value L
               int8(bitshift(pkgData(1),-8)) ...          % ref value H
               int8(pkgData(2:length(pkgData)))];         % diferences
end


end

