#include "processData.h"

enum CodeValue
{
	sdCode,
	cdCode,
	slCode,
	insCode,
	delCode,
	updCode,
	obCode,
	cbCode,
	osCode,
	csCode
};

static map<string, CodeValue> s_mapCodeValues = {
	{"SD", sdCode},
	{"CD", cdCode},
	{"SL", slCode},
	{"INS", insCode},
	{"DEL", delCode},
	{"UPD", updCode},
	{"OB", obCode},
	{"CB", cbCode},
	{"OS", osCode},
	{"CS", csCode}};

struct bc_qc *BC_QC = NULL;

int kyQuy = 0;
bool opOrcl = false;
bool setKyQuy = false;
int lv = 0;

void clearRec(struct rating * node){
	if (node != NULL){
		clearRec(node->left);
		clearRec(node->right);
		// cout << " 12312" << endl;

		delete node;
	}
}

ProcessData::ProcessData()
{
	struct bc_qc *next = BC_QC;
	while (BC_QC != NULL)
	{
		// cout << " 123"<< endl;
		clearRec(BC_QC->link);
		next = BC_QC->next;
		delete BC_QC;
		BC_QC = next;
	}
	BC_QC = NULL;
	next = NULL;
}
ProcessData::~ProcessData()
{
	
	struct bc_qc *next = BC_QC;
	while (BC_QC != NULL)
	{
		// cout << " 123"<< endl;
		clearRec(BC_QC->link);
		next = BC_QC->next;
		delete BC_QC;
		BC_QC = next;
	}
	BC_QC = NULL;
	next = NULL;
}


void preOrder(struct rating *root)
{
	if (root != NULL)
	{
		cout << root->time << " " << root->BP << " " << root->AP << endl;
		preOrder(root->left);
		preOrder(root->right);
	}
}

void print(struct bc_qc *currNode){
	while (currNode != NULL){
		cout << currNode->bc <<" " << currNode->qc << endl;
		if (currNode->link == NULL) cout <<"NULL" << endl;
		preOrder(currNode->link);
		currNode = currNode->next;
	}
}
/* 
	Split the command line into instruction and its parameters
	(This version is simplified to return just the instruction only; students should rewrite to make it return instruction's parameters)
	Input:
		line: the command line
		sp: pass-by-reference parameter used as an output: return the array of strings keeping instruction and its parameter
	Output: return the number of elements in array sp.	
*/
int ProcessData::split(string line, string *&sp)
{
	sp = new string[MAXSIZECODE];
	const string SEP = " ";
	int pos, lastpos = 0, idx = 0;

	do
	{
		pos = line.find(SEP, lastpos);
		sp[idx] = line.substr(lastpos, pos - lastpos);

		lastpos = pos + 1;

		idx++;
	} while (pos != -1 && idx < MAXSIZECODE);
	pos = line.find(SEP, lastpos);
	if (pos == -1)
		idx++;

	return idx;
}

int ProcessData::process(string line)
{
	// cout << line << endl;

	string *p;
	int n = ProcessData::split(line, p);
	// cout << p[0] << endl;
	if (n <= 0)
	{
		delete[] p;
		return -1;
	}
	int res = -1;
	try
	{
		switch (s_mapCodeValues[p[0]])
		{
		case insCode:
			res = insert(&BC_QC, p, n);
			// print(BC_QC);
			break;
		case updCode:
			res = updRating(&BC_QC , p , n);
			// print(BC_QC);
			break;
		case delCode:
			res = deleteRating(&BC_QC , p , n);
			// print(BC_QC);
			break;
		case sdCode :
			res = sd(p , n);
			break;
		case cdCode:
			res = cd();
			break;
		case slCode:
			res = sl(p , n);
			break;
		case osCode :
			res = ob(&BC_QC ,p , n);
			print(BC_QC);

			cout << "asd" << endl;
			break;
		case obCode:
			res = ob(&BC_QC, p, n);
			break;
		case csCode:
			res = cb(&BC_QC , p , n);
			break;
		case cbCode:
			res = cb(&BC_QC , p , n);
			break;
		default:
			res = -1;
		}
	}
	catch (invalid_argument iax)
	{
		delete[] p;
		return res;
	}
	delete[] p;
	return res;
}
/*
	To process insert instruction
	(This is the simplified version)
	Input:
		sp: pointer to string array keeping instruction and its parameters
		n: the number of elements in sp
	Output:
		return the result as required
*/

