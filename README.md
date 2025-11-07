
# ctestn

---

## QUESTION 1

### i) Implement the data link layer framing methods such as character, character-stuffing and bit stuffing.

**Character stuffing and bit stuffing implementations (C):**

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void char_stuff(const char *in, char *out) {
    strcpy(out, "FLAG ");
    for (int i = 0; in[i]; i++) {
        if (strncmp(&in[i], "FLAG", 4) == 0) { strcat(out, "ESC FLAG "); i += 3; }
        else if (strncmp(&in[i], "ESC", 3) == 0) { strcat(out, "ESC ESC "); i += 2; }
        else { char t[2] = {in[i], 0}; strcat(out, t); }
    }
    strcat(out, " FLAG");
}

void bit_stuff(const char *in, char *out) {
    int cnt = 0, j = 0;
    /* Start flag (bit pattern for HDLC) */
    strcpy(out, "01111110 ");
    j = strlen(out);
    for (int i = 0; in[i]; i++) {
        out[j++] = in[i];
        if (in[i] == '1') {
            if (++cnt == 5) { out[j++] = '0'; cnt = 0; }
        } else cnt = 0;
    }
    /* End flag */
    strcpy(out + j, " 01111110");
    out[j + 10] = '\0';
}

int main() {
    char data[200], cstuffed[1000], bstuffed[1000];
    printf("Enter data: ");
    if (!fgets(data, sizeof(data), stdin)) return 0;
    /* remove newline */
    data[strcspn(data, "\n")] = '\0';
    char_stuff(data, cstuffed);
    printf("Character Stuffed: %s\n", cstuffed);
    bit_stuff(data, bstuffed);
    printf("Bit Stuffed      : %s\n", bstuffed);
    return 0;
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
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned short crc(const char *data, const char *poly, int plen) {
    int dlen = strlen(data), i, j;
    char temp[300] = {0};
    strcpy(temp, data);
    for (i = 0; i < plen - 1; i++) temp[dlen + i] = '0';
    for (i = 0; i < dlen; i++) {
        if (temp[i] == '1') {
            for (j = 0; j < plen; j++)
                temp[i + j] = (temp[i + j] == poly[j]) ? '0' : '1';
        }
    }
    return (unsigned short)strtol(temp + dlen, NULL, 2);
}

int main() {
    char data[200];
    printf("Enter binary data: ");
    scanf("%199s", data);
    /* Note: polynomial strings must be provided in binary representation including the leading 1 */
    printf("CRC-12   : %03X\n", crc(data, "1100000001111", 13));
    printf("CRC-16   : %04X\n", crc(data, "11000000000000101", 17));
    printf("CRC-CCITT: %04X\n", crc(data, "10001000000100001", 17));
    return 0;
}
```

> **Note:** Polynomial representations and CRC conventions (initial value, final XOR, reflection) vary. Confirm your syllabus convention if required.

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
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WS 4
#define TF 12

int main() {
    int frames[TF], i;
    for (i = 0; i < TF; i++) frames[i] = i;
    int base = 0;
    srand(time(0));
    while (base < TF) {
        for (i = base; i < base + WS && i < TF; i++)
            printf("Sent frame %d\n", frames[i]);
        if (rand() % 5 == 0) printf("Timeout -> Resend from %d\n", base);
        else {
            int ack = base + (rand() % WS);
            if (ack >= TF) ack = TF - 1;
            printf("ACK %d received\n", ack);
            base = ack + 1;
        }
    }
    printf("Transmission Complete!\n");
    return 0;
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
#include <stdio.h>
#define V 5
#define INF 999

void dijkstra(int g[V][V], int src) {
    int dist[V], vis[V] = {0}, min, u = 0, v, i;
    for (i = 0; i < V; i++) dist[i] = INF;
    dist[src] = 0;
    for (i = 0; i < V; i++) {
        min = INF;
        for (v = 0; v < V; v++)
            if (!vis[v] && dist[v] < min) { min = dist[v]; u = v; }
        vis[u] = 1;
        for (v = 0; v < V; v++)
            if (!vis[v] && g[u][v] && dist[u] + g[u][v] < dist[v])
                dist[v] = dist[u] + g[u][v];
    }
    printf("Node\tDistance\n");
    for (i = 0; i < V; i++) printf("%d\t%d\n", i, dist[i]);
}

int main() {
    int g[V][V] = {
        {0,10,0,30,100},
        {10,0,50,0,0},
        {0,50,0,20,10},
        {30,0,20,0,60},
        {100,0,10,60,0}
    };
    dijkstra(g, 0);
    return 0;
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { int seq; char data[50]; } Frame;

void sort_frames(Frame f[], int n) {
    Frame temp;
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (f[j].seq > f[j+1].seq) {
                temp = f[j]; f[j] = f[j+1]; f[j+1] = temp;
            }
}

int main() {
    int n; printf("Frames: "); scanf("%d",&n);
    Frame *f = malloc(n * sizeof(Frame));
    for (int i = 0; i < n; i++) {
        printf("Seq %d: ", i+1); scanf("%d", &f[i].seq);
        printf("Data %d: ", i+1); scanf("%s", f[i].data);
    }
    printf("\nBefore:\n");
    for (int i = 0; i < n; i++) printf("%d: %s\n", f[i].seq, f[i].data);
    sort_frames(f, n);
    printf("\nAfter Sorting:\n");
    for (int i = 0; i < n; i++) printf("%d: %s\n", f[i].seq, f[i].data);
    free(f);
    return 0;
}
```

### ii) Network Commands — same as Q3.ii

---

