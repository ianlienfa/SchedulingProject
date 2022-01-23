\ LP format - for model browsing. Use MPS format to capture full model detail.
Minimize
  C + C + C + C + C + C + 0 Y + 0 Y + 0 Y + 0 Y + 0 Y + 0 Y + 0 Y + 0 Y
   + 0 Y + 0 Y + 0 Y
Subject To
 c1a: W + W + W + W + W + W = 6
 onceExpr1: W = 1
 onceExpr2: W = 1
 onceExpr3: W = 1
 onceExpr4: W = 1
 onceExpr5: W = 1
 onceExpr6: W = 1
 t1_r2_dep: - 10 W + W >= -9
 t1_r2_r_than_j: Y = 1
 t1_r3_dep: - 10 W + W >= -9
 t1_r3_r_than_j: Y = 1
 t2_r1_dep: - 10 W + W >= -9
 t2_r1_r_than_j: Y = 1
 t2_r2_dep: - 10 W + W >= -9
 t2_r2_r_than_j: Y = 1
 t3_r4_dep: - 10 W + W >= -9
 t3_r4_r_than_j: Y = 1
 t4_r1_dep: - 10 W + W >= -9
 t4_r1_r_than_j: Y = 1
 t4_r3_dep: - 10 W + W >= -9
 t4_r3_r_than_j: Y = 1
 t5_r2_dep: - 10 W + W >= -9
 t5_r2_r_than_j: Y = 1
 t5_r4_dep: - 10 W + W >= -9
 t5_r4_r_than_j: Y = 1
 job1_job2_order_clarity: Y + Y = 1
 job1_job3_order_clarity: Y + Y = 1
 job1_job4_order_clarity: Y + Y = 1
 job1_job5_order_clarity: Y + Y = 1
 job1_job6_order_clarity: Y + Y = 1
 job1_job7_order_clarity: Y + Y = 1
 job1_job8_order_clarity: Y + Y = 1
 job1_job9_order_clarity: Y + Y = 1
 job1_job10_order_clarity: Y + Y = 1
 job1_job11_order_clarity: Y + Y = 1
 job2_job3_order_clarity: Y + Y = 1
 job2_job4_order_clarity: Y + Y = 1
 job2_job5_order_clarity: Y + Y = 1
 job2_job6_order_clarity: Y + Y = 1
 job2_job7_order_clarity: Y + Y = 1
 job2_job8_order_clarity: Y + Y = 1
 job2_job9_order_clarity: Y + Y = 1
 job2_job10_order_clarity: Y + Y = 1
 job2_job11_order_clarity: Y + Y = 1
 job3_job4_order_clarity: Y + Y = 1
 job3_job5_order_clarity: Y + Y = 1
 job3_job6_order_clarity: Y + Y = 1
 job3_job7_order_clarity: Y + Y = 1
 job3_job8_order_clarity: Y + Y = 1
 job3_job9_order_clarity: Y + Y = 1
 job3_job10_order_clarity: Y + Y = 1
 job3_job11_order_clarity: Y + Y = 1
 job4_job5_order_clarity: Y + Y = 1
 job4_job6_order_clarity: Y + Y = 1
 job4_job7_order_clarity: Y + Y = 1
 job4_job8_order_clarity: Y + Y = 1
 job4_job9_order_clarity: Y + Y = 1
 job4_job10_order_clarity: Y + Y = 1
 job4_job11_order_clarity: Y + Y = 1
 job5_job6_order_clarity: Y + Y = 1
 job5_job7_order_clarity: Y + Y = 1
 job5_job8_order_clarity: Y + Y = 1
 job5_job9_order_clarity: Y + Y = 1
 job5_job10_order_clarity: Y + Y = 1
 job5_job11_order_clarity: Y + Y = 1
 job6_job7_order_clarity: Y + Y = 1
 job6_job8_order_clarity: Y + Y = 1
 job6_job9_order_clarity: Y + Y = 1
 job6_job10_order_clarity: Y + Y = 1
 job6_job11_order_clarity: Y + Y = 1
 job7_job8_order_clarity: Y + Y = 1
 job7_job9_order_clarity: Y + Y = 1
 job7_job10_order_clarity: Y + Y = 1
 job7_job11_order_clarity: Y + Y = 1
 job8_job9_order_clarity: Y + Y = 1
 job8_job10_order_clarity: Y + Y = 1
 job8_job11_order_clarity: Y + Y = 1
 job9_job10_order_clarity: Y + Y = 1
 job9_job11_order_clarity: Y + Y = 1
 job10_job11_order_clarity: Y + Y = 1
 job1_on_m1_startTime: S >= 0
 job2_on_m1_startTime: S >= 0
 job3_on_m1_startTime: S >= 0
 job4_on_m1_startTime: S >= 0
 job5_on_m1_startTime: S >= 0
 job6_on_m1_startTime: S >= 0
 job7_on_m1_startTime: S >= 0
 job8_on_m1_startTime: S >= 0
 job9_on_m1_startTime: S >= 0
 job10_on_m1_startTime: S >= 0
 job11_on_m1_startTime: S >= 0
 job1_finishes_bf_job2_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R92: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job1_finishes_bf_job3_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R94: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job1_finishes_bf_job4_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R96: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job1_finishes_bf_job5_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R98: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job1_finishes_bf_job6_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R100: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job1_finishes_bf_job7_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R102: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job1_finishes_bf_job8_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R104: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job1_finishes_bf_job9_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R106: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job1_finishes_bf_job10_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R108: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job1_finishes_bf_job11_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R110: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job2_finishes_bf_job3_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R112: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job2_finishes_bf_job4_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R114: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job2_finishes_bf_job5_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R116: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job2_finishes_bf_job6_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R118: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job2_finishes_bf_job7_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R120: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job2_finishes_bf_job8_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R122: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job2_finishes_bf_job9_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R124: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job2_finishes_bf_job10_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R126: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job2_finishes_bf_job11_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R128: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job3_finishes_bf_job4_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R130: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job3_finishes_bf_job5_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R132: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job3_finishes_bf_job6_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R134: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job3_finishes_bf_job7_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R136: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job3_finishes_bf_job8_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R138: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job3_finishes_bf_job9_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R140: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job3_finishes_bf_job10_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R142: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job3_finishes_bf_job11_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R144: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job4_finishes_bf_job5_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R146: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job4_finishes_bf_job6_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R148: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job4_finishes_bf_job7_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R150: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job4_finishes_bf_job8_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R152: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job4_finishes_bf_job9_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R154: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job4_finishes_bf_job10_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R156: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job4_finishes_bf_job11_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R158: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job5_finishes_bf_job6_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R160: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job5_finishes_bf_job7_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R162: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job5_finishes_bf_job8_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R164: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job5_finishes_bf_job9_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R166: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job5_finishes_bf_job10_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R168: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job5_finishes_bf_job11_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R170: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job6_finishes_bf_job7_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R172: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job6_finishes_bf_job8_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R174: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job6_finishes_bf_job9_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R176: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job6_finishes_bf_job10_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R178: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job6_finishes_bf_job11_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R180: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job7_finishes_bf_job8_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R182: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job7_finishes_bf_job9_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R184: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job7_finishes_bf_job10_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R186: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job7_finishes_bf_job11_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R188: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job8_finishes_bf_job9_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R190: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job8_finishes_bf_job10_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R192: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job8_finishes_bf_job11_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R194: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job9_finishes_bf_job10_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R196: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job9_finishes_bf_job11_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R198: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job10_finishes_bf_job11_on_1: S - C - 100000 W - 100000 W - 100000 Y
   >= -300000
 R200: S - C - 100000 W - 100000 W + 100000 Y >= -200000
 job1_on_m1_CompletionTime: C - 5 W + [ - S * W ] = 0
 job2_on_m1_CompletionTime: C - 3 W + [ - S * W ] = 0
 job3_on_m1_CompletionTime: C - 6 W + [ - S * W ] = 0
 job4_on_m1_CompletionTime: C - 2 W + [ - S * W ] = 0
 job5_on_m1_CompletionTime: C - 7 W + [ - S * W ] = 0
 job6_on_m1_CompletionTime: C + [ - S * W ] = 0
 job7_on_m1_CompletionTime: C - 2 W + [ - S * W ] = 0
 job8_on_m1_CompletionTime: C - 4 W + [ - S * W ] = 0
 job9_on_m1_CompletionTime: C - 3 W + [ - S * W ] = 0
 job10_on_m1_CompletionTime: C - 2 W + [ - S * W ] = 0
 job11_on_m1_CompletionTime: C + [ - S * W ] = 0
Bounds
Binaries
 W W W W W W W W W W W Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y
 Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y
 Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y
 Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y Y
Generals
 S S S S S S S S S S S C C C C C C C C C C C
End
