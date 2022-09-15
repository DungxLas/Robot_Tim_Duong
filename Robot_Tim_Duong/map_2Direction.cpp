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

//struct mapRobot
//{
//    int status, locationY, locationX, target;
//    mapRobot *left, *right, *parent;
//    char faceDirection;
//};

struct bot
{
    int locationY, locationX;
    bot *left, *right, *parent;
    char faceDirection;
};

// Robot đi thẳng
bot* goHead(bot *&robot, char faceDirection) {
    bot *q = new bot;
    switch (faceDirection) {
        case 's':
            q->locationY = robot->locationY++;
            q->locationX = robot->locationX;
            q->faceDirection = 's';
            break;
        case 'd':
            q->locationY = robot->locationY;
            q->locationX = robot->locationX++;
            q->faceDirection = 'd';
            break;
        case 'w':
            q->locationY = robot->locationY--;
            q->locationX = robot->locationX;
            q->faceDirection = 'w';
            break;
        case 'a':
            q->locationY = robot->locationY;
            q->locationX = robot->locationX--;
            q->faceDirection = 'a';
            break;
    }
    q->left = q->right = NULL;
    q->parent = robot;
    robot->left = q;
    
    return q;
}

// Robot rẽ trái
bot* goLeft(bot *&robot, char faceDirection) {
    bot *q = new bot;
    switch (faceDirection) {
        case 's':
            q->locationY = robot->locationY;
            q->locationX = robot->locationX++;
            q->faceDirection = 'd';
            break;
        case 'd':
            q->locationY = robot->locationY--;
            q->locationX = robot->locationX;
            q->faceDirection = 'a';
            break;
        case 'w':
            q->locationY = robot->locationY;
            q->locationX = robot->locationX--;
            q->faceDirection = 'a';
            break;
        case 'a':
            q->locationY = robot->locationY++;
            q->locationX = robot->locationX;
            q->faceDirection = 's';
            break;
    }
    q->left = q->right = NULL;
    q->parent = robot;
    robot->right = q;
    
    return q;
}

// Cho Robot tìm đường
void robotFindWay_NoRecursion(bot *botStart, map Map) {
    // Khởi tạo robot bắt đầu đi từ gốc map
    botStart->locationY = 0;
    botStart->locationX = 0;
    botStart->parent= botStart->left = botStart->right = NULL;
    botStart->faceDirection = 's';
    
    // Robot bắt đầu tim đường
    bot *p = botStart;
    while (true) {
        p = goHead(p, p->faceDirection);
        p = goLeft(p, p->faceDirection);
    }
}

