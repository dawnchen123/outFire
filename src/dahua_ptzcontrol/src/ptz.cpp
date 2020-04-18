#include "ptz.h"
#include "ros/ros.h"
#include "std_msgs/String.h"
// #include "dialog.h"
#include "stdio.h"
#include <sstream>
#include "UserDefine.h"
#include <iostream>
#include "dhnetsdk.h"

#pragma comment(lib , "dhnetsdk.lib")

#define SPEED 8 //rang is 1～8
using namespace std;
Dialog qcl_Dialog;
CPtz qcl_PTZ;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
// 设备断线回调函数
// 不建议在该回调函数中调用 SDK 接口
// 通过 CLIENT_Init 设置该回调函数,当设备出现断线时,SDK 会调用该函数。
void CALLBACK DisConnectFunc(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser)
{
    Dialog * pThis = (Dialog *)dwUser;
    if(NULL == pThis)
    {
        return;
    }

    return;
}
// 断线重连成功回调函数
// 不建议在该回调函数中调用 SDK 接口
// 通过 CLIENT_SetAutoReconnect 设置该回调函数,当已断线的设备重连成功时, SDK 会调用该函数。
void CALLBACK HaveReConnect(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort,LDWORD dwUser)
{
    Dialog * pThis = (Dialog *)dwUser;
    if(NULL == pThis)
    {
        return;
    }

    return;
}

Dialog::Dialog()
{
	//CLIENT_Cleanup();//反初始化，删除所有用户信息
	static BOOL g_bNetSDKInitFlag = FALSE;
	//初始化   parameter1 断线重连回调函数 2用户数据
	//成功返回 1
	g_bNetSDKInitFlag=CLIENT_Init(DisConnectFunc, (LDWORD)this);
	 
	if (FALSE == g_bNetSDKInitFlag)
	{
		printf("Initialize client SDK fail; \n");
		return;
	}
	else
	{
		printf("Initialize client SDK done; \n");
	}
	// 此操作为可选操作
	DWORD dwNetSdkVersion = CLIENT_GetSDKVersion();
	printf("NetSDK version is [%d]\n", dwNetSdkVersion);

	// 设置断线重连回调接口,设置过断线重连成功回调函数后,当设备出现断线情况, SDK
	// 内部会自动进行重连操作
	CLIENT_SetAutoReconnect(&HaveReConnect, (LDWORD)this);

	// 设置登录超时时间和尝试次数
	// 此操作为可选操作
	int nWaitTime = 5000; // 登录请求响应超时时间设置为 5s
	int nTryTimes = 3; // 登录时尝试建立链接 3 次
	CLIENT_SetConnectTime(nWaitTime, nTryTimes);
}

Dialog::~Dialog()
{
	CLIENT_Cleanup();//反初始化，删除所有用户信息
}

CPtz::CPtz()
{

}

CPtz::~CPtz()
{

}

//设置登录id和通道
bool CPtz::SetPtzParam(LLONG lLoginID, int nChannel)
{
    if(lLoginID <=0 || nChannel < 0 )
	{
		return false;
	}

	m_lLoginID = lLoginID;
	m_nChannel = nChannel;
	
	return true;
}

//只设置登录ID
bool CPtz::SetLoginID(LLONG lLoginID)
{
	if(lLoginID <= 0)
	{
		return false;
	}
	m_lLoginID = lLoginID;
	return true;
}

//只设置通道
bool CPtz::SetChannel(int nChannel)
{
    if( nChannel < 0)  
	{
		return false;
	}
	m_nChannel = nChannel;
	return true;
}

/*************************************************************************************************/

