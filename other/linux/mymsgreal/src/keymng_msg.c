
#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "itcast_asn1_der.h"
#include "itcastderlog.h"
#include "keymng_msg.h"

// 教 学   
/*

typedef struct _Teacher
{
char name[64];
int age;
char *p;
int plen;
}Teacher;

typedef struct _AdvTeacher
{
int tag;
Teacher *p;
}AdvTeacher;
*/

//////////////////////////////////////////////////////////////////////////
// 老师结构体 编码
// 
int TeacherEncode_(Teacher *pT/*in*/, ITCAST_ANYBUF **_outNode) ////unsigned char **out /*out*/, int *outlen)	
{
	int			ret = 0;
	ITCAST_ANYBUF		*pTmp = NULL, *pHeadBuf = NULL;
	ITCAST_ANYBUF		*pTmpBuf = NULL;
	ITCAST_ANYBUF		*pOutData = NULL;
	unsigned char		*tmpout = NULL;
	int					tmpoutlen = 0;

	//把C风格的字符串name 转化成  ITCAST_ANYBUF
	pTmp = malloc(sizeof(ITCAST_ANYBUF));
	if (pTmp == NULL)
	{
		ret = 100;
		printf("func malloc() err:%d \n", ret);
		return ret;
	}
	memset(pTmp, 0, sizeof(ITCAST_ANYBUF));

	pTmp->pData = malloc(strlen(pT->name) + 1);
	if (pTmp->pData == NULL)
	{
		DER_ITCAST_FreeQueue(pTmp); //
		ret = 100;
		printf("func malloc() err:%d \n", ret);
		return ret;
	}
	memcpy(pTmp->pData, pT->name, strlen(pT->name));
	pTmp->dataLen = strlen(pT->name);

	//编码name TLV
	ret = DER_ItAsn1_WritePrintableString(pTmp, &pHeadBuf);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pTmp); //
		printf("func DER_ItAsn1_WritePrintableString() err:%d \n", ret);
		return ret;
	}
	DER_ITCAST_FreeQueue(pTmp);
	pTmp = pHeadBuf; //两个辅助指针变量 同时 指向链表的头部

	//编码 age
	/*
	ret = DER_ItAsn1_WriteInteger(pT->age, &pTmpBuf );
	pTmp->next = pTmpBuf;
	*/
	//直接给pTmp结点的next域 赋值
	ret = DER_ItAsn1_WriteInteger(pT->age, &(pTmp->next));
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadBuf);
		printf("func DER_ItAsn1_WriteInteger() err:%d \n", ret);
		return ret;
	}
	pTmp = pTmp->next;

	//编码 p
	ret = EncodeChar(pT->p, pT->plen, &(pTmp->next));
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadBuf);
		printf("func DER_ItAsn1_WriteInteger() err:%d \n", ret);
		return ret;
	}
	pTmp = pTmp->next;

	//编码 plen
	ret = DER_ItAsn1_WriteInteger(pT->plen, &(pTmp->next));
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadBuf);
		printf("func DER_ItAsn1_WriteInteger() err:%d \n", ret);
		return ret;
	}

	//编码老师大结构
	ret = DER_ItAsn1_WriteSequence(pHeadBuf, &pOutData);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadBuf);
		printf("func DER_ItAsn1_WriteSequence() err:%d \n", ret);
		return ret;
	}

	DER_ITCAST_FreeQueue(pHeadBuf); //释放链表
 
	*_outNode = pOutData;

	return ret;
}

