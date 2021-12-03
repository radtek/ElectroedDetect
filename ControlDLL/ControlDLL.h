#pragma once

#ifdef _DLL_EXPORTS
#define DLL_API _declspec(dllexport)
#else
#define DLL_API _declspec(dllimport)
#endif

namespace ZC
{
	typedef struct tagPointF
	{
		float x, y;

		tagPointF() {
			x = 0; y = 0; }

		tagPointF(float X, float Y) {
			x = X; y = Y;
		}
	}PointF;

	typedef struct tagPointI
	{
		int x, y;

		tagPointI() {
			x = 0; y = 0;
		}

		tagPointI(int X, int Y) {
			x = X; y = Y;
		}
	}PointI;

	typedef struct tagRect
	{
		PointF p1, p3;

		tagRect() {
			p1.x = 0; p1.y = 0;
			p3.x = 0; p3.y = 0;
		}

		tagRect(PointF P1, PointF P3) {
			p1 = P1; p3 = P3;
		}

		tagRect(float x1, float y1, float x2, float y2) {
			p1.x = x1; p1.y = y1;
			p3.x = x2; p3.y = y2;
		}
		void Init() {
			p1.x = 0; p1.y = 0;
			p3.x = 0; p3.y = 0;
		}
	}Rect;
}