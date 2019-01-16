#include "Person.h"
#include "SocialMediaAccount.h"
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <stdexcept>
#include <algorithm>

using namespace std;
int SocialMediaAccount::n = 0;
SocialMediaAccount::SocialMediaAccount(string s, shared_ptr<Person> p) {
	score = 0;
    name = s;
    n++;
    accountnumber = n;
    authorized_persons = {};
    messages = {};
    add_person(p);
}

SocialMediaAccount::~SocialMediaAccount() {clear_weak_ptr();}

bool SocialMediaAccount::add_person(shared_ptr<Person> p) {
    if(authorized_persons.size() == 0){
        weak_ptr<Person> w = p;
        authorized_persons.push_back(w);
        return true;
    }
    vector<shared_ptr<SocialMediaAccount>> sma = p -> get_accounts();
    bool found;
    auto it = find_if(authorized_persons.begin(), authorized_persons.end(), [&] (const weak_ptr<Person>& ptr) {return ptr.lock() == p;});
    found = it != end(authorized_persons);
    if(found)
        return false;
    weak_ptr<Person> weak = p;
    authorized_persons.push_back(weak);
    return true;
    }

bool SocialMediaAccount::clear_weak_ptr() {
    bool removed = false;
    for_each(authorized_persons.begin(),authorized_persons.end(), [&] (weak_ptr<Person> p) {if (p.expired()) p.reset(); removed = true;});
    return removed;
    }

void SocialMediaAccount::clear_messages() {
    messages.clear();
    }

void SocialMediaAccount::write_msg(shared_ptr<SocialMediaAccount> p, string s) {
    if(messages.size() == message_limit) throw runtime_error("Limit reached!");
    add_msg(s);
    p->add_msg(s);
}


int SocialMediaAccount::get_accountnumber() const {return accountnumber;}

ostream& SocialMediaAccount::print(ostream& o) const {
    o << "[Name: " << name << ", id:" << accountnumber << ", Msgs: {";
    for(size_t i{0}; i < messages.size(); i++){
        o << messages[i];
        if(i != messages.size()-1)
            o << ", ";
    }
    o << "}, Owner: {";
    for(size_t i{0}; i < authorized_persons.size();i++){
       o <<authorized_persons[i].lock()->get_name();
       if(i != authorized_persons.size()-1)
        o << ", ";
    }
    o << "}, Score: " << score << "]";
    return o;}

ostream& SocialMediaAccount::print_small(ostream& o) const {
    o <<"[Name: " << name <<", Owner: {" ;
    for(size_t i{0}; i < authorized_persons.size();i++){
       o <<authorized_persons[i].lock()->get_name();
       if(i != authorized_persons.size()-1)
        o << ", ";
    }
    o << "}, #Msgs: " << messages.size() <<" ]";
    return o;
    }

NormalAccount::NormalAccount(string s, shared_ptr<Person> p) : SocialMediaAccount(s,p) {}

ostream& NormalAccount::print(ostream& o) const {
 SocialMediaAccount::print(o);
 o << "(Normal)";
 return o;
}

int NormalAccount::calc_score(string s) {return (5+s.size())%10;}

VipAccount::VipAccount (string s, shared_ptr<Person> p) : SocialMediaAccount(s,p) {}

ostream& VipAccount::print(ostream& o) const {
 SocialMediaAccount::print(o);
 o << " (VIP)";
 return o;
}

int VipAccount::calc_score(string s) {return (10+s.size())%20;}

