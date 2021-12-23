#include <iostream>
#include <string>
#define MAX 1000

using namespace std;

string lower (string s);
int check (string s, string arr[], int len);
void sorting (int len, int frequency[], string arr[]);
void del (int len, string arr[]);

string lower (string s) {
	for(int j= 0; j < s.length(); j++)
		s[j] = tolower( s[j] );
	return s;
} 

int check (string s, string arr[], int len) {
	int k= 0;
	while (k<len) {
		if(arr[k] == s) {
			return k;
		}
	k++;
	}
	return -1;
}

void sorting (int len, int frequency[], string arr[]) {
	int fretemp;
	string temp;
	for(int i= 1; i<len; i++) {
		for(int j= 0; j<len-i; j++) {
			if(arr[j+1] < arr[j]) {
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
					fretemp = frequency[j];
					frequency[j] = frequency[j+1];
					frequency[j+1] = fretemp;
			}
		}
	}
}

void del (int len, string arr[]) {
	for(int i= 0; i<len; i++)
		for(int j= i+1; j< len; ) {
			if(arr[i]==arr[j]) {
				for(int x= 0; x<len-1; x++)
					arr[x]=arr[x+1];   
					--len;
			}
			else
				j++;
		}
}

int main () {
	string s;
	string arr[MAX];
	int frequency[MAX];
	int pomf;
	int len;

	while(cin >> s) {
		s = lower (s);
		arr[len] = s;
		pomf = check (s, arr, len);

		if(pomf >= 0) {
			frequency[pomf]++;
		}

		else {
			frequency[len]++;
			len++;
		}
	}

	sorting (len,frequency,arr);
	del (len,arr);

	cout << "Vocabulary Size = " << len << endl;
	for(int i= 0; i<len; i++) {
		cout << arr[i] << " " << frequency[i] << endl;
	}

	return 0;
}