#include<iostream>
using namespace std;
//控制函数主题，所有函数都是调用的这个函数
bool CPtz::PtzControl(int nType, int nParam1, int nParam2, int nParam3, bool bStop /* = false */)
{
	//cout<<nType<<"'"<<m_lLoginID<<","<<m_nChannel<<","<<nParam1<<","<<nParam2<<","<<nParam3<<","<<bStop<<endl;
    if(m_lLoginID <=0 || m_nChannel < 0 )
	{
		return false;
	}
	// 私有云台控制扩展接口,支持三维快速定位
	//m_lLoginID  ID
	//m_nChannel  通道
	//nType       控制命令
	//nParam1     x移动
	//nParam2     y移动
	//nParam3	  镜头伸缩  //根据命令不同，nParam的含义也不同
	//bStop    
	return CLIENT_DHPTZControlEx(m_lLoginID, m_nChannel, nType, nParam1, nParam2, nParam3, bStop);
}


//基础控制 
//nType  控制类型
bool CPtz::PtzBasicControl(int nType, int nStep, bool bStop /* = false */)
{
	switch(nType) 
	{
	case DH_PTZ_UP_CONTROL:	//上
	case DH_PTZ_DOWN_CONTROL://下
	case DH_PTZ_LEFT_CONTROL://左
	case DH_PTZ_RIGHT_CONTROL://右
	case DH_PTZ_ZOOM_DEC_CONTROL://镜头缩放
	case DH_PTZ_ZOOM_ADD_CONTROL://
	case DH_PTZ_FOCUS_DEC_CONTROL://焦距
	case DH_PTZ_FOCUS_ADD_CONTROL://
	case DH_PTZ_APERTURE_DEC_CONTROL://光圈
	case DH_PTZ_APERTURE_ADD_CONTROL://
		{
			return PtzControl(nType, 0, nStep, 0, bStop);
		}	
		break;
	case DH_EXTPTZ_LEFTTOP:	//左上
	case DH_EXTPTZ_LEFTDOWN://左下
	case DH_EXTPTZ_RIGHTTOP: //右上
	case DH_EXTPTZ_RIGHTDOWN://右下
		{
			return PtzControl(nType, nStep, nStep, 0, bStop);
		}
		break;
	default:
		return false;
	}
}

//快速前往
bool CPtz::PtzFastGo(int nX, int nY, int nZoom,bool isabsolute)
{
	if(isabsolute=true)
		{return PtzControl(DH_EXTPTZ_EXACTGOTO, nX, nY, nZoom, false);}//绝对移动指令DH_EXTPTZ_MOVE_ABSOLUTELY
	else
		{return PtzControl(DH_EXTPTZ_FASTGOTO, nX, nY, nZoom, false);}//相对移动指令
	
	
}

// bool CPtz::PtzMenuControl(int nType)//（球机）菜单控制，和这个云台无关
// {
// 	switch(nType) 
// 	{
	// case DH_EXTPTZ_MENUUP://上
	// case DH_EXTPTZ_MENUDOWN://下
	// case DH_EXTPTZ_MENULEFT://左
	// case DH_EXTPTZ_MENURIGHT://右
	// case DH_EXTPTZ_OPENMENU://打开球机菜单
	// case DH_EXTPTZ_CLOSEMENU://关闭菜单
	// case DH_EXTPTZ_MENUOK://菜单确定
	// case DH_EXTPTZ_MENUCANCEL://菜单取消
// 		{
// 			return PtzControl(nType, 0, 0, 0);
// 		}	
// 		break;
// 	default:
// 		return false;
// 	}

// }

////辅助功能 自动变焦(缩放)
// bool CPtz::PtzAuxi(int nType, int nAuxi)
// {
// 	switch(nType) 
// 	{
// 	case DH_EXTPTZ_AUXIOPEN://开
// 	case DH_EXTPTZ_AUXICLOSE://关
// 		{
// 			return PtzControl(nType, nAuxi, 0, 0);
// 		}
// 		break;
// 	default:
// 		return false;
// 	}

// }



//左右扫描
// bool CPtz::PtzLineScan(int nType)
// {
// 	switch(nType)
// 	{
// 	case DH_EXTPTZ_SETLEFTBORDER:		//设置左边界			
// 	case DH_EXTPTZ_SETRIGHTBORDER:		//设置右边界			
// 	case DH_EXTPTZ_STARTLINESCAN:		//开始线扫			
//     case DH_EXTPTZ_CLOSELINESCAN:		//停止线扫			
// 		{
// 			return PtzControl(nType, 0, 0, 0);
// 		}
// 		break;
// 	default:
// 		return false;
// 	}
// }

