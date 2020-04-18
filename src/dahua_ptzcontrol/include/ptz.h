// Ptz.h: interface for the CPtz class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PTZ_H__3CBE7307_BC91_490C_91E9_B08535C6C7F4__INCLUDED_)
#define AFX_PTZ_H__3CBE7307_BC91_490C_91E9_B08535C6C7F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "dhnetsdk.h"
#include "dhconfigsdk.h"
#include "avglobal.h"



class Dialog 
{

public:
    Dialog();
    virtual ~Dialog();
    void client();
	void GetTemp();
	void OnBtnQuery();
    void my_client_longout();
    void my_PTZForBasicControl(int nType, bool bStop);
    void my_client_longin();
	void PTZForSIT( int nX, int nY, int nZoom,bool isabsolute);


private:
    LLONG      m_lLoginHandle;   ///登陆句柄
    int        m_bMessageTip;    
    int        m_nChannelIndex;  ///当前通道
    int        m_nCtrlParam;     /// 云台控制参数

};

class CPtz  
{
public:
	CPtz();
	virtual ~CPtz();

public://interface
	
	bool SetPtzParam(LLONG lLoginID, int nChannel);//������̨�����ĵ�½�����ͨ���š�
	bool SetLoginID(LLONG lLoginID);
	bool SetChannel(int nChannel);

	bool PtzBasicControl(int nType, int nStep, bool bStop = false);//��̨����,��ͷ����Ȧ�������Ŀ���
	// bool PtzMenuControl(int nType);//��̨�˵�����
	bool PtzFastGo(int nX, int nY, int nZoom,bool isabsolute);//��ά��λ����
	void GetPtzCapacity(LLONG g_lLoginHandle);
	// bool PtzRotate(int nType);//ˮƽ��ת
	// bool PtzAuxi(int nType, int nAuxi);//��������
	// bool PtzLineScan(int nType);//����ɨ��
	// bool PtzLoop(int nType, int nGroup, int nPresetData, bool bBeginLoop = false);//Ѳ��
	// bool PtzPreset(int nType, int nPresetData);//Ԥ�Ƶ�
	// bool PtzMode(int nType, int nGroup);//��̨Ѳ��
	
protected://data member
    LLONG	                        m_lLoginID;//�豸��½���
	int				m_nChannel;//����ͨ��

protected://method member
	bool PtzControl(int nType, int nParam1, int nParam2, int nParam3, bool bStop = false);
};

#endif // !defined(AFX_PTZ_H__3CBE7307_BC91_490C_91E9_B08535C6C7F4__INCLUDED_)
