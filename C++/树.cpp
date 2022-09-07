#include <iostream>
#include <stack>
#include <queue>
//如果不这样要命名要把MaxSize和MaxSons规定为常量
#define MaxSize 50
#define MaxSons 50
#define N 50

using namespace std;
typedef char ElemType;

//双亲存储结构
typedef struct {
    ElemType data;
    int parent;
} PTree[MaxSize];

//孩子链存储结构
struct TSonNode {
    ElemType data;
    TSonNode *sons[MaxSons];
};

//求树的高度
int TreeHeiht1(TSonNode *t) {
    TSonNode *p;
    int i, h, maxh = 0;
    if (t == NULL) return 0;
    for (i = 0; i < MaxSize; i++) {
        p = t->sons[i];
        if (p != NULL) {
            h = TreeHeiht1(p);
            if (maxh < h) maxh = h;
        }
    }
    return maxh + 1;
}

//孩子兄弟链储存结构
struct TSBNode {
    ElemType data;
    TSBNode *hp;
    TSBNode *vp;
};

//求树的高度
int TreeHight2(TSBNode *t) {
    TSBNode *p;
    int h, maxh = 0;
    if (t == NULL) return 0;
    p = t->vp;
    while (p != NULL) {
        h = TreeHight2(p);
        if (maxh < h) maxh = h;
        p = p->hp;
    }
    return maxh + 1;
}

//二叉树的链式储存结构
struct BTNode {
    ElemType data;
    BTNode *lchild;
    BTNode *rchild;
};

//创建二叉树
void CreateBTree(BTNode *&b, string str) {
    int k, top = -1;//k=1时说明下一个节点是左孩子节点，k=2时说明下一个为右孩子节点
    BTNode *p, *St[MaxSize];
    b = NULL;
    for (int i = 0; i < str.length(); i++) {
        //当str[i]为'('时,说明下一个为上一个节点的左节点,此时将上一个节点进栈,记k=1;
        //当str[i]为','时,说明下一个为栈顶元素的右节点,记k=2;
        //当str[i]为')'时,要退栈
        //str[i]为其它情况时,根据k的情况建立节点
        switch (str[i]) {
            case '(':
                k = 1;
                top++;
                St[top] = p;//进栈
                break;
            case ',':
                k = 2;
                break;
            case ')':
                top--;//退栈
                break;
            default :
                p = new BTNode;
                p->data = str[i];
                p->lchild = p->rchild = NULL;
                if (b == NULL)
                    b = p;
                else {
                    switch (k) {
                        case 1:
                            St[top]->lchild = p;
                            break;
                        case 2:
                            St[top]->rchild = p;
                            break;
                    }
                }
        }
    }
}

//销毁二叉树
void DestoryBTree(BTNode *&b) {
    if (b != NULL) {
        DestoryBTree(b->lchild);
        DestoryBTree(b->rchild);
        delete b;
    }
}

//查找节点
BTNode *FindNode(BTNode *b, ElemType x) {
    BTNode *p;
    if (b == NULL)
        return NULL;
    else if (b->data == x)
        return b;
    else {
        p = FindNode(b->lchild, x);
        if (p != NULL)
            return p;
        else
            return FindNode(b->rchild, x);
    }
}

//找孩子节点
BTNode *LchildNode(BTNode *p) {
    return p->lchild;
}

BTNode *RchildNode(BTNode *p) {
    return p->rchild;
}

//求树的高度
int BTHight(BTNode *b) {
    int lchildh, rchildh;
    if (b == NULL)return 0;
    lchildh = BTHight(b->lchild);
    rchildh = BTHight(b->rchild);
    return (lchildh > rchildh) ? (lchildh + 1) : (rchildh + 1);
}

//输出二叉树  将二叉树的括号和逗号补上
void DisBTree(BTNode *b) {
    if (b != NULL) {
        cout << b->data;
        if (b->lchild != NULL || b->rchild != NULL) {
            cout << '(';
            DisBTree(b->lchild);
            if (b->rchild != NULL)cout << ',';
            DisBTree(b->rchild);
            cout << ')';
        }
    }
}

//先序遍历递归
void PreOrder(BTNode *b) {
    if (b != NULL) {
        cout << b->data << " ";
        PreOrder(b->lchild);
        PreOrder(b->rchild);
    }
}

//先序遍历非递归
//因为二叉树节点个数不一定,所以要借助链式栈来实现非递归
void PreOrder1(BTNode *b) {
    BTNode *p;
    stack<BTNode *> sq;
    sq.push(b);
    while (!sq.empty()) {
        p = sq.top();
        sq.pop();
        cout << p->data << " ";
        if (p->rchild != NULL)
            sq.push(p->rchild);
        if (p->lchild != NULL)
            sq.push(p->lchild);
    }
    cout << endl;
}

