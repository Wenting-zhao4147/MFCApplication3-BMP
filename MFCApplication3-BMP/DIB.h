#pragma once
#pragma pack(2) // ����
struct BMPFileHeader {
	UINT16 bfType;		 // ˵��λͼ����  2�ֽ�
	DWORD bfSize;		 // ˵��λͼ��С  4�ֽ�
	UINT16 bfReserved1;  // �����֣�����Ϊ0  2�ֽ�
	UINT16 bfReserved2;  // �����֣�����Ϊ0  2�ֽ�
	DWORD bfOffBits;	 // ���ļ�ͷ��ʵ�ʵ�ͼ�����ݵ�ƫ�����Ƕ���  4�ֽ�
};

struct BMPInfoHeader {
	DWORD biSize;		// ˵���ýṹһ����Ҫ���ֽ��� 2�ֽ�
	LONG biWidth;		// ˵��ͼƬ�Ŀ�ȣ�������Ϊ��λ 4�ֽ�
	LONG biHeight;		// ˵��ͼƬ�ĸ߶ȣ�������Ϊ��λ 4�ֽ�
	WORD biPlanes;		// ��ɫ�壬������Ϊ1  2���ֽ�
	WORD biBitCount;		// ˵��ÿ������ռ����bitλ������ͨ������ֶ�֪��ͼƬ����  2���ֽ�
	DWORD biCompression;	// ˵��ʹ�õ�ѹ���㷨 2���ֽ� ��BMP��ѹ���㷨��
	DWORD biSizeImage;		// ˵��ͼ���С   2���ֽ�
	LONG biXPelsPerMeter;	// ˮƽ�ֱ��� 4�ֽ�  ��λ������/��
	LONG biYPelsPerMeter;	// ��ֱ�ֱ���4�ֽ�
	DWORD biClrUsed;		// ˵��λͼʹ�õ���ɫ������ 4�ֽ�
	DWORD biClrImportant;	// 4�ֽ�
};

struct RGBQuad {
	BYTE    rgbBlue;		// ��ɫ 1�ֽ�
	BYTE    rgbGreen;		//��ɫ 1�ֽ�
	BYTE    rgbRed;			// ��ɫ 1�ֽ�
	BYTE    rgbReserved;	// ������ 1�ֽ�
};

// DIB��
class DIB
{
public:
	BMPFileHeader* bfh;		// �ļ�ͷ
	BMPInfoHeader* bih;		// ��Ϣͷ
	RGBQuad* quad;			// ��ɫ��
	unsigned char *bdata;	// ���
	int bwidth;		// ��
	int bheight;	// ��
	int real_size;	// ��ʵ��С

public:
	DIB();	// ���캯��
	~DIB(); // ��������

	void read(const CString& fileName);		// ��ȡλͼ�ļ�
	void write(const CString& fileName);	// д��λͼ�ļ�
};

