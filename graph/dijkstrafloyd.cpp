#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <list>
#include <ctime>

#define MAX 30
#define MAXLINE 900
#define INF 10000000
using namespace std;

class cityweight
{
public:
    string city;
    int weight;
};

void printList(vector<string> city, vector<cityweight> v[], int count);
void makeOutput(vector<string> city, int **result, int count, double sectime);
void makeOutput2(vector<string> city, int **result, int count, double sectime);
int* dijkstra(int **arr, int count, int s);
int** floyd(int **arr, int count, int s);

int main()
{
    vector<string> city;
    vector<cityweight> v[MAX];
    char delim[] = " \t\n";     // strtok 함수 사용 시 구분할 기준 문자
    char line[MAXLINE] = {
        0,
    };
    char *ptr;
    int idx = 0, count = 0; // idx는 파일의 첫번째 줄 판별 위해, count는 vertex수
    int i = -1, j = 0;

    int **arr;
    arr = new int *[MAX];
    for (int k = 0; k < MAX; k++) {
        arr[k] = new int[MAX];
    }

    //파일 열고 읽기
    ifstream f("dijkstrafloyd_data.txt");

    if (!f.is_open())
    {
        cout << "Can't find file. File is not opened.\n";
        return 0;
    }

    //파일 끝까지 한 줄씩 읽기
    while (!f.eof())
    {
        j = 0;
        f.getline(line, MAXLINE);
        idx++;
        //tokenizing하고 첫 줄 vertex 개수 세고 저장하고
        ptr = strtok(line, delim);
        while (ptr != NULL)
        {
            if (idx == 1)
            { // 첫번째 줄이면 count 올려서 vertex 수 세기
                count++;
                city.push_back(string(ptr));
            }
            if (idx != 1 && j == 0)
            {
                city.erase(city.begin() + (idx - 2));
                city.insert(city.begin() + (idx - 2), string(ptr));
            }
            // 자기 자신이 아니고, 첫번째 줄이 아니면서 INF 가 아니면 (weight 가 있으면) vector에 저장
            if (idx != (j + 1) && j != 0 && idx != 1 && j != count + 1 && string(ptr).compare("INF") != 0)
            {
                cityweight temp;
                temp.city = city[j - 1];
                temp.weight = atoi(ptr);
                arr[i][j-1] = temp.weight;              // 배열 저장
                v[i].push_back(temp);                   // vertor 저장
            }
            j++; // vertex 구분
            ptr = strtok(NULL, delim);
        }
        i++; // line 구분
    }

    printList(city, v, count);

    // allocation for save result
    int **result;
    result = new int *[MAX];
    for (int k = 0; k < MAX; k++) {
        result[k] = new int[MAX];
    }
    int *d = new int[count];

    // dijstra
    clock_t startdijk = clock(); 
    for(int k=0;k<count;k++) {
        d = dijkstra(arr, count, k);
        for(int l=0;l<count;l++) {
            //cout << "city: " << l << "dis : " << d[l] << "\n";
            result[k][l] = d[l];
        }
    }
    double dijktime = (double)(clock() - startdijk)/CLOCKS_PER_SEC;
    makeOutput(city, result, count, dijktime);


    // allocation for save result
    int **resultfloyd;
    resultfloyd = new int *[MAX];
    for (int k = 0; k < MAX; k++) {
        resultfloyd[k] = new int[MAX];
    }

    // floyd
    clock_t startfloyd = clock(); 
    for(int k=0;k<count;k++) {
        if(k==0) 
            resultfloyd = floyd(arr, count, k);
        else 
            resultfloyd = floyd(resultfloyd, count, k);
        
    }
    clock_t finishfloyd = clock();
    double floydtime = (double)(clock() - startfloyd)/CLOCKS_PER_SEC;
    makeOutput2(city, resultfloyd, count, floydtime);   // 수행 시간이 너무 빨라서 microseconds 단위로도 바꿔 출력

    // deallocation
    delete[] d;
    for (int m = 0; m < count; m++) {
        delete[] result[m];
        delete[] arr[m];
    }
    delete[] result;
    delete[] arr;

    f.close();
    return 0;
}

void printList(vector<string> city, vector<cityweight> v[], int count)
{
    int i, cnt;

    for (i = 0; i < count; i++)
    {
        cnt = 0;
        cout << " [ " << city[i] << " ] " << '\n';

        for (cityweight c : v[i])
        {
            if (v[i].size() != cnt)
                cout << " -> "; // 마지막 노드이면 화살표 출력 x
            cout << c.city << "\n" << c.weight << "\n";
            cnt++;
        }
        cout << "\n\n";
    }
}

