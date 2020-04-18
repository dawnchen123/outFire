#ifndef GETTEMP_H
#define GETTEMP_H
// 温度状态回调函数
void CALLBACK cbRadiometryAttachCB(LLONG lAttachHandle, NET_RADIOMETRY_DATA* pBuf, int
nBufLen, LDWORD dwUser)
{
int nPixel = pBuf->stMetaData.nWidth*pBuf->stMetaData.nHeight;
unsigned short *pGray = new unsigned short[nPixel];
memset(pGray,0,nPixel);
float *pTemp = new float[nPixel];
memset(pTemp,0,nPixel);
CLIENT_RadiometryDataParse(pBuf,pGray,pTemp);
delete[] pGray;
delete[] pTemp;
}
// 订阅热图
NET_IN_RADIOMETRY_ATTACH stIn = {sizeof(stIn), 1, cbRadiometryAttachCB};
NET_OUT_RADIOMETRY_ATTACH stOut = {sizeof(stOut)};
LLONG attachHandle = CLIENT_RadiometryAttach(loginId, &stIn, &stOut, 3000);
if (NULL == attachHandle)
{
// 订阅失败
}
// 通知设备开始采集数据
NET_IN_RADIOMETRY_FETCH stInFetch = {sizeof(stInFetch), 1};
NET_OUT_RADIOMETRY_FETCH stOutFetch = {sizeof(stOutFetch)};
CLIENT_RadiometryFetch(m_lLoginID, &stInFetch, &stOutFetch, 3000);
// 使用完毕,取消订阅热图
CLIENT_RadiometryDetach(attachHandle);

#endif