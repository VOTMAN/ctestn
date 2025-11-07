
# ctestn

---

## QUESTION 1

### i) Implement the data link layer framing methods such as character, character-stuffing and bit stuffing.

**Character stuffing and bit stuffing implementations (C):**

bitstuff
```c
#include<stdio.h>
#include<string.h>
int main(){
  int i,c=0,j;
  char input[100],output[100];
  printf("Enter the frame(0's & 1's):\n");
  scanf("%s",input);
  int n=strlen(input);
  strcpy(output,"01111110");
  j=strlen(output);
  for(i=0;i<n;i++){
    output[j++]=input[i];
    if(input[i]=='1'){
      c++;
      if(c==5){
        output[j++]='0';
        c=0;
      }
    }
    else{
      c=0;
    }
  }
  strcpy(output+j,"01111110");
  printf("After Bit Stuffing the ouput is :");
  puts(output);
}
```

charstuff
```c
#include<stdio.h>
#include<string.h>
int main(){
  char input[50],output[50];
  printf("Enter the frame:\n");
  scanf("%s", input);
  int n=strlen(input);
  strcpy(output,"flag");
  int c=0,j=0,i;
  j=strlen(output);
  for(i=0;i<n;i++){
    if(input[i]=='f' && input[i+1]=='l' && input[i+2]=='a' && input[i+3]=='g'){
      output[j++]='e';
      output[j++]='s';
      output[j++]='c';
    }
    else if(input[i]=='e' && input[i+1]=='s' && input[i+2]=='c'){
      output[j++]='e';
      output[j++]='s';
      output[j++]='c';
    }
    else if(input[i]=='s' && input[i+1]=='t' && input[i+2]=='x'){
      output[j++]='e';
      output[j++]='s';
      output[j++]='c';
    }
    else if(input[i]=='e' && input[i+1]=='t' && input[i+2]=='x'){
      output[j++]='e';
      output[j++]='s';
      output[j++]='c';
    }
    output[j++]=input[i];
  }
  strcpy(output+j,"flag");
  printf("After Character Stuffing the ouput is :");
  puts(output);
}
```
---

### ii) How to run Nmap scan

**GUI (Zenmap):**
1. Download & Install Nmap — https://nmap.org/download.html (includes Zenmap GUI)
2. Open Zenmap → Enter target (IP or domain)
3. Choose Profile → Intense scan / Quick scan / Ping scan
4. Click Scan

**Command line examples:**
```bash
nmap 192.168.1.1
nmap -A -T4 scanme.nmap.org
nmap -sP 192.168.1.0/24
nmap -p 1-1000 8.8.8.8
```

---

## QUESTION 2

### i) Program to compute CRC code for CRC-12, CRC-16 and CRC-CCITT

```c
#include<stdio.h>
#include<string.h>
int main(){
  char data[100],div[100],temp[100],div1[100],rem[100],quot[100];
  printf("Enter the data:");
  scanf("%s",data);

  printf("\nEnter the divisor:");
  scanf("%s",div);
  printf("\n");

  int datalen=strlen(data);
  int divlen=strlen(div);

  for(int i=0;i<divlen-1;i++){
    data[datalen+i]='0';
  }
  data[datalen+divlen-1]='\0';

  strcpy(temp,data);
  strcpy(div1,div);

  for(int i=0;i<datalen;i++){
    quot[i]=temp[0];
    if(quot[i]=='0'){
      for(int j=0;j<divlen;j++){
        div[j]='0';
      }
    }
    else{
      strcpy(div,div1);
    }

    for(int j=1;j<divlen;j++){
      rem[j-1]=(temp[j]==div[j])?'0':'1';
    }
    rem[divlen-1]=data[i+divlen];
    rem[divlen]='\0';
    strcpy(temp,rem);
  }
  quot[datalen]='\0';
  strcpy(rem,temp);
  printf("Quotient: %s\n",quot);
  printf("Remainder: %s\n",rem);
  for(int i=0;i<divlen;i++){
    data[datalen+i]=rem[i];
  }
  data[datalen+divlen-1]='\0';
  printf("Final data: %s",data);
}
```

---

### ii) Operating System Detection using Nmap

