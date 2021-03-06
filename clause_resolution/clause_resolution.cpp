#include<iostream>
#include<map>
#include<queue>
#include<algorithm>
using namespace std;

//过程表达式
struct inferred 
{
    string process;//过程
    int count = 0;//前提个数
    map<string, bool> hasKnown;//每个前提是否已知
    string conclusion;//结论
};
//用于每个过程排序
bool compare(inferred a, inferred b)
{
    return a.count < b.count;
}
inferred counts[50];//过程表达式总数
queue<string> agenda;//还未使用的事实
int processNum;//过程个数
string target;//目标

//说明信息
void message()
{
    cout << "请使用命令行运行该程序\n";
    cout << "本实验为字句归结\n";
    cout << "首先一步便是将破案问题化为子句\n";
    cout << "根据问题表述，以及同可满足性，化出子句如下：\n";
    cout << "5条事实：\n";
    cout << "L(A) L(B) L(C) H(A,A) H(A,C)\n";
    cout << "33条限定蕴含式：\n";
    cout << "H(A,A)->H(B,A)\n";
    cout << "H(A,B)->H(B,B)\n";
    cout << "H(A,C)->H(B,C)\n";
    cout << "H(A,A)->NH(C,A)\n";
    cout << "H(A,B)->NH(C,B)\n";
    cout << "H(A,C)->NH(C,C)\n";
    cout << "H(B,A)->NR(A,A)\n";
    cout << "H(B,B)->NR(B,A)\n";
    cout << "H(B,C)->NR(C,A)\n";
    cout << "NH(B,A)->R(A,A)\n";
    cout << "NH(B,B)->R(B,A)\n";
    cout << "NH(B,C)->R(C,A)\n";
    cout << "H(A,A)&H(A,B)->NH(A,C)\n";
    cout << "H(A,A)&H(A,C)->NH(A,B)\n";
    cout << "H(A,B)&H(A,C)->NH(A,A)\n";
    cout << "H(B,A)&H(B,B)->NH(B,C)\n";
    cout << "H(B,A)&H(B,C)->NH(B,B)\n";
    cout << "H(B,B)&H(B,C)->NH(B,A)\n";
    cout << "H(C,A)&H(C,B)->NH(C,C)\n";
    cout << "H(C,A)&H(C,C)->NH(C,B)\n";
    cout << "H(C,B)&H(C,C)->NH(C,A)\n";
    cout << "NL(A)->NK(A,A)\n";
    cout << "NH(A,A)->NK(A,A)\n";
    cout << "R(A,A)->NK(A,A)\n";
    cout << "NL(B)->NK(B,A)\n";
    cout << "NH(B,A)->NK(B,A)\n";
    cout << "R(B,A)->NK(B,A)\n";
    cout << "NL(C)->NK(C,A)\n";
    cout << "NH(C,A)->NK(C,A)\n";
    cout << "R(C,A)->NK(C,A)\n";
    cout << "L(A)&H(A,A)&NR(A,A)&NK(B,A)&NK(C,A)->K(A,A)\n";
    cout << "L(B)&H(B,A)&NR(B,A)&NK(A,A)&NK(C,A)->K(B,A)\n";
    cout << "L(C)&H(C,A)&NR(C,A)&NK(A,A)&NK(B,A)->K(C,A)\n";
    cout << "1条结论：\n";
    cout << "K(A,A)\n";
    cout << "通过举例来说明这些子句\n";
    cout << "L(A)：A住在这儿\n";
    cout << "H(A,C)：A恨C\n";
    cout << "R(C,A)；C比A富有\n";
    cout << "K(A,A)：A杀死了A\n";
    cout << "NL(A)：A不住在这儿，其他以N开头的同理\n\n";
}

//初始化
void init()
{
    //事实部分
    cout << "请输入事实个数\n";
    int factNum;//事实个数
    string fact;//事实
    cin >> factNum;
    cout << "请输入每个事实\n";
    for (int i = 0; i < factNum; i++)
    {
        cin >> fact;
        agenda.push(fact);//入队
    }

    //过程部分
    cout << "请输入过程(限定蕴含式)个数\n";
    cin >> processNum;
    cout << "请输入每个过程\n";
    for (int i = 0; i < processNum; i++)
        cin >> counts[i].process;

    //目标部分
    cout << "请输入目标\n";
    cin >> target;
}

//分析
void analysis()
{
    //对过程进行分析，得到前件个数，并将前件标为false
    string s;
    for (int i = 0; i < processNum; i++)
    {
        //获取过程的字符串长度
        int processSize = counts[i].process.size();

        //对字符串进行划分
        for (int j = 0; j < processSize; j++)
        {
            //划分前提
            if (counts[i].process[j] == '&')
            {
                counts[i].count++;
                counts[i].hasKnown[s] = false;
                s = "";
            }

            //前提之后是后件
            else if (counts[i].process[j] == '-')
            {
                counts[i].count++;
                counts[i].hasKnown[s] = false;
                s = "";
                counts[i].conclusion = counts[i].process.substr(j + 2);
                break;
            }
            
            //延长字符串
            else
            {
                s += counts[i].process[j];
            }
        }
    }

    //根据前件个数排序
    sort(counts, counts + processNum,compare);
}

//归结
void resolution()
{
    //输出事实
    cout << "\n根据事实：";
    int agendaSize = agenda.size();
    for (int i = 0; i < agendaSize; i++)
    {
        string fact = agenda.front();
        cout << fact<<" ";
        agenda.pop();
        agenda.push(fact);
    }
    cout << endl;

    //进行归结
    while (!agenda.empty())
    {
        //取出一个事实
        string known = agenda.front();
        agenda.pop();

        //事实等于目标
        if (known == target)
        {
            cout << "得到结果：" << target << endl;
            return;
        }

        //找和事实相同的前件
        else
        {
            for (int i = 0; i < processNum; i++)
            {
                //当这条蕴含式还有前件
                if (counts[i].count != 0)
                {
                    //找到和事实相同的前件
                    if (counts[i].hasKnown.find(known) != counts[i].hasKnown.end())
                    {
                        counts[i].hasKnown[known] = true;
                        counts[i].count--;
                    }

                    //这条表达式没有前件了
                    if (counts[i].count == 0)
                    {
                        agenda.push(counts[i].conclusion);//后件转为事实
                        cout << "结合：" << counts[i].process << endl;
                        cout << "得出新事实：" << counts[i].conclusion << endl << endl;

                        //刚得到的事实等于目标
                        if (counts[i].conclusion == target)
                        {
                            cout << "得到结果：" << target << endl;
                            return;
                        }
                    }

                }
            }
        }
    }
}
int main()
{
    message();//给出说明信息
    init();//初始化
    analysis();//命题分析
    resolution();//归结
    return 0;
}