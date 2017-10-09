function [ outSignal ] = averageSamples( inSignal )
%% Average sampled data

L = length(inSignal);

outSignal=zeros(1,L/2);


j=1;
for i=1 : L/2
   outSignal(i) = (mean(inSignal(j:j+1))); %uint16
   j = j + 2;
end
end

