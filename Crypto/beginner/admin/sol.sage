from Crypto.Util.number import *
N = 138414653154398285173062025018564621548905641465498560868979028666553259473039379949430302118910864526886589739230545892620646783941978427867080800492069898362254552704457387255994570560846878107414642490239860616029798276112596145920141221129490742073210234440495082662580528004498419704055900034211554647579
hint = 2556067664046978652489453914564324537889824168345188260910089493313670678284018135099531833927707172379279335435002893864667471843327977584106492411924939954034804432369248416614941788969061223856099193586693738724062948950928470887960277573615330326685458726919292331237617690105640763007884852196548096426
M = matrix(ZZ, [[N, 0], [hint, 1]]).LLL()
print(long_to_bytes(M[0][0])) 