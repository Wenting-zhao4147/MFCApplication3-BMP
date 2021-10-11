#include "pch.h"
#include "DIB.h"

DIB::DIB() {
	real_size = 0;
	bwidth = 0;
	bheight = 0;
}
DIB::~DIB() {

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
