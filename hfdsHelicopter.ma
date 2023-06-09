[top]
components : ch148@Helicopter
out : LR
out : DC
out : OH
in : IH
in : DA
in : LC
in : TC
Link : IH inHelicopter@ch148
Link : DA inDeckAvailability@ch148
Link : LC inLandingClearance@ch148
Link : TC inTakeOffClearance@ch148
Link : outLandingRequest@ch148 LR
Link : outDeckAvailabilityCheck@ch148 DC
Link : outHelicopter@ch148 OH

[ch148]
durationOfApproach : 00:00:00:00
durationOfFinalApproach : 00:02:00:00
durationOfHover : 00:00:30:00
durationOfTakeOff : 00:01:00:00

