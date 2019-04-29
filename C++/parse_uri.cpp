#include <stdio.h>
#include <iostream>
#include <string>
#include <map>

using namespace std;


string  uri_trim(const string &str)
{
	size_t start = str.find_first_not_of(" \t\n\r");
	size_t end = str.find_last_not_of(" \t\n\r");
	
string::const_iterator s = (start == string::npos) ? str.begin() : (str.begin() + start);
    string::const_iterator e = (end == string::npos) ? str.end()   : (str.begin() + end + 1);
  
	return string(s, e);
}

int cdn_parse_uri(const string &raw_uri, map<string, string> &http_headers)
{
	if(raw_uri.empty()){
		return -1;
	}
	
	string domain;
	string url;
	string params;
	string uri = uri_trim(raw_uri);
	

    int offset = 0;
    size_t pos1, pos2;
	
	
    offset = offset==0 && uri.compare(0, 8, "https://") == 0 ? 8 : offset;
    offset = offset==0 && uri.compare(0, 7, "http://" ) == 0 ? 7 : offset;
	
	
	
    pos1 = uri.find_first_of('/', offset+1 );
    url = (pos1 == string::npos) ? "" : uri.substr(pos1);
	
    domain = string( uri.begin() + offset, pos1 != string::npos ? (uri.begin() + pos1) : uri.end() );
	
	
    params = (pos2 = url.find("?")) != string::npos ? url.substr(pos2 + 1) : "";
    url = pos2 != string::npos ? url.substr(0,pos2) : url;


    http_headers["host"] = domain;
    http_headers["url"] = url;
    http_headers["params"] = params;

	
//	cout << "domain: " << domain << endl;
//	cout << "url: " << url << endl;
//	cout << "params: " << params << endl;
	
	return 0;
}

void print_map(map<string, string> &http_headers)
{
   map<string, string> ::iterator iter;
   
   for(iter = http_headers.begin(); iter != http_headers.end(); iter++){
       cout << iter->first << " : " << iter->second << endl;
   }

}

int main()
{
      string uri("http://www.google.com/webhp/a/b/c?gws_rd=ssl&a=1&sam=sb"); 
      //string uri("http://www.google.com/webhp/a/b/c");
//	string uri("http://www.google.com");
	map<string, string> http_headers;
	cdn_parse_uri(uri, http_headers);
 
    print_map(http_headers);
	
    return 0;	
}

