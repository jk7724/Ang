#ifndef WORDBASE_H
#define WORDBASE_H

#include<QString>
#include<QVector>
#include<QMap>
#include<QDebug>

QT_BEGIN_NAMESPACE
class QString;
QT_END_NAMESPACE

class WordBase;
class Word //this class use to contain polish-english pair of word
{
public:
    Word(){}
    ~Word(){}
    Word(QString &pln, QString &eng):
        plnWord(pln),
        engWord(eng)
    {}
    QString getEng() const {return engWord;}
    QString getPln() const {return plnWord;}
    QString getEngPln() const {return plnWord + " - " + engWord + " <br> ";}
private:
    QString plnWord;
    QString engWord;
};

class WordSet //this class contain set composed of many Word class object.
{
public:
    WordSet(QVector<Word>* s=nullptr):
        set(s)
    {

        set = new QVector<Word>;
    }
    WordSet(const WordSet& a)
    {
        set = new QVector<Word>;
        *set = *a.set;
    }
    WordSet& operator=(const WordSet& a)
    {
        // Self-assignment detection
        if (&a == this)
            return *this;

        // Release any resource we're holding
        delete set;

        // Copy the resource
        set = new QVector<Word>;
        *set = *a.set;

        return *this;
    }
    WordSet(WordSet &&a):
        set(a.set)
    {
        a.set = nullptr;
    }

    WordSet& operator=(WordSet &&a)
    {
        if(&a == this)
        {
            return *this;
        }
        delete set;
        set = a.set;
        a.set = nullptr;
        return *this;

    }
    int getSize(){return set->size();}
    void addWord(QString pln, QString ang);
    void clear();
    void addID(int id){ID = id;}
    QString getEng(int i) const {
        return set->value(i).getEng();
    }
    QString getPln(int i) const {
        return set->value(i).getPln();
    }
    QString getEngPln(int i) const {return set->value(i).getEngPln();}
    QString getWordSetString() const;
private:
    QVector<Word> *set;
    int ID;

};

class Test // this class is dedicated to every action connected with repeating words.
{
public:
    Test(const QString &name) : baseFileName(name)
        {
            loadData();
        }
        ~Test()
        {
        }
    void calcTerm(int ID); ///calculate date repetition -> 2, 5, 9, 15 day after learn word
    void testDay(const WordBase& wb); ///testujemy umiejetnosci
    void eraseTerm(int date) { term->erase(term->find(date));}
    QVector<int> lateSet() const; //return IDs sets who user dont repeat in termin.
    QVector<int> todaySet() const; ///return IDs sets to repeat today.
    void erSetfTer(int ID); //erase chosen(ID) Set from term
private:
    QMap <int , QVector<int>> *term; // key store date of repetition, QVector store what set will be repetition
    QString *termString;
    QString baseFileName;

    int getDate(time_t sec) const; /// return present date format to integer : rrrmmdd/// sec represent time add to present date
    void loadData(); ///load data from file to term
    void saveData();///save data from term to file
};


class WordBase // this class contain all of word sets.
{

public:
    WordBase(const QString &filename);
    QString& getBaseFileName()
    {
        return baseFileName;
    }
    int addNewSet(WordSet &newS); ///return ID of newS set
    void addTerm(int ID){
        test->calcTerm(ID);
    }

    QString getEngPln(int ID, int i) const {
        return base->value(ID).getEngPln(i);

    }
    QString getWordSetString(int ID) const {
        return base->value(ID).getWordSetString();
    }
    QString& getBaseString()
    {
        return *baseString;
    }
    QSet<int> lateSet() const; ///making unique!
    QVector<int> todaySet() const{return test->todaySet();} ///return IDs sets to repeat today.
    //int repWordCount();
    void BaseStrUpdate(WordSet &newS);
    void saveBase();
    WordSet* getSet(int setID) const; //from QMap base
    void erSetfTer(int ID){test->erSetfTer(ID);} //erase chosen(ID) Set from term
private:
    Test *test;
    QString baseFileName;
    QString *baseString; // whole base word in string
    QMap <int, WordSet> *base; //whole base word

    void loadBase();


};

#endif // WORDBASE_H