```bash
nmap -O 192.168.1.1
nmap -A -T4 scanme.nmap.org
nmap -O -Pn 192.168.1.1   # Skip ping if ICMP is blocked
```
Nmap’s OS detection (a.k.a. fingerprinting) probes a target’s TCP/IP stack with specially crafted packets and compares the subtle differences in the replies (TTL, window size, TCP options, responses to malformed packets, etc.) against a database of known fingerprints. Run it with nmap -O <target> for basic detection or nmap -A -T4 <target> to combine OS detection with version and script scanning. Use -Pn when ICMP/ping is blocked.

Accuracy depends on privileges, available open services and network conditions—running as root/administrator and combining -sS (SYN scan) and -sV (version detection) usually improves results. Firewalls, NAT, virtual machines and uncommon or hardened stacks can make detection imprecise, so always check Nmap’s confidence/output and only scan hosts you are authorized to scan.

---

## QUESTION 3

### i) Sliding Window + Go-Back-N

```c
#include<stdio.h>
int main(){
  int i,w,f;
  printf("Enter the window size: ");
  scanf("%d",&w);
  printf("\n Enter the frames size to sent: ");
  scanf("%d",&f);
  int frames[f+1];
  printf("\n Enter the frames: ");
  for(i=0;i<f;i++){
    scanf("%d",&frames[i]);
  }
  printf("\nThe frames are sent to sender by using sliding window protocol");
  printf("\nThe %d no'of frames are sending to the receiver and sender watis until receives acknowledgement from receiver\n",w);
  for(int i=0;i<f;i++){
    if((i+1)%w==0){
      printf("%d \n",frames[i]);
      printf("The Acknowledgement of above frames are received by receiver\n");
    }
    else{
      printf("%d ",frames[i]);
    }
  }
  if(f%w!=0){
    printf("\nThe Acknowledgement of above frames are received by receiver");
  }
}
```

### ii) Basic Network Commands

```bash
# Windows / Linux equivalents
ipconfig / ifconfig / ip a
ping google.com
tracert google.com   # Windows
traceroute google.com  # Linux
netstat -an
route print / ip route show
nslookup google.com
arp -a
telnet google.com 80
dig google.com
tcpdump -i eth0
```

---

## QUESTION 4

### i) Dijkstra’s Algorithm

```c
#include<stdio.h>
int main(){
  int a[10][10],path[10][10],p,st=1,stp,edp,index,t[10],min;

  printf("Enter the cost Matrix:\n");
  for(int i=1;i<=5;i++){
    for(int j=1;j<=5;j++){
      scanf("%d",&a[i][j]);
    }
  }

  printf("\nEnter the number of possible paths:");
  scanf("%d",&p);

  printf("\nEnter the possible paths:");
  for(int i=1;i<=p;i++){
    for(int j=1;j<=5;j++){
      scanf("%d",&path[i][j]);
    }
  }

  for(int i=1;i<=p;i++){
    t[i]=0;
    stp=st;
    for(int j=1;j<=5;j++){
      edp=path[i][j+1];
      if(edp==0){
        break;
      }
      t[i]+=a[stp][edp];
      stp=edp;
    }
  }
  min=t[1];
  index=1;
  for(int i=1;i<=p;i++){
    if(min>t[i]){
      min=t[i];
      index=i;
    }
  }

  printf("\nMinimum cost: %d",min);
  printf("\nMinimum cost path:");
  for(int i=0;i<=5;i++){
    printf("--> %d",path[index][i]);
  }
}
```

### ii) How to run Nmap scan — same as Q1.ii

---

## QUESTION 5

### i) Broadcast Tree for Subnet (DFS)

```c
#include <stdio.h>
#include <stdlib.h>

void dfs(int g[10][10], int n, int start, int vis[10]) {
    vis[start] = 1;
    printf("%d ", start);
    for (int i = 0; i < n; i++)
        if (g[start][i] && !vis[i]) dfs(g, n, i, vis);
}

int main() {
    int n, root, g[10][10] = {0}, vis[10] = {0};
    printf("Enter nodes (max 10): "); scanf("%d", &n);
    printf("Enter adjacency matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &g[i][j]);
    printf("Enter root: "); scanf("%d", &root);
    printf("Broadcast path: ");
    dfs(g, n, root, vis);
    printf("\n");
    return 0;
}
```

