#include <iostream>
#include <string>
using namespace std;

// Дані працівника (Варіант 5: ПІБ, відділ, стаж)
struct a {
    string b;
    string c;
    int d;
};

// Вузол містить дані та адресу наступного вузла
struct e {
    a f;
    e* g;
};

// Список зберігає початок, кінець і кількість елементів
struct h {
    e* i;
    e* j;
    int k;
};

int l = 0, m = 0;

// Початкове налаштування порожнього списку
void n(h& o) {
    o.i = nullptr;
    o.j = nullptr;
    o.k = 0;
}

// Створення нового вузла та заповнення його даних
e* p(int q) {
    e* r = new e;
    r->f.b = "Employee" + to_string(q);
    r->f.c = (q % 2 == 0) ? "IT" : "Sales";
    r->f.d = q;
    r->g = nullptr;
    l++;
    return r;
}

// Додавання нового елемента в кінець списку
void s(h& o, int q) {
    e* r = p(q);
    if (o.i == nullptr)
        o.i = r;
    else
        o.j->g = r;
    o.j = r;
    o.k++;
}

// Додавання нового елемента на початок списку
void t(h& o, int q) {
    e* r = p(q);
    r->g = o.i;
    o.i = r;
    if (o.j == nullptr)
        o.j = r;
    o.k++;
}

// Формування списку з масиву початкових значень
void u(h& o, const int v[], int w) {
    for (int x = 0; x < w; x++)
        s(o, v[x]);
}

// Виведення всіх значень списку (стаж)
void y(const h& o) {
    e* r = o.i;
    if (!r) {
        cout << "empty";
        return;
    }
    while (r) {
        cout << r->f.d;
        if (r->g)
            cout << " -> ";
        r = r->g;
    }
}

// Пошук першого збігу та підрахунок переглянутих вузлів
e* z(h& o, int aa, int& ab, int& ac) {
    e* r = o.i;
    ab = -1;
    ac = 0;
    int x = 0;
    while (r) {
        ac++;
        if (r->f.d == aa) {
            ab = x;
            return r;
        }
        r = r->g;
        x++;
    }
    return nullptr;
}

// Пошук усіх збігів ключа та збереження їхніх позицій
int ad(h& o, int aa, int ae[], int af, int& ac) {
    e* r = o.i;
    int x = 0, ag = 0;
    ac = 0;
    while (r) {
        ac++;
        if (r->f.d == aa && ag < af)
            ae[ag++] = x;
        r = r->g;
        x++;
    }
    return ag;
}

// Вставлення елемента за заданою позицією
bool ah(h& o, int q, int ai) {
    if (ai < 0 || ai > o.k)
        return false;
    if (ai == 0) {
        t(o, q);
        return true;
    }
    if (ai == o.k) {
        s(o, q);
        return true;
    }
    e* aj = o.i;
    for (int x = 0; x < ai - 1; x++)
        aj = aj->g;
    e* r = p(q);
    r->g = aj->g;
    aj->g = r;
    o.k++;
    return true;
}

// Вставлення нового елемента перед першим вузлом із заданим ключем
bool ak(h& o, int aa, int q) {
    e* r = o.i;
    e* aj = nullptr;
    while (r && r->f.d != aa) {
        aj = r;
        r = r->g;
    }
    if (!r)
        return false;
    e* al = p(q);
    al->g = r;
    if (!aj)
        o.i = al;
    else
        aj->g = al;
    o.k++;
    return true;
}

// Вставлення нового елемента після першого вузла із заданим ключем
bool am(h& o, int aa, int q) {
    e* r = o.i;
    while (r && r->f.d != aa)
        r = r->g;
    if (!r)
        return false;
    e* al = p(q);
    al->g = r->g;
    r->g = al;
    if (o.j == r)
        o.j = al;
    o.k++;
    return true;
}