//老师结构体 解码
int TeacherDecode(unsigned char *in, int inLen, Teacher **pStruct)
{
	int					ret = 0;
	ITCAST_ANYBUF		*pTmp = NULL, *pHead = NULL;
	ITCAST_ANYBUF		*pTmpDABuf = NULL;
	ITCAST_ANYBUF		*pOutData = NULL;
	ITCAST_ANYBUF		*inAnyBuf = NULL;
	int					tmpNum = 0;
	Teacher				*pTmpStru = NULL;

	//把C的buf转化成 ITCAST_ANYBUF
	inAnyBuf = (ITCAST_ANYBUF *)malloc(sizeof(ITCAST_ANYBUF));
	if (inAnyBuf == NULL)
	{
		ret = 102;
		printf("func malloc() err:%d \n", ret);
		return ret;
	}
	memset(inAnyBuf, 0, sizeof(ITCAST_ANYBUF));
	//inAnyBuf->next;
	//inAnyBuf->prev;
	inAnyBuf->pData = (unsigned char *)malloc(inLen);
	if (inAnyBuf->pData == NULL)
	{
		ret = 103;
		printf("func malloc() err:%d \n", ret);
		return ret;
	}
	inAnyBuf->dataLen = inLen; //这句话很重要
	memcpy(inAnyBuf->pData, in, inLen);

	ret = DER_ItAsn1_ReadSequence(inAnyBuf, &pHead);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(inAnyBuf);
		printf("func DER_ItAsn1_ReadSequence() err:%d \n", ret);
		return ret;
	}
	DER_ITCAST_FreeQueue(inAnyBuf);
	pTmp = pHead;  //连个辅助指针变量 同时 指向链表的头部


	//把老师结构体 给malloc出来
	pTmpStru = (Teacher *)malloc(sizeof(Teacher));
	if (pTmpStru == NULL)
	{
		DER_ITCAST_FreeQueue(pHead);
		ret = 103;
		printf("func malloc() err:%d \n", ret);
		return ret;
	}
	memset(pTmpStru, 0, sizeof(Teacher));


	//解码 name
	ret = DER_ItAsn1_ReadPrintableString(pTmp, &pTmpDABuf);
	if (ret != 0)
	{
		free(pTmpStru);
		DER_ITCAST_FreeQueue(pHead);
		printf("func DER_ItAsn1_ReadPrintableString() err:%d \n", ret);
		return ret;
	}
	memcpy(pTmpStru->name, pTmpDABuf->pData, pTmpDABuf->dataLen);
	DER_ITCAST_FreeQueue(pTmpDABuf); //释放临时数据结点
	pTmp = pTmp->next; //结点下移

	//解码 age
	ret = DER_ItAsn1_ReadInteger(pTmp, (unsigned long  *)&(pTmpStru->age));
	if (ret != 0)
	{
		free(pTmpStru);
		DER_ITCAST_FreeQueue(pHead);
		printf("func DER_ItAsn1_ReadInteger() err:%d \n", ret);
		return ret;
	}
	pTmp = pTmp->next; //结点下移

	//解码 p
	ret = DER_ItAsn1_ReadPrintableString(pTmp, &pTmpDABuf);
	if (ret != 0)
	{
		free(pTmpStru);
		DER_ITCAST_FreeQueue(pHead);
		printf("func DER_ItAsn1_ReadPrintableString() err:%d \n", ret);
		return ret;
	}
	pTmpStru->p = (char *)malloc(pTmpDABuf->dataLen + 1);
	if (pTmpStru->p == NULL)
	{
		free(pTmpStru);
		DER_ITCAST_FreeQueue(pHead);
		ret = 104;
		printf("func malloc() err:%d \n", ret);
		return ret;
	}
	memset(pTmpStru->p, 0, pTmpDABuf->dataLen + 1);
	memcpy(pTmpStru->p, pTmpDABuf->pData, pTmpDABuf->dataLen);
	DER_ITCAST_FreeQueue(pTmpDABuf); //释放临时数据结点
	pTmp = pTmp->next; //结点下移

	//解码 plen
	ret = DER_ItAsn1_ReadInteger(pTmp, (unsigned long *)&(pTmpStru->plen));
	if (ret != 0)
	{
		free(pTmpStru->p);
		free(pTmpStru);
		DER_ITCAST_FreeQueue(pHead);
		printf("func DER_ItAsn1_ReadInteger() err:%d \n", ret);
		return ret;
	}

	DER_ITCAST_FreeQueue(pHead);
	//间接赋值 
	*pStruct = pTmpStru;
	return ret;

}

