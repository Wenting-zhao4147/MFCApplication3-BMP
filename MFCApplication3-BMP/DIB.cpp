#include "pch.h"
#include "DIB.h"



DIB::DIB() {
	real_size = 0;
	bwidth = 0;
	bheight = 0;
	maxp = 0;
	minp = 255;
	threshold = 0;

	EQU = new INT[256];
	CDF = new DOUBLE[256];

	ph = NULL;
	bfh = NULL;
	bih = NULL;
	quad = NULL;
	bdata = NULL;
}
DIB::~DIB() {
	delete[] bdata;
	ph = NULL;
	bfh = NULL;
	bih = NULL;

	EQU = NULL;
	CDF = NULL;

	quad = NULL;
	bdata = NULL;
}

void DIB::read(const CString& fileName)
{
	// �ļ���ȡ
	CFile file;
	file.Open(fileName, CFile::modeRead);
	real_size = (DWORD)file.GetLength();
	bdata = new unsigned char[real_size];

	file.Read(bdata, real_size);
	file.Close();

	// ͷ��Ϣ
	bfh = (BMPFileHeader*)bdata;
	bih = (BMPInfoHeader*)(bdata + sizeof(BMPFileHeader));

	// ��ɫ��
	quad = (RGBQuad*)(bdata + sizeof(BMPFileHeader) + sizeof(BMPInfoHeader));

	//ͼƬ�߶� ���
	bheight = bih->biHeight; 
	bwidth = bih->biWidth;

	//ͼƬָ��
	ph = (BYTE*)(bdata + bfh->bfOffBits);
}

void DIB::write(const CString& fileName)
{
	CFile new_file;
	new_file.Open(fileName, CFile::modeCreate | CFile::modeWrite);
	try {
		new_file.Write(bdata, real_size);
	}
	catch (CException* pe) {
		pe->Delete();
		AfxMessageBox(_T("д�����"));
		new_file.Close();
	}
	new_file.Close();
}

void DIB::equalizated()
{
	if (maxp == 0)
		return;
	for (int i = 0; i < 256; i++)
	{
		EQU[i] = (int)(255.0 * CDF[i] + 0.5);
	}
	int iw8 = bwidth;
	iw8 += 3;
	iw8 -= iw8 % 4;
	for (int i = 0; i < bheight; i++)
	{
		for (int j = 0; j < bwidth; j++)
		{
			UINT8 index = ph[i * iw8 + j];
			ph[i * iw8 + j] = EQU[index];
		}
	}
}

void DIB::standardized()
{
}

void DIB::getExtVal(DOUBLE *arr)
{
	UINT16 h = bheight;
	UINT16 w = bwidth;
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			UINT8 index = *(UINT8*)(ph + x + y * w);
			if (index > maxp) maxp = index;
			if (index < minp) minp = index;
			arr[index]++;
		}
	}
	// ��һ��
	int n = h * w;
	for (int i = 0; i < 256; i++) {
		arr[i] = (double)arr[i] / n;
		if (0 == i) CDF[i] = arr[i];
		else CDF[i] = CDF[i - 1] + arr[i]; //����CDF;
	}
}