// Видалення елемента за позицією
bool an(h& o, int ai) {
    if (ai < 0 || ai >= o.k || !o.i)
        return false;
    e* ao;
    if (ai == 0) {
        ao = o.i;
        o.i = ao->g;
        if (o.j == ao)
            o.j = o.i;
    }
    else {
        e* aj = o.i;
        for (int x = 0; x < ai - 1; x++)
            aj = aj->g;
        ao = aj->g;
        aj->g = ao->g;
        if (o.j == ao)
            o.j = aj;
    }
    delete ao;
    m++;
    o.k--;
    if (o.k == 0) {
        o.i = nullptr;
        o.j = nullptr;
    }
    return true;
}

// Видалення першого елемента із заданим ключем
bool ap(h& o, int aa) {
    e* r = o.i;
    e* aj = nullptr;
    while (r && r->f.d != aa) {
        aj = r;
        r = r->g;
    }
    if (!r)
        return false;
    if (!aj)
        o.i = r->g;
    else
        aj->g = r->g;
    if (o.j == r)
        o.j = aj;
    delete r;
    m++;
    o.k--;
    if (!o.i)
        o.j = nullptr;
    return true;
}

// Видалення всіх елементів із заданим ключем
int aq(h& o, int aa) {
    int ar = 0;
    e* r = o.i;
    e* aj = nullptr;
    while (r) {
        if (r->f.d == aa) {
            e* ao = r;
            r = r->g;
            if (!aj)
                o.i = r;
            else
                aj->g = r;
            if (o.j == ao)
                o.j = aj;
            delete ao;
            m++;
            o.k--;
            ar++;
        }
        else {
            aj = r;
            r = r->g;
        }
    }
    if (!o.i)
        o.j = nullptr;
    return ar;
}

// Перевірка списку на наявність циклу методом двох вказівників
bool as(const h& o) {
    e* at = o.i;
    e* au = o.i;
    while (au && au->g) {
        at = at->g;
        au = au->g->g;
        if (at == au)
            return true;
    }
    return false;
}

// Перевірка кількості вузлів, кінцевого вузла та коректності посилань
bool av(const h& o, bool aw = true) {
    if (as(o)) {
        if (aw)
            cout << "error: cycle";
        return false;
    }
    int ax = 0;
    e* r = o.i;
    e* ay = nullptr;
    while (r) {
        ax++;
        ay = r;
        r = r->g;
    }
    bool az = (ax == o.k &&
        ay == o.j &&
        ((!o.i && !o.j && o.k == 0) ||
            (o.i && o.j && o.j->g == nullptr)));
    if (aw)
        cout << (az ? "structure OK" : "structure error");
    return az;
}

// Звільнення пам'яті всіх вузлів і очищення списку
void ba(h& o) {
    e* r = o.i;
    while (r) {
        e* bb = r->g;
        delete r;
        m++;
        r = bb;
    }
    n(o);
}

// Порівняння списку з очікуваними значеннями
bool bc(const h& o, const int bd[], int w) {
    if (o.k != w)
        return false;
    e* r = o.i;
    int x = 0;
    while (r && x < w) {
        if (r->f.d != bd[x])
            return false;
        r = r->g;
        x++;
    }
    return r == nullptr && x == w && av(o, false);
}

int be = 0, bf = 0;

// Виконання одного тесту
void bg(const string& bh, h& o, const int bd[], int w) {
    bf++;
    bool az = bc(o, bd, w);
    cout << "Test " << bf << " - " << bh << ": "
        << (az ? "PASSED" : "FAILED") << " | ";
    y(o);
    cout << "\n";
    if (az)
        be++;
    ba(o);
}

// Виведення стану списку та перевірка його структури
void bi(const string& bj, h& o) {
    cout << bj << ": ";
    y(o);
    cout << " | size=" << o.k << " | ";
    av(o);
    cout << "\n";
}

