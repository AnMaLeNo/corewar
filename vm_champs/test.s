.name "Antoine"
.comment "Description"

# test ld et st
#ld %42, r17
#st r17, 10

# test register
#ld -42, r1
ld %10, r1
ld %-1, r2
ld %42, r3
ld %-42, r4