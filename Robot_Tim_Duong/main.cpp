//
//  main.cpp
//  Robot_Tim_Duong
//
//  Created by PHẠM HÙNG DŨNG on 13/09/2022.
//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct map
{
    int numRow, numCol;
    int **location;
    int targetY, targetX;
};

struct mapRobot
{
    int status, locationY, locationX, target;
    mapRobot *left, *right, *parent, *faceDirection;
};

// Khởi tạo cây từ map
void iNit(mapRobot *&mapRobot) {
    mapRobot = NULL;
}

// Khởi tạo Node
mapRobot* getNode(int status) {
    mapRobot* p = new mapRobot;
    if (p == NULL) {
        return NULL;
    }
    p->status = status;
    p->locationY = p->locationX = p->target = 0;
    p->left = p->right = p->parent = p->faceDirection = NULL;
    return p;
}

// Khởi tạo cây từ Map
int creatMap_NoRecursion(mapRobot *&mapRobot, map Map) {
    if (mapRobot == NULL) {
        mapRobot = getNode(status);
    }
    
}

void docFileInput(string tenFile, map &Map) {
    ifstream fileIn;
    fileIn.open(tenFile, ios_base::in);
    
    if(!fileIn)
    {
        cout << "\nKhong tim thay tap tin " << tenFile;
        fileIn.close();
        return;
    }
    
    // Nếu vẫn chạy được xuống dưới đây tức là có tồn tại tập tin => đọc dữ liệu vào cây
    //int dem = 0;
    cout << "\nDu lieu trong tap tin " << tenFile << " da duoc doc thanh cong";
    
    fileIn >> Map.numRow;
    fileIn >> Map.numCol;
    
    Map.location = new int*[Map.numRow];
    for (int i = 0; i < Map.numCol; i++) {
        Map.location[i] = new int[Map.numCol];
    }
    for (int i = 0; i < Map.numRow; i++) {
        for(int j = 0; j < Map.numCol; j++) {
            fileIn >> Map.location[i][j];
        }
    }
    
    fileIn >> Map.targetY;
    fileIn >> Map.targetX;
    
    fileIn.close();
}



int main() {
    map Map;
    docFileInput("/Users/phamhungdung/CoDe/C:C++/Robot_Tim_Duong/input.txt", Map); // Có câp phát bộ nhớ cho con trỏ cấp 2 Map.location
    
    mapRobot *mapRobot;
    iNit(mapRobot);
    
    // Trước khi kết thúc chương trình phải giải phóng bộ nhớ đã cấp phát cho con trỏ cấp 2 Map.location
    for( int i = 0; i < Map.numRow; i++) {
        delete[] Map.location[i];
    }
    delete[] Map.location;
    
    return 0;
}
