/* Name-Rishabh Jain UID- 3035453608
   Name- Harsh Nagra UID- 3035437707*/
#include<iostream>
#include<string.h>
#include<list>
#include<time.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
using namespace std;
class Record{
public:
    
    double time;
    string command;
};

int main(){
    list <Record> history;
    string command;
    int i;
    cout<<"tinyshell>";
    getline(cin,command);
    string commandnew=""; //string commandnew;
    int leng=command.length();
    for(int i=0;i<leng;i++){
        int a=command[i];
        if(a>='a' && a<='z'){
            commandnew+=command[i];
        }
        else if(a>='-'){
            commandnew+=command[i];
        }
    }
    while(commandnew!="exit")
    {
        clock_t tStart = clock();
            if(commandnew=="history")
            {
                pid_t pid = fork();
                if(pid==0)
                {
                list <Record> :: iterator itr;
                itr=history.end();
                itr--;
                for(int i=history.size()-1, j=0 ; i>=0 && j<5 ;i--, j++)
                    {
                    cout<<(*itr).command<<"  "<<(*itr).time<<"s"<<endl;
                    if(i>0)
                        itr--;
                    }
		
                cout<<"tinyshell>";
                exit(0);
                }

            }
	if(commandnew=="history-sbu")
            {
                pid_t pid = fork();
                if(pid==0)
                {
                	list <Record> sorted;
			list <Record> :: iterator itr2;
			for(itr2=history.begin(); itr2!=history.end(); itr2++){
				sorted.push_back(*itr2);
			}
			sorted.sort();
			list <Record> :: iterator itr3;
			itr3=sorted.end();
			itr3--;
			for(int i=sorted.size()-1, j=0 ; i>=0 && j<5 ;i--, j++)
			{
				cout<<(*itr3).command<<"  "<<(*itr3).time<<"s"<<endl;
				if(i>0)
					itr3--;
			}
			cout<<"tinyshell>";
			exit(0);
                }

            }
	
        wait(NULL);
        //clock_t tStart = clock();
        if(commandnew!="history" && commandnew!="history-sbu")
        {
            system(command.c_str());
	    cout<<"tinyshell>";
	}
            float t=(float)(clock() - tStart)/CLOCKS_PER_SEC;
            Record r;
            r.command=command;
            r.time=t;
            history.push_back(r);
        
            getline(cin,command);
	    commandnew=""; //string commandnew;
            int leng=command.length();
            for(int i=0;i<leng;i++){
          	int a=command[i];
       		if(a>='a' && a<='z'){
           	 commandnew+=command[i];
        	}
       		else if(a>='-'){
            	commandnew+=command[i];
       		}
		
	    }
	    
        
    }
    
    exit(0);
}
bool operator<(const Record &a, const Record &b){
    return a.time<b.time;
}
