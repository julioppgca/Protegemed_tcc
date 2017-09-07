function [ X ] = fft_analisys( Fs, signal )
%% Apply fft transform and reconstruct the signal based on some harmonics
% Input: 
%   Fs: Sample frequency
%   signal: Vector of the original signal
% Output:
%   r_signal: Reconstructed signal
%
% Reconstruct equation:
%   r_singal = dc_component + amplitude * cos(2*pi*f + phi);    
%

%% process fft
T=1/Fs;             % sample periode
L=length(signal);   % frame size
t=(0:L-1)*T;        % time vector
X=fft(signal);      % take the fft
A= abs(X/(L/2));    % amplitude 
phi = angle(X);     % angle
A=A(1:L/2+1);       % half of frequency spectre
f=Fs*(0:(L/2))/L;   % frequency vector

%% reconstruct wave based on harmonics defined by Max_harmonic;
Max_harmonic = 60*13;       % 13rd harmonic of 60Hz (780)
p = linspace(0,2*pi,L);     % points in signal
r_signal=A(1);              % DC component
for j=2 : 1 : ( Max_harmonic /(Fs/L))
    r_signal = r_signal + ( A(j) * (cos((j-1)* p + phi(j))));
end

%% plot results
subplot(3,1,1);     % original signal plot
plot(t,signal);     
title('Original signal');
xlabel('time (s)');
ylabel('amplitude (v)');
legend(strcat(num2str(rms(signal)),' Vrms'));
grid;
subplot(3,1,2);      % frequency vs amplitude
bar(f(1:( Max_harmonic /(Fs/L))),A(1:( Max_harmonic /(Fs/L))),'g'); 
title('Frequency spectre');
xlabel('frequency (Hz)');
ylabel('amplitude (v)');
grid;
legend(strcat('Frequency resolution: ', num2str(Fs/L),'Hz'));
subplot(3,1,3);
plot(t,r_signal,'r');   % reconstructed signal
title('Reconstructed signal');
xlabel('time (s)');
ylabel('amplitude (v)');
legend(strcat(num2str(rms(r_signal)),' Vrms'));
grid
end