// Запуск 20 автоматичних тестів для різних випадків
void bk() {
    h o;
    int ac, ab, ag, ae[20];
    int v0[1] = { 0 };

    n(o);
    z(o, 5, ab, ac);
    bg("search in empty list", o, v0, 0);

    n(o);
    ah(o, 5, 0);
    int v1[] = { 5 };
    bg("insert into empty list", o, v1, 1);

    n(o);
    s(o, 5);
    an(o, 0);
    bg("delete the only element", o, v0, 0);

    int v[] = { 1, 3 };
    n(o);
    u(o, v, 2);
    ah(o, 2, 1);
    int w4[] = { 1, 2, 3 };
    bg("insert in the middle", o, w4, 3);

    n(o);
    u(o, v, 2);
    ah(o, 0, 0);
    int w5[] = { 0, 1, 3 };
    bg("insert at the beginning", o, w5, 3);

    n(o);
    u(o, v, 2);
    ah(o, 4, 2);
    int w6[] = { 1, 3, 4 };
    bg("insert at the end", o, w6, 3);

    int bl[] = { 1, 2, 3 };
    n(o);
    u(o, bl, 3);
    an(o, 0);
    int w7[] = { 2, 3 };
    bg("delete the first element", o, w7, 2);

    n(o);
    u(o, bl, 3);
    an(o, 1);
    int w8[] = { 1, 3 };
    bg("delete a middle element", o, w8, 2);

    n(o);
    u(o, bl, 3);
    an(o, 2);
    int w9[] = { 1, 2 };
    bg("delete the last element", o, w9, 2);

    int bm[] = { 1, 2, 2, 3 };
    n(o);
    u(o, bm, 4);
    ap(o, 2);
    int w10[] = { 1, 2, 3 };
    bg("delete the first matching key", o, w10, 3);

    int bn[] = { 2, 2, 1, 2 };
    n(o);
    u(o, bn, 4);
    aq(o, 2);
    int w11[] = { 1 };
    bg("delete all matching keys", o, w11, 1);

    n(o);
    u(o, bl, 3);
    ah(o, 9, 5);
    bg("invalid insertion position", o, bl, 3);

    n(o);
    u(o, bl, 3);
    an(o, -1);
    bg("invalid deletion position", o, bl, 3);

    n(o);
    u(o, bl, 3);
    am(o, 3, 9);
    int w14[] = { 1, 2, 3, 9 };
    bg("insert after the last element", o, w14, 4);

    n(o);
    u(o, bl, 3);
    ak(o, 1, 0);
    int w15[] = { 0, 1, 2, 3 };
    bg("insert before the first element", o, w15, 4);

    int bo[] = { 4, 4, 4, 2 };
    n(o);
    u(o, bo, 4);
    ag = ad(o, 4, ae, 20, ac);
    bool bp = (ag == 3 && ae[0] == 0 && ae[1] == 1 && ae[2] == 2);
    cout << "Test 16 - consecutive duplicate keys: "
        << (bp ? "PASSED" : "FAILED") << "\n";
    bf++;
    if (bp) be++;
    ba(o);

    n(o);
    u(o, bl, 3);
    bool bq = ak(o, 99, 7) == false;
    cout << "Test 17 - missing key for insertion: "
        << (bq && bc(o, bl, 3) ? "PASSED" : "FAILED") << "\n";
    bf++;
    if (bq && bc(o, bl, 3)) be++;
    ba(o);

    n(o);
    u(o, bl, 3);
    bool br = ap(o, 99) == false;
    cout << "Test 18 - missing key for deletion: "
        << (br && bc(o, bl, 3) ? "PASSED" : "FAILED") << "\n";
    bf++;
    if (br && bc(o, bl, 3)) be++;
    ba(o);

    n(o);
    u(o, bl, 3);
    ba(o);
    int bs[] = { 8, 6 };
    u(o, bs, 2);
    int w19[] = { 8, 6 };
    bg("refill after clearing", o, w19, 2);

    n(o);
    int bt[] = { 1, 2, 3 };
    u(o, bt, 3);
    ah(o, 4, 1);
    ap(o, 3);
    am(o, 2, 8);
    an(o, 0);
    ak(o, 8, 6);
    ah(o, 10, o.k);
    aq(o, 2);
    int w20[] = { 4, 6, 8, 10 };
    bg("series of mixed operations", o, w20, 4);
}

