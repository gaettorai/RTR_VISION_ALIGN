#pragma once

class Cam_set;
class connect_Baumer
{
public:

	Cam_set* m_Cam_set;
	Cam_set* m_camera_set;

	BGAPI2::SystemList* systemList;
	BGAPI2::System* pSystem;
	BGAPI2::String sSystemID;
	BGAPI2::InterfaceList* interfaceList;
	BGAPI2::Interface* pInterface;
	BGAPI2::String sInterfaceID;

	BGAPI2::DeviceList* deviceList;
	BGAPI2::Device* pDevice;
	BGAPI2::String sDeviceID;

	BGAPI2::BufferList* bufferList;
	BGAPI2::Buffer* pBuffer;
	BGAPI2::String sBufferID;
	
	BOOL Status[CamCount];

	void Init();
	void Open(); 
	void Connect();

	int m_cameracount;

};


class Cam_set
{
public:
	PVOID m_buf;
	BITMAPINFO* m_pBitmapInfo;
	int m_SizeX; // ī�޶��� ���� ����� �޾ƿ� ����
	int m_SizeY; // ī�޶��� ���� ����� �޾ƿ� ����
	int m_updisplay; // �̹����� bmp�� ���÷��� �Ҷ� ����� �÷��� ����

	CString name;	// ī�޶� �̸�

	BGAPI2::DeviceList* deviceListf;
	BGAPI2::Device* pDevicef;
	BGAPI2::String sDeviceIDf;

	BGAPI2::DataStreamList* datastreamListf;
	BGAPI2::DataStream* pDataStreamf;
	BGAPI2::String sDataStreamIDf;

	BGAPI2::BufferList* bufferListf;
	BGAPI2::Buffer* pBufferf;
	BGAPI2::String sBufferIDf;
};