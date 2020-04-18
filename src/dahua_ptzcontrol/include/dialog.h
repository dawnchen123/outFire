#ifndef DIALOG_H
#define DIALOG_H

#include "dhnetsdk.h"

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

public:
    void ShowMessage();//
    void PTZForBasicControl(int nType, bool bStop);//
    void PTZForPresetControl( int nType, int nPresetNo );//
    void PTZForAutoTour( int nType, int nTourNo, int nPresetNo, bool bAutoTour );//
    void PTZForPattem( int nType, int nPattemNo );//
    void PTZForScan( int nType );//
    void PTZForPan( int nType );//
    void PTZForSIT( int nX, int nY, int nZoom);//
    void PTZForAUX( int nType, int nAuxNo );//
    void PTZForMenu( int nType);//
protected:
    bool eventFilter(QObject *obj, QEvent *event);//
protected:
    bool InitData();//
    bool UnInitData();//
private:
    LLONG      m_lLoginHandle;   ///��½���
    QTimer     *m_counter;       ///��ʱ��
    int        m_bMessageTip;
    int        m_nChannelIndex;  ///��ǰͨ��
    int        m_nCtrlParam;     /// ��̨���Ʋ���
private:
    Ui::Dialog *ui;

private slots:
    void on_ButDelPatterm_clicked();//
    void on_ButStopPatterm_clicked();//
    void on_ButStartPatterm_clicked();//
    void on_ButStopProgram_clicked();//
    void on_ButStartProgram_clicked();//
    void on_ButStopPan_clicked();//
    void on_ButStartPan_clicked();//
    void on_butStopScan_clicked();//
    void on_ButStartScan_clicked();//
    void on_ButLimitRight_clicked();//
    void on_ButLimitLeft_clicked();//
    void on_ButCloseAUX_clicked();//
    void on_ButOpenAUX_clicked();//
    void on_ButSIT_clicked();//
    void on_ButMenuCancel_clicked();//
    void on_ButMenuOK_clicked();//
    void on_ButCloseMenu_clicked();//
    void on_ButOpenMenu_clicked();//
    void on_ButMenuDown_clicked();//
    void on_ButMenuRight_clicked();//
    void on_ButMenuUP_clicked();//
    void on_ButMenuLeft_clicked();//
    void on_ButDelTourNo_clicked();//
    void on_ButDelTourPreset_clicked();//删除自动旅行点
    void on_ButAddTour_clicked();//增加自动旅行点
    void on_ButStopTour_clicked();//取消
    void on_ButStartTour_clicked();//自动旅行
    void on_pushButGotoPreset_clicked();//perset NO  前往预设点
    void on_pushButPresetDel_clicked();//   perset NO  删除预设点
    void on_pushButSet_clicked();//perset NO  设置预设点
    void on_pushButDAperture_released();//光圈减少
    void on_pushButDAperture_pressed();//
    void on_pushButAperture_released();//光圈增加
    void on_pushButAperture_pressed();//
    void on_pushButDFocus_released();//焦距减少
    void on_pushButDFocus_pressed();//
    void on_pushButAFocus_released();//焦距增加
    void on_pushButAFocus_pressed();//
    void on_pushButDZoom_released();//（缩放）变焦减少
    void on_pushButDZoom_pressed();//
    void on_pushButAZoom_released();//（缩放）变焦增加
    void on_pushButAZoom_pressed();//
    void on_pushButRDown_released();//右下
    void on_pushButRDown_pressed();//
    void on_pushButDown_released();//下
    void on_pushButDown_pressed();//
    void on_pushButLeftDown_released();//左下
    void on_pushButLeftDown_pressed();//
    void on_pushButRight_released();//右
     void on_pushButRight_pressed();//
    void on_pushButRightUP_pressed();//右上
    void on_pushButRightUP_released();//   
    void on_pushButLeft_released();//左
    void on_pushButLeft_pressed();//
    void on_comboxCtrlParam_activated(QString );//云台运动参数激活
    void on_comboxChannel_activated(QString );//视频通道激活
    void on_pushButUp_released();//上键
    void on_pushButUp_pressed();//
    void on_pushButLeftUp_released();//左上键
    void on_pushButLeftUp_pressed();//
    void on_Logout_clicked();//检查登出
    void on_Login_clicked();//检查登录
};

#endif // DIALOG_H
