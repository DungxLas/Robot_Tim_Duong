//
//  main.cpp
//  Robot_Tim_Duong
//
//  Created by PHẠM HÙNG DŨNG on 13/09/2022.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct map
{
    int numRow, numCol;
    int **location;
    int targetY, targetX;
};

struct bot
{
    int locationY, locationX;
    bot *left, *right, *parent;
    char faceDirection;
    int thuTuDuyet = 0;
};

void docFileInput(string tenFile, map &Map) {
    ifstream fileIn;
    fileIn.open(tenFile, ios::in);
    
    if(!fileIn)
    {
        cout << "Không tìm thấy tập tin: " << tenFile;
        fileIn.close();
        return;
    }
    
    // Nếu vẫn chạy được xuống dưới đây tức là có tồn tại tập tin => đọc dữ liệu vào cây
    //int dem = 0;
    cout << "Dữ liệu trong tập tin " << tenFile << " đã được đọc thành công";
    
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

void ghiFileOutput(string tenFile, vector<string> outPut) {
    ofstream fileOut;
    fileOut.open(tenFile, ios::out);
    
    fileOut << to_string(outPut.size()) << endl;
    while (!outPut.empty()) {
        fileOut << outPut.back() << endl;
        outPut.pop_back();
    }
    
    fileOut.close();
}

// Robot đi thẳng
bot* goHead(bot *&robot) {
    bot *q = new bot;
    switch (robot->faceDirection) {
        case 's':
            q->locationY = robot->locationY + 1;
            q->locationX = robot->locationX;
            q->faceDirection = 's';
            break;
        case 'd':
            q->locationY = robot->locationY;
            q->locationX = robot->locationX + 1;
            q->faceDirection = 'd';
            break;
        case 'w':
            q->locationY = robot->locationY - 1;
            q->locationX = robot->locationX;
            q->faceDirection = 'w';
            break;
        case 'a':
            q->locationY = robot->locationY;
            q->locationX = robot->locationX - 1;
            q->faceDirection = 'a';
            break;
    }
    q->left = q->right = NULL;
    q->parent = robot;
    robot->left = q;
    
    return q;
}

// Robot rẽ trái
bot* goLeft(bot *&robot) {
    bot *q = new bot;
    switch (robot->faceDirection) {
        case 's':
            q->locationY = robot->locationY;
            q->locationX = robot->locationX + 1;
            q->faceDirection = 'd';
            break;
        case 'd':
            q->locationY = robot->locationY - 1;
            q->locationX = robot->locationX;
            q->faceDirection = 'a';
            break;
        case 'w':
            q->locationY = robot->locationY;
            q->locationX = robot->locationX - 1;
            q->faceDirection = 'a';
            break;
        case 'a':
            q->locationY = robot->locationY + 1;
            q->locationX = robot->locationX;
            q->faceDirection = 's';
            break;
    }
    q->left = q->right = NULL;
    q->parent = robot;
    robot->right = q;
    
    return q;
}

// Kiểm tra trùng
bool testDuplicate(bot *botTest, bot *botStart) {
    bot *p = botStart;
    string s = "NLR";
    int duplicate = 0;
    while (true) {
        if (p->thuTuDuyet <= 2) {
            if (s[p->thuTuDuyet] == 'N') {
                if (p->locationY == botTest->locationY && p->locationX == botTest->locationX && p->faceDirection == botTest->faceDirection) {
                    duplicate++;
                }
                p->thuTuDuyet++;
            }
            else if (s[p->thuTuDuyet] == 'L')
            {
                p->thuTuDuyet++;
                if (p->left != NULL) {
                    p = p->left;
                }
            }
            else if (s[p->thuTuDuyet] == 'R')
            {
                p->thuTuDuyet++;
                if (p->right != NULL) {
                    p = p->right;
                }
            }
        }
        else {
            p->thuTuDuyet = 0;
            p = p->parent;
            if (p == NULL) {  //Dieu Kien Dung
                break;
            }
        }
    }
    
    if (duplicate == 1) {
        return false;
    }
    else {
        return true;
    }
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
        bot *q = NULL;
        if (p->left == NULL) {
            q = goHead(p);
        }
        else if (p->right == NULL) {
            q = goLeft(p);
        }
        else if (p->left != NULL && p->right != NULL) {
            p = p->parent;
            continue;
        }
        
        if (q->locationY < 0 || q->locationY >= Map.numRow || q->locationX < 0 || q->locationX >= Map.numCol) {
            // Robot đi ra ngoài Map, quay lại vị trí trước
            p = q->parent;
        }
        else {
            // Robot vẫn ở trong Map
            if (Map.location[q->locationY][q->locationX] == 0) {
                // Robot ko đụng vật cản, xét có phải là đích ko
                if (q->locationY == Map.targetY - 1 && q->locationX == Map.targetX - 1) {
                    // Là đích thì xuất kết quả
                    vector<string> outPut;
                    while (q != NULL) {
                        outPut.push_back(to_string(q->locationY + 1) + " " + to_string(q->locationX + 1));
                        q = q->parent;
                    }
                    ghiFileOutput("/Users/phamhungdung/CoDe/C:C++/Robot_Tim_Duong/output.txt", outPut);
                    cout << "\nGhi File kết quả thành công" << endl;
                    return;
                }
                else {
                    // Ko là đích, xét vị trí này đã đi chưa
                    if (testDuplicate(q, botStart) == true) {
                        // Đã đi vị trí này, quay lại vị trí trước
                        p = q->parent;
                    }
                    else {
                        // Chưa đi vị trí này, đi tiếp
                        p = q;
                    }
                }
            }
            else if (Map.location[q->locationY][q->locationX] == 1) {
                // Robot đụng vật cản, quay lại vị trí trước
                p = q->parent;
            }
        }
    }
}

int main() {
    map Map;
    docFileInput("/Users/phamhungdung/CoDe/C:C++/Robot_Tim_Duong/input1.txt", Map); // Có câp phát bộ nhớ cho con trỏ cấp 2 Map.location
    
    cout << "\n\nSố hàng và cột của map: " << Map.numRow << "x" << Map.numCol;
    cout << "\n\nMap: ";
    for (int i = 0; i < Map.numRow; i++) {
        for (int j = 0; j < Map.numCol; j++) {
            cout << Map.location[i][j] << " ";
        }
        cout << "\n     ";
    }
    cout << "\nVị trí đích: (" << Map.targetY << "," << Map.targetX << ")";
    
    bot *botStart = new bot;
    
    robotFindWay_NoRecursion(botStart, Map);
    
    // Trước khi kết thúc chương trình phải giải phóng bộ nhớ đã cấp phát cho con trỏ cấp 2 Map.location
    for( int i = 0; i < Map.numRow; i++) {
        delete[] Map.location[i];
    }
    delete[] Map.location;
    
    // Giải phóng cây
    delete botStart;
    
    return 0;
}
