#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include "SocialMediaAccount.h"
class SocialMediaAccount;
using namespace std;

class Person:public enable_shared_from_this<Person>{
private:
  string name;
  vector<shared_ptr<SocialMediaAccount>> media_accounts;
public:
  Person(string);
  string get_name() const;
  int add_account(string, int = 1 );
  bool remove_account(int);
  bool share(shared_ptr<Person>, shared_ptr<SocialMediaAccount>);
  ostream& print(ostream&) const;
  ostream& print_small(ostream&) const;
  const vector<shared_ptr<SocialMediaAccount>>& get_accounts() const;
};

struct Administration {
    unordered_map<string,shared_ptr<Person>> u_map;
    string create_person(string name){
        shared_ptr<Person> p = make_shared<Person>(name);
        u_map[name] = p;
        return name;
    }
    void del_person(string name){
        auto it = u_map.find(name);
        if(it == end(u_map)) throw runtime_error("Unexisting Person!");
        u_map.erase(it);
    }
    ostream& print(ostream& o) const{
        o << "Map: [" << endl;
        for (auto i : u_map){
            i.second -> print(o);
            o << endl;
        }
        o << "]";
        return o;
    }
};



#endif
