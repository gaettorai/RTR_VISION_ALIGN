#include "pch.h"
#include "connect_Baumer.h"
#include "RVisionDlg.h"

void connect_Baumer::Init()
{
	// 초기화 진행
	systemList = NULL;
	pSystem = NULL;
	interfaceList = NULL;
	pInterface = NULL;
	bufferList = NULL;
	pBuffer = NULL;

	m_Cam_set = new Cam_set[5];
	m_camera_set = new Cam_set[5];

	for (int i = 0; i < CamCount; i++)
	{
		m_Cam_set[i].m_buf = NULL;
		m_camera_set[i].m_buf = NULL;

		m_Cam_set[i].m_updisplay = 0;
		m_camera_set[i].m_updisplay = 0;

		Status[i] = FALSE;
	}

	m_cameracount = 0;
}

void connect_Baumer::Open()
{
	// Camera Open

	systemList = SystemList::GetInstance();
	systemList->Refresh();

	for (SystemList::iterator sysIterator = systemList->begin(); sysIterator != systemList->end(); sysIterator++)
	{
		sysIterator->second->Close();
		sysIterator->second->Open();
		sSystemID = sysIterator->first;
		pSystem = (*systemList)[sSystemID];
		interfaceList = sysIterator->second->GetInterfaces();
		interfaceList->Refresh(100);

		for (InterfaceList::iterator ifIterator = interfaceList->begin(); ifIterator != interfaceList->end(); ifIterator++)
		{
			ifIterator->second->Open();
			deviceList = ifIterator->second->GetDevices();
			deviceList->Refresh(100);

			if (deviceList->size() == 0)
				ifIterator->second->Close();

			else
			{
				//DEVICE INFORMATION BEFORE OPENING
				for (DeviceList::iterator devIterator = deviceList->begin(); devIterator != deviceList->end(); devIterator++)
				{
					sInterfaceID = ifIterator->first;
					if (sInterfaceID != "")
					{
						m_Cam_set[m_cameracount].pDevicef = devIterator->second;
						m_Cam_set[m_cameracount].name = devIterator->second->GetDisplayName();

						if (m_Cam_set[m_cameracount].name == CamName1)
						{
							m_camera_set[0].pDevicef = m_Cam_set[m_cameracount].pDevicef;
							m_camera_set[0].name = m_Cam_set[m_cameracount].name;

							Status[0] = TRUE;
						}

						else if (m_Cam_set[m_cameracount].name == CamName2)
						{
							m_camera_set[1].pDevicef = m_Cam_set[m_cameracount].pDevicef;
							m_camera_set[1].name = m_Cam_set[m_cameracount].name;

							Status[1] = TRUE;
						}

						else if (m_Cam_set[m_cameracount].name == CamName3)
						{
							m_camera_set[2].pDevicef = m_Cam_set[m_cameracount].pDevicef;
							m_camera_set[2].name = m_Cam_set[m_cameracount].name;

							Status[2] = TRUE;
						}

						else if (m_Cam_set[m_cameracount].name == CamName4)
						{
							m_camera_set[3].pDevicef = m_Cam_set[m_cameracount].pDevicef;
							m_camera_set[3].name = m_Cam_set[m_cameracount].name;

							Status[3] = TRUE;
						}

						else if (m_Cam_set[m_cameracount].name == CamName5)
						{
							m_camera_set[4].pDevicef = m_Cam_set[m_cameracount].pDevicef;
							m_camera_set[4].name = m_Cam_set[m_cameracount].name;

							Status[4] = TRUE;
						}

						m_cameracount++;
					}
				}
			}
		}
	}

	// 카메라의 갯수만큼 data 저장
	for (int i = 0; i < CamCount; i++)
	{
		if (Status[i] == true)
		{
			m_camera_set[i].pDevicef->Open();
			m_camera_set[i].datastreamListf = m_camera_set[i].pDevicef->GetDataStreams();

			m_camera_set[i].datastreamListf->Refresh();

			m_camera_set[i].pDataStreamf = m_camera_set[i].datastreamListf->begin()->second;
			m_camera_set[i].pDataStreamf->Open();

			m_camera_set[i].bufferListf = m_camera_set[i].pDataStreamf->GetBufferList();

			for (int j = 0; j < 4; j++)
			{
				pBuffer = new BGAPI2::Buffer();
				m_camera_set[i].bufferListf->Add(pBuffer);
			}

			for (BufferList::iterator bufIterator = m_camera_set[i].bufferListf->begin();
				bufIterator != m_camera_set[i].bufferListf->end(); bufIterator++)
			{
				bufIterator->second->QueueBuffer();
			}

			m_camera_set[i].pDataStreamf->RegisterNewBufferEvent(Events::EVENTMODE_EVENT_HANDLER);
		}
	}
}


