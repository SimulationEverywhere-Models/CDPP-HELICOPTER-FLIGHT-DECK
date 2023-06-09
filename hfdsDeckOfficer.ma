[top]
components : deckOfficer@DeckOfficer
out : DA
in : DC
in : HA
Link : DC inDeckAvailabilityCheck@deckOfficer
Link : HA inHangarAvailability@deckOfficer
Link : outDeckAvailability@deckOfficer DA

[deckOfficer]
durationOfPreparation : 00:00:10:00
