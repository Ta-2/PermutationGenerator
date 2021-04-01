#include <string>
#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

template<class U>
class PermutationGenerator{
private:
	         vector<pair<bool, U>> source;
	typename vector<pair<bool, U>>::iterator send = source.end(); /**/
	         vector<typename vector<pair<bool, U>>::iterator> itrs;
	typename vector<typename vector<pair<bool, U>>::iterator>::iterator begin = itrs.begin(); /**/
	typename vector<typename vector<pair<bool, U>>::iterator>::iterator end = itrs.end(); /**/
	vector<U> result;
	int stage = 0;
	bool GenFlag = false; /**/
public:
	int all = 0;
	void AddElement(U add){
		source.push_back(make_pair(true, add));
		if(result.capacity() < source.size())result.reserve(source.size());
		if(itrs.capacity() < source.size())itrs.reserve(source.size());
		cout << "source.size: " << source.size() << ", result.capacity: " << result.capacity() << endl;
		GenFlag = false; /**/
	}
	void reset(){
		source.clear();
		Initialize();
		GenFlag = false; /**/
	}
	void Initialize(){
		send = source.end(); /**/
		result.clear();
		itrs.clear();
		GenFlag = false;
		return;
	}
	void Gen(int extract = -1){
		Initialize();
		GenFlag = true;
		for(typename vector<pair<bool, U>>::iterator s = source.begin(); s != source.end() && extract; s++, extract--){
			result.push_back(s->second);
			s->first = false;
			itrs.push_back(s);
		}
		begin = itrs.begin(); /**/
		end = itrs.end(); /**/
		return;
	}
	bool nextPermutation(){
		typename vector<typename vector<pair<bool, U>>::iterator>::iterator it = itrs.end();
		for( typename vector<typename vector<pair<bool, U>>::iterator>::reverse_iterator rit = itrs.rbegin(); rit != itrs.rend(); rit++){
			typename vector<pair<bool, U>>::iterator elem = *rit;
			while(!elem->first && elem != source.end()) elem++;
 			result.pop_back();
			(*rit)->first = true;
			if(elem != source.end()){
				result.push_back(elem->second);
				elem->first = false;
				it = --rit.base();
				*it = elem;
				break;
			}
		}
		if(it == itrs.end())return false;
		auto s = source.begin();
			it++;
		while(it != itrs.end()){
			while(!s->first && s != source.end())s++;
			*it = s;
			s->first = false;
			result.push_back(s->second);
			it++;
		}
		return true;
	}
	bool nextPermutation2(){
		typename vector<typename vector<pair<bool, U>>::iterator>::iterator rit = end;
		cout << "nextPer" << endl;
		while(previous_begin(&rit)){
			cout << (*rit)->second;
			//while(!(*itr)->first && (*itr) != send)--(*itr);
			//result.pop_back();
			//();

			//if(itr == begin)break;
		}

		return true;
	}
	inline bool previous_begin(typename vector<typename vector<pair<bool, U>>::iterator>::iterator* it){
		if(it == NULL){
			//cout << "its NULL" << endl;
			return false;
		} else if(*it == begin){
			//cout << "its begin" << endl;
			it = NULL;
			return false;
		} else {
			//cout << "its other" << endl;
			--(*it);
			return true;
		}
	}
	inline bool next_begin(typename vector<typename vector<pair<bool, U>>::iterator>::iterator* it){
		if(it == NULL){
			*it = begin;
			return true;
		} else return false;
	}

	void PrintAllPermutation(){
		Initialize();
		AllPermutation();
	}
	void AllPermutation(){
		if(stage == (int)source.size()){
			all++;
			for(auto r: result) cout << r;
			cout << endl;
			return;
		}
		for(typename vector<pair<bool, U>>::iterator s = source.begin(); s != source.end(); s++){
			if(s->first){
				stage++;
				result.push_back(s->second);
				s->first = false;
				AllPermutation();
				result.pop_back();
				s->first = true;
				stage--;
			}
		}
		return;
	}
	vector<pair<bool, U>>* Getsource(){
		return &source;
	}
	const vector<U>* GetResult (){
		return &result;
	}
	void PrintSource(){
		cout << "<<source>>: ";
		for(auto s: source)cout << s.second << ", ";
		cout << endl;
	}
	void PrintResult(){
		cout << "<<result>>: ";
		for(auto r: result)cout << r;
		cout << endl;
	}
};

int main(int argc, char *argv[]){
	int elems[] = {0, 1, 2, 3};
	PermutationGenerator<int*> *pg = new PermutationGenerator<int*>;
	
	for(int &a: elems) pg->AddElement(&a);
	pg->PrintSource();
	/*
	pg->PrintAllPermutation();
	cout << "all: " << pg->all << endl;
	*/
	pg->Gen();
	pg->PrintResult();
	int num = 1;
	while(pg->nextPermutation()){
		//pg->PrintResult();pg2		//error
		for(auto r: *(pg->GetResult())) cout << *r;
		cout << endl;
		num++;
	}
	cout << "all: " << num << endl;

	PermutationGenerator<char> *pg2 = new PermutationGenerator<char>;
	cout << "Permutation of \"CRYPTO\" " << endl;
	for(char &s: string("CRYPTO") )pg2->AddElement(s);
	pg2->Gen();
	pg2->nextPermutation2();
	/*
	pg2->PrintSource();
	pg2->AllPermutation();
	
	pg2->reset();
	cout << "Permutation of \"C\" " << endl;
	for(char &s: string("C") )pg2->AddElement(s);
	pg2->PrintSource();
	pg2->AllPermutation();
	
	pg2->reset();
	for(char &s: string("CR") )pg2->AddElement(s);
	pg2->PrintSource();
	pg2->AllPermutation();

	pg2->reset();
	for(char &s: string("CRYPTO") )pg2->AddElement(s);
	
	if(argc > 1)pg2->Gen((int)atoi(argv[1]));
	else pg2->Gen(3);
	num = 1;
	pg2->PrintResult();
	while(pg2->nextPermutation()){
		pg2->PrintResult();
		num++;
	}
	cout << "all: " << num << endl;
	*/
	return 0;
}