//巡航模式
// bool CPtz::PtzLoop(int nType, int nGroup, int nPresetData, bool bBeginLoop /* = false */)
// {
// 	switch(nType)
// 	{
// 		case DH_PTZ_POINT_LOOP_CONTROL://开始巡航,停止巡航
// 			{
// 				if (bBeginLoop) 
// 				{
// 					return PtzControl(nType, nGroup, 0, 76);//开始
// 				}
// 				else
// 				{
// 					return PtzControl(nType, nGroup, 0, 96);//停止
// 				}
// 			}
// 			break;
// 		case DH_EXTPTZ_ADDTOLOOP://增加巡航点
// 		case DH_EXTPTZ_DELFROMLOOP://删除巡航点
// 			{
// 				return PtzControl(nType, nGroup, nPresetData, 0);
// 			}
// 			break;
// 		case DH_EXTPTZ_CLOSELOOP://删除巡航组
// 			{
// 				return PtzControl(nType, nGroup, 0, 0);
// 			}
// 			break;
// 		default:
// 			return false;
// 	}
// }

// bool CPtz::PtzPreset(int nType, int nPresetData)
// {
// 	switch(nType)
// 	{
// 	case DH_PTZ_POINT_MOVE_CONTROL://转至预置点
// 	case DH_PTZ_POINT_SET_CONTROL://设置
// 	case DH_PTZ_POINT_DEL_CONTROL://删除
// 		{
// 			return PtzControl(nType, 0, nPresetData, 0);
// 		}
// 		break;
// 	default:
// 		return false;
// 	}
// }

// bool CPtz::PtzRotate(int nType)
// {
// 	switch(nType)
// 	{
// 	case DH_EXTPTZ_STARTPANCRUISE:		//开始水平旋转			
// 	case DH_EXTPTZ_STOPPANCRUISE:		//停止水平旋转
// 		{
// 			return PtzControl(nType, 0, 0, 0);
// 		}
// 	default:
// 		return false;
// 	}
// }

// bool CPtz::PtzMode(int nType, int nGroup)
// {
// 	switch(nType)
// 	{
// 	case DH_EXTPTZ_SETMODESTART://开始记录
// 	case DH_EXTPTZ_SETMODESTOP:	//停止记录
// 	case DH_EXTPTZ_RUNMODE:	//开始巡迹
// 	case DH_EXTPTZ_STOPMODE://停止巡迹
// 	case DH_EXTPTZ_DELETEMODE://删除巡迹
// 		{
// 			return PtzControl(nType, nGroup, 0, 0);
// 		}
// 		break;
// 	default:
// 		return false;
// 	}
// }

//// 获取云台能力集have error
//m_lLoginHandle 登录句柄 
//CFG_CAP_CMD_PTZ 查询指令
//
void CPtz::GetPtzCapacity(LLONG g_lLoginHandle)
{
	
    // char szBuffer[2048] = "";
	// int nError = 0;
	// if (FALSE == CLIENT_QueryNewSystemInfo(g_lLoginHandle, CFG_CAP_CMD_PTZ, 0,szBuffer, (DWORD)sizeof(szBuffer), &nError))//系统能力查询接口
	// {
	// 	printf("CLIENT_QueryNewSystemInfo Failed, cmd[CFG_CAP_CMD_PTZ], Last Error[%x]\n" , CLIENT_GetLastError());
	// 	return;
	// }
	// CFG_PTZ_PROTOCOL_CAPS_INFO stuPtzCapsInfo =	{sizeof(CFG_PTZ_PROTOCOL_CAPS_INFO)};
	// if (FALSE == CLIENT_ParseData(CFG_CAP_CMD_PTZ, szBuffer, &stuPtzCapsInfo,sizeof(stuPtzCapsInfo), NULL))//解析接口
	// {
	// 	printf("CLIENT_ParseData Failed, cmd[CFG_CAP_CMD_PTZ], Last	Error[%x]\n" , CLIENT_GetLastError());
	// 	return;
	// }
}