// Виконання операцій відповідно до варіанта 5 (рядок 5: 3, 8, 1, 8, 6 | знайти 9 | вставити 2 на поз. 1 | видалити всі 8)
void bu() {
    h o;
    n(o);

    int bv[] = { 3, 8, 1, 8, 6 };
    u(o, bv, 5);

    cout << "\n=== VARIANT 5 ===\n";
    bi("Initial list", o);

    int ab, ac, ae[20];
    e* r = z(o, 9, ab, ac);
    cout << "Search first 9: " << (r ? "found" : "not found")
        << ", position=" << ab << ", checked=" << ac << "\n";

    int w = ad(o, 9, ae, 20, ac);
    cout << "Search all 9s: matches=" << w << " | checked=" << ac << "\n";

    ah(o, 2, 1);
    bi("After inserting 2 at position 1", o);

    aq(o, 8);
    bi("After deleting all 8s", o);

    ba(o);
    cout << "After clearing: ";
    y(o);
    cout << " | ";
    av(o);
    cout << "\n";
}

// Виконання сценарію з 20 командами та перевіркою після кожної
void bw() {
    cout << "\n=== 20-COMMAND LOG ===\n";

    h o;
    n(o);

    int bx[] = { 3, 8, 1, 8, 6 };
    u(o, bx, 5);

    for (int x = 1; x <= 20; x++) {
        if (x == 1) {
            int ab, ac;
            z(o, 9, ab, ac);
            cout << x << ". search 9, position " << ab;
        }
        else if (x == 2) {
            int ae[20], ac;
            int w = ad(o, 8, ae, 20, ac);
            cout << x << ". search all 8s, matches " << w;
        }
        else if (x == 3) {
            ah(o, 2, 1);
            cout << x << ". insert 2 at position 1";
        }
        else if (x == 4) {
            ak(o, 3, 20);
            cout << x << ". insert 20 before 3";
        }
        else if (x == 5) {
            am(o, 1, 21);
            cout << x << ". insert 21 after 1";
        }
        else if (x == 6) {
            an(o, 2);
            cout << x << ". delete position 2";
        }
        else if (x == 7) {
            ap(o, 8);
            cout << x << ". delete first 8";
        }
        else if (x == 8) {
            ah(o, 30, o.k);
            cout << x << ". add 30 at the end";
        }
        else if (x == 9) {
            ah(o, 10, 0);
            cout << x << ". add 10 at the beginning";
        }
        else if (x == 10) {
            aq(o, 8);
            cout << x << ". delete all 8s";
        }
        else if (x == 11) {
            am(o, 1, 31);
            cout << x << ". insert 31 after 1";
        }
        else if (x == 12) {
            an(o, o.k - 1);
            cout << x << ". delete the last element";
        }
        else if (x == 13) {
            ak(o, 6, 15);
            cout << x << ". insert 15 before 6";
        }
        else if (x == 14) {
            ap(o, 999);
            cout << x << ". try to delete 999";
        }
        else if (x == 15) {
            ah(o, 40, 1);
            cout << x << ". insert 40 at position 1";
        }
        else if (x == 16) {
            an(o, 0);
            cout << x << ". delete the first element";
        }
        else if (x == 17) {
            ah(o, 50, o.k);
            cout << x << ". insert 50 at the end";
        }
        else if (x == 18) {
            ap(o, 21);
            cout << x << ". delete 21";
        }
        else if (x == 19) {
            ah(o, 60, 0);
            cout << x << ". insert 60 at the beginning";
        }
        else {
            aq(o, 31);
            cout << x << ". delete all 31s";
        }

        cout << " | ";
        y(o);
        cout << " | ";
        av(o);
        cout << "\n";
    }

    ba(o);
}

// Головна функція програми
int main() {
    cout << "PRACTICAL WORK 12. VARIANT 5\n";

    bk();

    cout << "\nTest summary: " << be
        << "/" << bf << " passed\n";

    bu();
    bw();

    cout << "\nAllocated nodes: " << l << "\n";
    cout << "Freed nodes: " << m << "\n";
    cout << "Active nodes: " << l - m << "\n";

    cout << ((l == m)
        ? "Memory balance OK"
        : "MEMORY BALANCE ERROR") << "\n";

    return 0;
}
