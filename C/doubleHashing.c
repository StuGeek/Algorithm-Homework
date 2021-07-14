#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int TABLE_SIZE = 64;
double probes = 0;
long int collision_times = 0;

//哈希表结构
typedef struct hashTable{
    unsigned long int *Hash_Table;//一个存放12位无符号整数的数组
    int size;//一个表示当前数组中存放的数据个数
} *HashTable;

HashTable creat_hash_table();
HashTable double_size(HashTable t);
HashTable insert(HashTable t, int key);
void display(HashTable t);
void free_hash_table(HashTable t);

//根据当前哈希表的容量大小TABLE_SIZE创建新的哈希表
HashTable creat_hash_table(){
    HashTable t = (HashTable)malloc(sizeof(struct hashTable));
    t->Hash_Table = (unsigned long int *)malloc(TABLE_SIZE * sizeof(unsigned long int));
    //将数组中所有的值都置为-1
    memset(t->Hash_Table, -1, TABLE_SIZE * sizeof(unsigned long int));
    //哈希表中的数据个数为0个
    t->size = 0;
    return t;
}

int hash1(int key){
    //数据与(000000111111)2=63求并，得到数据的后6位
    return key & 63;
}

int hash2(int key){
    //数据右移6位，得到数据的前6位
    return key >> 6;
}

//如果哈希表数据放满了，那么进行扩容
HashTable double_size(HashTable t){
    TABLE_SIZE = TABLE_SIZE * 2;
    HashTable temp = creat_hash_table();
    //根据新的容量值将原来的数据进行重新哈希
    for(int i = 0; i < t->size; ++i){
        if (t->Hash_Table[i] != -1){
            temp = insert(temp, t->Hash_Table[i]);
        }
    }
    free_hash_table(t);
    return temp;
}

HashTable insert(HashTable t, int key){
    //哈希表已满，进行扩容
    if (t->size == TABLE_SIZE){
        t = double_size(t);
    }
    //获取bin值
    int bin = hash1(key);
    probes++;
    //如果哈希表对应的bin值处没有数据，那么直接加入数据
    if (t->Hash_Table[bin] == -1){
        t->Hash_Table[bin] = key;
    }
    //否则通过第二个哈希函数获取跳转值获取新下标
    else{
        //通过第二个哈希函数获取的值要或上1从而获取跳转值
        int jump_size = hash2(key) | 1;
        int newbin = bin;
        while(1){
            //获取新下标，如果新下标处也有数据，那么再重新获取下标
            newbin = (newbin + jump_size) % TABLE_SIZE;
            probes++;
            collision_times++;
            if (t->Hash_Table[newbin] == -1){
                t->Hash_Table[newbin] = key;
                break;
            }
        }
    }
    //数据加入后，哈希表数据个数加一
    t->size++;
    return t;
}

//将哈希表中存入的数据打印出来
void display(HashTable t){
    for (int i = 0; i < TABLE_SIZE; ++i){
        if (t->Hash_Table[i] != -1){
            printf("Hash_Table[%d]: %lu\n", i, t->Hash_Table[i]);
        }
    }
}

//释放哈希表所申请的动态内存
void free_hash_table(HashTable t){
    if (t != NULL){
        if (t->Hash_Table != NULL){
            free(t->Hash_Table);
            t->Hash_Table = NULL;
        }
        free(t);
        t = NULL;
    }
}

int main(){
    HashTable t = creat_hash_table();
    int n;
    printf("请输入要输入的12位无符号整数(范围为0~8191)个数：");
    scanf("%d", &n);
    printf("请输入整数序列：");
    for (int i = 0; i < n; ++i){
        unsigned long int num;
        scanf("%lu", &num);
        t = insert(t, num);
    }
    display(t);
    printf("The average number of probes is %.2lf", (double)probes / (double)t->size);
    free_hash_table(t);
    //测试多次产生的冲突次数，估计平均冲突次数
    /*int n = 10000;
    srand((unsigned) time(NULL));
    for (int j = 0; j < 10; ++j){
        n = 10000;
        collision_times = 0;
        while(n--){
        probes = 0;
        HashTable t = creat_hash_table();
        int visited[8192] = {0};
        for (int i = 0; i < 40; ++i){
            int num = rand() % 8192;
            while(visited[num] == 1){
                num = rand() % 8192;
            }
            visited[num] = 1;
            t = insert(t, num);
        }
        free_hash_table(t);
        }
        printf("collision times: %ld\n", collision_times);
    }*/
}