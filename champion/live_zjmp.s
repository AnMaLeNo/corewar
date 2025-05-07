.name           "live_zjmp"
.comment        "Just a basic test Program"

fork %100
live %42
#st r1, 16
#st r1, 27
#st r1, 16
#st r1, 6
#start:	live %42
#	zjmp %:start