int MsgKey_ReqEncode(MsgKey_Req *pT, ITCAST_ANYBUF **_outNode)
{
	/*
	typedef struct _MsgKey_Req
	{
	//1 密钥更新  	//2 密钥校验; 	//3 密钥注销
	int				cmdType;		//报文命令码
	char			clientId[12];	//客户端编号
	char			AuthCode[16];	//认证码
	char			serverId[12];	//服务器端I编号
	char			r1[64];		//客户端随机数
	}MsgKey_Req;
	*/
	int			ret = 0;
	ITCAST_ANYBUF		*pTmp = NULL, *pHeadBuf = NULL;
	ITCAST_ANYBUF		*pTmpBuf = NULL;
	ITCAST_ANYBUF		*pOutData = NULL;
	unsigned char			*tmpout = NULL;
	int								tmpoutlen = 0;

	pTmp = malloc(sizeof(ITCAST_ANYBUF));
	if (pTmp == NULL)
	{
		ret = 100;
		printf("func malloc() err:%d \n", ret);
		return ret;
	}
	memset(pTmp, 0, sizeof(ITCAST_ANYBUF));

	//编码 cmdType
	ret = DER_ItAsn1_WriteInteger(pT->cmdType, &pHeadBuf);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadBuf);
		printf("func DER_ItAsn1_WriteInteger() err:%d \n", ret);
		return ret;
	}
	DER_ITCAST_FreeQueue(pTmp);
	pTmp = pHeadBuf;

	//编码 clientId
	ret = EncodeChar(pT->clientId, strlen(pT->clientId), &(pTmp->next));
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadBuf);
		printf("func DER_ItAsn1_WriteInteger() err:%d \n", ret);
		return ret;
	}
	pTmp = pTmp->next;

	//编码 AuthCode
	ret = EncodeChar(pT->AuthCode, strlen(pT->AuthCode), &(pTmp->next));
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadBuf);
		printf("func DER_ItAsn1_WriteInteger() err:%d \n", ret);
		return ret;
	}
	pTmp = pTmp->next;

	//编码 serverId
	ret = EncodeChar(pT->serverId, strlen(pT->serverId), &(pTmp->next));
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadBuf);
		printf("func DER_ItAsn1_WriteInteger() err:%d \n", ret);
		return ret;
	}
	pTmp = pTmp->next;

	//编码 r1
	ret = EncodeChar(pT->r1, strlen(pT->r1), &(pTmp->next));
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadBuf);
		printf("func DER_ItAsn1_WriteInteger() err:%d \n", ret);
		return ret;
	}

	//编码老师大结构
	ret = DER_ItAsn1_WriteSequence(pHeadBuf, &pOutData);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadBuf);
		printf("func DER_ItAsn1_WriteSequence() err:%d \n", ret);
		return ret;
	}

	DER_ITCAST_FreeQueue(pHeadBuf); //释放链表

	*_outNode = pOutData;

	return ret;
}

int MsgKey_ReqDecode(unsigned char *in, int inLen, MsgKey_Req **pStruct)
{
	int					ret = 0;
	ITCAST_ANYBUF		*pTmp = NULL, *pHead = NULL;
	ITCAST_ANYBUF		*pTmpDABuf = NULL;
	ITCAST_ANYBUF		*pOutData = NULL;
	ITCAST_ANYBUF		*inAnyBuf = NULL;
	int					tmpNum = 0;
	MsgKey_Req				*pTmpStru = NULL;

	//把C的buf转化成 ITCAST_ANYBUF
	inAnyBuf = (ITCAST_ANYBUF *)malloc(sizeof(ITCAST_ANYBUF));
	if (inAnyBuf == NULL)
	{
		ret = 102;
		printf("func malloc() err:%d \n", ret);
		return ret;
	}
	memset(inAnyBuf, 0, sizeof(ITCAST_ANYBUF));
	inAnyBuf->pData = (unsigned char *)malloc(inLen);
	if (inAnyBuf->pData == NULL)
	{
		ret = 103;
		printf("func malloc() err:%d \n", ret);
		return ret;
	}
	inAnyBuf->dataLen = inLen;
	memcpy(inAnyBuf->pData, in, inLen);

	ret = DER_ItAsn1_ReadSequence(inAnyBuf, &pHead);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(inAnyBuf);
		printf("func DER_ItAsn1_ReadSequence() err:%d \n", ret);
		return ret;
	}
	DER_ITCAST_FreeQueue(inAnyBuf);
	pTmp = pHead;

	pTmpStru = (MsgKey_Req *)malloc(sizeof(MsgKey_Req));
	if (pTmpStru == NULL)
	{
		DER_ITCAST_FreeQueue(pHead);
		ret = 103;
		printf("func malloc() err:%d \n", ret);
		return ret;
	}
	memset(pTmpStru, 0, sizeof(MsgKey_Req));

	//解码 cmdType
	ret = DER_ItAsn1_ReadInteger(pTmp, (unsigned long *)&(pTmpStru->cmdType));

	if (ret != 0)
	{
		free(pTmpStru);
		DER_ITCAST_FreeQueue(pHead);
		printf("func DER_ItAsn1_ReadInteger() err:%d \n", ret);
		return ret;
	}
	DER_ITCAST_FreeQueue(pTmpDABuf);
	pTmp = pTmp->next;

	//解码 clientId
	ret = DER_ItAsn1_ReadPrintableString(pTmp, &pTmpDABuf);
	if (ret != 0)
	{
		free(pTmpStru);
		DER_ITCAST_FreeQueue(pHead);
		printf("func DER_ItAsn1_ReadPrintableString() err:%d \n", ret);
		return ret;
	}
	memset(pTmpStru->clientId, 0, pTmpDABuf->dataLen + 1);
	memcpy(pTmpStru->clientId, pTmpDABuf->pData, pTmpDABuf->dataLen);

	DER_ITCAST_FreeQueue(pTmpDABuf);
	pTmp = pTmp->next; //结点下移

	//解码 AuthCode
	ret = DER_ItAsn1_ReadPrintableString(pTmp, &pTmpDABuf);
	if (ret != 0)
	{
		free(pTmpStru);
		DER_ITCAST_FreeQueue(pHead);
		printf("func DER_ItAsn1_ReadPrintableString() err:%d \n", ret);
		return ret;
	}
	memset(pTmpStru->AuthCode, 0, pTmpDABuf->dataLen + 1);

	memcpy(pTmpStru->AuthCode, pTmpDABuf->pData, pTmpDABuf->dataLen);

	DER_ITCAST_FreeQueue(pTmpDABuf);
	pTmp = pTmp->next; //结点下移

	//解码 serverId
	ret = DER_ItAsn1_ReadPrintableString(pTmp, &pTmpDABuf);
	if (ret != 0)
	{
		free(pTmpStru);
		DER_ITCAST_FreeQueue(pHead);
		printf("func DER_ItAsn1_ReadPrintableString() err:%d \n", ret);
		return ret;
	}
	memset(pTmpStru->serverId, 0, pTmpDABuf->dataLen + 1);

	memcpy(pTmpStru->serverId, pTmpDABuf->pData, pTmpDABuf->dataLen);

	DER_ITCAST_FreeQueue(pTmpDABuf);
	pTmp = pTmp->next; //结点下移

	//解码 r1
	ret = DER_ItAsn1_ReadPrintableString(pTmp, &pTmpDABuf);
	if (ret != 0)
	{
		free(pTmpStru);
		DER_ITCAST_FreeQueue(pHead);
		printf("func DER_ItAsn1_ReadPrintableString() err:%d \n", ret);
		return ret;
	}
	memset(pTmpStru->r1, 0, pTmpDABuf->dataLen + 1);

	memcpy(pTmpStru->r1, pTmpDABuf->pData, pTmpDABuf->dataLen);

	DER_ITCAST_FreeQueue(pHead);
	*pStruct = pTmpStru;
	return ret;
}

