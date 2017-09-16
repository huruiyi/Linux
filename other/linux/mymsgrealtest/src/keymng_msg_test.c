
#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "keymng_msg.h"

int mywritefile(unsigned char *buf, int len)
{
	FILE *fp = NULL;
	fp = fopen("c:/teacher.ber", "wb+");
	if (fp == NULL)
	{
		printf("fopen file error \n");
		return -1;
	}
	fwrite(buf, 1, len, fp);
	fclose(fp);
	return 0;
}


int TeacherEnDecode()
{
	int				ret = 0;
	Teacher			t1;

	unsigned char	*myout = NULL;
	int				myoutlen = 0;

	Teacher			*pTeacher = NULL;
	int				iType = 0;

	strcpy(t1.name, "myname");
	t1.age = 31;
	t1.p = malloc(100);
	strcpy(t1.p, "mypppppp");
	t1.plen = strlen(t1.p);

	//编码
	ret = MsgEncode(&t1, ID_MsgKey_Teacher, (unsigned char	**)&myout, &myoutlen); //free1
	if (ret != 0)
	{
		printf("func MsgEncode() err:%d \n", ret);
		return ret;
	}
 
	//解码
	ret = MsgDecode(myout, myoutlen, (void **)&pTeacher, &iType); //free2
	if (ret != 0)
	{
		printf("func MsgDecode() err:%d \n", ret);
		return ret;
	}

	if ((t1.age == pTeacher->age) &&
		strcmp(t1.p, pTeacher->p) == 0)
	{
		printf("Teacher编码和解码的结果 一致\n");
	}
	else
	{
		printf("Teacher编码和解码的结果 不一致\n");
	}

	//释放 编码以后的内存块
	MsgMemFree((void **)&myout, 0); //这样是OK
	//free(myout);  //这样是不行的
	MsgMemFree((void **)&pTeacher, iType);
	return 0;
}
int MsgKey_ReqEnDecode()
{
	//编码
	int							ret = 0;
	MsgKey_Req			req;
	unsigned char		*myout = NULL;
	int							myoutlen = 0;
	/*
	char			clientId[12];	//客户端编号
	char			AuthCode[16];	//认证码
	char			serverId[12];	//服务器端I编号
	char			r1[64];		//客户端随机数*/
	req.cmdType = 3;
	strcpy(req.clientId, "ClientIdVal");
	strcpy(req.AuthCode, "AuthCodeVal");
	strcpy(req.serverId, "ServerIdVal");
	strcpy(req.r1, "R1Value");
	ret = MsgEncode(&req, ID_MsgKey_Req, (unsigned char	**)&myout, &myoutlen); //free1
	if (ret != 0)
	{
		printf("func MsgEncode() err:%d \n", ret);
		return ret;
	}
 

	//解码
	MsgKey_Req *		pReq = NULL;
	int							iType = 0;
	ret = MsgDecode(myout, myoutlen, (void **)&pReq, &iType); //free2
	if (ret != 0)
	{
		printf("func MsgDecode() err:%d \n", ret);
		return ret;
	}

	if ((req.cmdType == pReq->cmdType) &&
		strcmp(req.serverId, pReq->serverId) == 0 &&
		strcmp(req.AuthCode, pReq->AuthCode) == 0 &&
		strcmp(req.clientId, pReq->clientId) == 0 &&
		strcmp(req.r1, pReq->r1) == 0)
	{
		printf("MsgKey_Req编码和解码的结果 一致\n");
	}
	else
	{
		printf("MsgKey_Req编码和解码的结果 不一致\n");
	}

	//释放 编码以后的内存块
	MsgMemFree((void **)&myout, 0);
	MsgMemFree((void **)&pReq, iType);
	return ret;
}

int main()
{
	TeacherEnDecode();
	MsgKey_ReqEnDecode(); 
 
	return 0;
}