// void my_ptzcontrol(){
// 	std::vector<PtzControlInfo> vecPtzControl;
// if (TRUE == stuPtzCapsInfo.bTile)
// {
// 	vecPtzControl.push_back(PtzControlInfo(int(DH_PTZ_UP_CONTROL), "上",true));
// 	vecPtzControl.push_back(PtzControlInfo(int(DH_PTZ_DOWN_CONTROL), "下", true));
// }
// if (TRUE == stuPtzCapsInfo.bPan)
// {
// vecPtzControl.push_back(PtzControlInfo(int(DH_PTZ_LEFT_CONTROL), "左
// ", true));
// vecPtzControl.push_back(PtzControlInfo(int(DH_PTZ_RIGHT_CONTROL), "
// 右", true));
// }
// if (TRUE == stuPtzCapsInfo.bZoom)
// {
// vecPtzControl.push_back(PtzControlInfo(int(DH_PTZ_ZOOM_ADD_CONTROL),
// "变倍+", true));
// vecPtzControl.push_back(PtzControlInfo(int(DH_PTZ_ZOOM_DEC_CONTROL),
// "变倍-", true));
// }
// if (TRUE == stuPtzCapsInfo.bFocus)
// {
// vecPtzControl.push_back(PtzControlInfo(int(DH_PTZ_FOCUS_ADD_CONTROL),
// "调焦+", true));
// vecPtzControl.push_back(PtzControlInfo(int(DH_PTZ_FOCUS_DEC_CONTROL),
// "调焦-", true));
// }
// if (TRUE == stuPtzCapsInfo.bIris)
// {
// vecPtzControl.push_back(PtzControlInfo(int(DH_PTZ_APERTURE_ADD_CONTROL), "光
// 圈+", true));
// vecPtzControl.push_back(PtzControlInfo(int(DH_PTZ_APERTURE_DEC_CONTROL), "光
// 圈-", true));
// }
// if (TRUE == stuPtzCapsInfo.bPreset)
// {
// vecPtzControl.push_back(PtzControlInfo(int(DH_PTZ_POINT_MOVE_CONTROL), " 转至
// 预置点", false));
// vecPtzControl.push_back(PtzControlInfo(int(DH_PTZ_POINT_SET_CONTROL),
// "设置预置点", false));
// }
// if (TRUE == stuPtzCapsInfo.bRemovePreset)
// {
// vecPtzControl.push_back(PtzControlInfo(int(DH_PTZ_POINT_DEL_CONTROL),
// "删除预置点", false));
// }
// if (TRUE == stuPtzCapsInfo.bTour)
// {
// vecPtzControl.push_back(PtzControlInfo(int(DH_PTZ_POINT_LOOP_CONTROL), " 点间
// 巡航", false));
// vecPtzControl.push_back(PtzControlInfo(int(DH_EXTPTZ_ADDTOLOOP), "加
// 入预置点到巡航", false));
// vecPtzControl.push_back(PtzControlInfo(int(DH_EXTPTZ_DELFROMLOOP), "
// 删除巡航中预置点", false));
// }
// if (TRUE == stuPtzCapsInfo.bRemoveTour)
// {
// vecPtzControl.push_back(PtzControlInfo(int(DH_EXTPTZ_CLOSELOOP), "清
// 除巡航", false));
// }
// if (TRUE == stuPtzCapsInfo.bTile && TRUE == stuPtzCapsInfo.bPan)
// {
// vecPtzControl.push_back(PtzControlInfo(int(DH_EXTPTZ_LEFTTOP), "左上
// ", true));
// vecPtzControl.push_back(PtzControlInfo(int(DH_EXTPTZ_RIGHTTOP), " 右上
// ", true));
// vecPtzControl.push_back(PtzControlInfo(int(DH_EXTPTZ_LEFTDOWN), " 左下
// ", true));
// vecPtzControl.push_back(PtzControlInfo(int(DH_EXTPTZ_RIGHTDOWN), "右
// 下", true));
// }
// if (TRUE == stuPtzCapsInfo.bMoveRelatively)
// {
// vecPtzControl.push_back(PtzControlInfo(int(DH_EXTPTZ_FASTGOTO), " 快速
// 定位", false));
// }
// if (TRUE == stuPtzCapsInfo.bMoveAbsolutely)
// {
// vecPtzControl.push_back(PtzControlInfo(int(DH_EXTPTZ_EXACTGOTO), "三
// 维精确定位", false));
// }
// vecPtzControl.push_back(PtzControlInfo(int(-2), "暂停", false));
// vecPtzControl.push_back(PtzControlInfo(int(-1), "退出", true));
// PtzControlInfo cLastChoose;
// 	while(TRUE)
// 	{
// 		printf("云台控制操作:\n");
// 		for (std::vector<PtzControlInfo>::const_iterator iter=vecPtzControl.begin(); iter != vecPtzControl.end(); ++iter)
// 		{
// 			printf("\t%d\t:%s\n", iter->m_iCmd,iter->m_sDescription.c_str());
// 		}
// 		int nError = 0;
// 		int nChoose = GetIntInput("\t 选择:", nError);
// 		if (0 != nError)
// 		{
// 			printf("无效输入!\n");
// 			continue;
// 		}
// 		std::vector<PtzControlInfo>::iterator iterFind =
// 		vecPtzControl.begin();
// 		for (; iterFind != vecPtzControl.end(); ++iterFind)
// 		{
// 			if (nChoose == iterFind->m_iCmd)
// 		{
// 			break;
// 		}
// 		}
// 		if (iterFind == vecPtzControl.end())
// 		{
// 			printf("请输入有效范围内的操作\n");
// 			continue;
// 		}
// 		// 停止上一个操作
// int nChannelId = 0;
// if (true == cLastChoose.m_bStopFlag)
// {
// if (FALSE == CLIENT_DHPTZControlEx2(g_lLoginHandle, nChannelId,
// cLastChoose.m_iCmd, 0, 0, 0, TRUE))
// {
// printf("CLIENT_DHPTZControlEx2 Failed,
// cLastChoose->GetCmd()[%x]!Last Error[%x] \n" , cLastChoose.m_iCmd,
// CLIENT_GetLastError());
// }
// }
// if (iterFind->m_sDescription == "暂停")
// {
// cLastChoose = *iterFind;
// continue;
// }
// if (iterFind->m_sDescription == "退出")
// {
// break;
// }
// }






