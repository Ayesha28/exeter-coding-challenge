#include <stdio.h>
#include<bits/stdc++.h>
#include<fstream>
using namespace std;
int main()
{
    //reading csv file
    map<pair<string,string>,int>output_map;
    fstream fin;
    fin.open("french_dictionary.csv", ios::in);
    vector<string> row;
    map<string,string>m;
    string line, word;
    while (!fin.eof())
    {
        row.clear();
        getline(fin, line);
        stringstream s(line);
        while (getline(s, word, ','))
        {
            row.push_back(word);
        }
       m[row[0]]=row[1];
    }
    fin.close();

    //reading shakespeare file
  ifstream myfile ("t8.shakespeare.txt");
  std::streambuf *coutbuf = std::cout.rdbuf();
  std::ofstream out("performance.txt");
  ofstream MyFile("t8.shakespeare.translated.txt");

     fstream fout;
     fout.open("frequency.csv", ios::out | ios::app);

  std::cout.rdbuf(out.rdbuf());
  if (myfile.is_open())
  {
      set<string>output_set;
    while (getline(myfile,line) )
    {
      stringstream ss(line);
      vector<string>out;
      while (ss.good())
      {
        string substr;
        getline(ss, substr, ' ');
        string s1=substr;
        string s2=substr;
        int flag=0;
        transform(s2.begin(), s2.end(), s2.begin(), ::toupper);
        transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
        if(m.find(s1)==m.end()&&m.find(s2)==m.end()&&m.find(substr)==m.end())
        {
          out.push_back(substr);
        }
        else
        {
            output_set.insert(substr);
            if(substr==s1)
            {
               string temp=m[substr];
               transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
               output_map[{substr,temp}]++;
               out.push_back(temp);
            }
            else if(substr==s2)
            {
               if(m.find(s2)!=m.end())
               {
                   string temp=m[s2];
                   transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
                   output_map[{substr,temp}]++;
                   out.push_back(temp);
               }
               else if(m.find(s1)!=m.end())
               {
               string temp=m[s1];
               transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
               output_map[{substr,temp}]++;
               out.push_back(temp);
               }
            }
            else if(substr[0]>='A'&&substr[0]<='Z'&&substr[1]>='a'&&substr[1]<='z')
            {
               flag=1;
            }
            if(flag==1)
            {
                string temp=substr;
                string temp2=substr;
                transform(temp2.begin(), temp2.end(), temp2.begin(), ::toupper);
                transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
                if(m.find(substr)!=m.end())
                {
                out.push_back(m[substr]);
                output_map[{substr,m[substr]}]++;
                }
                else if(m.find(temp)!=m.end())
                {
                    char ch=toupper(m[temp][0]);
                    m[temp][0]=ch;
                    output_map[{substr,m[temp]}]++;
                    out.push_back(m[temp]);
                }
                else if(m.find(temp2)!=m.end())
                {
                    transform(temp2.begin(), temp2.end(), temp2.begin(), ::tolower);
                    char ch=toupper(m[temp2][0]);
                    m[temp2][0]=ch;
                    output_map[{substr,m[temp2]}]++;
                    out.push_back(m[temp2]);
                }
            }
        }
      }
    for (auto x:out)
       std::cout << x << "  ";
       std::cout<<endl;
    }

    MyFile<<"Unique list of words that was replaced with French words from the dictionary"<<endl;
    for(auto x:output_set)
        MyFile<< x<<endl;

     for(auto x:output_map)
         fout << x.first.first << ", "
             << x.first.second<<", "
             << x.second
             << "\n";
    myfile.close();
    std::cout.rdbuf(coutbuf);
  }
  else cout << "Unable to open fil";
  return 0;
}
