[top]
components : missionPlanning@MissionPlanning
out : NM
in : CL
Link : CL inCompletedLanding@missionPlanning
Link : outNewMission@missionPlanning NM

[missionPlanning]
distribution : chi
degreesfreedom : 5
shapeFactor : 7
minimumDuration : 30
