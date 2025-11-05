.name "Antoine"
.comment "Description"

# 04 09 ... faux ACB test
add r2, r3, r4
zjmp %65535
xor %16909060, %928675163, r1

st r1, 13