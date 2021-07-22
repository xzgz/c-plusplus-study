#include <bits/stdc++.h>

using namespace std;
namespace CWIDTACKERSPACE {
    void munkres(float **C, int nr, int nc, bool **assignment, float &cost);

    void step_one(int &step, float **C_dynamic, int nnr, int nnc, bool **starZ,
                  bool **primeZ, bool *RowCover, bool *ColCover);

    void step_two(int &step, float **C_dynamic, int nnr, int nnc, bool **starZ,
                  bool **primeZ, bool *RowCover, bool *ColCover);

    void step_three(int &step, float **C_dynamic, int nnr, int nnc, bool **starZ,
                    bool **primeZ, bool *RowCover, bool *ColCover, int K);

    void step_four(int &step, float **C_dynamic, int nnr, int nnc, bool **starZ,
                   bool **primeZ, bool *RowCover, bool *ColCover, int &path_row_0,
                   int &path_col_0);

    void find_non_covered_zero(float **C_dynamic, int nnr, int nnc, bool *RowCover,
                               bool *ColCover, int &r, int &c);

    void find_star_in_row(bool **starZ, int nnr, int nnc, int r, int &c);

    void step_five(int &step, float **C_dynamic, int nnr, int nnc, bool **starZ,
                   bool **primeZ, bool *RowCover, bool *ColCover, int path_row_0,
                   int path_col_0);

    void find_star_in_col(bool **starZ, int nnr, int nnc, int &r, int c);

    void find_prime_in_row(bool **primeZ, int nnr, int nnc, int r, int &c);

    void step_six(int &step, float **C_dynamic, int nnr, int nnc, bool **starZ,
                  bool **primeZ, bool *RowCover, bool *ColCover);

    void find_smallest(float **C_dynamic, int nnr, int nnc, bool *RowCover,
                       bool *ColCover, float &min_val);

    void step_seven(bool **assignment, float &cost, bool b_translated, float **C,
                    int nr, int nc, bool **starZ);
}

static void show_cost_matrix(float **C, const int r, const int c) {
    static int step = 1;
    cout << "\nstep: " << step << endl;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            cout << C[i][j] << '\t';
        }
        cout << endl;
    }
    step++;
}

void CWIDTACKERSPACE::munkres(float** C, int nr, int nc, bool** assignment,
                              float& cost) {
    for (int i = 0; i < nr; ++i) {
        for (int j = 0; j < nc; ++j) {
            assignment[i][j] = false;
        }
    }

    /*Translate the cost matrix if the number of rows is larger than the number
     * of columns*/

    float** C_dynamic;
    bool** starZ;
    bool** primeZ;
    bool* RowCover;
    bool* ColCover;

    bool b_translated = false;
    int nnr = nr, nnc = nc;
    if (nr > nc) {
        nnr = nc;
        nnc = nr;
        b_translated = true;
    }
    int K = nnr;
    C_dynamic = new float*[nnr];
    starZ = new bool*[nnr];
    primeZ = new bool*[nnr];
    RowCover = new bool[nnr];
    ColCover = new bool[nnc];

    for (int i = 0; i < nnr; ++i) {
        C_dynamic[i] = new float[nnc];
        starZ[i] = new bool[nnc];
        primeZ[i] = new bool[nnc];
        memset(starZ[i], 0, nnc * sizeof(bool));
        memset(primeZ[i], 0, nnc * sizeof(bool));
    }

    if (b_translated) {
        for (int i = 0; i < nnr; ++i) {
            for (int j = 0; j < nnc; ++j) {
                C_dynamic[i][j] = C[j][i];
            }
        }
    } else {
        for (int i = 0; i < nnr; ++i) {
            for (int j = 0; j < nnc; ++j) {
                C_dynamic[i][j] = C[i][j];
            }
        }
    }

    /*The step-by-step implementation of munkres' algorithm*/

    bool b_done = false;
    int step = 1;
    int path_row_0;
    int path_col_0;

    while (!b_done) {
        switch (step) {
            case 1:
                step_one(step, C_dynamic, nnr, nnc, starZ, primeZ, RowCover,
                         ColCover);
                break;
            case 2:
                step_two(step, C_dynamic, nnr, nnc, starZ, primeZ, RowCover,
                         ColCover);
                break;
            case 3:
                step_three(step, C_dynamic, nnr, nnc, starZ, primeZ, RowCover,
                           ColCover, K);
                break;
            case 4:
                step_four(step, C_dynamic, nnr, nnc, starZ, primeZ, RowCover,
                          ColCover, path_row_0, path_col_0);
                break;
            case 5:
                step_five(step, C_dynamic, nnr, nnc, starZ, primeZ, RowCover,
                          ColCover, path_row_0, path_col_0);
                break;
            case 6:
                step_six(step, C_dynamic, nnr, nnc, starZ, primeZ, RowCover,
                         ColCover);
                break;
            case 7:
                step_seven(assignment, cost, b_translated, C, nr, nc, starZ);
                b_done = true;
                break;
        }
    }

    for (int i = 0; i < nnr; ++i) {
        delete[] C_dynamic[i];
        delete[] starZ[i];
        delete[] primeZ[i];
    }
    delete[] C_dynamic;
    delete[] starZ;
    delete[] primeZ;
    delete[] ColCover;
    delete[] RowCover;
}

