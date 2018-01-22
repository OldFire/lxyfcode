int jogAction(int axi,double speed)
{
	long mask,pclock,sts;
	short count;
	int flag1,flag2;

	GT_SetVel(axi, speed);
	mask=axi-1;
	mask=1<<mask;
	GT_Update(mask);

	GT_GetSts(axi, &sts,count,&pclock);
	flag1=sts&0x20;
	flag2=sts&0x40;
	return 0;
}




