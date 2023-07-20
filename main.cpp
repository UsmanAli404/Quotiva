#include<iostream>
#include<fstream>
#include<string>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<cctype>
#include<chrono>
#include<unordered_map>
#include<vector>
using namespace std;


string getCurrentDate()
{
    chrono::system_clock::time_point now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);
    char dateBuffer[11];
    strftime(dateBuffer, sizeof(dateBuffer), "%d-%m-%Y", localtime(&currentTime));
    return string(dateBuffer);
}

string getCurrentTime()
{
    chrono::system_clock::time_point now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);
    char timeBuffer[9];
    strftime(timeBuffer, sizeof(timeBuffer), "%H:%M:%S", localtime(&currentTime));
    return string(timeBuffer);
}

string toTitleCaps(const string& str)
{
    string result=str;
    bool makeUppercase=true;

    for (size_t i=0; i<result.length(); ++i)
    {
        if (makeUppercase&&isalpha(result[i]))
        {
            result[i]=toupper(result[i]);
            makeUppercase=false;
        }
        else if (isspace(result[i])||result[i]=='-')
        {
            makeUppercase=true;
        }
    }

    return result;
}

bool isFileEmpty(const string& fileName)
{
    ifstream file(fileName);
    return file.peek() == ifstream::traits_type::eof();
}

int* resize(int* arr, int& size)
{
    int* temp = new int[size+1];
    for(int i=0; i<size; i++)
    {
        temp[i]=arr[i];
    }
    delete[]arr;
    size++;

    return temp;
}

string* resize_string_arr(string* arr, int& size)
{
    string* temp = new string[size+1];
    for(int i=0; i<size; i++)
    {
        temp[i]=arr[i];
    }
    delete[]arr;
    size++;

    return temp;
}

void display(int* arr, int size)
{
    cout<<"Array: ";
    for(int i=0; i<size; i++)
    {
        cout<<arr[i]<<" ";
    }
    cout<<endl<<"size: "<<size<<endl;
}

void remove_extras_p()
{
    ifstream readfile("philosophy.txt");
    ofstream writefile("temp.txt");
    string line, quote, name, updated_line;
    int count=0;
    bool ft=true, change_line=true;
    while(getline(readfile, line))
    {
        for(int i=0; line[i]!='\0'; i++)
        {
            if(line[0]!=' ')
            {
                change_line=false;
                break;
            }
            if(line[i]=='"'&&count!=2)
            {
                count++;
            }
            if(count==1)
            {
                if(ft)
                {
                    ft=false;
                }
                else
                {
                    quote+=line[i];
                }
            }
            if(count>=2)
            {
                if(count==4)
                {
                    name+=line[i];
                }
                if(line[i]==' '&&count<4)
                {
                    count++;
                }
            }
        }
        if(change_line)
        {
            updated_line=quote+"|"+name;
        }
        else
        {
            updated_line=line;
        }
        writefile<<updated_line<<endl;
        change_line=true;
        count=0;
        name="";
        quote="";
        ft=true;
    }
    readfile.close();
    writefile.close();

    remove("philosophy.txt");
    rename("temp.txt", "philosophy.txt");
}

void remove_extras_m()
{
    ifstream readfile("motivation.txt");
    ofstream writefile("temp.txt");
    string line, quote, name, updated_line;
    int count=0;
    bool ft=true, change_line=true;
    while(getline(readfile, line))
    {
        for(int i=0; line[i]!='\0'; i++)
        {
            if(line[0]!=' ')
            {
                change_line=false;
                break;
            }
            if(line[i]=='"'&&count!=2)
            {
                count++;
            }
            if(count==1)
            {
                if(ft)
                {
                    ft=false;
                }
                else
                {
                    quote+=line[i];
                }
            }
            if(count>=2)
            {
                if(count==4)
                {
                    name+=line[i];
                }
                if(line[i]==' '&&count<4)
                {
                    count++;
                }
            }
        }
        if(change_line)
        {
            updated_line=quote+"|"+name;
        }
        else
        {
            updated_line=line;
        }
        cout<<updated_line<<endl;
        writefile<<updated_line<<endl;
        change_line=true;
        count=0;
        name="";
        quote="";
        ft=true;
    }
    readfile.close();
    writefile.close();

    remove("motivation.txt");
    rename("temp.txt", "motivation.txt");
}