void CWIDTACKERSPACE::step_one(int& step, float** C_dynamic, int nnr, int nnc,
                               bool** starZ, bool** primeZ, bool* RowCover,
                               bool* ColCover) {
    float min_cost;
    for (int i = 0; i < nnr; ++i) {
        min_cost = C_dynamic[i][0];
        for (int j = 0; j < nnc; ++j) {
            if (C_dynamic[i][j] < min_cost) {
                min_cost = C_dynamic[i][j];
            }
        }
        for (int j = 0; j < nnc; ++j) {
            C_dynamic[i][j] -= min_cost;
        }
    }
    step = 2;
    show_cost_matrix(C_dynamic, 3, 3);
}

void CWIDTACKERSPACE::step_two(int& step, float** C_dynamic, int nnr, int nnc,
                               bool** starZ, bool** primeZ, bool* RowCover,
                               bool* ColCover) {
    memset(RowCover, 0, nnr * sizeof(bool));
    memset(ColCover, 0, nnc * sizeof(bool));

    for (int i = 0; i < nnr; ++i) {
        for (int j = 0; j < nnc; ++j) {
            if (C_dynamic[i][j] == 0 && !RowCover[i] && !ColCover[j]) {
                starZ[i][j] = true;
                RowCover[i] = true;
                ColCover[j] = true;
            }
        }
    }
    step = 3;
    show_cost_matrix(C_dynamic, 3, 3);
}

void CWIDTACKERSPACE::step_three(int& step, float** C_dynamic, int nnr, int nnc,
                                 bool** starZ, bool** primeZ, bool* RowCover,
                                 bool* ColCover, int K) {
    memset(RowCover, 0, nnr * sizeof(bool));
    memset(ColCover, 0, nnc * sizeof(bool));

    for (int i = 0; i < nnr; ++i) {
        for (int j = 0; j < nnc; ++j) {
            primeZ[i][j] = false;
        }
    }

    int col_count = 0;
    for (int i = 0; i < nnr; ++i) {
        for (int j = 0; j < nnc; ++j) {
            if (starZ[i][j]) {
                ColCover[j] = true;
            }
        }
    }
    for (int j = 0; j < nnc; ++j) {
        if (ColCover[j]) {
            ++col_count;
        }
    }
    if (col_count >= K) {
        step = 7;
    } else {
        step = 4;
    }
    show_cost_matrix(C_dynamic, 3, 3);
}

void CWIDTACKERSPACE::step_four(int& step, float** C_dynamic, int nnr, int nnc,
                                bool** starZ, bool** primeZ, bool* RowCover,
                                bool* ColCover, int& path_row_0,
                                int& path_col_0) {
    int r = -1;
    int c = -1;
    bool b_done = false;

    while (!b_done) {
        find_non_covered_zero(C_dynamic, nnr, nnc, RowCover, ColCover, r, c);
        if (r == -1) {
            b_done = true;
            step = 6;
            show_cost_matrix(C_dynamic, 3, 3);
        } else {
            primeZ[r][c] = true;
            int starc = -1;
            find_star_in_row(starZ, nnr, nnc, r, starc);
            if (starc == -1) {
                b_done = true;
                path_row_0 = r;
                path_col_0 = c;
                step = 5;
                show_cost_matrix(C_dynamic, 3, 3);
            } else {
                RowCover[r] = true;
                ColCover[starc] = false;
                show_cost_matrix(C_dynamic, 3, 3);
            }
        }
    }
}

void CWIDTACKERSPACE::find_non_covered_zero(float** C_dynamic, int nnr, int nnc,
                                            bool* RowCover, bool* ColCover,
                                            int& r, int& c) {
    r = -1;
    c = -1;
    for (int i = 0; i < nnr; ++i) {
        if (RowCover[i]) continue;
        for (int j = 0; j < nnc; ++j) {
            if (!ColCover[j] && C_dynamic[i][j] == 0) {
                r = i;
                c = j;
                return;
            }
        }
    }
}

