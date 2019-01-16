#include "Person.h"
#include "SocialMediaAccount.h"
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <stdexcept>
#include <algorithm>
//shared_from_this()

using namespace std;


Person::Person(string s) {
        if (s.empty()) throw runtime_error {"Empty name!"};
	name = s;
	media_accounts = {};
}

string Person::get_name() const { return name;}

int Person::add_account(string s, int x) {
	shared_ptr<Person> p(shared_from_this());
	shared_ptr<SocialMediaAccount> account;

	if(x==1){
		account = make_shared<VipAccount>(s, p);
	} else if(x==0){
		account = make_shared<NormalAccount>(s, p);
	}
	else throw runtime_error("Invalid Parameter!");
	media_accounts.push_back(account);
	return account -> get_accountnumber();
}

bool Person::remove_account (int id) {
    auto it = find_if(media_accounts.begin(),media_accounts.end(), [&] (shared_ptr<SocialMediaAccount> sma) {return sma->get_accountnumber() == id;});
    bool found = it != end(media_accounts);
    media_accounts.erase(remove_if(media_accounts.begin(),media_accounts.end(), [&] (shared_ptr<SocialMediaAccount> sma) {return sma->get_accountnumber() == id;}));
	return found;
}

bool Person::share(shared_ptr<Person> p, shared_ptr<SocialMediaAccount> sma) {
    auto it = find(media_accounts.begin(),media_accounts.end(), sma);
    bool found1 = it != end(media_accounts);
    vector<shared_ptr<SocialMediaAccount>> accounts = p->get_accounts();
    auto it2 = find(accounts.begin(),accounts.end(),sma);
    bool found2 = it2 != end(accounts);
    if((found1 && found2) || !found1 ){
       return false;
    }
    else {
    p->media_accounts.push_back(sma);
    sma->add_person(p);
    return true;
    }
}

ostream& Person::print(ostream& o) const
{
	o<<"[Name: "<<name<<", Account: {";
    for (auto i : media_accounts){
        i->print_small(o);
    }
	o<<"}]";
return o;
}

ostream& Person::print_small(ostream& o) const {
	o << name;
	return o;
}

const vector<shared_ptr<SocialMediaAccount>>& Person:: get_accounts() const {return media_accounts;}
