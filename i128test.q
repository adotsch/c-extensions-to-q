\l i128.q
.t.e:{$[value x;;"failed: ",x]}
l:1+2*1000?0Wj
t)(+/)[l]=i128.low (i128.add/) i128.cast l
t)(-/)[l]=i128.low (i128.sub/) i128.cast l
t)(*/)[l]=i128.low (i128.mul/) i128.cast l
t)"170141183460469231731687303715884105727" ~ i128.str "G"$"ffffffff-ffff-ffff-ffff-ffffffffff7f"
t)("G"$"ffffffff-3f22-8a09-7ac4-865aa84c3b4b") ~ i128.parse 38#"9"
t)("G"$"01000000-c0dd-75f6-853b-79a557b3c4b4") ~ i128.parse "-",38#"9"
//more to come
\\