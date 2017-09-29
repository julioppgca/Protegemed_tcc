function [ pkgData ] = dataPack( inData )
%% Packing data test.
%
% Fistr try to pack data using difference value from the previous point,
% if the difference value is greather than 127 (255/2), pack data into a
% merged format. Merged format merge two int16 ADC values into 3 bytes.
% This can be done because maximum resolution of TM4C ADC is 12bits.
%
% inData: ADC raw data (uint16)
% pkgData: outputed data (int8)
%
%

pkgData = dataDiff(inData);

if(length(pkgData)==1)
   pkgData = dataMerge(inData);
end

end