//// Khởi tạo cây từ map
//void iNit(mapRobot *&mapRobot) {
//    mapRobot = NULL;
//}
//
//// Khởi tạo Node
//mapRobot* getNode(int status) {
//    mapRobot* p = new mapRobot;
//    if (p == NULL) {
//        return NULL;
//    }
//    p->status = status;
//    p->locationY = p->locationX = p->target = 0;
//    p->left = p->right = p->parent = NULL;
//    p->faceDirection = 's';
//    return p;
//}
//
//// Khởi tạo cây từ Map
//void creatMap_NoRecursion(mapRobot *&mapTree, map Map) {
//    mapRobot *p = NULL;
//    mapRobot *q = mapTree;
//    for (int i = 0; i < Map.numRow; i++) {
//        q = getNode(Map.location[i][0]);
//        q->locationY = i;
//        q->locationX = 0;
//        if (q->locationY == Map.targetY && q->locationX == Map.targetX) {
//            q->target = 1;
//        }
//        q->parent = p;
//        p = q;
//        mapRobot *k = q;
//        //cout << "\n" << q->status << "(" << q->locationY << "," << p->locationX << ";" << q->target << ")" << " ";
//        q = q->right;
//        for (int j = 1; j < Map.numCol; j++) {
//            q = getNode(Map.location[i][j]);
//            q->locationY = i;
//            q->locationX = j;
//            if (q->locationY == Map.targetY - 1 && q->locationX == Map.targetX - 1) {
//                q->target = 1;
//            }
//            q->parent = p;
//            p = q;
//            //cout << q->status << "(" << q->locationY << "," << p->locationX << ";" << q->target << ")" << " ";
//            q = q->right;
//        }
//        q = k->left;
//        p = k;
//    }
//}
//
//// Tìm vị trí trên Map
//mapRobot* findLocation(mapRobot *mapTree, int locationY, int locationX) {
//    mapRobot *p = mapTree;
//    while (p != NULL) {
//        mapRobot *q = p;
//        while (p != NULL) {
//            if (p->locationY == locationY && p->locationX == locationX) {
//                return p;
//            }
//            p = p->right;
//        }
//        p = q->left;
//    }
//    return p;
//}
//
//// Robot đi thẳng
//mapRobot* goHead(mapRobot *mapTree, mapRobot *robot, char faceDirection) {
//    switch (faceDirection) {
//        case 's':
//            if (robot->left == NULL || robot->status == 1) {
//                return NULL;
//            }
//            else {
//                return robot->left;
//            }
//            break;
//
//        case 'd':
//            if (robot->right == NULL || robot->status == 1) {
//                return NULL;
//            }
//            else {
//                return robot->right;
//            }
//            break;
//        case 'w':
//            mapRobot *p = findLocation(mapTree, robot->locationY - 1, robot->locationX);
//            if (p == NULL || p->status == 1) {
//                return NULL;
//            }
//            else {
//                return p;
//            }
//            break;
//    }
//}
//
//// Cho Robot tìm đường
//void robot_NoRecursion(mapRobot *mapTree) {
//    mapRobot *robot = mapTree;
//    while (true) {
//        if (robot->faceDirection == 's') {
//            // Đi thẳng
//            if (robot->left == NULL) {
//
//            }
//            robot = robot->left;
//            robot->faceDirection = 's';
//            // Rẽ trái
//            robot = robot->right;
//            robot->faceDirection = 'd';
//        }
//        else if (robot->faceDirection == 'd') {
//            // Đi thẳng
//            robot = robot->right;
//            robot->faceDirection = 'd';
//            // Rẽ trái
//            robot = robot->right;
//            robot->faceDirection = 'w';
//        }
//        else if (robot->faceDirection == 'd') {
//            // Đi thẳng
//            robot = robot->right;
//            robot->faceDirection = 'd';
//            // Rẽ trái
//            robot = robot->right;
//            robot->faceDirection = 'w';
//        }
//        else if (robot->faceDirection == 'd') {
//            // Đi thẳng
//            robot = robot->right;
//            robot->faceDirection = 'd';
//            // Rẽ trái
//            robot = robot->right;
//            robot->faceDirection = 'w';
//        }
//    }
//}
//
//// Giải phóng Map
//void deleteMap_NoRecursion(mapRobot *&mapTree) {
//    if (mapTree != NULL) {
//        mapRobot *parentRow = NULL;
//        mapRobot *q = mapTree;
//        while (true) {
//            if (q->left != NULL) {
//                q = q->left;
//            }
//            else {
//                mapRobot *firstRow = q;
//                mapRobot *parentCol = NULL;
//                while (true) {
//                    if (q->right != NULL) {
//                        q = q->right;
//                    }
//                    else {
//                        parentCol = q->parent;
//                        delete q;
//                        if (parentCol == firstRow) {
//                            break;
//                        }
//                        else {
//                            q = parentCol;
//                        }
//                    }
//                }
//                parentRow = q->parent;
//                delete q;
//                if (parentRow == NULL) {
//                    break;
//                }
//                else {
//                    q = parentRow;
//                }
//            }
//        }
//    }
//}

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
    
//    mapRobot *mapRobot;
//    iNit(mapRobot);
//    creatMap_NoRecursion(mapRobot, Map);
    
    
    
    // Trước khi kết thúc chương trình phải giải phóng bộ nhớ đã cấp phát cho con trỏ cấp 2 Map.location
    for( int i = 0; i < Map.numRow; i++) {
        delete[] Map.location[i];
    }
    delete[] Map.location;
    
    // Giải phóng cây
    deleteMap_NoRecursion(mapRobot);
    
    return 0;
}