int* fill_random_array(int*arr, int&size, int c)
{
    int num, num_count=0, num_lines, count=0;

    ifstream readfile("counter.txt");
    string line, mlines, plines;

    while(getline(readfile, line))
    {
        for(int i=0; line[i]!='\0'; i++)
        {
            if(line[i]==',')
            {
                count++;
            }
            if(count!=0&&line[i]!=',')
            {
                plines+=line[i];
            }
            else
            {
                mlines+=line[i];
            }
        }
    }

    if(c==1)
    {
        num_lines=stoi(mlines);
    }
    else
    {
        num_lines=stoi(plines);
    }
    while(true)
    {
        num = (rand()%num_lines)+1;
        if(size==1)
        {
            arr[size-1]=num;
            arr=resize(arr,size);
        }
        else if(size==num_lines+1)
        {
            break;
        }
        else
        {
            for(int i=0; i<size-1; i++)
            {
                if(num==arr[i])
                {
                    num_count++;
                }
            }
            if(num_count==0)
            {
                arr[size-1]=num;
                arr=resize(arr,size);
            }
            else
            {
                num_count=0;
                continue;
            }
        }
    }
    size--;

    return arr;
}

void show_a_random_quote(int n, int* arr, int size, string username)
{
    static int a=0;
    static int t=0;
    int num, count=1, c=0;
    string line, quote, name;
    bool shown=false;
    if(n==2)
    {
        //philosophy
        if(a<size)
        {
            ifstream readfile("philosophy.txt");
            while(getline(readfile, line))
            {
                if(count==arr[a])
                {
                    for(int i=0; line[i]!='\0'; i++)
                    {
                        if(line[i]=='|')
                        {
                            c++;
                        }
                        if(c==0)
                        {
                            quote+=line[i];
                        }
                        else
                        {
                            if(line[i]!='|')
                            {
                                name+=line[i];
                            }
                        }
                    }
                    cout<<"\nHere's something worth pondering over for you!\n";
                    cout<<"\033[1m\""<<quote<<"\"\033[0m - \033[1m"<<name<<"\033[0m"<<endl<<endl;
                    shown=true;
                    a++;
                }
                if(shown)
                {
                    break;
                }
                count++;
            }
            readfile.close();
            //rate the quote
            ofstream appendfile(username+".txt", ios::app);
            cout<<"worst(1) very bad(2) bad(3) mid(4) good(5) very good(6) best(7)\n";
            a:
            cout<<"Rate the quote on a scale of 1-7: ";
            cin>>num;
            if(num>=1&&num<=7)
            {
                //search if the quote is already present 
                bool quote_present=false;
                string quote_in_file;
                int count=1, c=1;
                ifstream readfile(username+".txt");
                while(getline(readfile, line))
                {
                    for(int i=0; line[i]!='\0'; i++)
                    {
                        if(line[i]=='|')
                        {
                            break;
                        }

                        quote_in_file+=line[i];
                    }
                    if(quote_in_file==quote)
                    {
                        quote_present=true;
                        //retrieve previous rating
                        size_t posn = line.rfind("|");
                        string numberString = line.substr(posn + 1);
                        int number = stoi(numberString);
                        readfile.close();
                        //update in the file
                        if(num!=number)
                        {
                            ifstream Readfile(username+".txt");
                            ofstream Writefile("temp.txt");
                            while(getline(Readfile, line))
                            {
                                if(c==count)
                                {
                                    Writefile<<quote<<"|"<<name<<"|"<<num<<endl;
                                }
                                else
                                {
                                    Writefile<<line<<endl;
                                }
                                c++;
                            }
                            Readfile.close();
                            Writefile.close();

                            remove((username+".txt").c_str());
                            rename("temp.txt", (username+".txt").c_str());

                            cout<<"Rating updated from "<<number<<" to "<<num<<"!\n";
                        }
                        break;
                    }
                    quote_in_file="";
                    quote_present=false;
                    count++;
                }
                if(!quote_present)
                {
                    ofstream appendfile(username+".txt", ios::app);
                    appendfile<<quote<<"|"<<name<<"|"<<num<<endl;
                    appendfile.close();
                }
            }
            else
            {
                goto a;
            }
            appendfile.close();
            cout<<endl<<endl;
        }
        else
        {
            cout<<"All the philosophical quotes have been shown, stay tuned for more!\n";
        }
        
    }
    else if(n==1)
    {
        //motivation
        if(t<size)
        {
            ifstream readfile("motivation.txt");
            while(getline(readfile, line))
            {
                if(count==arr[t])
                {
                    for(int i=0; line[i]!='\0'; i++)
                    {
                        if(line[i]=='|')
                        {
                            c++;
                        }
                        if(c==0)
                        {
                            quote+=line[i];
                        }
                        else
                        {
                            if(line[i]!='|')
                            {
                                name+=line[i];
                            }
                        }
                    }
                    cout<<"\nHere's something energetic for you!\n";
                    cout<<"\033[1m\""<<quote<<"\"\033[0m - \033[1m"<<name<<"\033[0m"<<endl<<endl;
                    shown=true;
                    t++;
                }
                if(shown)
                {
                    break;
                }
                count++;
            }
            readfile.close();
            //rate the quote
            cout<<"worst(1) very bad(2) bad(3) mid(4) good(5) very good(6) best(7)\n";
            d:
            cout<<"Rate the quote on a scale of 1-7: ";
            cin>>num;
            if(num>=1&&num<=7)
            {
                //search if the quote shown is already present
                bool quote_present=false;
                string quote_in_file;
                int count=1, c=1;
                ifstream readfile(username+".txt");
                while(getline(readfile, line))
                {
                    for(int i=0; line[i]!='\0'; i++)
                    {
                        if(line[i]=='|')
                        {
                            break;
                        }

                        quote_in_file+=line[i];
                    }
                    if(quote_in_file==quote)
                    {
                        quote_present=true;
                        //retrieve previous rating
                        size_t posn = line.rfind("|");
                        string numberString = line.substr(posn + 1);
                        int number = stoi(numberString);
                        readfile.close();

                        if(number!=num)
                        {
                            //update in the file
                            ifstream Readfile(username+".txt");
                            ofstream Writefile("temp.txt");
                            while(getline(Readfile, line))
                            {
                                if(c==count)
                                {
                                    Writefile<<quote<<"|"<<name<<"|"<<num<<endl;
                                }
                                else
                                {
                                    Writefile<<line<<endl;
                                }
                                c++;
                            }
                            Readfile.close();
                            Writefile.close();

                            remove((username+".txt").c_str());
                            rename("temp.txt", (username+".txt").c_str());

                            cout<<"Rating updated from "<<number<<" to "<<num<<"!\n";
                        }
                        break;
                    }

                    quote_in_file="";
                    quote_present=false;
                    count++;
                }
                if(!quote_present)
                {
                    ofstream appendfile(username+".txt", ios::app);
                    appendfile<<quote<<"|"<<name<<"|"<<num<<endl;
                    appendfile.close();
                }
            }
            else
            {
                goto d;
            }
            cout<<endl<<endl;
        }
        else
        {
            cout<<"All the motivational quotes have been shown, stay tuned for more!\n";
        }
        
    }
}