//释放内存
int  TeacherDecode_Free(Teacher *pT)
{
	if (pT == NULL)
	{
		return 0;
	}
	if (pT->p != NULL)
	{
		free(pT->p);
	}

	free(pT);
	return 0;
}

//不光把指针所执行的内存释放 而且把实参制成NULL 避免野指针
int  TeacherDecode_Free2(Teacher **  pT)
{
	if (pT == NULL)
	{
		return 0;
	}

	TeacherDecode_Free(*pT);

	*pT = NULL;
	return 0;
}


int  MsgKey_ReqDecode_Free(MsgKey_Req **  pT)
{
	if (pT == NULL)
	{
		return 0;
	}

	free(*pT);
	*pT = NULL;
	return 0;
}
//////////////////////////////////////////////////////////////////////////


int MsgEncode(
	void			*pStruct, /*in*/
	int				type,
	unsigned char	**outData, /*out*/
	int				*outLen)
{
	ITCAST_ANYBUF			*pHeadbuf = NULL, *pTemp = NULL;
	ITCAST_ANYBUF			*pOutData = NULL;
	int						ret = 0;

	//检查输入参数
	if (pStruct == NULL || type < 0 || outData == NULL || outLen == NULL)
	{
		ret = KeyMng_ParamErr;
		printf("func MsgEncode() err:%d (pStruct == NULL || type < 0 || outData == NULL || outLen == NULL)\n", ret);
		return 0;
	}
	
	//编码type
	ret = DER_ItAsn1_WriteInteger(type, &pHeadbuf/*out*/);
	if (ret != 0)
	{
		printf("func DER_ItAsn1_WriteInteger() err:%d \n", ret);
		return ret;
	}

	//根据type进行具体结构体的编码
	switch (type)
	{
	case ID_MsgKey_Teacher:
		//调用老师结构体编码函数
		ret = TeacherEncode_(pStruct/*in*/, &pTemp);
		break;
	case	ID_MsgKey_Req:
		ret = MsgKey_ReqEncode(pStruct/*in*/, &pTemp);
		
		//编码请求报文
		break;
	case	ID_MsgKey_Res:
		//编码应答报文
		break;
	default:
		ret = KeyMng_TypeErr;
		printf("类型输入失败()　itype:%d err:%d \n", type, ret);
		break;
	}

	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadbuf);
		printf("编码失败err:%d \n", ret);
		return ret;
	}
	pHeadbuf->next = pTemp;

	ret = DER_ItAsn1_WriteSequence(pHeadbuf, &pOutData);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadbuf);
		printf("func DER_ItAsn1_WriteSequence() err:%d \n", ret);
		return ret;
	}

	(*outData) = (unsigned char *)malloc(pOutData->dataLen);
	if (*outData == NULL)
	{
		DER_ITCAST_FreeQueue(pHeadbuf);
		ret = KeyMng_MallocErr;
		printf("func malloc() err:%d \n", ret);
		return ret;
	}
	memcpy(*outData, pOutData->pData, pOutData->dataLen);

	*outLen = pOutData->dataLen;

	DER_ITCAST_FreeQueue(pHeadbuf);
	DER_ITCAST_FreeQueue(pOutData);
	
	return ret;
}



