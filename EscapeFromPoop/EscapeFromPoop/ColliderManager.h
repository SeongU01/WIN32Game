#pragma once
#include"WinApp.h"
#include"Object.h"
class ColliderManager
{
private:
	ColliderManager() {}
	~ColliderManager() {}
	static ColliderManager* instance;

public:

	bool ColliderAWithB(Object* A, Object* B,int AStatus,int BStatus)
	{
		
		HBITMAP Abitmap = A->GetBitMap(AStatus);
		HBITMAP Bbitmap = B->GetBitMap(BStatus);

		BITMAP AbitmapInfo, BbitmapInfo;

		GetObject(Abitmap, sizeof(BITMAP), &AbitmapInfo);
		GetObject(Bbitmap, sizeof(BITMAP), &BbitmapInfo);
		GetObject(A->GetBitMap(AStatus), sizeof(BITMAP), &AbitmapInfo);
		GetObject(B->GetBitMap(BStatus), sizeof(BITMAP), &BbitmapInfo);
		float AxMin = A->x;
		float AxMax = A->x + AbitmapInfo.bmWidth;
		float AyMin = A->y;
		float AyMax = A->y + AbitmapInfo.bmHeight;

		float BxMin = B->x;
		float BxMax = B->x + BbitmapInfo.bmWidth;
		float ByMin = B->y;
		float ByMax = B->y + BbitmapInfo.bmHeight;

		return (AxMin<BxMax && AxMax>BxMin
			&& AyMin<ByMax && AyMax>ByMax);
	}


	static ColliderManager* GetInstance();
	void DestroyInstance();
};