void remove_repeating_quotes_m()
{
    ifstream readfile("motivation.txt");
    ofstream writefile("temp.txt");
    string mline, tline;
    bool is_found=false;
    while(getline(readfile, mline))
    {
        if(isFileEmpty("temp.txt"))
        {
            writefile<<mline<<endl;
            writefile.close();
        }
        else
        {
            ifstream readtemp("temp.txt");
            while (getline(readtemp, tline))
            {
                if(mline==tline)
                {
                    is_found=true;
                    break;
                }
            }
            readtemp.close();
            if(!is_found)
            {
                ofstream writetemp("temp.txt", ios::app);
                writetemp<<mline<<endl;
                writetemp.close();
            }
            is_found=false;
        }
    }
    readfile.close();
    remove("motivation.txt");
    rename("temp.txt", "motivation.txt");
}

void remove_repeating_quotes_p()
{
    ifstream readfile("philosophy.txt");
    ofstream writefile("temp.txt");
    string mline, tline;
    bool is_found=false;
    while(getline(readfile, mline))
    {
        if(isFileEmpty("temp.txt"))
        {
            writefile<<mline<<endl;
            writefile.close();
        }
        else
        {
            ifstream readtemp("temp.txt");
            while (getline(readtemp, tline))
            {
                if(mline==tline)
                {
                    is_found=true;
                    break;
                }
            }
            readtemp.close();
            if(!is_found)
            {
                ofstream writetemp("temp.txt", ios::app);
                writetemp<<mline<<endl;
                writetemp.close();
            }
            is_found=false;
        }
    }
    readfile.close();
    remove("philosophy.txt");
    rename("temp.txt", "philosophy.txt");
}

void show_all_searched_m(string word)
{
    ifstream readfile("motivation.txt");
    string line, word_constructed, quote, name;
    int t=0, a=0, c=0;

    while(getline(readfile, line))
    {
        for(int i=0; i<(line.length()-word.length())+1; i++)
        {
            for(int j=a; j<a+word.length(); j++)
            {
                word_constructed+=line[j];
            }
            if(word_constructed==word)
            {
                //cout<<line<<endl;
                for(int i=0; line[i]!='\0'; i++)
                {
                    if(line[i]=='|')
                    {
                        c++;
                    }
                    if(c==0)
                    {
                        quote+=line[i];
                    }
                    else
                    {
                        if(line[i]!='|')
                        {
                            name+=line[i];
                        }
                    }
                }
                cout<<"\033[1m\""<<quote<<"\"\033[0m - \033[1m"<<name<<"\033[0m"<<endl<<endl;
                quote="";
                name="";
                c=0;
                break;
            }
            a++;
            word_constructed="";
        }
        a=0;
    }
    readfile.close();
}

