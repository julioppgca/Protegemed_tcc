function [ outData ] = dataUndiff( inData )

%% signal length
L = length(inData);

%% Difference method
outData = int16(zeros(1,L-3));

%% bytes 2..4 are the reference value
outData(1)=bitor(bitor(bitshift(inData(4),8),bitshift(inData(3),4)),inData(2));

%% loop elements
for i=5:L
    outData(i-3) = outData(i-4)-inData(i);
end
% 
% %% limit test
% if(max(pkgData(2:L)) > 127)   % exceed max diffefence value?
%     pkgData = int8(-1);
% else                % pack into diference
%     pkgData = [DIFF ...                                   % used algorithm
%                int8(bitand(pkgData(1),hex2dec('FF'))) ... % ref value L
%                int8(bitshift(pkgData(1),-8)) ...          % ref value H
%                int8(pkgData(2:length(pkgData)))];         % diferences
% end


end

