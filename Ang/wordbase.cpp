#include "wordbase.h"
#include<QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <algorithm>
#include<iterator>

void WordSet::addWord(QString pln, QString ang)
{
    Word temp{pln, ang};
    set->push_back(temp);

}
void WordSet::clear()
{
    set->clear();

}
QString WordSet::getWordSetString() const
{

   QString temp;
   if(set->empty())
   {
       temp.push_back("Pusto :(");
   }
   else
   {
       for(int i = 0; i<set->size(); i++) //create QString contain every word in Wird Library
       {
           temp.push_back(set->at(i).getEngPln() + "\n");
       }
   }

   return temp;
}
////////WordBase///////////
WordBase::WordBase(const QString &filename):
    baseFileName(filename)
{

    loadBase();
    test = new Test("terminator.txt");
}

int WordBase::addNewSet(WordSet &newS)
{
    int ID = base->size()+1;
    base->insert(ID, newS);
    return ID;
}

QSet<int> WordBase::lateSet() const
{
    auto temp = test->lateSet(); // get all set of word who user shoud repeat but faill
    auto d = temp.toList();
    auto c = d.toSet(); // erase reccuring words set
    return c;
}

void WordBase::BaseStrUpdate(WordSet &newS)
{
      baseString->remove('&');
      baseString->append(QString::number(base->size())+"\n<br>\n");
      baseString->append(newS.getWordSetString());
      baseString->append("* <br>\n&");

}
void WordBase::loadBase()
{

    base = new QMap <int, WordSet>;

    QFile file(baseFileName);

    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug()<<"nie moge otworzyc pliku Base";
        return;

    }
    QTextStream stream(&file);
    baseString = new QString(stream.readAll());
    stream.seek(0); //reset position
    int n = 0;
    QString pln, eng, temp, x;
    WordSet tempSet;
    while(!stream.atEnd())
    {
        temp = stream.readLine();
        if(temp=="* <br>")
        {
            base->insert(n, std::move(tempSet));
            tempSet.clear();
            continue;
        }
        else if(temp=="&")
        {
            return;
        }
        else if(temp=="<br>")
        {
            continue;
        }
        else
        {
            if(temp.toInt()==0)
            {
                QTextStream take(&temp);
                while(true)
                {
                    x.clear();
                    take>>x;
                    if(x=="-") break;
                    pln +=x;
                    pln +=" ";
                }
                while(true)
                {
                    x.clear();
                    take>>x;
                    if(x=="<br>") break;
                    eng +=x;
                    eng +=" ";
                }

                //take>>eng;
                tempSet.addWord(pln, eng);
                pln.clear();
                eng.clear();
            }
            else if(temp.toInt())
            {
                n = temp.toInt();
            }
        }
    }


    file.close();
}

void WordBase::saveBase()
{
    QFile file(baseFileName);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug()<<"nie moge otworzyc pliku";
        return;
    }

    QTextStream stream(&file);

    stream<<getBaseString();

    file.close();
}

WordSet* WordBase::getSet(int setID) const
{
    return &(*base)[setID];
            //base->value(setID);

}
//////////////TEST/////////////////////
void Test::calcTerm(int ID)
{
    using namespace std;
   QVector<int> rep_date;
   const int s_day = 86400; ///1 day in second
   rep_date.push_back(getDate(s_day));
   rep_date.push_back(getDate(s_day * 3));
   rep_date.push_back(getDate(s_day * 8));
   rep_date.push_back(getDate(s_day * 17));
   rep_date.push_back(getDate(s_day * 32));

   for_each(rep_date.begin(), rep_date.end(), [&](auto rep){
       if(term->find(rep) == term->end())
       {
           term->insert(rep, QVector<int>());
           (*term)[rep].push_back(ID);

       }
       else
       {
           (*term)[rep].push_back(ID);
       }
   });
   saveData(); ///save new generate term to terminator.txt file
}

QVector<int> Test::lateSet() const
{
    int today = getDate(0);
    QVector<int> temp;
    auto it = term->lowerBound(today);
    std::for_each(term->begin(), it, [&temp](auto t){

        temp +=t;
    });
    return temp;
}

QVector<int> Test::todaySet() const
{
    int today = getDate(0);
    auto d = term->find(today);
    if(d == term->end()) return QVector<int>();
    else return d.value();
}

void Test::erSetfTer(int ID)
{
    int today = getDate(0);
    auto it = term->lowerBound(today);
    std::for_each(term->begin(), it+1, [&ID](auto &i){
        auto new_end = std::remove(i.begin(), i.end(), ID);
        i.erase(new_end, i.end());
    });

    saveData();
}

int Test::getDate(time_t sec) const
{
    time_t dt = time(0);
    dt += sec;
    tm* data = gmtime(&dt);
    return (data->tm_mday + (data->tm_mon) * 100 + data->tm_year * 10000);
}

void Test::loadData()
{
    term = new QMap <int, QVector<int>>;
    termString = new QString;

    QFile file("terminator.txt");

    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug()<<"nie moge otworzyc pliku Data";
        return;
    }

    QTextStream stream(&file);
    int date = 0;
    QString line;
    QVector<int> IDs;

    termString = new QString(stream.readAll());
    stream.seek(0); //reset position

    while(!stream.atEnd())
    {
        line = stream.readLine();
        QTextStream temp(&line);
        temp >> date;
        while(!temp.atEnd())
        {
            int i;
            temp >> i;
            if(i==0) continue;
            IDs.push_back(i);
        }
        term->insert(date, IDs);
        IDs.clear();
    }

    file.close();
}

void Test::saveData()
{
    QFile file(baseFileName);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug()<<"nie moge otworzyc pliku Data";
        return;
    }

    QTextStream stream(&file);

    for(auto e: term->toStdMap())
    {
        if(e.second.empty()) continue;
        stream << e.first;
        stream <<" ";
        for(auto i: e.second)
        {
            stream << i;
            stream <<" ";
        }
            stream <<"\n";
    }

    file.close();

}
