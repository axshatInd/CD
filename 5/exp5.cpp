#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

void computeFirstSet(const vector<string>& productions, vector<string>& firstSets, int numProductions)
{
    for (int i=0;i<numProductions;i++)
        firstSets[i]="";
    for (int i=0;i<numProductions;i++)
    {
        int j=3;
        while (productions[i][j]!='\0')
        {
            if (productions[i][j]<'A' || productions[i][j]>'Z')
            {
                if (firstSets[i].find(productions[i][j])==string::npos)
                    firstSets[i]+=productions[i][j];
            }
            else
            {
                int prodIdx=0;
                while (productions[i][j]!=productions[prodIdx][0])
                    prodIdx++;
                for (char f:firstSets[prodIdx])
                {
                    if (firstSets[i].find(f)==string::npos)
                        firstSets[i]+=f;
                }
            }
            j++;
        }
    }
}

void computeFollowSet(const vector<string>& productions, const vector<string>& firstSets, vector<string>& followSets, int numProductions)
{
    followSets[0]="$";
    for (int i=0;i<numProductions;i++)
    {
        int j=3;
        while (productions[i][j]!='\0')
        {
            if (productions[i][j]=='|')
            {
                j++;
                continue;
            }
            if (productions[i][j]<'A' || productions[i][j]>'Z')
            {
                if (followSets[i].find(productions[i][j])==string::npos)
                    followSets[i]+=productions[i][j];
            }
            else
            {
                int prodIdx=0;
                while (productions[i][j]!=productions[prodIdx][0]) prodIdx++;
                for (char f:firstSets[prodIdx])
                {
                    if (f!='e' && followSets[i].find(f)==string::npos)
                        followSets[i]+=f;
                }
                if (firstSets[prodIdx].find('e')!=string::npos)
                {
                    for (char f:followSets[prodIdx])
                    {
                        if (followSets[i].find(f)==string::npos)
                            followSets[i]+=f;
                    }
                }
            }
            j++;
        }
    }
}

void computeParsingTable(const vector<string>& productions, const vector<string>& firstSets, const vector<string>& followSets, int numProductions)
{
    vector<string>parsingTable;
    for (int i=0;i<numProductions;i++)
    {
        int s=0, j=3;
        while (productions[i][j]!='\0')
        {
            if ((productions[i][j-1]=='|') || (j==3))
            {
                string productionPart=productions[i].substr(0, j);
                int t=j;
                while (productions[i][j]!='|' && productions[i][j]!='\0')
                {
                    productionPart+=productions[i][j];
                    j++;
                }
                productionPart+='\0';
                if (productions[i][t]=='e')
                {
                    for (char follow:followSets[i])
                        cout<<"M["<<productions[i][0]<<","<<follow<<"]="<<productionPart<<endl;
                }
                else
                {
                    for (char first:firstSets[i])
                    {
                        cout<<"M["<<productions[i][0]<<","<<first<<"]="<<productionPart<<endl;
                    }
                }
                s++;
            }
            if (productions[i][j]=='|')
                j++;
        }
    }
}

int main()
{
    int numProductions;

    cout<<"Enter the number of rules : ";
    cin>>numProductions;

    vector<string>productions(numProductions);
    vector<string>firstSets(numProductions);
    vector<string>followSets(numProductions);

    cout<<"Enter the productions : "<<endl;
    for (int i=0;i<numProductions;i++)
        cin>>productions[i];
       
    computeFirstSet(productions, firstSets, numProductions);
    computeFollowSet(productions, firstSets, followSets, numProductions);

    cout<<endl<<"First sets : "<<endl;
    for (int i=0;i<numProductions;i++)
        cout<<"FIRST["<<productions[i][0]<<"] = "<<firstSets[i]<<endl;

    cout<<endl<<"Follow sets : "<<endl;
    for (int i=0;i<numProductions;i++)
        cout<<"FOLLOW["<<productions[i][0]<<"] = "<<followSets[i]<<endl;

    cout<<endl<<"Parsing table : "<<endl;
    computeParsingTable(productions, firstSets, followSets, numProductions);

    return 0;
}
