.name           "live_zjmp"
.comment        "Just a basic test Program"

#zjmp %:start
#start: st r1, 13
#st r1, 24
#st r1, 38
#ld 50, r2

#st r1, r2
#st r2, 6
#start:  live %42
#        zjmp %:start



#        ld %42, r7
#        st r7, 50
#        ld %0, r2
#        st r1, r3
#        st r3, 6
#start:  live %42
#        zjmp %:start


#ld %5, r1
#ld %-5, r2
# add r1, r2, r3
#start:  live %42
#        zjmp %:start

live %0
live %1
live %2