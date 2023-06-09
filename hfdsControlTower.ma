[top]
components : ct@ControlTower
out : WC
out : LC
out : TC
in : LR
in : WA
in : TO
Link : LR inLandingRequest@ct
Link : WA inWeatherAcceptability@ct
Link : TO inTakeOff@ct
Link : outWeatherCheck@ct WC
Link : outLandingClearance@ct LC
Link : outTakeOffClearance@ct TC

[ct]
distribution : normal
mean : 120000
deviation : 30000
durationOfApproach : 00:00:30:00
durationOfHover : 00:00:15:00
durationOfLanding : 00:00:15:00

