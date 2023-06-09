[top]
components : mp@MissionPlanning
components : hangar@Hangar
components : rast@Rast
out : TO
out : HA
in : LC
Link : LC inLandingClearance@rast
Link : outTakeOff@rast inTakeOff@hangar
Link : outCompletedLanding@rast inCompletedLanding@hangar
Link : outCompletedLanding@rast inCompletedLanding@mp
Link : outNewMission@mp inNewMission@rast
Link : outTakeOff@rast TO
Link : outHangarAvailability@hangar HA

[rast]
durationOfLanding : 00:10:00:00
durationOfTakeOff : 00:05:00:00

[hangar]
durationOfPreparation : 00:00:30:00

[mp]
distribution : chi
degreesfreedom : 5
shapeFactor : 7
minimumDuration : 30

