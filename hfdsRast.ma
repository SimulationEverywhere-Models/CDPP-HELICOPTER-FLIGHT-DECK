[top]
components : rast@Rast
out : CL
out : TO
in : LC
in : NM
Link : LC inLandingClearance@rast
Link : NM inNewMission@rast
Link : outCompletedLanding@rast CL
Link : outTakeOff@rast TO

[rast]
durationOfLanding : 00:10:00:00
durationOfTakeOff : 00:05:00:00
