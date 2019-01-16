#ifndef SOCIAL_MEDIA_ACCOUNT_H_INCLUDED
#define SOCIAL_MEDIA_ACCOUNT_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Person.h"

class Person;
using namespace std;

class SocialMediaAccount{
private:
 constexpr static size_t message_limit{100};

 int score;
 string name;
 int accountnumber = 0;
 static int n;
 vector<weak_ptr<Person>> authorized_persons;
 vector<string> messages;

 void add_msg(const string s) {messages.push_back(s); score += calc_score(s); }

public:
 SocialMediaAccount(string, shared_ptr<Person>);
 virtual ~SocialMediaAccount();
 bool add_person(shared_ptr<Person>);
 bool clear_weak_ptr();
 void clear_messages();
 virtual int calc_score(string) = 0;
 void write_msg(shared_ptr<SocialMediaAccount>, string);
 size_t size() const;
 int get_accountnumber() const;
 virtual ostream& print(ostream&) const;
 ostream& print_small(ostream&) const;
};

class VipAccount: public SocialMediaAccount{

public:
  VipAccount(string, shared_ptr<Person>);
  ostream& print(ostream&) const;
  int calc_score(string);
};

class NormalAccount: public SocialMediaAccount{

public:
  NormalAccount(string, shared_ptr<Person>);
  ostream& print(ostream&) const;
  int calc_score(string);
};



#endif