int MsgDecode( 
	unsigned char *inData,/*in*/
	int           inLen,
	void          **pStruct /*out*/,
	int           *type /*out*/)
{
	ITCAST_ANYBUF		*pHeadBuf = NULL, *pTmp = NULL;
	int					ret = 0;
	unsigned long		itype = 0;

	//参数的检查
	if (inData == NULL || inLen < 0 || pStruct == NULL || type == NULL)
	{
		ret = KeyMng_ParamErr;
		printf("func MsgDecode() err:%d (inData == NULL || inLen < 0 || pStruct == NULL || type == NULL) \n", ret);
		return ret;
	}


	pTmp = (ITCAST_ANYBUF *)malloc(sizeof(ITCAST_ANYBUF));
	if (pTmp == NULL)
	{
		ret = KeyMng_MallocErr;
		printf("func malloc() err:%d\n", ret);
		return ret;
	}
	//pTmp->next;
	//pTmp->prev;
	memset(pTmp, 0, sizeof(ITCAST_ANYBUF)); //这句话很重要 保证结点的正确性

	pTmp->pData = (unsigned char *)malloc(inLen);
	if (pTmp == NULL)
	{
		DER_ITCAST_FreeQueue(pTmp);
		ret = KeyMng_MallocErr;
		printf("func malloc() err:%d\n", ret);
		return ret;
	}
	memcpy(pTmp->pData, inData, inLen);
	pTmp->dataLen = inLen;

	//解码 大结构体
	ret = DER_ItAsn1_ReadSequence(pTmp, &pHeadBuf);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pTmp);
		printf("func DER_ItAsn1_ReadSequence() err:%d \n", ret);
		return ret;
	}
	DER_ITCAST_FreeQueue(pTmp);//把临时结点 释放

	//解码 type
	ret = DER_ItAsn1_ReadInteger(pHeadBuf, &itype);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadBuf);
		printf("func DER_ItAsn1_ReadInteger() err:%d \n", ret);
		return ret;
	}

	//根据不同的类型 进行具体结构体的解码
	switch (itype)
	{
	case ID_MsgKey_Teacher:
		//调用解码 老师结构体的解码函数
		ret = TeacherDecode(pHeadBuf->next->pData, pHeadBuf->next->dataLen, (Teacher **)pStruct);
		break;
	case ID_MsgKey_Req:
		ret = MsgKey_ReqDecode(pHeadBuf->next->pData, pHeadBuf->next->dataLen, (MsgKey_Req **)pStruct);
		break;
	case ID_MsgKey_Res:
		break;
	
	default:
		ret = KeyMng_TypeErr;
		printf("itype:%d失败 :%d \n", itype, ret);
		break;
	}

	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadBuf);
		return ret;
	}
	DER_ITCAST_FreeQueue(pHeadBuf);

	//把结构体的标签 赋值
	*type = itype;
	return ret;
}

//dasfdsaf

int MsgMemFree(void **point, int type)
{
	//
	if (point == NULL   )
	{
		return 0;
	}

	if (type == 0)
	{
		free(*point);
		*point = NULL;
	}

	//释放老师结构体
	switch (type)
	{
	case ID_MsgKey_Teacher:
		TeacherDecode_Free2((Teacher **)point);
		break;
	case ID_MsgKey_Req:
		MsgKey_ReqDecode_Free((MsgKey_Req **)point);
		break;
	case ID_MsgKey_Res:
		break;
	default:
		break;
	}

	return 0;
}


