#include<iostream>
#include<map>
#include<queue>
#include<algorithm>
using namespace std;

//���̱��ʽ
struct inferred 
{
    string process;//����
    int count = 0;//ǰ�����
    map<string, bool> hasKnown;//ÿ��ǰ���Ƿ���֪
    string conclusion;//����
};
//����ÿ����������
bool compare(inferred a, inferred b)
{
    return a.count < b.count;
}
inferred counts[50];//���̱��ʽ����
queue<string> agenda;//��δʹ�õ���ʵ
int processNum;//���̸���
string target;//Ŀ��

//˵����Ϣ
void message()
{
    cout << "��ʹ�����������иó���\n";
    cout << "��ʵ��Ϊ�־���\n";
    cout << "����һ�����ǽ��ư����⻯Ϊ�Ӿ�\n";
    cout << "��������������Լ�ͬ�������ԣ������Ӿ����£�\n";
    cout << "5����ʵ��\n";
    cout << "L(A) L(B) L(C) H(A,A) H(A,C)\n";
    cout << "33���޶��̺�ʽ��\n";
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
    cout << "1�����ۣ�\n";
    cout << "K(A,A)\n";
    cout << "ͨ��������˵����Щ�Ӿ�\n";
    cout << "L(A)��Aס�����\n";
    cout << "H(A,C)��A��C\n";
    cout << "R(C,A)��C��A����\n";
    cout << "K(A,A)��Aɱ����A\n";
    cout << "NL(A)��A��ס�������������N��ͷ��ͬ��\n\n";
}

//��ʼ��
void init()
{
    //��ʵ����
    cout << "��������ʵ����\n";
    int factNum;//��ʵ����
    string fact;//��ʵ
    cin >> factNum;
    cout << "������ÿ����ʵ\n";
    for (int i = 0; i < factNum; i++)
    {
        cin >> fact;
        agenda.push(fact);//���
    }

    //���̲���
    cout << "���������(�޶��̺�ʽ)����\n";
    cin >> processNum;
    cout << "������ÿ������\n";
    for (int i = 0; i < processNum; i++)
        cin >> counts[i].process;

    //Ŀ�겿��
    cout << "������Ŀ��\n";
    cin >> target;
}

//����
void analysis()
{
    //�Թ��̽��з������õ�ǰ������������ǰ����Ϊfalse
    string s;
    for (int i = 0; i < processNum; i++)
    {
        //��ȡ���̵��ַ�������
        int processSize = counts[i].process.size();

        //���ַ������л���
        for (int j = 0; j < processSize; j++)
        {
            //����ǰ��
            if (counts[i].process[j] == '&')
            {
                counts[i].count++;
                counts[i].hasKnown[s] = false;
                s = "";
            }

            //ǰ��֮���Ǻ��
            else if (counts[i].process[j] == '-')
            {
                counts[i].count++;
                counts[i].hasKnown[s] = false;
                s = "";
                counts[i].conclusion = counts[i].process.substr(j + 2);
                break;
            }
            
            //�ӳ��ַ���
            else
            {
                s += counts[i].process[j];
            }
        }
    }

    //����ǰ����������
    sort(counts, counts + processNum,compare);
}

//���
void resolution()
{
    //�����ʵ
    cout << "\n������ʵ��";
    int agendaSize = agenda.size();
    for (int i = 0; i < agendaSize; i++)
    {
        string fact = agenda.front();
        cout << fact<<" ";
        agenda.pop();
        agenda.push(fact);
    }
    cout << endl;

    //���й��
    while (!agenda.empty())
    {
        //ȡ��һ����ʵ
        string known = agenda.front();
        agenda.pop();

        //��ʵ����Ŀ��
        if (known == target)
        {
            cout << "�õ������" << target << endl;
            return;
        }

        //�Һ���ʵ��ͬ��ǰ��
        else
        {
            for (int i = 0; i < processNum; i++)
            {
                //�������̺�ʽ����ǰ��
                if (counts[i].count != 0)
                {
                    //�ҵ�����ʵ��ͬ��ǰ��
                    if (counts[i].hasKnown.find(known) != counts[i].hasKnown.end())
                    {
                        counts[i].hasKnown[known] = true;
                        counts[i].count--;
                    }

                    //�������ʽû��ǰ����
                    if (counts[i].count == 0)
                    {
                        agenda.push(counts[i].conclusion);//���תΪ��ʵ
                        cout << "��ϣ�" << counts[i].process << endl;
                        cout << "�ó�����ʵ��" << counts[i].conclusion << endl << endl;

                        //�յõ�����ʵ����Ŀ��
                        if (counts[i].conclusion == target)
                        {
                            cout << "�õ������" << target << endl;
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
    message();//����˵����Ϣ
    init();//��ʼ��
    analysis();//�������
    resolution();//���
    return 0;
}