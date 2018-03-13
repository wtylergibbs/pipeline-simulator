	.text
	ori	$s0,$0,24
	lw	$t1,0($s0)
	lw	$t2,4($s0)
	add	$t3,$t1,$t2
	sw	$t3,8($s0)
	halt
	.data
Data1:	.word	15
Data2:	.word	25