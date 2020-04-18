#include "ptz.h"
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Float32MultiArray.h"

// #include "dialog.h"
#include "stdio.h"
#include <sstream>
#include "UserDefine.h"
#include <iostream>
#include "dhnetsdk.h"
#include "dahua_ptzcontrol/HeatMapTemp.h"
#include "dahua_ptzcontrol/Temperature.h"

// #include "hit_nav/Angle.h"
// #include "avhlobal.h"
// #include "dhconfigsdk.h"
// #include "dialog.h"

#define interval_time 6


#pragma comment(lib , "dhnetsdk.lib")
using namespace std;

//---ROS msgs define space---//
std_msgs::Float32MultiArray temperature;

LLONG m_lLoginID;
int m_nChannel,m_nCtrlParam;
int position_basi=-40;
float nMax =-1;
float nMin =-1;
// vector<int> PositionAngle;
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
void InitClient()
{
	//CLIENT_Cleanup();//反初始化，删除所有用户信息
	static BOOL g_bNetSDKInitFlag = FALSE;
	//初始化   parameter1 断线重连回调函数 2用户数据
	//成功返回 1
	g_bNetSDKInitFlag=CLIENT_Init(DisConnectFunc,0);
	 
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
	CLIENT_SetAutoReconnect(&HaveReConnect,0);

	// 设置登录超时时间和尝试次数
	// 此操作为可选操作
	int nWaitTime = 5000; // 登录请求响应超时时间设置为 5s
	int nTryTimes = 3; // 登录时尝试建立链接 3 次
	CLIENT_SetConnectTime(nWaitTime, nTryTimes);
}


void clientlogin(LLONG& m_lLoginHandle){	
	
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
	// 登录设备
	m_lLoginHandle = CLIENT_LoginEx2((char *)strIp.c_str(), lPort, (char*)strUserName.c_str(),
                                          (char*)strPassword.c_str(), EM_LOGIN_SPEC_CAP_TCP, NULL, &stDevInfo, &nError);

	// LLONG lLoginHandle = CLIENT_LoginEx2("192.168.1.108", 37777, "admin", "admin123",
	// EM_LOGIN_SPEC_CAP_TCP, NULL, &stDevInfo, &nError);
	if(m_lLoginHandle == 0)
	{

			cout<<"Login failed!"<<endl;

	}
	else
	{   
		cout<<"login success"<<endl;
		m_lLoginID=m_lLoginHandle;
		//initalize comboxChannel		
		m_nChannel=1;
		m_nCtrlParam =8; //1~8

	}
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

#define __min(a, b) (((a) < (b)) ? (a) : (b))
void SearchMin(float &nMin, float *YData, int yDataLen)
{
	if (NULL == YData)
	{
		return;
	}
	nMin = (float)YData[0];
	for (int i=1; i <yDataLen; i++)
	{
		nMin = __min(nMin, (float)YData[i]);
	}
}
// 温度状态回调函数
void CALLBACK cbRadiometryAttachCB(LLONG lAttachHandle, NET_RADIOMETRY_DATA* pBuf, int nBufLen, LDWORD dwUser)
{	

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
			// cout<<"解析数据成功"<<endl;
	}

	else{
		//	cout<<"解析数据失败"<<endl;
	}
//	cout<<"the picture number is "<<nPixel<<endl;

	SearchMax(nMax, pTemp, nPixel);
	SearchMin(nMin, pTemp, nPixel);

	// cout<<"温度is :"<<pTemp[200]<<endl;
	cout<<"最小温度是："<<nMin<<endl;

	cout<<"最大温度是："<<nMax<<endl;
	delete[] pImg;
	delete[] pTemp;
}





void GetTemp(LLONG m_lLoginHandle){

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

	// char szJsonBuf[1024 * 40] = {0};
    // int nerror = 0;
    // int nChannel = -1;

	// BOOL ret = CLIENT_GetNewDevConfig(m_lLoginHandle,CFG_CMD_THERMOMETRY,nChannel,szJsonBuf,1024*40,&nerror,3000);
    // if (0 != ret)
    // {
    //     CFG_THERMOMETRY_INFO stuInfo = {0};
    //     DWORD dwRetLen = 0;
    //     ret = CLIENT_ParseData(CFG_CMD_THERMOMETRY,szJsonBuf,(char*)&stuInfo,sizeof(stuInfo),&dwRetLen);
	// 	if(!ret){
	// 		cout<<"getconfig error"<<endl;
	// 	}
	// 	else {
	// 		// cout<<"温度"<<stuInfo.fReflectedTemperature<<endl;
	// 		cout<<"距离"<<stuInfo.nObjectDistance<<endl;
	// 	}
	// }
															 	
	// 使用完毕,取消订阅热图
	//   CLIENT_RadiometryDetach(attachHandle);
}