void makeOutput(vector<string> city, int **result, int count, double sectime)
{
    int i = 0, j = 0;
    double sec=0;

    ofstream f1("dijkstrafloyd_output.txt");
    //dijkstra table 출력
    f1 << "\nIt took " << sectime << " seconds (" << CLOCKS_PER_SEC * sectime << " microseconds) to compute shortest path between cities with Dijkstra's algorithm as follows.\n";

    f1 << "\n--------------------------------------------------------------------------------------------------------\n";
    f1 << "\t\t\t"
       << " | ";
    for (i = 0; i < count; i++)
    {
        f1 << city[i] << " | ";
    }

    f1 << "\n---------------------------------------------------------------------------------------------------------\n";

    for (i = 0; i < count; i++)
    {
        f1 << "\t" << city[i] << "\t|";
        for (j = 0; j < count; j++)
        {
            f1 << "\t" << result[i][j] << "\t|";
        }
        f1 << "\n---------------------------------------------------------------------------------------------------------\n";
    }

    f1 << "\n\n";

    f1.close();
}

void makeOutput2(vector<string> city, int **result, int count, double sectime)
{
    int i = 0, j = 0;
    double sec=0;

    ofstream f1("dijkstrafloyd_output.txt", ios::app);        // 이어서 쓰기
    //floyd table 출력
    f1 << "It took " << sectime << " seconds (" << CLOCKS_PER_SEC * sectime << " microseconds) to compute shortest path between cities with Floyd algorithm as follows.\n";

    f1 << "\n--------------------------------------------------------------------------------------------------------\n";
    f1 << "\t\t\t"
       << " | ";
    for (i = 0; i < count; i++)
    {
        f1 << city[i] << " | ";
    }

    f1 << "\n---------------------------------------------------------------------------------------------------------\n";

    for (i = 0; i < count; i++)
    {
        f1 << "\t" << city[i] << "\t|";
        for (j = 0; j < count; j++)
        {
            f1 << "\t" << result[i][j] << "\t|";
        }
        f1 << "\n---------------------------------------------------------------------------------------------------------\n";
    }

    f1.close();
}

int* dijkstra(int **arr, int count, int s)
{
    typedef pair<int,int> p;
    priority_queue<p, vector<p>, greater<p> > pq;       // keydistance, vertex
    list<p> adj[MAX];                                   // edgeweight, vertex
    list<p>::iterator it;

    int *d = new int[count];
    int i, j, u, v, w;
    int vertex;

    //initialize
    d[s] = 0;       //source distance = 0
    pq.push(p(d[s], 0));
    for(i=0;i<count;i++) {
        if(i!=s) 
            d[i] = INF;              // 10000000 무한대(INF) 표현
        pq.push(p(d[i], i));
    }

    while(!pq.empty()) {
        u = pq.top().first;       // extract min distance
        vertex = pq.top().second;   // min distance를 가지고 있는 vertex extract
        pq.pop();

        // 관련 adjacent vertex 다 찾고 adj list에 저장
        for(i=0;i<count;i++) {
            for(j=0;j<count;j++) {
                if(i == vertex && arr[i][j]!=0) {
                    adj[i].push_back(p(arr[i][j], j));
                }
            }
        }

        // relaxation
        for(it = adj[vertex].begin();it!=adj[vertex].end();it++){
            w = it->first;      //edge weight
            v = it->second;     // adj vertex
            if(d[v] > d[vertex] + w){
                d[v] = d[vertex] + w;
                pq.push(p(d[v],v));
            }
        }
    }

    return d;
}

int** floyd(int **arr, int count, int s) {
    int i, j, k;

    if (s==0) {     // intermediate vertex가 없으면 edge weight이 곧 min distance
        for(i=0;i<count;i++) {
            for(j=0;j<count;j++) {
                if(i==j)                // 자기자신
                    arr[i][j] = 0; 
                else if(arr[i][j] == 0)      // Edge weight 없을 때 무한대
                    arr[i][j] = INF;
            }
        }
    }
    else {
        //min(d[ij](k-1), d[ik](k-1)+d[kj](k-1))
        for(k=0;k<count;k++) {
            for(i=0;i<count;i++) {
                for(j=0;j<count;j++) {
                    if(arr[i][k] + arr[k][j] < arr[i][j]) {
                        arr[i][j] = arr[i][k] + arr[k][j];
                    }
                }
            }
        }
    }

    return arr;
}