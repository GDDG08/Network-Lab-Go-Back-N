#include "GBN1.cpp"
using namespace std;
//�����ļ��� 
const string config_file = "config1.txt";

int main()
{
    GBN host(config_file);
	//���͸���12345�˿� 
    thread([&host] { host.excute(12345); }).detach();
    //�����ļ����Է��� 
	string s;
    while(cin>>s)
	{
//		if(s=="debug")
//		{
//			host.debug();
//		}
//        else
		host.send_file(s);
    }
    return 0;
}
