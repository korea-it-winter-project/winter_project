#pragma once
#include "pch.h"

#define xx -9

class utils {
public:
    int* GetPath() { return path; };
    int GetPathLength() { return mptr; }
    //int* GetDirection() { return directions; }

	static void DrawText(HDC hdc, Vector pos, const WCHAR str[1024]) {
		::TextOut(hdc, (int)pos.x, (int)pos.y, str, lstrlen(str));
	}
	static void DrawRect(HDC hdc, Vector pos, int w, int h) {
		::Rectangle(hdc, (int)(pos.x - w / 2), (int)(pos.y - h / 2), (int)(pos.x + w / 2), (int)(pos.y + h / 2));
	};
	static void DrawCircle(HDC hdc, Vector pos, int r) {
		::Ellipse(hdc, (int)(pos.x - r / 2), (int)(pos.y - r / 2), (int)(pos.x + r / 2), (int)(pos.y + r / 2));
	}

    // ��ã�� �Լ�
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
                            int* p = dat + newRow * MC + newCol; // 1D �迭 �ε��� ���
                            if (!*p) *p = n + 1;
                            else if (*p == 999) {
                                if (!quit) quit = i; // ������
                                if (quit && mptr == 0) quit2 = i; // ������-1
                                else if (quit && !quit2) quit2 = i + sdir1[dir]; // ������-1
                                path[mptr++] = dir;
                                *(dat + i) = 999; // ���� ��ġ�� �湮 ó��
                                return 1;
                            }
                        }
                    }
                }
            }
        } while (j && smt(n + 1, dat, MR, MC,sdir1));
        return 0;
    }

    void RunPathfinding(const int* MainMap, int MR, int MC) {
        int sdir1[5] = { 0,-MC,1,MC,-1 }; // ��, ������, ��, ��
        // ���� �迭�� ��ȯ
        // �Է� �Ķ���� ��ȿ�� �˻�
    if (MainMap == nullptr) {
        std::cerr << "Error: MainMap is null." << std::endl;
        return;
    }
    if (MR <= 0 || MC <= 0) {
        std::cerr << "Error: Invalid map dimensions." << std::endl;
        return;
    }

    // �޸� �Ҵ� �� ���� ó��
    int* dat = nullptr;
    try {
        dat = new int[(MR ) * (MC )];
    } catch (std::bad_alloc& e) {
        std::cerr << "Error: Memory allocation failed: " << e.what() << std::endl;
        return;
    }

    // ������ ����
    for (int i = 0; i < (MR ) * (MC ); i++) {
        dat[i] = MainMap[i];
    }
        for (int i = 0; i < MR; i++) {
            for (int j = 0; j < MC; j++) {
                printf("%3d ", *(dat + (i * MC) + j));
            }
            printf("\n\n");
        }
        // ��ã�� �Լ� ȣ��
        printf("%d\n",smt(1, dat, MR, MC,sdir1));
        

        // ��� ���
        for (int i = mptr; i >= 0; i--) {
            int direction = path[i];
            //directions[ i ] = direction;
            int x = direction / MC;
            int y = direction % MC;
            // ��� ��� (���⼭�� �ܼ��� �ε��� ���)
            printf("���: (%d, %d)\n", x, y);
        }
        for (int i = 0; i < MR; i++) {
            for (int j = 0; j < MC; j++) {
                printf("%3d ", *(dat + (i * MC) + j));
            }
            printf("\n\n");
        }
        // ���� �޸� ����
        delete[] dat;
    }

private:
    int path[500], mptr = 0, mptr2 = 0, quit = 0, quit2 = 0;
    //int directions[ 100 ];
};