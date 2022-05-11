# AHC-predictive-control
Active heave compensation predictive control algorithm

An active heave compensation approach
for offshore cranes to decouple the lift operation of an
offshore crane from the vertical motion of the vessel that the
crane is attached to. 
The active heave compensation system consists basically of
a controller and a prediction algorithm for the vertical motion
to overcome the system delays. The prediction algorithm itself
can be divided into an identification as well as an estimation
and prediction part. During the identification part, the measured
wave-induced motion is analyzed in the frequency domain via
an FFT. Single modes are extracted from the frequency-domain
signal using a peak-detection algorithm and summed up to a
motion sequence consisting of regular waves with different amplitudes,
frequencies, and phases. After the system’s identification,
an estimation of the vertical motion has to be performed
because the results of the identification are only mean values
over a certain time interval. The actual vertical motion is estimated
by a Kalman filter that is initialized with the identified
model obtained in the first step of the prediction algorithm. The
Kalman filter estimates the amplitude and phase of each mode
online. This information is used to predict the vertical motion
over a finite-time horizon.
