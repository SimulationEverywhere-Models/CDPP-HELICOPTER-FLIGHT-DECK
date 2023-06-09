[top]
components : weather@Weather
components : ShipDeck
components : ControlledAirspace
out : outHelicopter
out : outLandingGranted
in : inHelicopter
Link : inHelicopter IH@ControlledAirspace
Link : WC@ControlledAirspace inWeatherCheck@weather
Link : outWeatherAcceptability@weather WA@ControlledAirspace
Link : HA@ShipDeck HA@ControlledAirspace
Link : TO@ShipDeck TO@ControlledAirspace
Link : LC@ControlledAirspace LC@ShipDeck
Link : OH@ControlledAirspace outHelicopter
Link : LC@ControlledAirspace outLandingGranted

[weather]
distribution : normal
mean : 0
deviation : 1
acceptability : 0.84
durationOfPreparation : 00:05:00:00

[ControlledAirspace]
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

[ShipDeck]
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
