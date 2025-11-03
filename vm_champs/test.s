.name "Antoine"
.comment "Description"

# test ld et st
#ld -1, r1
#st r1, -7

# test register
#ld %42, r1
#ld %-42, r1
#ld %1, r1
#ld %-1, r1
#ld %-10, r1

# test add
#ld %-2147483648, r2
#ld %2147483647, r3
# add r2, r3, r1 # -1

ld %2147483647, r2
ld %1, r3
add r2, r3, r1 # -2147483648

ld %-2147483647, r2
ld %2, r3
sub r2, r3, r1 # -2147483648

st r1, 10