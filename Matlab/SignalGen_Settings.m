%%     
%      Signal Generation Init Script
%
%  Author: Júlio Santos - julio.ppgca@gmail.com
%  Date: 29/12/2016
%  V1.1
%   
% This script generates 4 test signals using F29069M (LaunchPadXL) and 
% embedded code generation tool from Matlab/Simulink.
% Model SignalGen4.slx call it at startup moment to generate the 
% values used by model lookup tables.
%
% Test signal are outputed as a follow:
%   DAC1 = Phase Current        (DAC1 is PWM7_A)
%   DAC2 = Differential Current (DAC2 is PWM7_B)
%   DAC3 = Phase Voltage        (DAC3 is PWM8_A)
%   DAC4 = Pure 60Hz sine wave  (DAC4 is PWM8_B)
%
%

%% Clear workspace
clear

%% Sampling Parameters
SampleNumber = 512;
BaseFrequency = 60; %Hz
SampleTime = 1 / (BaseFrequency*SampleNumber);
SampleFrequency = 1 / SampleTime;
t = linspace(0,2*pi,SampleNumber);
time_vector = 0:1/SampleFrequency:(1/BaseFrequency)-1/SampleFrequency;

%% PWM Parameters
CPU_Frequency = 90e6; % F28069M run at 90MHz.
PWM_Frequency = 250e3; % 250KHz is good enought, DAC is a LPF (R=1k, C=0.1uF)
PWM_Counter = CPU_Frequency/PWM_Frequency; % Max PWM conter
PWM_Offset = PWM_Counter/2; % Middle point of PWM counter

%% Wave Generation Parameters
PWM_Max_Voltage = 3.3; %Volts
PWM_Scale = PWM_Max_Voltage/PWM_Counter;

%% DAC1: Phase Current wave
DAC1_H1 = 0.25 * cos(t);
DAC1_H2 = 0.15 * cos(3 * t + pi/4);
DAC1_H3 = 0.08 * cos(7 * t + pi);
DAC1_A  = 1;
DAC1 = ceil( DAC1_A  * PWM_Counter * ...
           ( DAC1_H1 + DAC1_H2 + DAC1_H3) + ...
             PWM_Offset );
   
%% DAC2: Differential Current Wave
DAC2_H1 = 0.1 * cos(t);
DAC2_H2 = 0.08 * cos(3 * t + pi/4);
DAC2_H3 = 0.05 * cos(7 * t + pi/6);
DAC2_H4 = 0.07 * cos(13 * t + pi/2);
DAC2_A  = 1;
DAC2 = ceil( DAC2_A  * PWM_Counter * ...
           ( DAC2_H1 + DAC2_H2 + DAC2_H3 + DAC2_H3) + ...
             PWM_Offset );

%% DAC3: Phase Voltage, pure sine 60HZ wave
DAC3_H1 = 0.8 * cos(t);
DAC3_A  = 0.5;
DAC3 = ceil( DAC3_A  * PWM_Counter * ...
             DAC3_H1 + ...
             PWM_Offset );
         
%% DAC4:  60Hz sine wave with gaussian noise
DAC4_H1 = 0.5 * cos(t);
DAC4_noise = 0.05*wgn(SampleNumber,1,0)';
DAC4_A  = 0.8;
DAC4 = ceil( DAC4_A  * PWM_Counter * ...
           ( DAC4_H1 + DAC4_noise ) + ...
             PWM_Offset );
         
%% Uncomment bellow to see wave forms and rms values scaled to 3.3V
% %% DAC1: expected osciloscope wave (AC coupled)
% DAC1_Voltage = DAC1*PWM_Scale;
% DAC1_rms = rms(DAC1_Voltage-mean(DAC1_Voltage));
% figure(1);
% stairs(time_vector,DAC1_Voltage-mean(DAC1_Voltage));
% title('DAC1: Phase current');
% legend(strcat('DAC1: ', num2str(DAC1_rms), 'Vrms'));
% xlabel('time (s)');
% ylabel('amplitue (v)');
% grid
% 
% %% DAC2: expected osciloscope wave (AC coupled)
% DAC2_Voltage = DAC2*PWM_Scale;
% DAC2_rms = rms(DAC2_Voltage-mean(DAC2_Voltage));
% figure(2);
% stairs(time_vector,DAC2_Voltage-mean(DAC2_Voltage));
% title('DAC2: Differential current');
% legend(strcat('DAC2: ', num2str(DAC2_rms), 'Vrms'));
% xlabel('time (s)');
% ylabel('amplitue (v)');
% grid
% 
% %% DAC3: expected osciloscope wave (AC coupled)
% DAC3_Voltage = DAC3*PWM_Scale;
% DAC3_rms = rms(DAC3_Voltage-mean(DAC3_Voltage));
% figure(3);
% stairs(time_vector,DAC3_Voltage-mean(DAC3_Voltage));
% title('DAC3: Phase voltage');
% legend(strcat('DAC3: ', num2str(DAC3_rms), 'Vrms'));
% xlabel('time (s)');
% ylabel('amplitue (v)');
% grid
% 
% %% DAC4: expected osciloscope wave (AC coupled)
% DAC4_Voltage = DAC4*PWM_Scale;
% DAC4_rms = rms(DAC4_Voltage-mean(DAC4_Voltage));
% figure(4);
% stairs(time_vector,DAC4_Voltage-mean(DAC4_Voltage));
% title('DAC4: Sine wave with gaussian noise');
% legend(strcat('DAC4: ', num2str(DAC4_rms), 'Vrms'));
% xlabel('time (s)');
% ylabel('amplitue (v)');
% grid