void show_all_searched_p(string word)
{
    ifstream readfile("philosophy.txt");
    string line, word_constructed, quote, name;
    int t=0, a=0, c=0;
    while(getline(readfile, line))
    {
        for(int i=0; i<(line.length()-word.length())+1; i++)
        {
            for(int j=a; j<a+word.length(); j++)
            {
                word_constructed+=line[j];
            }
            if(word_constructed==word)
            {
                for(int i=0; line[i]!='\0'; i++)
                {
                    if(line[i]=='|')
                    {
                        c++;
                    }
                    if(c==0)
                    {
                        quote+=line[i];
                    }
                    else
                    {
                        if(line[i]!='|')
                        {
                            name+=line[i];
                        }
                    }
                }
                cout<<"\033[1m\""<<quote<<"\"\033[0m - \033[1m"<<name<<"\033[0m"<<endl<<endl;
                quote="";
                name="";
                c=0;
                break;
            }
            a++;
            word_constructed="";
        }
        a=0;
    }
    readfile.close();
}

void show_favorite_quotes(string username)
{
    int c=0;
    string line, quote, name;

    if(!isFileEmpty(username+".txt"))
    {
        ifstream readfile(username+".txt");
        while(getline(readfile, line))
        {
            size_t lastPipePos = line.rfind("|");
            string numberString = line.substr(lastPipePos + 1);
            int number = stoi(numberString);
            if(number==6||number==7)
            {
                for(int i=0; line[i]!='\0'; i++)
                {
                    if(line[i]=='|')
                    {
                        c++;
                    }
                    if(c==0)
                    {
                        quote+=line[i];
                    }
                    else if(c==1&&line[i]!='|')
                    {
                        name+=line[i];
                    }
                }
                cout<<"\033[1m\""<<quote<<"\"\033[0m - \033[1m"<<name<<"\033[0m"<<endl<<endl;
                quote="";
                name="";
                c=0;
            }
        }
    }
}

bool quote_is_present(string filename, string quote)
{
    string line, quote_in_file="";
    bool found=false;
    
    ifstream readfile(filename+".txt");
    while(getline(readfile, line))
    {
        for(int i=0; line[i]!='\0'; i++)
        {
            if(line[i]=='|')
            {
                break;
            }
            quote_in_file+=line[i];
        }
        if(quote==quote_in_file)
        {
            found=true;
            break;
        }
        quote_in_file="";
    }
    readfile.close();

    return found;
}

void add_a_quote()
{
    int n, count=0;
    string quote, name, n1, n2, line;
    cout<<"Do you want to add a motivational(1) or a philosophical(2) quote? ";
    cin>>n;
    cout<<"(don't forget to follow grammar and punctuation rules)\n";
    cout<<"Enter the quote: ";
    cin.ignore();
    getline(cin,quote);
    if(n==1)
    {
        if(!quote_is_present("motivation.txt", quote))
        {
            ofstream appendfile("motivation.txt", ios::app);
            cout<<"Enter the author's name: ";
            cin.ignore();
            getline(cin,name);
            appendfile<<quote<<"|"<<name<<endl;
            cout<<"quote has been added!\n";
            appendfile.close();

            ifstream readcounter("counter.txt");
            while(getline(readcounter, line))
            {
                for(int i=0; line[i]!='\0'; i++)
                {
                    if(line[i]==',')
                    {
                        count++;
                    }
                    if(count==0)
                    {
                        n1+=line[i];
                    }
                    else if(count==1&&line[i]!=',')
                    {
                        n2+=line[i];
                    }
                }
            }
            readcounter.close();

            ofstream writefile("counter.txt");
            writefile<<stoi(n1)+1<<","<<n2<<endl;
            writefile.close();
        }
        else
        {
            cout<<"The quote is already present in motivation.txt\n";
        }
    }
    else
    {
        if(!quote_is_present("philosophy.txt", quote))
        {
            ofstream appendfile("philosophy.txt", ios::app);
            cout<<"Enter the author's name: ";
            getline(cin,name);
            appendfile<<quote<<"|"<<name<<endl;
            cout<<"quote has been added!\n";
            appendfile.close();

            ifstream readcounter("counter.txt");
            while(getline(readcounter, line))
            {
                for(int i=0; line[i]!='\0'; i++)
                {
                    if(line[i]==',')
                    {
                        count++;
                    }
                    if(count==0)
                    {
                        n1+=line[i];
                    }
                    else if(count==1&&line[i]!=',')
                    {
                        n2+=line[i];
                    }
                }
            }
            readcounter.close();

            ofstream writefile("counter.txt");
            writefile<<n1<<","<<stoi(n2)+1<<endl;
            writefile.close();
        }
        else
        {
            cout<<"The quote is already present in philosophy.txt\n";
        }
    }
    
}

void view_all_users()
{
    string line;

    ifstream readfile("users.txt");
    cout<<"List of users:\n";
    while(getline(readfile, line))
    {
        cout<<line<<endl;
    }
    cout<<endl;
}