void PreOrder2(BTNode *b) {
    BTNode *p = b;
    stack<BTNode *> sq;
    while (!sq.empty() || p != NULL) {
        while (p != NULL) {
            cout << p->data << " ";
            sq.push(p);
            p = p->lchild;
        }
        if (!sq.empty()) {
            p = sq.top();
            sq.pop();
            p = p->rchild;
        }
    }
    cout << endl;
}

//中序遍历递归
void InOrder(BTNode *b) {
    if (b != NULL) {
        InOrder(b->lchild);
        cout << b->data << " ";
        InOrder(b->rchild);
    }
}

//中序遍历非递归 类似与前序遍历的非递归
void InOrder1(BTNode *b) {
    BTNode *p = b;
    stack<BTNode *> sq;
    while (!sq.empty() || p != NULL) {
        while (p != NULL) {
            sq.push(p);
            p = p->lchild;
        }
        if (!sq.empty()) {
            p = sq.top();
            sq.pop();
            cout << p->data << " ";
            p = p->rchild;
        }
    }
    cout << endl;
}

//后序遍历递归
void PostOrder(BTNode *b) {
    if (b != NULL) {
        PostOrder(b->lchild);
        PostOrder(b->rchild);
        cout << b->data << " ";
    }
}

//后序遍历非递归  类似与前序遍历的非递归
void PostOrder1(BTNode *b) {
    BTNode *p = b, *r;
    bool flag;
    stack<BTNode *> sq;
    do {
        while (p != NULL) {
            sq.push(p);
            p = p->lchild;
        }
        r = NULL;
        flag = true;
        while (!sq.empty() && flag) {
            p = sq.top();
            if (p->rchild == r) {
                cout << p->data << ' ';
                sq.pop();
                r = p;
            } else {
                p = p->rchild;
                flag = false;
            }

        }
    } while (!sq.empty());
    cout << endl;
}

void PostOrder2(BTNode *b) {
    stack<BTNode *> sq;
    BTNode *pre = NULL;//pre本来想写char类型，但是下面if里就要换成pre==t->l->data，如果t->l为空则会报错！
    sq.push(b);
    while (!sq.empty()) {
        b = sq.top();
        if ((b->lchild == NULL && b->rchild == NULL) ||
            (pre != NULL && (pre == b->lchild || pre == b->rchild))) //pre=t->l代表仅有左且已访问或者先访问过右又访问了左
        {
            cout << b->data << " ";
            pre = b;
            sq.pop();
        } else {
            if (b->rchild) sq.push(b->rchild);
            if (b->lchild) sq.push(b->lchild);
        }
    }
    cout << endl;
}

//层次遍历
void LevelOrder(BTNode *b) {
    BTNode *p;
    queue<BTNode *> q;
    q.push(b);
    while (!q.empty()) {
        p = q.front();
        q.pop();
        cout << p->data << " ";
        if (p->lchild != NULL)
            q.push(p->lchild);
        if (p->rchild != NULL)
            q.push(p->rchild);
    }
    cout << endl;
}

//寻找值为x的节点的祖先节点
stack<BTNode *> FindAncestorsNode(BTNode *b, ElemType x) {
    BTNode *p = b, *r;
    stack<BTNode *> sq;
    bool flag;
    do {
        while (p != NULL) {
            sq.push(p);
            p = p->lchild;
        }
        r = NULL;
        flag = true;
        while (!sq.empty() && flag) {
            p = sq.top();
            if (p->rchild == r) {
                if (p->data == x) {
                    sq.pop();
                    return sq;
                } else {
                    sq.pop();
                }
                r = p;
            } else {
                p = p->rchild;
                flag = false;
            }
        }
    } while (!sq.empty());
    return sq;
}

//判别给定的二叉树是否为完全二叉树
//我们将二叉树中的结点和层次遍历一样加入到队列中,同时为空的用NULL加到队列中,
// 这样会发现完全二叉树所有的NULL会出现在非空结点的后面,这样我们就可以设计算法了
bool JudgeCompleteBinaryTree(BTNode *b) {
    BTNode *p;
    queue<BTNode *> q, sq;
    q.push(b);
    while (!q.empty()) {
        p = q.front();
        sq.push(p);
        q.pop();
        if (p != NULL) {
            q.push(p->lchild);
            q.push(p->rchild);
        }
    }//按层次遍历的方法将二叉树的节点输入队列中
    bool flag = false;//判断是否过了非空结点
    while (!sq.empty()) {
        p = sq.front();
        sq.pop();
        if (p == NULL)
            flag = true;
        if (p != NULL && flag)
            return false;
    }
    return true;
}