void connect_Baumer::Connect()
{
	// 카메라의 이름을 통해 연결된 카메라가 어떠한 종류인지 확인.

	for (int i = 0; i < CamCount; i++)
	{
		// ALIGN_1
		if (Status[i] == true)
		{
			if (i == 0)
				m_camera_set[i].pDataStreamf->RegisterNewBufferEventHandler(m_camera_set[i].pDataStreamf,
					(Events::NewBufferEventHandler)&BufferHandler1);

			else if (i == 1)
				m_camera_set[i].pDataStreamf->RegisterNewBufferEventHandler(m_camera_set[i].pDataStreamf,
					(Events::NewBufferEventHandler)&BufferHandler2);

			else if (i == 2)
				m_camera_set[i].pDataStreamf->RegisterNewBufferEventHandler(m_camera_set[i].pDataStreamf,
					(Events::NewBufferEventHandler)&BufferHandler3);

			else if (i == 3)
				m_camera_set[i].pDataStreamf->RegisterNewBufferEventHandler(m_camera_set[i].pDataStreamf,
					(Events::NewBufferEventHandler)&BufferHandler4);

			else if (i == 4)
				m_camera_set[i].pDataStreamf->RegisterNewBufferEventHandler(m_camera_set[i].pDataStreamf,
					(Events::NewBufferEventHandler)&BufferHandler5);
		}

		if (Status[i] == true)
		{
			m_camera_set[i].m_SizeX = m_camera_set[i].pDevicef->GetRemoteNode("Width")->GetDouble();
			m_camera_set[i].m_SizeY = m_camera_set[i].pDevicef->GetRemoteNode("Height")->GetDouble();

			m_camera_set[i].pDevicef->GetRemoteNode("TriggerMode")->SetString("Off");

			m_camera_set[i].m_pBitmapInfo = (BITMAPINFO*) new BYTE[sizeof(BITMAPINFO) + 255 * sizeof(RGBQUAD)];

			m_camera_set[i].m_pBitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			m_camera_set[i].m_pBitmapInfo->bmiHeader.biPlanes = 1;
			m_camera_set[i].m_pBitmapInfo->bmiHeader.biBitCount = 8;
			m_camera_set[i].m_pBitmapInfo->bmiHeader.biCompression = BI_RGB;

			m_camera_set[i].m_pBitmapInfo->bmiHeader.biSizeImage = 0;
			m_camera_set[i].m_pBitmapInfo->bmiHeader.biXPelsPerMeter = 0;
			m_camera_set[i].m_pBitmapInfo->bmiHeader.biYPelsPerMeter = 0;
			m_camera_set[i].m_pBitmapInfo->bmiHeader.biClrUsed = 0;
			m_camera_set[i].m_pBitmapInfo->bmiHeader.biClrImportant = 0;

			for (int j = 0; j < 256; j++)
			{
				m_camera_set[i].m_pBitmapInfo->bmiColors[j].rgbBlue = (BYTE)j;
				m_camera_set[i].m_pBitmapInfo->bmiColors[j].rgbGreen = (BYTE)j;
				m_camera_set[i].m_pBitmapInfo->bmiColors[j].rgbRed = (BYTE)j;
				m_camera_set[i].m_pBitmapInfo->bmiColors[j].rgbReserved = 0;
			}

			m_camera_set[i].pDataStreamf->StartAcquisition(-1);
			m_camera_set[i].pDevicef->GetRemoteNode("AcquisitionStart")->Execute();
		}
	}
}