void show_login_history(string username)
{
    //username|date|time
    string line, username_in_file;

    ifstream readfile("login_data.txt");

    cout<<"username|date|time , date=dd-mm-yyyy , time=hh:mm:ss\n\nLogins:\n";
    while(getline(readfile, line))
    {
        for(int i=0; line[i]!='\0'; i++)
        {
            if(line[i]=='|')
            {
                break;
            }
            username_in_file+=line[i];
        }
        if(username==username_in_file)
        {
            cout<<line<<endl;
        }
        username_in_file="";
    }

    readfile.close();
}

void show_percentage_of_total_quotes_viewed(string username)
{
    string line, n1, n2;
    int count=0, total_quotes, quotes_viewed;
    double percentage;
    ifstream readcounter("counter.txt");

    while(getline(readcounter, line))
    {
        for(int i=0; line[i]!='\0'; i++)
        {
            if(line[i]==',')
            {
                count++;
            }
            if(count==0)
            {
                n1+=line[i];
            }
            else if(count==1&&line[i]!=',')
            {
                n2+=line[i];
            }
        }
    }
    readcounter.close();

    total_quotes=stoi(n1)+stoi(n2);

    count=0;
    ifstream readfile(username+".txt");
    while(getline(readfile, line))
    {
        count++;
    }
    readfile.close();
    percentage=((float)count/total_quotes)*100;

    cout<<"percentage of total quotes seen by \033[1m"<<username<<"\033[0m : "<<percentage<<"%"<<endl;
}

vector<string> findMostRepeatedStrings(const string* arr, int size)
{
    unordered_map<string, int> frequencyMap;
    vector<string> mostRepeatedStrings;
    int maxFrequency = 0;

    // Count the frequency of each string in the array
    for (int i = 0; i < size; ++i)
    {
        frequencyMap[arr[i]]++;
        int frequency = frequencyMap[arr[i]];
        if (frequency > maxFrequency)
        {
            maxFrequency = frequency;
            mostRepeatedStrings.clear();
            mostRepeatedStrings.push_back(arr[i]);
        }
        else if (frequency == maxFrequency)
        {
            mostRepeatedStrings.push_back(arr[i]);
        }
    }

    return mostRepeatedStrings;
}

void show_favorite_author(string username)
{
    int count=0, size=1, i=0, highest_rating=0;
    string line, author_in_file, rating;

    string *authors = new string[size];

    ifstream readfile(username+".txt");
    //loop to find highest rating
    while(getline(readfile, line))
    {
        for(int i=0; line[i]!='\0'; i++)
        {
            if(line[i]=='|')
            {
                count++;
            }
            if(count==2&&line[i]!='|')
            {
                rating+=line[i];
            }
        }
        if(highest_rating<stoi(rating))
        {
            highest_rating=stoi(rating);
        }
        count=0;
        rating="";
    }

    cout<<"highest rating given: "<<highest_rating<<endl;

    count=0;
    rating="";
    author_in_file="";

    readfile.close();

    ifstream Readfile(username+".txt");
    //loop to store authors of that rating
    while(getline(Readfile, line))
    {
        for(int i=0; line[i]!='\0'; i++)
        {
            if(line[i]=='|')
            {
                count++;
            }
            if(count==1&&line[i]!='|')
            {
                author_in_file+=line[i];
            }
            if(count==2&&line[i]!='|')
            {
                rating+=line[i];
            }
        }
        if(stoi(rating)==highest_rating)
        {
            authors[i]=author_in_file;
            i++;
            authors=resize_string_arr(authors, size);
        }
        count=0;
        author_in_file="";
        rating="";
    }
    Readfile.close();
    size--;

    vector<string> fav_authors = findMostRepeatedStrings(authors, size);

    cout << "favorite author(s): ";
    for (const auto& author : fav_authors)
    {
        cout << author << " . ";
    }
    cout << endl;

    delete[] authors;
}

void delete_a_user(string username)
{
    //delete form users.txt
    string line, username_in_file;

    ifstream readfile("users.txt");
    ofstream writefile("temp.txt");
    while(getline(readfile, line))
    {
        for(int i=0; line[i]!='\0'; i++)
        {
            if(line[i]==',')
            {
                break;
            }
            username_in_file+=line[i];
        }
        if(username_in_file==username)
        {
            username_in_file="";
            continue;
        }
        writefile<<line<<endl;
        username_in_file="";
    }
    readfile.close();
    writefile.close();

    remove("users.txt");
    rename("temp.txt", "users.txt");

    //delete username.txt
    remove((username+".txt").c_str());

    //delete login data
    ifstream Readfile("login_data.txt");
    ofstream Writefile("temp.txt");
    while(getline(Readfile, line))
    {
        for(int i=0; line[i]!='\0'; i++)
        {
            if(line[i]=='|')
            {
                break;
            }
            username_in_file+=line[i];
        }
        if(username_in_file==username)
        {
            username_in_file="";
            continue;
        }
        Writefile<<line<<endl;
        username_in_file="";
    }
    Readfile.close();
    Writefile.close();

    remove("login_data.txt");
    rename("temp.txt", "login_data.txt");

    cout<<username<<" deleted!\n";
}