//线索二叉树
struct TBTNode {
    ElemType data;
    //ltag=0时表示有左孩子 ltag=1时表示有前驱结点
    //rtag=0时表示有有孩子 rtag=1时表示有后驱结点
    int ltag, rtag;
    TBTNode *lchild;
    TBTNode *rchild;
};
TBTNode *pre;//进行线索化元素的前一个元素
/*
 * p为线索化的元素
 * p的前驱结点为pre
 * pre的后驱结点为p
 */
void Thread(TBTNode *&p) {
    if (p != NULL) {
        Thread(p->lchild);
        if (p->lchild == NULL) {//对p进行前驱线索化
            p->lchild = pre;
            p->ltag = 1;
        } else
            p->ltag = 0;
        if (pre->rchild = NULL) {//对pre进行后驱线索化
            pre->rchild = p;
            pre->rtag = 1;
        } else
            pre->rtag = 0;
        pre = p;
        Thread(p->rchild);
    }
}

//让root的左边指向根节点 右边指向遍历的最后一个结点
//遍历的第一个结点的前驱结点为root 遍历的最后一个结点的后驱结点为root
TBTNode *CreateThread(TBTNode *b) {
    TBTNode *root;
    root = new TBTNode;
    root->ltag = 0;
    root->rtag = 1;
    root->rchild = b;
    if (b == NULL)
        root->lchild = root;
    else {
        root->lchild = b;
        pre = root;
        Thread(b);
        pre->rchild = root;
        pre->rtag = 1;
        root->rchild = pre;
    }
    return root;
}

//遍历线索二叉树
void ThInOrder(TBTNode *tb) {
    TBTNode *p = tb->lchild;
    while (p != tb) {
        while (p->ltag == 0)p = p->lchild;
        cout << p->data;
        while (p->rtag == 1 && p->rchild != tb) {
            p = p->rchild;
            cout << p->data;
        }
        p = p->rchild;
    }
}

//哈夫曼树的构造
struct HTNode {
    char data;          //结点值
    double weight;      //权重
    int parent;         //双亲结点
    int lchild;         //左孩子结点
    int rchild;         //右孩子结点
};

//n0为叶子结点
void CreateHT(HTNode ht[], int n0) {
    int i, k, lnode, rnode;
    double min1, min2;
    //将ht[]初始化
    for (i = 0; i < 2 * n0 - 1; i++)
        ht[i].parent = ht[i].lchild = ht[i].rchild = -1;
    for (i = n0; i < 2 * n0 - 1; i++) {
        min1 = min2 = 32767;
        lnode = rnode = -1;
        for (k = 0; k < i; k++) {//找到权最小的两个
            if (ht[k].parent == -1) {
                if (ht[k].weight < min1) {
                    min2 = min1;
                    rnode = lnode;
                    min1 = ht[k].weight;
                    lnode = k;
                } else if (ht[k].weight < min2) {
                    rnode = k;
                    min2 = ht[k].weight;
                }
            }
        }
        //将两个权最小的合成
        ht[i].weight = min1 + min2;
        ht[i].rchild = rnode;
        ht[i].lchild = lnode;
        ht[lnode].parent = ht[rnode].parent = i;
    }
}

//哈夫曼编码
struct HCode {
    char cd[N];
    int start;
};

void CreateHCode(HTNode ht[], HCode hcd[], int n0) {
    int i, f, c;
    HCode hc;
    for (i = 0; i < n0; i++) {
        hc.start = n0;
        c = i;
        f = ht[i].parent;
        while (f != -1) {
            if (ht[f].lchild == c) {
                hc.cd[hc.start--] = '0';
                //cout << '0';
            } else {
                hc.cd[hc.start--] = '1';
                //cout << '1';
            }
            c = f;
            f = ht[f].parent;
        }
        hc.start++;
        hcd[i] = hc;
    }
}

void DisHTCode(HTNode ht[], HCode hcd[], int n0) {
    for (int i = 0; i < n0; i++) {
        cout << ht[i].data << "的哈夫曼编码为:";
        for (int j = hcd[i].start; j <= n0; j++) {
            cout << hcd[i].cd[j];
        }
        cout << endl;
    }
};
//并查集树
struct UFSTree {
    int data;       //结点对应的人的编号
    int rank;       //结点对应的秩 秩表示为树的深度
    int parent;     //结点对应的双亲结点
};

//并查集树的初始化
void MAKE_SET(UFSTree t[], int n) {
    for (int i = 1; i <= n; i++) {
        t[i].data = i;
        t[i].rank = 0;
        t[i].parent = i;//让双亲结点指向自己
    }
}

//查找一个元素所属的集合
//用根结点表示元素的所属的标志
int FIND_SET(UFSTree t[], int x) {
    if (t[x].parent != x)
        t[x].parent = FIND_SET(t, t[x].parent);
    return t[x].parent;
}

