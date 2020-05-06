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

int control_x = 0;
int control_y = 0;

int cnnResult = 0;
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


/**************云台控制*************/

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
	//nParam1     x移动(speed,0-8)
	//nParam2     y移动(speed,0-8)
	//nParam3	  镜头伸缩  //根据命令不同，nParam的含义也不同
	//bStop    
	return CLIENT_DHPTZControlEx2(m_lLoginID, m_nChannel, nType, nParam1, nParam2, nParam3, bStop);
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
	// cout<<"最小温度是："<<nMin<<endl;

	// cout<<"最大温度是："<<nMax<<endl;
	delete[] pImg;
	delete[] pTemp;
}


//火源坐标回调函数
void firePosition_Callback(const std_msgs::Float32MultiArray msg){
	std::cout<<"x: "<<msg.data[0]<<",y: "<<msg.data[1]<<std::endl;
	control_x = msg.data[0];
	control_y = msg.data[1];

}

//火源坐标回调函数
void cnnDetect_Callback(const std_msgs::Float32MultiArray msg){
	std::cout<<"cnn_result: "<<msg.data[0]<<std::endl;
	cnnResult = msg.data[0];

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
		PtzControl(DH_EXTPTZ_STOPPANCRUISE,0,0,0,false); //停止

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
		// PtzControl(DH_EXTPTZ_STOPPANCRUISE,0,0,0,false); //停止
	}
}



int main(int argc, char *argv[])
{

	LLONG m_lLoginHandle;
	ros::init(argc, argv, "ptzcontrol123");


	ros::NodeHandle nh;
	// ros::MultiThreadedSpinner s(2);
	ros::Publisher temperature_pub = nh.advertise<std_msgs::Float32MultiArray>("temperature_data",20);//发布温度数据

	//订阅热红外检测话题
	ros::Subscriber sub_hotmap = nh.subscribe("/fire/position", 30, firePosition_Callback);
	//订阅CNN检测话题
	ros::Subscriber sub_cnn = nh.subscribe("/fire/result", 30, cnnDetect_Callback);
	
 	InitClient();
	clientlogin(m_lLoginHandle);
	
	ros::Rate loop_rate(30);
	
	while(ros::ok()){
	// PositionAngle=int(msg->angle[i]*10)+position_basi;	
		
		GetTemp(m_lLoginHandle);
		temperature.data.push_back(nMin);
		temperature.data.push_back(nMax);
		// ros::Time::now().sec;
		temperature_pub.publish(temperature);	
		temperature.data.clear();
		// if (control_x<-50 && control_y<-50) {
		// 	PtzControl(DH_EXTPTZ_LEFTTOP,1,1,0,false); //左上
		// 	std::cout<<"LEFTTOP"<<std::endl;
		// } 
		// else if (control_x<-50 && control_y>50) {
		// 	PtzControl(DH_EXTPTZ_LEFTDOWN,1,1,0,false);	//左下
		// 	std::cout<<"LEFTDOWN"<<std::endl;
		// }
		// else if (control_x>50 && control_y<-50) {
		// 	PtzControl(DH_EXTPTZ_RIGHTTOP,1,1,0,false);	//右上
		// 	std::cout<<"RIGHTTOP"<<std::endl;
		// }
		// else if (control_x>50 && control_y>50) {
		// 	PtzControl(DH_EXTPTZ_RIGHTDOWN,1,1,0,false); //右下
		// 	std::cout<<"RIGHTDOWN"<<std::endl;
		// } else {
		// 	PtzControl(DH_EXTPTZ_DELETEMODE,0,0,0,true); //停止
		// }

		// control_x = 0;
		// control_y = 0;
		// std::cout<<"cx: "<<control_x<<", cy: "<<control_y<<std::endl;
		// PtzControl(DH_EXTPTZ_STOPPANCRUISE,0,0,0,false); //停止




		ros::spinOnce();
		loop_rate.sleep();
	}
	return 0;
}