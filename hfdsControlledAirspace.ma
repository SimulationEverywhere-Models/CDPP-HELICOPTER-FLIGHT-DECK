[top]
components : deckOfficer@DeckOfficer
components : ct@ControlTower
components : ch148@Helicopter
out : OH
out : LC
out : WC
in : IH
in : HA
in : TO
in : WA
Link : IH inHelicopter@ch148
Link : HA inHangarAvailability@deckOfficer
Link : TO inTakeOff@ct
Link : WA inWeatherAcceptability@ct
Link : outDeckAvailabilityCheck@ch148 inDeckAvailabilityCheck@DeckOfficer
Link : outLandingRequest@ch148 inLandingRequest@ct
Link : outTakeOffClearance@ct inTakeOffClearance@ch148
Link : outLandingClearance@ct inLandingClearance@ch148
Link : outDeckAvailability@deckOfficer inDeckAvailability@ch148
Link : outHelicopter@ch148 OH
Link : outLandingClearance@ct LC
Link : outWeatherCheck@ct WC

[ch148]
durationOfApproach : 00:00:00:00
durationOfFinalApproach : 00:02:00:00
durationOfHover : 00:00:30:00
durationOfTakeOff : 00:01:00:00

[deckOfficer]
durationOfPreparation : 00:00:10:00

[ct]
distribution : normal
mean : 120000
deviation : 30000
durationOfApproach : 00:00:30:00
durationOfHover : 00:00:15:00
durationOfLanding : 00:00:15:00
