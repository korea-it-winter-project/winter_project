#pragma once
#include "pch.h"

#define xx -9

class utils {
public:
	static void DrawText(HDC hdc, Vector pos, const WCHAR str[1024]) {
		::TextOut(hdc, (int)pos.x, (int)pos.y, str, lstrlen(str));
	}
	static void DrawRect(HDC hdc, Vector pos, int w, int h) {
		::Rectangle(hdc, (int)(pos.x - w / 2), (int)(pos.y - h / 2), (int)(pos.x + w / 2), (int)(pos.y + h / 2));
	};
	static void DrawCircle(HDC hdc, Vector pos, int r) {
		::Ellipse(hdc, (int)(pos.x - r / 2), (int)(pos.y - r / 2), (int)(pos.x + r / 2), (int)(pos.y + r / 2));
	}

    // 길찾기 함수
    int smt(int n, int* dat, int MR, int MC, int sdir1[]) {
        int i, j, dir;
        do {
            j = 0;
            for (i = 0; i < MR * MC; i++) {
                if (*(dat + i) == n) {
                    j++;
                    for (dir = 1; dir < 5; dir++) {
                        int newRow = i / MC + sdir1[dir] / MC;
                        int newCol = i % MC + sdir1[dir] % MC;
                        if (newRow >= 0 && newRow < MR && newCol >= 0 && newCol < MC) {
                            int* p = dat + newRow * MC + newCol; // 1D 배열 인덱스 계산
                            if (!*p) *p = n + 1;
                            else if (*p == 999) {
                                if (!quit) quit = i; // 도착지
                                if (quit && mptr == 0) quit2 = i; // 도착지-1
                                else if (quit && !quit2) quit2 = i + sdir1[dir]; // 도착지-1
                                path[mptr++] = dir;
                                *(dat + i) = 999; // 현재 위치를 방문 처리
                                return 1;
                            }
                        }
                    }
                }
            }
        } while (j && smt(n + 1, dat, MR, MC,sdir1));
        return 0;
    }

    void RunPathfinding(int* MainMap, int MR, int MC) {
        int sdir1[5] = { 0,-MR,1,MR,-1 }; // 앞, 오른쪽, 뒤, 왼
        // 동적 배열로 변환
        int* dat = new int[MR * MC];
        for (int i = 0; i < MR * MC; i++) {
            dat[i] = MainMap[i];
        }
        for (int i = 0; i < MR; i++) {
            for (int j = 0; j < MC; j++) {
                printf("%3d ", *(dat + (i * MR) + j));
            }
            printf("\n\n");
        }
        // 길찾기 함수 호출
        printf("%d\n",smt(1, dat, MR, MC,sdir1));
        

        // 결과 출력
        for (int i = 0; i < mptr; i++) {
            int direction = path[i];
            int x = direction / MC;
            int y = direction % MC;
            // 경로 출력 (여기서는 단순히 인덱스 출력)
            printf("경로: (%d, %d)\n", x, y);
        }
        for (int i = 0; i < MR; i++) {
            for (int j = 0; j < MC; j++) {
                printf("%3d ", *(dat + (i * MR) + j));
            }
            printf("\n\n");
        }
        // 동적 메모리 해제
        delete[] dat;
    }

private:
    int path[50], mptr = 0, mptr2 = 0, quit = 0, quit2 = 0;
};