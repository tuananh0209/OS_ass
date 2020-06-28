#include "dbLib.h"

class ProcessData
{
private:
	static const int MAXSIZECODE = 8;
	static int split(string line, string *&sp);

public:
	ProcessData();
	~ProcessData();
	int process(string line);
	
};

// enum BalanceValue
// {
// 	LH = -1,
// 	EH = 0,
// 	RH = 1
// };

struct rating {
	int time;
	float BP;
	float AP;
	int height;
	struct rating *left;
	struct rating *right;
	// BalanceValue balance;
};


struct deal {
	string obOrOs;
	int id;
	float lot;
	int time;
	float mnDeal;
	bool open;

	struct deal* left;
	struct deal* right;
	int height;
};

struct bc_qc
{
	string bc;
	string qc;
	struct bc_qc *next;
	struct rating *link;
	struct deal *linkDeal;
};

int insert(struct bc_qc **curr, string *p, int n);
struct rating *insertAVL(struct rating *currNode, string *p);
int deleteRating(struct bc_qc **currNode, string *p, int n);

bool checkDataInsert(string p, int n);
bool checkFloat(string a);
bool checkInt(string a);
bool checkString(string a);
bool checkins_upd(string * sp, int n);
bool check_BC_PC(struct BC_QC * node, string bc, string qc);
bool checkst_del(string * sp, int n);
struct rating *newNode(string * p);
struct rating *rightRotate(struct rating * y);
struct rating *leftRotate(struct rating * x);
int getBalance(struct rating * N);
int height(struct rating * N);
int max(int a, int b);
void getTime(string *p, int *timeA, int *timeB, int n);
void findRating(struct rating *node, int timeA, int timeB , string *a);
void deleteNode(struct rating *node, int timeA, int timeB);
int updRating(struct bc_qc **currNode, string *p, int n);
int sd(string *p, int n);
int cd();
int sl(string *p , int n);
int ob(struct bc_qc **currNode, string *p, int n);
int cb(struct bc_qc **currNode, string *p, int n);