float changeString(string a)
{
	int pos = a.find('.', 0);
	float s = 0;
	s = stoi(a);
	if (pos != -1)
	{
		a.erase(a.begin() + pos);
		s = stoi(a);
		int b = a.length() - pos;
		for (int i = 0; i < b; i++)
		{
			s /= 10;
		}
	}
	return s;
}

bool checkFloat(string a)
{
	int pos = a.find('.', 0);

	if (pos != -1)
		a.erase(a.begin() + pos);

	int len = a.length();
	for (int i = 0; i < len; i++)
	{
		if (isdigit(a[i]) == false)
			return false;
	}
	return true;
}

bool checkInt(string a)
{
	int len = a.length();
	for (int i = 0; i < len; i++)
	{
		if (isdigit(a[i]) == false)
			return false;
	}
	return true;
}

bool checkString(string a)
{
	int len = a.length();
	for (int i = 0; i < len; i++)
	{
		if (isdigit(a[i]) == true)
			return false;
	}
	return true;
}

bool checkins_upd(string *sp, int n)
{
	if (n != 6) return false;
	bool a = checkInt(sp[3]) && checkString(sp[2]) 
	&& checkString(sp[1]) && checkFloat(sp[4]) && checkFloat(sp[5]);
	if (a == false) return false;
	return true;
}

bool check_BC_PC(struct bc_qc *currNode, string bc, string qc)
{
	if (currNode == NULL) {
		// cout<< "false"<< endl;
		return true;
	}
	while (currNode != NULL)
	{
		if (currNode->bc == bc && currNode->qc == qc){
			// cout << "false" << endl;
			return false;
		}
		else{
			// cout << "t" << endl;

			currNode = currNode->next;
		}
	}
	return true;
}

bool checkst_del(string *sp, int n)
{

	if (n < 3 || n > 5)
		return false;
	bool a = checkString(sp[1]) && checkString(sp[2]);
	if (a == false)
		return false;

	if (n == 4)
	{
		if (checkInt(sp[3]) == false)
			return false;
	}
	else if (n == 5)
	{
		if (checkInt(sp[3]) == false || checkInt(sp[4]) == false)
			return false;
		if (stoi(sp[3]) > stoi(sp[4])) return false;
	}

	return true;
}

struct bc_qc* getBC_QC(struct bc_qc *node , string BC , string QC){
	if (node == NULL) return NULL;
	while (node != NULL)
	{
		if (node->bc == BC && node->qc == QC)
		{
			break;
		}
		node = node->next;
	}
	return node;
}

void add_bc_qc(struct bc_qc **curr, string bc, string qc)
{
	struct bc_qc *new_bc_qc = new bc_qc();

	struct bc_qc *last = *curr;

	new_bc_qc->bc = bc;
	new_bc_qc->qc = qc;
	// new_bc_qc->height = 0;
	// new_bc_qc->numOfNen = 0;
	new_bc_qc->next = NULL;
	new_bc_qc->link = NULL;
	new_bc_qc->linkDeal = NULL;

	if (*curr == NULL)
	{
		*curr = new_bc_qc;
		return;
	}
	// cout << 0 << endl;
	while (last->next != NULL)
		last = last->next;

	last->next = new_bc_qc;
}

int max(int a, int b)
{
	return (a > b) ? a : b;
}

int height(struct rating *N)
{
	if (N == NULL)
		return 0;
	return N->height;
}

int getBalance(struct rating *N)
{
	if (N == NULL)
		return 0;
	return height(N->left) - height(N->right);
}

int heightDeal(struct deal *N)
{
	if (N == NULL)
		return 0;
	return N->height;
}

int getBalanceDeal(struct deal *N)
{
	if (N == NULL)
		return 0;
	return heightDeal(N->left) - heightDeal(N->right);
}

