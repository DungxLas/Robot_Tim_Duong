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
    cout << "\n" << Map.numRow << " " << Map.numCol << endl;
    for (int i = 0; i < Map.numRow; i++) {
        for(int j = 0; j < Map.numCol; j++) {
            cout << Map.location[i][j] << " ";
        }
        cout << endl;
    }
    cout << Map.targetY << " " << Map.targetX << endl;
    
    // Trước khi kết thúc chương trình phải giải phóng bộ nhớ đã cấp phát cho con trỏ cấp 2 Map.location
    for( int i = 0; i < Map.numRow; i++) {
        delete[] Map.location[i];
    }
    delete[] Map.location;
    
    return 0;
}
