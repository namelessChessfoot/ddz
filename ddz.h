using namespace std;
string cardList[15]= {"3","4","5","6","7","8","9","10","J","Q","K","A","2","X","Y"};
#define WangZha 9999
#define ZhaDan 999
#define DanZhang 0
#define DuiZi 1
#define SanZhang 2
#define SanDaiYi 3
#define SanDaiEr 4
#define ShunZi 5
#define LianDui 6
#define LianSan 7
#define FeiJiDanChi 8
#define FeiJiShuangChi 9
class ct
{
public:
    int theCardType,val1,val2;
    int tran(string str,vector<int> &ans)
    {
        ans.clear();
        int i,tag;
        for(i=0; i<str.size(); ++i)
        {
            if(str[i]=='1')
            {
                if(i+1==str.size()) return 0;
                if(str[i+1]!='0') return 0;
                ans.push_back(7);
                ++i;
            }
            else
            {
                string t;
                t+=toupper(str[i]);
                tag=1;
                for(int j=0; j<15; ++j)
                {
                    if(t==cardList[j])
                    {
                        ans.push_back(j);
                        tag=0;
                        break;
                    }
                }
                if(tag) return 0;
            }
        }
        return 1;
    }
    int checker(string str)
    {
        int tag,a[15]= {0},i,LEI=0,le;
        vector<int> preprocess;
        if(tran(str,preprocess)==0) return 0;
        sort(preprocess.begin(),preprocess.end());
        le=preprocess.size();
        if(le==2&&preprocess[0]==13&&preprocess[1]==14)///王炸
        {
            theCardType=WangZha;
            return 1;
        }
        if(le==4)///炸弹
        {
            tag=1;
            for(int i=0; i<3; ++i)
            {
                if(preprocess[i]!=preprocess[i+1])
                {
                    tag=0;
                    break;
                }
            }
            if(tag==1)
            {
                theCardType=ZhaDan;
                val1=preprocess[0];
                return 1;
            }
        }
        if(le==1)///单张
        {
            theCardType=DanZhang;
            val1=preprocess[0];
            return 1;
        }
        if(le==2)///对子
        {
            if(preprocess[0]!=preprocess[1]) return 0;
            theCardType=DuiZi;
            val1=preprocess[0];
            return 1;
        }
        if(le==3)///三张
        {
            if(preprocess[0]==preprocess[1]&&preprocess[0]==preprocess[2])
            {
                theCardType=SanZhang;
                val1=preprocess[0];
                return 1;
            }
            return 0;
        }
        if(le==4)///三带一？
        {
            int b[2];
            for(i=0; i<4; ++i)
            {
                if(a[preprocess[i]]==0)
                {
                    if(LEI<2) b[LEI]=preprocess[i];
                    ++LEI;
                }
                ++a[preprocess[i]];
            }
            if(LEI!=2) return 0;
            if(a[b[0]]==3) val1=b[0];
            else if(a[b[1]]==3) val1=b[1];
            else return 0;
            theCardType=SanDaiYi;
            return 1;
        }
        if(le==5)///三带二或者顺子
        {
            for(i=0; i<5; ++i)
            {
                if(a[preprocess[i]]==0) ++LEI;
                ++a[preprocess[i]];
            }
            if(LEI!=2&&LEI!=5) return 0;
            if(LEI==5)
            {
                int tag=1;
                for(i=0; i<4; ++i)
                {
                    if(preprocess[i]+1!=preprocess[i+1])
                    {
                        tag=0;
                        break;
                    }
                }
                if(tag==0) return 0;
                theCardType=ShunZi;
                val1=5;
                val2=preprocess[0];
                return 1;
            }
            if(LEI==2)
            {
                i=0;
                while(a[i]!=3) ++i;
                theCardType=SanDaiEr;
                val1=i;
                return 1;
            }
        }
        for(i=0; i<le; ++i)
        {
            if(a[preprocess[i]]==0) ++LEI;
            ++a[preprocess[i]];
        }
        if(LEI==le)///顺子
        {
            tag=1;
            for(i=1; i<le; ++i)
            {
                if(preprocess[i]-1!=preprocess[i-1])
                {
                    tag=0;
                    break;
                }
            }
            if(tag==0) return 0;
            theCardType=ShunZi;
            val1=le;
            val2=preprocess[0];
            return 1;
        }
        else if(2*LEI==le)///连对
        {
            tag=1;
            for(i=0; i<le-2; i+=2)
            {
                if(preprocess[i]+1!=preprocess[i+2]||preprocess[i]!=preprocess[i+1])
                {
                    tag=0;
                    break;
                }
            }
            if(preprocess[i]!=preprocess[i+1]) tag=0;
            if(tag==1)///连对匹配成功
            {
                theCardType=LianDui;
                val1=LEI;
                val2=preprocess[0];
                return 1;
            }
            ///尝试三带一对

        }
        else if(3*LEI==le)///连三
        {
            tag=1;
            for(i=0; i<le-3; i+=3)
            {
                if(preprocess[i]+1!=preprocess[i+3]||preprocess[i]!=preprocess[i+1]||preprocess[i]!=preprocess[i+2])
                {
                    tag=0;
                    break;
                }
            }
            if(preprocess[i]!=preprocess[i+1]||preprocess[i]!=preprocess[i+2]) tag=0;
            if(tag==1)///连三匹配成功
            {
                theCardType=LianSan;
                val1=LEI;
                val2=preprocess[0];
                return 1;
            }
        }
        if(le%4==0)///尝试三带一飞机
        {
            i=0;
            while(a[i]!=3) ++i;
            val2=i;
            for(i=0; a[val2+i]==3; ++i) ;
            if(i*4==le)
            {
                val1=i;
                theCardType=FeiJiDanChi;
                return 1;
            }
        }
        if(le%5==0)///尝试三带二飞机
        {
            i=0;
            while(a[i]!=3) ++i;
            val2=i;
            for(i=0; a[val2+i]==3; ++i) ;
            if(i*5==le)
            {
                val1=i;
                theCardType=FeiJiShuangChi;
                int c2=0;
                for(i=0; i<15; ++i)
                {
                    if(a[i]==2) ++c2;
                    if(c2==val1) break;
                }
                if(c2==val1) return 1;
            }
        }
        return 0;//unknown
    }
    bool canFollow(ct last)
    {
        if(last.theCardType==-1) return true;
        if(theCardType==WangZha) return true;
        if(theCardType==ZhaDan)
        {
            if(val1>last.val1) return true;
            return false;
        }
        if(theCardType!=last.theCardType) return false;
        if(theCardType>=0&&theCardType<5)
        {
            if(val1>last.val1) return true;
            else return false;
        }
        if(val1!=last.val1) return false;
        if(val2>last.val2) return true;
        return false;
    }
};
class card
{
public:
    int myCard[108],NumberOfCards;
    card(int n=0)
    {
        int i,j;
        NumberOfCards=0;
        srand((int)time(NULL));
        for(i=0; i<13; ++i)
        {
            for(j=0; j<4*n; ++j) myCard[NumberOfCards++]=i;
        }
        for(i=13; i<15; ++i)
        {
            for(j=0; j<n; ++j) myCard[NumberOfCards++]=i;
        }
    }
    void show()
    {
        cout<<"牌  // ";
        for(int i=0; i<NumberOfCards; ++i)
        {
            cout<<cardList[myCard[i]]<<' ';
        }
        cout<<"//   "<<NumberOfCards<<"张剩余"<<endl;
    }
    void getCard(int n)
    {
        myCard[NumberOfCards++]=n;
    }
    void ShellSort()
    {
        int i,j,k,l,t,span=NumberOfCards/2;
        while(span)
        {
            for(i=0; i<span; ++i)
            {
                for(j=i; j<NumberOfCards-span; j=j+span)
                {
                    t=myCard[j+span];
                    k=j;
                    while(k>=0&&myCard[k]>t)
                    {
                        myCard[k+span]=myCard[k];
                        k-=span;
                    }
                    myCard[k+span]=t;
                }
            }
            span/=2;
        }
    }
    void shuffle()
    {
        int i,j,t;
        for(i=0; i<NumberOfCards; ++i)
        {
            j=rand()%NumberOfCards;
            t=myCard[i];
            myCard[i]=myCard[j];
            myCard[j]=t;
        }
    }
};
class player
{
public:
    string name,identity;
    int score;
    card myCard;
    player()
    {

    }
    player(int myScore)
    {
        string rubbish;
        cin>>name;
        getline(cin,rubbish);
        score=myScore;
        identity="未知";
    }
    void setInfo(int myScore)
    {
        string rubbish;
        cout<<"请输入玩家昵称： ";
        cin>>name;
        getline(cin,rubbish);
        score=myScore;
        identity="未知";
    }
    void show(int opt=0)///para=1, show card
    {
        cout<<"玩家:"<<name<<"   积分:"<<score<<"   身份:"<<identity<<endl;
        if(opt) myCard.show();
    }
    string &getName()
    {
        return name;
    }
    void setID(string ID)
    {
        identity=ID;
    }
    void getCard(int a)
    {
        myCard.getCard(a);
    }
    void mySort()
    {
        myCard.ShellSort();
    }
    void noCard()
    {
        myCard.NumberOfCards=0;
    }
    bool canPut(string str)
    {
        ct help;
        vector<int> hh;
        help.tran(str,hh);
        int a[15]= {0},b[15]= {0},i;
        for(i=0; i<hh.size(); ++i) ++a[hh[i]];
        for(i=0; i<myCard.NumberOfCards; ++i) ++b[myCard.myCard[i]];
        for(i=0; i<15; ++i)
        {
            if(a[i]>b[i]) return false;
        }
        return true;
    }
    void GoGoGo(string str)
    {
        int i,j;
        vector<int> tr;
        ct help;
        help.tran(str,tr);
        for(i=0; i<tr.size(); ++i)
        {
            for(j=0; j<myCard.NumberOfCards; ++j)
            {
                if(tr[i]==myCard.myCard[j])
                {
                    myCard.myCard[j]=99999;
                    break;
                }
            }
        }
        mySort();
        myCard.NumberOfCards-=tr.size();
    }
    bool hasWin()
    {
        if(myCard.NumberOfCards==0) return true;
        return false;
    }
    void account(int a)
    {
        score+=a;
    }
};
class Game
{
private:
    int CardSet,NumbersOfPalyers;
    player *ListOfPlayer;
    vector<string> Recorder;
    string rubbish;
public:
    Game(int myCard,int myPlayer,int score)
    {
        CardSet=myCard;
        NumbersOfPalyers=myPlayer;
        ListOfPlayer=new player[NumbersOfPalyers];
        for(int i=0; i<NumbersOfPalyers; ++i) ListOfPlayer[i].setInfo(score);
    }
    void showGame()
    {
        cout<<'\n'<<CardSet<<"副牌, "<<NumbersOfPalyers<<"名玩家\n"<<endl;
        for(int i=0; i<NumbersOfPalyers; ++i) ListOfPlayer[i].show();
    }
    bool canPlay()
    {
        for(int i=0; i<NumbersOfPalyers; ++i)
        {
            if(ListOfPlayer[i].score<=0) return false;
        }
        return true;
    }
    int LetsPlay(int start)
    {
        int i,j,k,basePoints=0,ans,LandLord=-1;
        card AllCard(CardSet);
        AllCard.shuffle();
        for(i=0; i<NumbersOfPalyers; ++i) ListOfPlayer[i].noCard();
        for(i=0; i<AllCard.NumberOfCards-3; ++i) ListOfPlayer[i%NumbersOfPalyers].getCard(AllCard.myCard[i]);
        for(i=0; i<NumbersOfPalyers; ++i) ListOfPlayer[i].mySort();
        for(i=0; i<NumbersOfPalyers&&basePoints<3; ++i)
        {
            system("cls");
            ListOfPlayer[(start+i)%NumbersOfPalyers].setID("未知");
            ListOfPlayer[(start+i)%NumbersOfPalyers].show(1);
            ans=-1;
            while((ans<=basePoints&&ans!=0)||(ans<0||ans>3))
            {
                cout<<"当前底分："<<basePoints<<endl;
                for(j=basePoints+1; j<=3; ++j) cout<<j<<"分？";
                cin>>ans;
                getline(cin,rubbish);
            }
            if(ans!=0)
            {
                basePoints=ans;
                LandLord=(start+i)%NumbersOfPalyers;
            }
        }
        if(basePoints==0) return 0;
        for(i=0; i<NumbersOfPalyers; ++i)
        {
            ListOfPlayer[i].setID(i==LandLord?"地主":"农民");
        }
        system("cls");
        cout<<ListOfPlayer[LandLord].getName()<<"是本轮地主"<<endl;
        cout<<"底牌是 ";
        for(i=AllCard.NumberOfCards-3; i<AllCard.NumberOfCards; ++i)
        {
            cout<<cardList[AllCard.myCard[i]]<<' ';
            ListOfPlayer[LandLord].getCard(AllCard.myCard[i]);
        }
        cout<<endl;
        ListOfPlayer[LandLord].mySort();
        Recorder.clear();
        ct last,cp;
        last.theCardType=-1;
        i=LandLord;
        system("pause");
        while(true)
        {
            system("cls");
            for(j=0; j<Recorder.size(); ++j) cout<<Recorder[j]<<endl;
            cout<<"*当前底分 "<<basePoints<<"\n///////////////////////"<<endl;
            Recorder.push_back(ListOfPlayer[i].getName());
            Recorder[j]+="  ";
            Recorder[j]+=ListOfPlayer[i].identity;
            ListOfPlayer[i].show(1);
            cout<<"请出牌（不需空格） 不出请输入T"<<endl;
            string ChuPai;
            cin>>ChuPai;
            getline(cin,rubbish);
            for(k=0; k<ChuPai.size(); ++k) ChuPai[k]=toupper(ChuPai[k]);
            while((last.theCardType==-1&&ChuPai=="T")||(ChuPai!="T"&&(ListOfPlayer[i].canPut(ChuPai)==false||cp.checker(ChuPai)==0||cp.canFollow(last)==false)))
            {
                cout<<"错误，请重新出牌（不需空格） 不出请输入T"<<endl;
                cin>>ChuPai;
                getline(cin,rubbish);
                for(k=0; k<ChuPai.size(); ++k) ChuPai[k]=toupper(ChuPai[k]);
            }
            Recorder[j]+="   ";
            Recorder[j]+=ChuPai;
            if(ChuPai!="T")
            {
                ListOfPlayer[i].GoGoGo(ChuPai);
                if(cp.theCardType>=999) basePoints*=2;
                last=cp;
            }
            else
            {
                int p=Recorder[j-1].size();
                if(Recorder[j-1][p-1]=='T')
                {
                    last.theCardType=-1;
                    Recorder.clear();
                }
            }
            if(ListOfPlayer[i].hasWin()) break;
            ++i;
            i%=NumbersOfPalyers;
        }
        system("cls");
        cout<<"本轮结束！   ";
        if(i==LandLord)
        {
            cout<<"地主胜！"<<endl;
            for(k=0; k<NumbersOfPalyers; ++k)
            {
                ans=k==LandLord?(2*basePoints):(-1*basePoints);
                cout<<ListOfPlayer[k].getName()<<"   得分 "<<ans<<endl;
                ListOfPlayer[k].account(ans);
            }
        }
        else
        {
            cout<<"农民胜！"<<endl;
            for(k=0; k<NumbersOfPalyers; ++k)
            {
                ans=k==LandLord?(-2*basePoints):(basePoints);
                cout<<ListOfPlayer[k].getName()<<"   得分 "<<ans<<endl;
                ListOfPlayer[k].account(ans);
            }
        }
        for(k=0; k<NumbersOfPalyers; ++k) ListOfPlayer[k].show();
        return i;
    }
    ~Game()
    {
        system("cls");
        cout<<"最终情况"<<endl;
        for(int i=0; i<NumbersOfPalyers; ++i)
        {
            ListOfPlayer[i].setID("未知");
            ListOfPlayer[i].show();
        }
        delete []ListOfPlayer;
        cout<<"游戏结束！！！"<<endl;
    }
};
