#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <iterator>
#include <charconv>

#define MAX 20
#define MAXLINE 400
using namespace std;

void printList(vector<int> v[], int count);

int main() {
    vector<int> v1[MAX];
    vector<int> v2[MAX];
    char line[MAXLINE]={0,};
    int arr[MAX][MAX]={-1,};
    char *ptr;
    int idx=0, count=0;     // idx는 파일의 첫번째 줄 판별 위해, count는 vertex수
    int i=0, j=0;

    //파일 열고 읽기
    ifstream f("matrixtolist_data.txt");

    if(!f.is_open()) {
        cout << "Can't find file. File is not opened.\n";
        return 0;
    }

    //파일 끝까지 한 줄씩 읽기
    while(!f.eof()) {
        j=0;
        f.getline(line, MAXLINE);
        idx++;
        //tokenizing하고 첫 줄 vertex 개수 세고 저장하고
        //각 줄의 1,0값 숫자로 바꾼 후 2차원 배열에 저장
        ptr = strtok(line, " ");
        while(ptr != NULL) {
            if(idx == 1) count++;       // 첫번째 줄이면 count 올려서 vertex 수 세기
            if(idx != 1 && string(ptr).compare("1")==0 || string(ptr).compare("0")==0 || string(ptr).compare("1\n")||string(ptr).compare("0\n")) {
                // 두번째 줄부터 0또는 1의 값이면 숫자로 바꿔서 배열에 저장
                arr[i][j] = atoi(ptr);
                j++;
            }
            ptr = strtok(NULL, " ");
        }
        i++;
    }

    //값에 따라 adj list로 표현 (vector 사용)
    //transpose도 똑같이 adj list로 표현(vector 사용)
    for(i=1;i<count+1;i++) {
        for(j=1;j<count+1;j++) {
            /*  i가 1이면 A에서, 2이면 B에서, ...
                transpose할 때, i==j 는 자기 자신이므로 고려 대상 x
                arr 배열 값이 1이면 edge가 있다는 뜻으로 vector에 저장   */
            if(arr[i][j]==1) {
                v1[i].push_back(j);
                v2[j].push_back(i);     //transpose
            }
            
        }
    }

    // adj list 출력
    cout << "1) Array of adjacency list of above graph\n";
    printList(v1, count);

    // transpose 한 adj list 출력
    cout << "2) Array of adjacency list of transpose graph\n";
    printList(v2, count);

    f.close();
    return 0;
}

void printList(vector<int> v[], int count) {
    int i, cnt;

    for(i=1;i<count+1;i++) {
        cnt=0;
        cout << char(i+64) << " -> ";
        for(auto &c:v[i]) {
            cout << char(c+64);
            cnt++;
            if(v[i].size() != cnt) cout << " -> ";      // 마지막 노드이면 화살표 출력 x
        }
        cout << "\n";
    }
    cout << "\n";
}