void CWIDTACKERSPACE::find_star_in_row(bool** starZ, int nnr, int nnc, int r,
                                       int& c) {
    c = -1;
    assert(r < nnr);
    for (int j = 0; j < nnc; ++j) {
        if (starZ[r][j]) {
            c = j;
            return;
        }
    }
}

void CWIDTACKERSPACE::step_five(int& step, float** C_dynamic, int nnr, int nnc,
                                bool** starZ, bool** primeZ, bool* RowCover,
                                bool* ColCover, int path_row_0,
                                int path_col_0) {
    bool b_done = false;
    int primeR = path_row_0;
    int primeC = path_col_0;
    int r, c;
    while (!b_done) {
        find_star_in_col(starZ, nnr, nnc, r, primeC);
        starZ[primeR][primeC] = true;
        if (r == -1) {
            b_done = true;
            show_cost_matrix(C_dynamic, 3, 3);
        } else {
            starZ[r][primeC] = false;
            find_prime_in_row(primeZ, nnr, nnc, r, c);
            assert(c != -1);
            primeR = r;
            primeC = c;
            show_cost_matrix(C_dynamic, 3, 3);
        }
    }
    step = 3;
    show_cost_matrix(C_dynamic, 3, 3);
}

void CWIDTACKERSPACE::find_star_in_col(bool** starZ, int nnr, int nnc, int& r,
                                       int c) {
    r = -1;
    assert(c < nnc);
    for (int i = 0; i < nnr; ++i) {
        if (starZ[i][c]) {
            r = i;
            return;
        }
    }
}

void CWIDTACKERSPACE::find_prime_in_row(bool** primeZ, int nnr, int nnc, int r,
                                        int& c) {
    c = -1;
    assert(r < nnr);
    for (int j = 0; j < nnc; ++j) {
        if (primeZ[r][j]) {
            c = j;
            return;
        }
    }
}

void CWIDTACKERSPACE::step_six(int& step, float** C_dynamic, int nnr, int nnc,
                               bool** starZ, bool** primeZ, bool* RowCover,
                               bool* ColCover) {
    float min_val;
    find_smallest(C_dynamic, nnr, nnc, RowCover, ColCover, min_val);
    for (int i = 0; i < nnr; ++i) {
        for (int j = 0; j < nnc; ++j) {
            if (RowCover[i]) {
                C_dynamic[i][j] += min_val;
            }
            if (!ColCover[j]) {
                C_dynamic[i][j] -= min_val;
            }
        }
    }
    step = 4;
    show_cost_matrix(C_dynamic, 3, 3);
}

void CWIDTACKERSPACE::find_smallest(float** C_dynamic, int nnr, int nnc,
                                    bool* RowCover, bool* ColCover,
                                    float& min_val) {
    min_val = 1e20f;
    for (int i = 0; i < nnr; ++i) {
        for (int j = 0; j < nnc; ++j) {
            if (!RowCover[i] && !ColCover[j] && C_dynamic[i][j] < min_val) {
                min_val = C_dynamic[i][j];
            }
        }
    }
    assert(min_val != 1e20);
}

void CWIDTACKERSPACE::step_seven(bool** assignment, float& cost,
                                 bool b_translated, float** C, int nr, int nc,
                                 bool** starZ) {
    cost = 0;
    for (int i = 0; i < nr; ++i) {
        for (int j = 0; j < nc; ++j) {
            bool bassigned;
            if (b_translated) {
                bassigned = starZ[j][i];
            } else {
                bassigned = starZ[i][j];
            }
            if (bassigned) {
                cost += C[i][j];
            }
            assignment[i][j] = bassigned;
        }
    }
}

int main() {
    float cost_array[3][3] = { 1, 2, 3,
                               2, 4, 6,
                               3, 6, 9 };
    float total_cost = 0;
    int nr = 3, nc = 3;
    float **cost_ptr = new float*[nr];
    bool **assign_ptr = new bool*[nr];
    for (int i = 0; i < nr; ++i) {
        cost_ptr[i] = new float[nc];
        assign_ptr[i] = new bool[nc];
        for (int j = 0; j < nc; ++j) {
            cost_ptr[i][j] = cost_array[i][j];
            assign_ptr[i][j] = false;
        }
    }

    CWIDTACKERSPACE::munkres(cost_ptr, nr, nc, assign_ptr, total_cost);

    return 0;
}