void Dialog::my_client_longin(){

	string strIp;
	string strUserName;
	string strDvrPort;
	string strPassword;
	strIp = "192.168.1.108"; //自己设定信息
	strUserName = "admin";
	strPassword = "admin123";
	strDvrPort ="37777";
	
	stringstream sstrport;
	sstrport<<strDvrPort;
    long lPort ;
	sstrport>>lPort;
	NET_DEVICEINFO_Ex stDevInfo = {0};
	int nError = 0;
	LLONG m_lLoginHandle = CLIENT_LoginEx2((char *)strIp.c_str(), lPort, (char*)strUserName.c_str(),
                                          (char*)strPassword.c_str(), EM_LOGIN_SPEC_CAP_TCP, NULL, &stDevInfo, &nError);

	if(m_lLoginHandle == 0)
	{
	
			cout<<"Login failed!"<<endl;	}
	else
	{   
		cout<<"login success"<<endl;
		qcl_PTZ.SetLoginID(m_lLoginHandle);
		//initalize comboxChannel
		
		m_nChannelIndex = 1;
		qcl_PTZ.SetChannel(m_nChannelIndex);
		m_nCtrlParam =SPEED; //1~8

	}
	sleep(5);
	
}

void Dialog::PTZForSIT( int nX, int nY, int nZoom,bool isabsolute)
{
    bool bRet = false;

    bRet = qcl_PTZ.PtzFastGo(nX, nY, nZoom,isabsolute);

    if(bRet == false)
    {
       cout<<"Operate fail"<<endl;
    }
	else {
		cout<<"Operate success"<<endl;
	}
}

