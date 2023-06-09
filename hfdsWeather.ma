[top]
components : weather@Weather
out : WA
in : WC
Link : WC inWeatherCheck@weather
Link : outWeatherAcceptability@weather WA

[weather]
distribution : normal
mean : 0
deviation : 1
acceptability : 0.84
durationOfPreparation : 00:05:00:00