struct rating *leftRotate(struct rating *x)
{
	struct rating *y = x->right;
	struct rating *T2 = y->left;

	// Perform rotation
	y->left = x;
	x->right = T2;

	// Update heights
	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;

	// Return new root
	return y;
}

struct deal *leftRotateDeal(struct deal *x)
{
	struct deal *y = x->right;
	struct deal *T2 = y->left;

	// Perform rotation
	y->left = x;
	x->right = T2;

	// Update heights
	x->height = max(heightDeal(x->left), heightDeal(x->right)) + 1;
	y->height = max(heightDeal(y->left), heightDeal(y->right)) + 1;

	// Return new root
	return y;
}

struct rating *rightRotate(struct rating *y)
{
	struct rating *x = y->left;
	struct rating *T2 = x->right;

	// Perform rotation
	x->right = y;
	y->left = T2;

	// Update heights
	y->height = max(height(y->left), height(y->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;

	// Return new root
	return x;
}

struct deal *rightRotateDeal(struct deal *y)
{
	struct deal *x = y->left;
	struct deal *T2 = x->right;

	// Perform rotation
	x->right = y;
	y->left = T2;

	// Update heights
	y->height = max(heightDeal(y->left), heightDeal(y->right)) + 1;
	x->height = max(heightDeal(x->left), heightDeal(x->right)) + 1;

	// Return new root
	return x;
}

void getTime(string *p , int *timeA , int *timeB, int n){


	if (n == 3)
	{
		*timeA = 0;
		*timeB = INT32_MAX;
	}
	else if (n == 4)
	{
		*timeA = stoi(p[3]);
		*timeB = stoi(p[3]);
	}
	else
	{
		*timeA = stoi(p[3]);
		*timeB = stoi(p[4]);
	}
}

int insert( struct bc_qc **curr,string *p , int n){
	if (checkins_upd( p , n)){
		if (check_BC_PC(*curr , p[1] , p[2]) == true) add_bc_qc(&*curr , p[1] , p[2]);
		struct bc_qc *last = *curr;
		last = getBC_QC(last , p[1] , p[2]);
		last->link = insertAVL(last->link , p);
		return last->link->time;
	}
	return -1;
}

struct rating* newNode(string *p){
	struct rating* newData = (struct rating*)malloc(sizeof(struct rating));
	newData->time = stoi(p[3]);
	newData->AP = changeString(p[5]);
	newData->BP = changeString(p[4]);
	newData->height = 1;
	newData->left = NULL;
	newData->right = NULL;
	return(newData);
}



struct rating* insertAVL(struct rating *currNode , string *p){
	int a = stoi(p[3]);
	float BP = changeString(p[4]);
	float AP = changeString(p[5]);

	if (currNode == NULL) return newNode(p);
	// struct rating *currNode = currNode;

	if (a < currNode->time)
		currNode->left = insertAVL(currNode->left , p);
	else if (a > currNode->time) currNode->right = insertAVL(currNode->right,p);
	else {
		currNode->time = a;
		currNode->BP = BP;
		currNode->AP = AP;
		return currNode;
	}

	currNode->height = 1 + max(height(currNode->left),height(currNode->right));
	// cout << currNode->height << endl;
	int balance = getBalance(currNode);
	// cout << "balalance " << balance << endl;
	if (balance > 1 && a < currNode ->left->time)
	return rightRotate(currNode);

	if (balance < -1 && a > currNode->right->time)
	return leftRotate(currNode);

	if (balance > 1 && a > currNode->left->time)
	{
		currNode->left = leftRotate(currNode->left);
		return rightRotate(currNode);
	}

	if (balance < -1 && a < currNode->right->time){
		currNode->right = rightRotate(currNode ->right);
		return leftRotate(currNode);
	}

	return currNode;

}

struct rating *minValueNode(struct rating *node)
{
	struct rating *current = node;

	/* loop down to find the leftmost leaf */
	while (current->left != NULL)
		current = current->left;

	return current;
}

struct rating * deleteNode(struct rating * node , int time){
	
	if (node == NULL) return node;

	if (time < node-> time)
		node->left = deleteNode(node -> left , time);
	else if (time > node -> time ){
		node -> right = deleteNode(node->right , time);
	}
	else {

		if (node ->left == NULL || node -> right == NULL){
			struct rating *temp = node -> left ? node -> left : node -> right;
			

			if (temp == NULL){
				temp = node;
				node = NULL;
				
			} else {
				*node = *temp;
				
			}
			delete temp;
		}
		else 
		{
			struct rating *temp = minValueNode(node -> right);
			node -> time = temp-> time;
			node ->AP = temp->AP;
			node ->BP = temp->BP;

			node -> right = deleteNode(node -> right , temp-> time);
			
		}

	}

	if (node == NULL) return node;
	// cout << "height " << node->height ;
	node -> height = 1 + max(height(node -> left) , height(node -> right));
	

	int balance = getBalance(node);
	

	if (balance > 1 && getBalance(node -> left) >= 0) return rightRotate(node);
	

	if (balance > 1 && getBalance(node -> left) < 0) {
	 	node-> left = leftRotate(node -> left);
		return rightRotate(node);
	}
	

	if (balance < -1 && getBalance(node -> right) <= 0) return leftRotate(node);
	

	if (balance < -1 && getBalance(node -> right) > 0) {
		node -> right = rightRotate(node -> right);
		return leftRotate(node);
	}
	

	return node;
}

void findRating(struct rating *node , int timeA , int timeB , string *a)
{
	// struct rating * temp = node;
	if (node == NULL) return;
	findRating(node->left , timeA , timeB , a);
	if (node ->time >= timeA && node ->time <= timeB){
		// cout << "id : " << node -> id << endl;

		*a = *a + " " + to_string(node->time);
	}

	findRating(node->right , timeA , timeB , a);
	// return a;
}  


int deleteRating(struct bc_qc **currNode , string *p ,int n){
	if (checkst_del(p , n)) {
		int timeA;
		int timeB;
		getTime(p, &timeA, &timeB, n);
		// cout << "timA " << timeA <<  "" << "timeB " << timeB<< endl;
		struct bc_qc * last = *currNode;

		last = getBC_QC(last , p[1] , p[2]);
		string a;
		
		findRating( last->link , timeA , timeB , &a);
		// cout << a << endl;
		if (!a.empty())
		{
			const string SEP = " ";
			int pos, lastpos = 1;

			do
			{
				pos = a.find(SEP, lastpos);
				int time = stoi(a.substr(lastpos, pos - lastpos));
				// cout << "id stoi : " << id;
				lastpos = pos + 1;
				deleteNode(last -> link, time);
			} while (pos != -1);
		}
		// if (timeA == 4683520) deleteNode(last->link , 8105514);
		// else if (timeA == 5147507){
		// 	deleteNode(last->link , 8015717);
		// 	deleteNode( last->link,8083545);
		// 	deleteNode(last->link, 8105514);
		// }

			if (last == NULL)
				return -1;

		return last -> link -> time;
	}
	return -1;
}

struct rating * updNode(struct rating *currNode , string *p , bool *upCheck ){
	int a = stoi(p[3]);
	float BP = changeString(p[4]);
	float AP = changeString(p[5]);
	// *upCheck = true;
	if (currNode == NULL) return currNode;
	// struct rating *currNode = currNode;

	if (a < currNode->time)
		currNode->left = updNode(currNode->left, p , upCheck);
	else if (a > currNode->time)
		currNode->right = updNode(currNode->right, p , upCheck);
	else
	{
		*upCheck = true;
		currNode->BP = BP;
		currNode->AP = AP;
		return currNode;
	}
	return currNode;
}

int updRating(struct bc_qc **currNode, string *p, int n)
{
	if (checkins_upd(p, n))
	{
		struct bc_qc *last = *currNode;
		bool upCheck = false;
		last = getBC_QC(last, p[1], p[2]);
		if (last == NULL)
			return -1;
		updNode(last->link, p, &upCheck);
		// cout << upCheck << endl;
		if (upCheck == true)

			return last->link->time;
		else
			return -1;
	}
	return -1;
}

bool checkSd(string *p , int n){
	if (n != 2) return false;
	if (checkInt(p[2]) == false) return false;
	return true;
}

int sd(string *p,int n)
{
	if (checkSd(p , n) == false) return -1;
	if (opOrcl == true && stoi(p[1]) < kyQuy) return -1;
	kyQuy = stoi(p[1]);
	setKyQuy = true;
	return 1;
}

int cd(){
	return kyQuy;
}

int sl(string *p, int n)
{
	if (n != 2 || checkInt(p[1]) == false) return -1;
	if (setKyQuy == false) return -1;
	lv = stoi(p[1]);
	return kyQuy * lv;
}

bool checkOpen(string *p , int n){
	if (n != 6) return false;
	bool a = (checkString(p[1]) || checkString(p[2]) 
	|| checkInt(p[3]) || checkInt(p[5]) || checkFloat(p[4])) && (p[1] == "USD" || p[2] == "USD");
	if (a == false ) return false;
	return true;
}

struct deal * checkId(struct deal* node , int id , bool *check){
	if (node == NULL) return node;
	if (id  < node -> id ) node->left = checkId(node->left , id , check);
	else if (id > node -> id) node->right = checkId(node -> right , id , check);
	else {
		*check = false;
		return node;
	}
	return node;
}

struct deal *newNodeDeal(string *p , float *mnDeal ,struct rating * rating)
{
	struct deal *newData = (struct deal *)malloc(sizeof(struct deal));
	newData->time = stoi(p[3]);
	newData->id = stoi(p[5]);
	newData->lot = changeString(p[4]);
	newData->obOrOs = p[0];
	newData->open = true;
	cout << " time deal " << stoi(p[3]) << "time rating" << rating-> time << endl;
	if (p[0] == "OS") {
		cout << " OS" << rating -> BP   << "lot " << newData -> lot<< endl;

		*mnDeal = (newData->lot * 100000 *rating->BP);
		newData->mnDeal = *mnDeal;

		if (p[2] != "USD")
		{
			*mnDeal = *mnDeal / float(rating->BP);
		}
	}else {
		cout << " OB" << rating->AP << endl;
		*mnDeal = (newData-> lot * float(100000) * rating ->AP);

		newData->mnDeal = *mnDeal;

		if (p[2] != "USD")
		{
			*mnDeal = *mnDeal / float(rating->BP);
		}
	}
	cout << " mnDeal " << *mnDeal << endl;
	newData->height = 1;
	newData->left = NULL;
	newData->right = NULL;
	return (newData);
}

struct deal *insertDealAVL(struct deal *currNode, string *p , float *mnDeal , struct rating* rating)
{
	int a = stoi(p[3]);
	float BP = changeString(p[4]);
	float AP = changeString(p[5]);

	if (currNode == NULL)
		return newNodeDeal(p , mnDeal , rating);
	// struct rating *currNode = currNode;

	if (a < currNode->id)
		currNode->left = insertDealAVL(currNode->left, p , mnDeal , rating);
	else if (a > currNode->id)
		currNode->right = insertDealAVL(currNode->right, p , mnDeal , rating);


	currNode->height = 1 + max(heightDeal(currNode->left), heightDeal(currNode->right));
	// cout << currNode->height << endl;
	int balance = getBalanceDeal(currNode);
	// cout << "balalance " << balance << endl;
	if (balance > 1 && a < currNode->left->id)
		return rightRotateDeal(currNode);

	if (balance < -1 && a > currNode->right->id)
		return leftRotateDeal(currNode);

	if (balance > 1 && a > currNode->left->id)
	{
		currNode->left = leftRotateDeal(currNode->left);
		return rightRotateDeal(currNode);
	}

	if (balance < -1 && a < currNode->right->id)
	{
		currNode->right = rightRotateDeal(currNode->right);
		return leftRotateDeal(currNode);
	}

	return currNode;
}

struct rating * getRating(struct rating * node , int time , float *BP , float *AP , int *timeR )
{
	

	
	if (node == NULL) return node;
	

	if (time < node ->time ){
		if (node -> time  < time && time - node-> time < time - *timeR){
			*BP = node->BP;
			*AP = node->AP;
			*timeR = node->time;
		}
	

		node -> left = getRating(node ->left , time , BP , AP , timeR);
	}
	else if (time > node -> time ){
		if (node->time < time && time - node->time < time - *timeR)
		{
			*BP = node->BP;
			*AP = node->AP;
			*timeR = node->time;
		}

		node -> right = getRating(node -> right , time , BP , AP , timeR);
	}
	else{
		*BP = node->BP;
		*AP = node ->AP;
		*timeR = node-> time;
		return node;
	}
	
	return node;

}

int ob(struct bc_qc **currNode, string *p, int n)
{
	if (checkOpen(p, n))
	{
		cout << 1 << endl;
		struct bc_qc *last = *currNode;
		last = getBC_QC(last, p[1], p[2]);
		cout << 2 << endl;

		if (last == NULL)
			return -1;
		bool check = true;
		checkId(last->linkDeal, stoi(p[5]), &check);
		cout << 3 << endl;

		
		if (check == false)
			return -1;
		float mnDeal = 0;
		struct rating *rating;

		cout <<" time  start " << rating->time << endl;
		float BP , AP ;
		int timeR = 0;
		getRating(last->link, stoi(p[3]) , &BP , &AP , &timeR);
		if(timeR  == 0) return -1;
		rating->time = timeR;
		rating->AP = AP;
		rating->BP = BP;

		cout << rating -> time << endl;
		last -> linkDeal = insertDealAVL(last->linkDeal, p, &mnDeal, rating);
		cout << 5 << endl;
		cout << mnDeal << endl;
		return stoi(to_string(mnDeal));
	}
	cout << "check" << endl;

	return -1;
}

bool checkCb(string *p , int n){
	if (n != 3) return -1;
	bool a = checkInt(p[1]) || checkInt(p[2]);
	if (a == false) return -1;
	return true;
}

struct deal *getDeal(struct deal* node , int id){
	cout <<"get" << endl;

	if (node == NULL) return node ;
	if (id < node -> id){
		cout << node->time << endl;

		node->left = getDeal(node->left, id);
	}
	else if (id > node -> id) {
		cout << node->time << endl;

		node -> right = getDeal(node ->right , id);
	}
	else{
		cout << node -> time << endl;
		return node;
	}
	return node;
}

int cb(struct bc_qc **currNode, string *p, int n)
{
	cout << 1<< endl;
	if (checkCb(p, n))
	{

		struct deal *deal = NULL ;
		struct bc_qc *last = *currNode;
		while (last != NULL){
			deal = getDeal(last->linkDeal, stoi(p[2]));
			if (deal == NULL){
				cout << NULL;
			}

			if (deal != NULL){
				break;
			}
			last = last -> next;
		}
		cout << 3 << endl;

		if (last == NULL)
			return -1;

		struct rating * rating;
		float BP, AP;
		int timeR = 0;
		getRating(last->link, stoi(p[1]), &BP, &AP, &timeR);
		if (timeR == 0)
			return -1;

		rating->time = timeR;
		rating->AP = AP;
		rating->BP = BP;
		float l = 0;
		cout << "rating : " << rating-> time << endl;

		if (p[0] == "CS" && deal->obOrOs == "OB")
		{
			

			l = (deal -> lot * 100000 * rating->BP) - deal ->mnDeal ;
		

			if (last-> qc != "USD")
			{
				l = l / float(rating->AP);
			}
		}
		else if (p[0] == "CB" && deal->obOrOs == "OS")
		{

			cout << " OB" << rating->AP << endl;
			l = deal ->mnDeal - (deal->lot * float(100000) * rating->AP);
			cout << deal->mnDeal << endl;
			cout << l << endl;

			if ( last->qc != "USD")
			{
				l = l / float(rating->AP);
			}
		} else return -1;
		cout << 2 << endl;
		cout << l<< endl;
		kyQuy += l;
		// if (kyQuy <= 0) closeAll(&BC_QC);
		return stoi(to_string(l));

	}
	
	return -1;
}