void Dialog::my_PTZForBasicControl(int nType, bool bStop)
{
    bool bRet = false;
    bRet = qcl_PTZ.PtzBasicControl(nType, m_nCtrlParam, bStop);
    if(bRet == false)
    {
        // m_bMessageTip = TRUE;
		cout<<"Operate fail"<<endl;
    }
	else {
		cout<<"Operate success"<<endl;
	}
}


//clinet longout
void Dialog::my_client_longout(){
	if (m_lLoginHandle != 0)
	{
		BOOL bSuccess = CLIENT_Logout(m_lLoginHandle);
		if(bSuccess)
		{
	

		}
		else
		{
			cout<<"Logout failed!"<<endl;
		}
	}

}

void Dialog::client(){
	CLIENT_Init(DisConnectFunc, (LDWORD)this);//初始化
	CLIENT_Cleanup();//反初始化，删除所有用户信息
}

#define __max(a, b) (((a) > (b)) ? (a) : (b))
void SearchMax(float &nMax, float *YData, int yDataLen)
{
	if (NULL == YData)
	{
		return;
	}
	nMax = (float)YData[0];
	for (int i=1; i <yDataLen; i++)
	{
		nMax = __max(nMax, (float)YData[i]);
	}
}





// 温度状态回调函数
void CALLBACK cbRadiometryAttachCB(LLONG lAttachHandle, NET_RADIOMETRY_DATA* pBuf, int nBufLen, LDWORD dwUser)
{	
// float maxTemp=-99999;
// 	int num=0;
// 	cout<<"灰调函数被调用"<<endl;
// 	NET_RADIOMETRY_DATA *pTmpBuf = new NET_RADIOMETRY_DATA;
// 	if (NULL == pTmpBuf)
// 	{
// 	return;
// 	}

// 	pTmpBuf->dwBufSize = pBuf->dwBufSize;
// 	memcpy(&pTmpBuf->stMetaData, &pBuf->stMetaData, sizeof(pBuf->stMetaData));

// 	pTmpBuf->pbDataBuf = new BYTE[pBuf->dwBufSize];
// 	if (NULL != pTmpBuf->pbDataBuf)
// 	{	
// 		memcpy(pTmpBuf->pbDataBuf, pBuf->pbDataBuf, pBuf->dwBufSize);
// 	}

// 	 cout<<"m_nHeight"<<pBuf->stMetaData.nHeight<<endl;
// 	 cout<<"nWidth"<<pBuf->stMetaData.nWidth<<endl;
// 	 cout<<"nLength"<<pBuf->stMetaData.nLength<<endl;
// 	 cout<<"dwBufSize"<<pBuf->dwBufSize<<endl;
// 	cout<<"time"<<pBuf->stMetaData.stTime.dwSecond<<endl;
// 	cout<<"NET_RADIOMETRY_METADATA_SIZE"<<sizeof(NET_RADIOMETRY_METADATA)<<endl;
//  pBuf->stMetaData.nLength-=1520;
// pBuf->dwBufSize-=1520;
	int nPixel = pBuf->stMetaData.nWidth*pBuf->stMetaData.nHeight;

	unsigned short *pImg = new unsigned short[nPixel];
	if(NULL!=pImg){
		memset(pImg,0,sizeof(unsigned short)*nPixel);
	}
	else{
		return;
	}

	float *pTemp = new float[nPixel];
	if(NULL!=pTemp){
		memset(pTemp,0,sizeof(float)*nPixel);
	}
	else{
		if (NULL != pImg)
		{
			delete [] pImg;
			pImg = NULL;
		}
		return;
	}

if(	CLIENT_RadiometryDataParse(pBuf,NULL,pTemp)){

		cout<<"解析数据成功"<<endl;

}

else{

		cout<<"解析数据失败"<<endl;

}
		



	cout<<"the picture number is "<<nPixel<<endl;
	// for(int i=0;i<nPixel;i++){
	// 	// if(maxTemp<pTemp[i]){
	// 	// 	maxTemp=pTemp[i];
	// 		cout<<"温度"<<i<<"is :"<<pTemp[i]<<endl;
	// 	//  }
		
	// 	if(pTemp[i]!=0){
	// 		num++;
	// 	}

	float nMax =-1;
	SearchMax(nMax, pTemp, nPixel);
	cout<<"温度is :"<<pTemp[200]<<endl;

	cout<<"最大温度是："<<nMax<<endl;
	delete[] pImg;
	delete[] pTemp;
}