//两个元素各自所属的集合的合并
void UNION(UFSTree t[], int x, int y) {
    x = FIND_SET(t, x);
    y = FIND_SET(t, y);
    if (t[x].rank > t[y].rank)
        t[y].parent = x;
    else {
        t[x].parent = y;
        if (t[x].rank == t[y].rank)
            t[y].rank++;
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    UFSTree t[n + 1];
    MAKE_SET(t, n);
    while (m--) {
        int x, y;
        cin >> x >> y;
        UNION(t, x, y);
    }
    for (int i = 1; i <= n; i++) {
        cout << t[i].data << " " << t[i].parent << " " << t[i].rank << endl;
    }
    int Q;
    cin >> Q;
    while (Q--) {
        int x, y;
        cin >> x >> y;
        if (FIND_SET(t, x) == FIND_SET(t, y))
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
//    BTNode *b, *p, *lp, *rp;
//    cout << "二叉树的基本运算如下:" << endl;
//    cout << "  (1)创建二叉树" << endl;
//    CreateBTree(b, "A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))");
//    cout << "  (2)输出二叉树:";
//    DisBTree(b);
//    cout << endl;
//    cout << "  (3)H的节点:";
//    p = FindNode(b, 'H');
//    if (p != NULL) {
//        lp = LchildNode(p);
//        rp = RchildNode(p);
//        if (lp != NULL)
//            cout << "左孩子为" << lp->data << " ";
//        else
//            cout << "无左孩子" << " ";
//        if (rp != NULL)
//            cout << "右孩子为" << rp->data << " ";
//        else
//            cout << "右左孩子" << " ";
//    }
//    cout << endl;
//    cout << "  (4)二叉树b的高度:" << BTHight(b) << endl;
//    cout << "  (5)释放二叉树b" << endl;
//    DestoryBTree(b);
//    BTNode *b;
//    CreateBTree(b, "A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))");
//    cout << "二叉树b：";
//    DisBTree(b);
//    cout << endl;
//    cout << "层次遍历序列：";
//    LevelOrder(b);
//    cout << "先序遍历序列：" << endl;
//    cout << "\t递归算法：";
//    PreOrder(b);
//    cout << endl;
//    cout << "\t非递归算法1：";
//    PreOrder1(b);
//    cout << "\t非递归算法2：";
//    PreOrder2(b);
//    cout << "中序遍历序列：" << endl;
//    cout << "\t递归算法：";
//    InOrder(b);
//    cout << endl;
//    cout << "\t非递归算法：";
//    InOrder1(b);
//    cout << "后序遍历序列：" << endl;
//    cout << "\t递归算法：";
//    PostOrder(b);
//    cout << endl;
//    cout << "\t非递归算法1：";
//    PostOrder1(b);
//    cout << "\t非递归算法2：";
//    PostOrder2(b);
//    DestoryBTree(b);

//    BTNode *b;
//    CreateBTree(b, "A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))");
//    ElemType x = 'N';
//    if (b->data == x) {
//        cout << "值为"<<x<<"的节点为根节点" << endl;
//        return 0;
//    }
//    stack<BTNode *> sq = FindAncestorsNode(b, x);
//    stack<BTNode *> s;
//    if (sq.empty()) {
//        cout << "没有值为"<<x<<"的节点" << endl;
//    } else {
//        while (!sq.empty()) {
//            s.push(sq.top());
//            sq.pop();
//        }
//        cout<<"值为"<<x<<"的节点的所有祖先为:";
//        while (!s.empty()) {
//            cout << s.top()->data << "  ";
//            s.pop();
//        }
//        cout<<endl;
//    }
//    DestoryBTree(b);
//    return 0;
//    BTNode *b;
//    //CreateBTree(b, "A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))");
//    //CreateBTree(b, "A(B(C,C),B(C))");
//    //CreateBTree(b, "A(B(C,C),B(,C))");
//    //CreateBTree(b, "A(B(C,C),B(C,C))");
////    CreateBTree(b, "A(B(C(D,D),C(,D)),B(C,C))");
////    CreateBTree(b, "A(B(C(D,D),C(D,D)),B(C))");
//    CreateBTree(b, "A(B(C(D,D),C(D,D)),B(C,C))");
//    if(JudgeCompleteBinaryTree(b))
//        cout<<"二叉树b是完全二叉树"<<endl;
//    else
//        cout<<"二叉树b不是完全二叉树"<<endl;
//    DestoryBTree(b);

//    int n0;
//    cin >> n0;
//    HTNode ht[2 * n0 - 1];
//    for (int i = 0; i < n0; i++) {
//        cin >> ht[i].data >> ht[i].weight;
//    }
//    HCode hcd[n0];
//    CreateHT(ht, n0);
//    CreateHCode(ht, hcd, n0);
//    DisHTCode(ht,hcd,n0);
}