/**************云台控制*************/
#include<iostream>
using namespace std;
//控制函数主题，所有函数都是调用的这个函数
bool PtzControl(int nType, int nParam1, int nParam2, int nParam3, bool bStop /* = false */)
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
bool PtzBasicControl(int nType, int nStep, bool bStop /* = false */)
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
bool PtzFastGo(int nX, int nY, int nZoom,bool isabsolute)
{
	if(isabsolute=true)
		{return PtzControl(DH_EXTPTZ_EXACTGOTO, nX, nY, nZoom, false);}//绝对移动指令DH_EXTPTZ_MOVE_ABSOLUTELY
	else
		{return PtzControl(DH_EXTPTZ_FASTGOTO, nX, nY, nZoom, false);}//相对移动指令
	
	
}

void PTZForSIT( int nX, int nY, int nZoom,bool isabsolute)
{
    bool bRet = false;

    bRet =PtzFastGo(nX, nY, nZoom,isabsolute);

    // if(bRet == false)
    // {
    //    cout<<"Operate fail"<<endl;
    // }
	// else {
	// 	cout<<"Operate success"<<endl;
	// }
}

void Dialog::my_PTZForBasicControl(int nType, bool bStop)
{
    bool bRet = false;
    bRet = PtzBasicControl(nType, m_nCtrlParam, bStop);
    // if(bRet == false)
    // {
    //     // m_bMessageTip = TRUE;
	// 	cout<<"Operate fail"<<endl;
    // }
	// else {
	// 	cout<<"Operate success"<<endl;
	// }
}

int position=0;
int ptz_timer=0;
int target_point=0;
int all_point_num=0;
int first_flag=1;//如果第一次进入则为1，否则为0
// void PTZ_ControlCallback(const hit_nav::Angle::ConstPtr& msg){

// 	// all_point_num=sizeof(msg->angle)/sizeof(float)/2;
// 	all_point_num=msg->angle.size();
// 	// cout<<"**********************************************总共有"<<all_point_num<<"个点*********************"<<endl;
	
// 	if(all_point_num==0){
// 		first_flag=1;
// 		PTZForSIT(0,0,0,true);//坐标移动
// 		PositionAngle.clear();
// 	}
// 	// cout<<"**********************************************"<<first_flag<<"**********************************************"<<endl;
// 	if(first_flag&&all_point_num!=0){
// 		ptz_timer=0;
// 		for(int i=0;i<all_point_num;i++){
// 			int intpoint=int(msg->angle[i]*10)+position_basi;
// 			PositionAngle.push_back(intpoint);
// 		}
// 		first_flag=0;
// 	}
// 		cout<<"**********************************************总共有"<<PositionAngle.size()<<"个点*********************"<<endl;
	
// }
int main(int argc, char *argv[])
{

	LLONG m_lLoginHandle;
	ros::init(argc, argv, "ptzcontrol123");


	ros::NodeHandle nh;
	// ros::MultiThreadedSpinner s(2);
	ros::Publisher temperature_pub = nh.advertise<std_msgs::Float32MultiArray>("temperature_data",20);//发布温度数据

	// ros::Subscriber sub = nh.subscribe("rotation_angle", 100, PTZ_ControlCallback);
 	InitClient();
	clientlogin(m_lLoginHandle);
	
	ros::Rate loop_rate(20);
	
	while(ros::ok()){
	// PositionAngle=int(msg->angle[i]*10)+position_basi;	
		
		GetTemp(m_lLoginHandle);
		temperature.data.push_back(nMin);
		temperature.data.push_back(nMax);
		// ros::Time::now().sec;
		temperature_pub.publish(temperature);	
		temperature.data.clear();

		// if(PositionAngle.size()){
		// 	PTZForSIT(PositionAngle.at(target_point),-0,0,true);//坐标移动
		// 	if(ptz_timer%(interval_time+1)==interval_time){
		// 		target_point++;
		// 		if(target_point>(PositionAngle.size()-1)){
		// 			PositionAngle.clear();
		// 			target_point=0;
					
		// 		}
		// 	}
		// }
		// else {
		// 	PTZForSIT(0,-0,0,true);//坐标移动
		// }

		ros::spinOnce();
		loop_rate.sleep();
		ptz_timer++;
	}
	return 0;
}