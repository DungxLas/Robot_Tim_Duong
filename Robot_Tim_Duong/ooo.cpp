#include <iostream>
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
            q->faceDirection = 'w';
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
            if (p == NULL) {
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

void robotFindWay_NoRecursion(bot *botStart, map Map) {
    botStart->locationY = 0;
    botStart->locationX = 0;
    botStart->parent= botStart->left = botStart->right = NULL;
    botStart->faceDirection = 's';
    
    bot *p = botStart;
    while (true) {
        if (p == NULL) {
            cout << 0;
            return;
        }
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
            p = q->parent;
        }
        else {
            if (Map.location[q->locationY][q->locationX] == 0) {
                if (q->locationY == Map.targetY - 1 && q->locationX == Map.targetX - 1) {
                    vector<int> outPut;
                    while (q != NULL) {
                        outPut.push_back(q->locationX + 1);
                        outPut.push_back(q->locationY + 1);
                        q = q->parent;
                    }
                    cout << outPut.size() / 2 << endl;
                    while (!outPut.empty()) {
                        cout << outPut.back() << " ";
                        outPut.pop_back();
                        cout << outPut.back() << endl;
                        outPut.pop_back();
                    }
                    return;
                }
                else {
                    if (testDuplicate(q, botStart) == true) {
                        p = q->parent;
                    }
                    else {
                        p = q;
                    }
                }
            }
            else if (Map.location[q->locationY][q->locationX] == 1) {
                p = q->parent;
            }
        }
    }
}

int main() {
    map Map;
    cin >> Map.numRow;
    cin >> Map.numCol;
    
    Map.location = new int*[Map.numRow];
    for (int i = 0; i < Map.numRow; i++) {
        Map.location[i] = new int[Map.numCol];
    }
    for (int i = 0; i < Map.numRow; i++) {
        for(int j = 0; j < Map.numCol; j++) {
            cin >> Map.location[i][j];
        }
    }
    
    cin >> Map.targetY;
    cin >> Map.targetX;
    
    bot *botStart = new bot;
    
    robotFindWay_NoRecursion(botStart, Map);
    
    for( int i = 0; i < Map.numRow; i++) {
        delete[] Map.location[i];
    }
    delete[] Map.location;
    
    delete botStart;
    
    return 0;
}
