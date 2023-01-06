int div_b(BN a, BN b, BN q, BN rem)
{
	memset(rem, 0, sizeof(rem));
	memset(q, 0, sizeof(q));
	BND b_t;//��ʱ���b
	BND tempq = { 0 };
	BND tempsub = { 0 };//����̺���ʱ��
	BND q_t = { 0 };//ÿ����
	BND r_t;

	cpy_b(r_t, a);
	cpy_b(b_t, b);
	if (DIGITS_B(b) == 0)//���b��0,��0����
		return FLAG_DIVZERO;
	else if (DIGITS_B(r_t) == 0)//���a=0
	{
		SETZERO_B(q);
		SETZERO_B(rem);
		return FLAG_OK;
	}
	else if (cmp_b(r_t, b_t) == -1)//���a<b,����a�ͺ���
	{
		cpy_b(rem, r_t);
		SETZERO_B(q);//��Ϊ0
		return FLAG_OK;
	}
	else if (cmp_b(r_t, b_t) == 0)//���a=b,����1�ͺ���
	{
		q[0] = 1; q[1] = 1;//��Ϊ1
		SETZERO_B(rem);//����Ϊ0
		return FLAG_OK;
	}
	else if (DIGITS_B(r_t) == 0)//���a=0���ǳ���
	{
		SETZERO_B(q);
		SETZERO_B(rem);
		return FLAG_OK;
	}
	//���������
	SETDIGITS_B(q_t, DIGITS_B(r_t) - DIGITS_B(b_t) + 1);
	int abit = getbits_b(r_t);
	int bbit = getbits_b(b);

	int shiftnum = abit - bbit;
	int subtimes = abit - bbit + 1;

	for (int i = 0; i < shiftnum; i++)
		shl_b(b_t);

	for (int i = 0; i < subtimes; i++) {

		if (cmp_b(r_t, b_t) >= 0)//�����еȺţ���������
		{
			sub(r_t, b_t, tempsub);
			cpy_b(r_t, tempsub);
			shl_b(q_t);
			adduint_b(q_t, 1U, tempq);//��1
			cpy_b(q_t, tempq);
			shr_b(b_t);
		}
		else
		{
			shl_b(q_t);//��0
			shr_b(b_t);
		}
	}
	cpy_b(q, q_t);
	RMLDZRS_B(q);
	cpy_b(rem, r_t);
	RMLDZRS_B(rem);
	return FLAG_OK;
}