**Sample Output:**
```
Broadcast path from node 1: 1 0 2
```

### ii) OS Detection using Nmap — same as Q2.ii

---

## QUESTION 6

### i) Distance Vector Routing

```c
#include <stdio.h>
#define N 4
#define INF 999

int main() {
    int cost[N][N] = {
        {0,5,INF,10},
        {5,0,3,INF},
        {INF,3,0,1},
        {10,INF,1,0}
    };
    int dist[N][N], i, j, k;
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++) dist[i][j] = cost[i][j];
    for (k = 0; k < N; k++)
        for (i = 0; i < N; i++)
            for (j = 0; j < N; j++)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
    for (i = 0; i < N; i++) {
        printf("Node %d Table:\n", i);
        for (j = 0; j < N; j++)
            printf("  To %d -> %d\n", j, dist[i][j] == INF ? -1 : dist[i][j]);
    }
    return 0;
}
```

### ii) Network Commands — same as Q3.ii

---

## QUESTION 7

### i) Data Encryption & Decryption

```c
#include <stdio.h>
#include <string.h>

int main() {
    char s[100]; int ch, i;
    printf("Enter string: ");
    if (!fgets(s, sizeof(s), stdin)) return 0;
    s[strcspn(s, "\n")] = '\0';
    printf("1. Encrypt  2. Decrypt: ");
    if (scanf("%d", &ch) != 1) return 0;
    for (i = 0; s[i]; i++) s[i] += (ch==1) ? 3 : -3;
    printf("%s: %s\n", ch==1 ? "Encrypted" : "Decrypted", s);
    return 0;
}
```

### ii) How to run Nmap scan — same as Q1.ii

---

## QUESTION 8

### i) Leaky Bucket Algorithm

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void leaky(int bsize, int rate, int np) {
    int bucket = 0, pkt, i;
    srand(time(0));
    printf("Time\tPkt\tBucket\tAction\n");
    for (i = 1; i <= np; i++) {
        pkt = rand() % 10 + 1;
        printf("%d\t%d\t%d\t", i, pkt, bucket);
        if (bucket + pkt <= bsize) { bucket += pkt; printf("Accepted\n"); }
        else printf("Dropped\n");
        bucket -= rate; if (bucket < 0) bucket = 0;
        printf("\t\t\t%d\tLeak\n", bucket);
    }
}

int main() {
    int bs, r, n;
    printf("Bucket size: "); scanf("%d",&bs);
    printf("Output rate: "); scanf("%d",&r);
    printf("Packets: "); scanf("%d",&n);
    leaky(bs, r, n);
    return 0;
}
```

**Sample Output:**
```
Time    Pkt     Bucket  Action
1       5       0       Accepted
                        4       Leak
```

### ii) OS Detection using Nmap — same as Q2.ii

---

## QUESTION 9

### i) Frame Sorting in Buffers

```c
#include<stdio.h>
#include<time.h>

void shuffle(int arr[], int n){
  srand(time(NULL));
  for (int i=0;i<n;i++){
    int j=rand()%(i+1);
    int t=arr[i];
    arr[i]=arr[j];
    arr[j]=t;
  }
}

void bubblesort(int arr[], int n){
  for(int i=0;i<n-1;i++){
    for(int j=0;j<n-i-1;j++){
      if(arr[j]>arr[j+1]){
        int t=arr[j];
        arr[j]=arr[j+1];
        arr[j+1]=t;
      }
    }
  }
}

int main(){
  int p,input[100];
  printf("Enter the size of packets:");
  scanf("%d",&p);
  printf("\nEnter the frame: ");
  for(int i=0;i<p;i++){
    scanf("%d",&input[i]);
  }
  shuffle(input,p);
  printf("\nReceived frame:");
  for(int i=0;i<p;i++){
    printf("%d ",input[i]);
  }
  bubblesort(input,p);
  printf("\nFrame after sorting:");
   for(int i=0;i<p;i++){
    printf("%d ",input[i]);
  }
}
```

### ii) Network Commands — same as Q3.ii

---