void Dialog::GetTemp(){

	// 订阅热图
	// NET_IN_RADIOMETRY_ATTACH stIn = {sizeof(stIn), 1, cbRadiometryAttachCB};
	// NET_OUT_RADIOMETRY_ATTACH stOut = {sizeof(stOut)};
	int m_nHeatChannel=1;
	NET_IN_RADIOMETRY_ATTACH stIn = {sizeof(stIn)};
    stIn.nChannel = m_nHeatChannel;
    stIn.dwUser = 0;
    stIn.cbNotify = cbRadiometryAttachCB;
    NET_OUT_RADIOMETRY_ATTACH stOut = {sizeof(stOut)};

	LLONG attachHandle = CLIENT_RadiometryAttach(m_lLoginHandle, &stIn, &stOut, 1000);//订阅温度分布数据
	
	if (attachHandle==0)
	{
		cout<<"订阅失败"<<endl;
	}
	else {
		cout<<"订阅成功"<<endl;
	}
	// // 通知设备开始采集数据
	// // NET_IN_RADIOMETRY_FETCH stInFetch = {sizeof(stInFetch), 1};
	// NET_OUT_RADIOMETRY_FETCH stOutFetch = {sizeof(stOutFetch)};
	NET_IN_RADIOMETRY_FETCH stInFetch = {sizeof(stInFetch), m_nHeatChannel};
    NET_OUT_RADIOMETRY_FETCH stOutFetch = {sizeof(stOutFetch)};
	BOOL bRet=CLIENT_RadiometryFetch(m_lLoginHandle, &stInFetch, &stOutFetch, 1000);//获取温度分布数据

	if (bRet)
	{
		cout<<"获取数据成功"<<endl;
	}
	else{
		cout<<"获取数据失败"<<endl;
	}
															 	
	// 使用完毕,取消订阅热图
	//  CLIENT_RadiometryDetach(attachHandle);
}

int main(int argc, char *argv[])
{
	ros::init(argc, argv, "ptzcontrol_test");

	ros::NodeHandle n;

	qcl_Dialog.my_client_longin();
	// qcl_Dialog.OnBtnQuery();
	qcl_Dialog.GetTemp();
	ros::Rate loop_rate(1);
	// while(true){
		/***********************************/
		// DH_PTZ_UP_CONTROL:	//上
		// DH_PTZ_DOWN_CONTROL://下
		// DH_PTZ_LEFT_CONTROL://左
		// DH_PTZ_RIGHT_CONTROL://右
		// DH_EXTPTZ_LEFTTOP:	//左上
		// DH_EXTPTZ_LEFTDOWN://左下
		// DH_EXTPTZ_RIGHTTOP: //右上
		// DH_EXTPTZ_RIGHTDOWN://右下
		// DH_PTZ_ZOOM_DEC_CONTROL://镜头缩
		// DH_PTZ_ZOOM_ADD_CONTROL://镜头伸
		// DH_PTZ_FOCUS_DEC_CONTROL://焦距近
		// DH_PTZ_FOCUS_ADD_CONTROL://焦距远
		// DH_PTZ_APERTURE_DEC_CONTROL://光圈小
		// DH_PTZ_APERTURE_ADD_CONTROL://光圈大
		/*****************************************/
		//qcl_Dialog.my_PTZForBasicControl(DH_PTZ_LEFT_CONTROL, false);//往右转

	// qcl_Dialog.PTZForSIT(-0,-0,0,true);//坐标移动

	
	//   while(1){
		  
	// 		ros::spinOnce();
	// 		loop_rate.sleep();
	// 	}


	

}