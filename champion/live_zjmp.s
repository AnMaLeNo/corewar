.name           "live_zjmp"
.comment        "Just a basic test Program"


start:	live %1
	st r1,-4
	zjmp %:start