int main()
{
    //rethink your approaches, do not always go for the simplest solution
    //login and sign up functionality added
    //menu made
    //a file named on user's name will store rated_quotes, number of logins, and more data

    //menu

    blind:

    int choice, count=0, search_count=0;
    string line, username, password, file_username, file_password;
    bool username_found=false;

    cout<<"\t\t\t\t\t\t\t\t\t\033[1mQuotiva\033[0m\n\n";
    cout<<"1) log in\n";
    cout<<"2) sign up\n";
    cout<<"3) About\n";
    cout<<"0) Exit\n";
    cout<<"Enter your choice: ";
    cin>>choice;
    if(choice==1)
    {
        //check user file
        system("cls");
        cout<<"\t\t\t\t\t\t\t\t\t\033[1mQuotiva\033[0m\n\n";
        cout<<"Enter your username: ";
        cin>>username;
        if(username=="UsmanAli")
        {
            cout<<"Enter password: ";
            cin>>password;
            if(password=="admin")
            {
                admin:
                system("cls");
                cout<<"\t\t\t\t\t\t\t\t\t\033[1mQuotiva\033[0m\n\n";
                cout<<"Welcome Back, Admin!\n\n";
                cout<<"1) Add a quote\n";
                cout<<"2) View the list of users\n";
                cout<<"0) go back\n";
                cout<<"Enter your choice: ";
                cin>>choice;
                if(choice==1)
                {
                    system("cls");
                    cout<<"\t\t\t\t\t\t\t\t\t\033[1mQuotiva\033[0m\n\n";
                    add_a_quote();
                    system("pause");
                    goto admin;
                }
                else if(choice==2)
                {
                    system("cls");
                    cout<<"\t\t\t\t\t\t\t\t\t\033[1mQuotiva\033[0m\n\n";
                    view_all_users();
                    string usrnm;
                    cout<<"Enter a username for more options: ";
                    cin>>usrnm;
                    cando:
                    system("cls");
                    cout<<"\t\t\t\t\t\t\t\t\t\033[1mDaily Motivation\033[0m\n\n";
                    cout<<"1) View login history\n";
                    cout<<"2) view percentage of total quotes seen\n";
                    cout<<"3) view favorite quotes\n";
                    cout<<"4) view favorite author(s)\n";
                    cout<<"5) delete the user\n";
                    cout<<"0) go back\n";
                    cout<<"Enter your choice: ";
                    cin>>choice;
                    if(choice==1)
                    {
                        system("cls");
                        cout<<"\t\t\t\t\t\t\t\t\t\033[1mQuotiva\033[0m\n\n";
                        show_login_history(usrnm);
                        system("pause");
                        goto cando;
                    }
                    else if(choice==2)
                    {
                        system("cls");
                        cout<<"\t\t\t\t\t\t\t\t\t\033[1mQuotiva\033[0m\n\n";
                        show_percentage_of_total_quotes_viewed(usrnm);
                        system("pause");
                        goto cando;
                    }
                    else if(choice==3)
                    {
                        system("cls");
                        cout<<"\t\t\t\t\t\t\t\t\t\033[1mQuotiva\033[0m\n\n";
                        cout<<"\033[1m"<<usrnm<<"\033[0m's favorite quotes: \n\n";
                        show_favorite_quotes(usrnm);
                        system("pause");
                        goto cando;
                    }
                    else if(choice==4)
                    {
                        system("cls");
                        cout<<"\t\t\t\t\t\t\t\t\t\033[1mQuotiva\033[0m\n\n";
                        cout<<"\033[1m"<<usrnm<<"\033[0m's favorite author: \n";
                        show_favorite_author(usrnm);
                        system("pause");
                        goto cando;
                    }
                    else if(choice==5)
                    {
                        system("cls");
                        cout<<"\t\t\t\t\t\t\t\t\t\033[1mQuotiva\033[0m\n\n";
                        delete_a_user(usrnm);
                        system("pause");
                        goto admin;
                    }
                    else if(choice==0)
                    {
                        goto admin;
                    }
                    
                }
                else if(choice==0)
                {
                    system("cls");
                    goto blind;
                }
            }
        }
        else
        {
            if(!isFileEmpty("users.txt"))
            {
                ifstream readfile("users.txt");
                while(getline(readfile, line))
                {
                    for(int i=0; line[i]!='\0'; i++)
                    {
                        if(line[i]==',')
                        {
                            count++;
                        }
                        if(count==0)
                        {
                            file_username+=line[i];
                        }
                        if(count!=0&&line[i]!=',')
                        {
                            file_password+=line[i];
                        }
                    }
                    count=0;
                    if(username==file_username)
                    {
                        mp:
                        cout<<"Enter password: ";
                        cin>>password;
                        if(password==file_password)
                        {
                            cout<<"Successfully logged in!\n\n";
                            ofstream appendfile("login_data.txt", ios::app);
                            appendfile<<username<<"|"<<getCurrentDate()<<"|"<<getCurrentTime()<<endl;
                            appendfile.close();

                            here:
                            cout<<"1) View a random quote\n";
                            cout<<"2) Search by keyword or by author's name\n";
                            cout<<"3) View favorite quotes\n";
                            cout<<"4) View favorite author\n";
                            cout<<"0) Menu\n\n";

                            cout<<"Enter your choice: ";
                            cin>>choice;
                            if(choice==1)
                            {
                                //show a random quote
                                int size_marr=1, size_parr=1;
                                int* marr = new int[size_marr];
                                int* parr = new int[size_parr];

                                srand(static_cast<unsigned>(time(0)));

                                marr=fill_random_array(marr, size_marr, 1);
                                parr=fill_random_array(parr, size_parr, 2);

                                while(true)
                                {
                                    system("cls");
                                    cout<<"\t\t\t\t\t\t\t\t\t\033[1mQuotiva\033[0m\n\n";
                                    cout<<"[Enter any number other than 1 or 2 to go back]\nWanna see something motivational(1) or philosophical(2)?: ";
                                    cin>>choice;
                                    if(choice==1)
                                    {
                                        show_a_random_quote(choice, marr, size_marr, username);
                                        system("pause");
                                    }
                                    else if(choice==2)
                                    {
                                        show_a_random_quote(choice, parr, size_parr, username);
                                        system("pause");
                                    }
                                    else
                                    {
                                        break;
                                    }   
                                }

                                delete[] marr;
                                delete[] parr;

                                system("cls");
                                cout<<"\t\t\t\t\t\t\t\t\t\033[1mQuotiva\033[0m\n\n";
                                goto here;
                            }
                            else if(choice==2)
                            {
                                //search something
                                system("cls");
                                cout<<"\t\t\t\t\t\t\t\t\t\033[1mQuotiva\033[0m\n\n";
                                string word_to_search;
                                cout<<"Enter author's name, quote, or a word to search: ";
                                cin.ignore();
                                getline(cin,word_to_search);
                                cout<<endl;
                                show_all_searched_m(word_to_search);
                                show_all_searched_p(word_to_search);
                                cout<<endl;

                                system("pause");
                                system("cls");
                                cout<<"\t\t\t\t\t\t\t\t\t\033[1mQuotiva\033[0m\n\n";
                                goto here;
                            }
                            else if(choice==3)
                            {
                                //show favorites
                                system("cls");
                                cout<<"\t\t\t\t\t\t\t\t\t\033[1mQuotiva\033[0m\n\n";

                                show_percentage_of_total_quotes_viewed(username);
                                cout<<"\n\033[1mFavorite quotes:\033[0m\n\n";
                                show_favorite_quotes(username);
                                cout<<endl;
                                system("pause");
                                system("cls");
                                cout<<"\t\t\t\t\t\t\t\t\t\033[1mQuotiva\033[0m\n\n";
                                goto here;
                            }
                            else if(choice==4)
                            {
                                system("cls");
                                cout<<"\t\t\t\t\t\t\t\t\t\033[1mQuotiva\033[0m\n\n";
                                show_favorite_author(username);
                                system("pause");
                                system("cls");
                                cout<<"\t\t\t\t\t\t\t\t\t\033[1mQuotiva\033[0m\n\n";
                                goto here;
                            }
                            else if(choice==0)
                            {
                                system("cls");
                                goto blind;
                            }
                        }
                        else
                        {
                            cout<<"wrong password!\n";
                            goto mp;
                        }
                        username_found=true;
                    }
                    file_username="";
                    file_password="";
                }
                readfile.close();
                if(!username_found)
                {
                    cout<<"No such username exists!\nSign up for a new account!\n";
                    //goto main menu
                    system("pause");
                    system("cls");
                    goto blind;
                }
            }
            else
            {
                cout<<"can't log in; no user records found!\n";
                system("pause");
                system("cls");
                goto blind;
            }
        }
        
    }
    else if(choice==2)
    {
        //check user file
        system("cls");
        cout<<"\t\t\t\t\t\t\t\t\t\033[1mQuotiva\033[0m\n\n";
        d:
        cout<<"Enter username: ";
        cin>>username;
        if(!isFileEmpty("users.txt"))
        {
            ifstream readfile("users.txt");
            while(getline(readfile, line))
            {
                for(int i=0; line[i]!='\0'; i++)
                {
                    if(line[i]==',')
                    {
                        break;
                    }
                    file_username+=line[i];
                }

                if(username==file_username)
                {
                    cout<<"The username already exists!\n";
                    file_username="";
                    username_found=true;
                    break;
                }
                file_username="";
            }
            readfile.close();

            if(username_found)
            {
                username_found=false;
                goto d;
            }
            else
            {
                cout<<"Enter password: ";
                cin>>password;
                ofstream writefile("users.txt", ios::app);
                writefile<<username<<","<<password<<endl;
                cout<<"Account created successfully!\n";
                writefile.close();
                ofstream Writefile(username+".txt");
                Writefile.close();
                
            }
        }
        else
        {
            cout<<"Enter password: ";
            cin>>password;
            ofstream writefile("users.txt", ios::app);
            writefile<<username<<","<<password<<endl;
            cout<<"Account created successfully!\n";
            writefile.close();
            ofstream Writefile(username+".txt");
            Writefile.close();
        }
        system("pause");
        system("cls");
        cout<<"\t\t\t\t\t\t\t\t\t\033[1mQuotiva\033[0m\n\n";
        cout<<"Welcome to Quotiva, \033[1m"<<username<<"\033[0m!"<<endl<<endl;
        ofstream appendfile("login_data.txt", ios::app);
        appendfile<<username<<"|"<<getCurrentDate()<<"|"<<getCurrentTime()<<endl;
        appendfile.close();

        here1:
        cout<<"1) View a random quote\n";
        cout<<"2) Search by keyword or by author's name\n";
        cout<<"3) View favorite quotes\n";
        cout<<"4) View favorite author\n";
        cout<<"0) Menu\n\n";

        cout<<"Enter your choice: ";
        cin>>choice;
        if(choice==1)
        {
            //show a random quote
            int size_marr=1, size_parr=1;
            int* marr = new int[size_marr];
            int* parr = new int[size_parr];

            srand(static_cast<unsigned>(time(0)));

            marr=fill_random_array(marr, size_marr, 1);
            parr=fill_random_array(parr, size_parr, 2);

            while(true)
            {
                system("cls");
                cout<<"\t\t\t\t\t\t\t\t\t\033[1mQuotiva\033[0m\n\n";
                cout<<"[Enter any number other than 1 or 2 to go back]\nWanna see something motivational(1) or philosophical(2)?: ";
                cin>>choice;
                if(choice==1)
                {
                    show_a_random_quote(choice, marr, size_marr, username);
                    system("pause");
                }
                else if(choice==2)
                {
                    show_a_random_quote(choice, parr, size_parr, username);
                    system("pause");
                }
                else
                {
                    break;
                }   
            }

            delete[] marr;
            delete[] parr;

            system("cls");
            cout<<"\t\t\t\t\t\t\t\t\t\033[1mQuotiva\033[0m\n\n";
            goto here1;
        }
        else if(choice==2)
        {
            //search something
            system("cls");
            cout<<"\t\t\t\t\t\t\t\t\t\033[1mQuotiva\033[0m\n\n";
            string word_to_search;
            cout<<"Enter author's name, quote, or a word to search: ";
            cin.ignore();
            getline(cin,word_to_search);
            cout<<endl;
            show_all_searched_m(word_to_search);
            show_all_searched_p(word_to_search);
            cout<<endl;

            system("pause");
            system("cls");
            cout<<"\t\t\t\t\t\t\t\t\t\033[1mQuotiva\033[0m\n\n";
            goto here1;
        }
        else if(choice==3)
        {
            //show favorites
            system("cls");
            cout<<"\t\t\t\t\t\t\t\t\t\033[1mQuotiva\033[0m\n\n";

            show_percentage_of_total_quotes_viewed(username);
            cout<<"\n\033[1mFavorite quotes:\033[0m\n\n";
            show_favorite_quotes(username);
            cout<<endl;
            system("pause");
            system("cls");
            cout<<"\t\t\t\t\t\t\t\t\t\033[1mQuotiva\033[0m\n\n";
            goto here1;
        }
        else if(choice==4)
        {
            system("cls");
            cout<<"\t\t\t\t\t\t\t\t\t\033[1mQuotiva\033[0m\n\n";
            show_favorite_author(username);
            system("pause");
            system("cls");
            cout<<"\t\t\t\t\t\t\t\t\t\033[1mQuotiva\033[0m\n\n";
            goto here1;
        }
        else if(choice==0)
        {
            system("cls");
            goto blind;
        }
    }
    else if(choice==3)
    {
        system("cls");
        cout<<"\t\t\t\t\t\t\t\t\t\033[1mQuotiva\033[0m\n\n";
        cout<<"This program was coded by \033[1mUsman Ali\033[0m, a very hard working lad\nIf you want to suggest any changes, feel free to contact him through any of the following channels:\n";
        cout<<"whatsapp: +923000968255\n";
        cout<<"email: aottoman551@gmail.com\n\n";
        system("pause");
        system("cls");
        goto blind;
    }
    else if(choice==0)
    {
        return 0;
    }
    else
    {
        goto blind;
    }

    return 0;
}
