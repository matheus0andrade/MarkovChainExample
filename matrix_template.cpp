#include <bits/stdc++.h>

using namespace std;

// to use exponentiation, define a unity
template<class T>
class Matrix {
    T unity;
    void inicialize() {
        a.resize(dim);
        for(int i = 0; i < dim; i++)
            a[i].resize(dim);
    }
public:
    int dim;
    vector<vector<T>> a;
    Matrix (int dim) : dim(dim) {
        inicialize();
    }
    Matrix (vector<vector<T>> v) {
        dim = v.size();
        inicialize();
        for(int i = 0; i < dim; i++) {
            for(int j = 0; j < dim; j++) {
                a[i][j] = v[i][j];
            }
        }
    }
    Matrix (int dim, T unity) : dim(dim), unity(unity) {
        inicialize();
        for(int i = 0; i < dim; i++)
            a[i][i] = unity;
    }
    Matrix (const Matrix &m) : dim(m.dim){
        inicialize();
        for(int i = 0; i < dim; i++)
            for(int j = 0; j < dim; j++)
                a[i][j] = m.a[i][j];
    }
    void defUnity(T u) {
        unity = u;
    }
    Matrix& operator+=(const Matrix &m) {
        for(int i = 0; i < dim; i++) {
            for(int j = 0; j < dim; j++) {
                a[i][j] += m.a[i][j]; 
            }
        }
        return *this;
    }
    Matrix operator+(const Matrix &m) {
        Matrix ans(*this);
        return (ans += m);
    }
    Matrix operator-=(const Matrix &m) {
        for(int i = 0; i < dim; i++) {
            for(int j = 0; j < dim; j++) {
                a[i][j] -= m.a[i][j]; 
            }
        }
        return *this;
    }
    Matrix operator-(const Matrix &m) {
        Matrix ans(*this);
        return (ans -= m);
    }
    Matrix operator*(const Matrix &m) {
        Matrix ans(dim);
        for(int i = 0; i < dim; i++) {
            for(int j = 0; j < dim; j++) {
                for(int k = 0; k < dim; k++) {
                    ans.a[i][j] += a[i][k] * m.a[k][j];
                }
            }
        }
        return ans;
    }
    Matrix operator^(long long n) {
        Matrix a(*this), ans(dim, unity);
        while(n) {
            if(n & 1)
                ans = (ans * a);
            n >>= 1;
            a = (a * a);
        }
        return ans;
    }
    void print() {
        for(int i = 0; i < dim; i++) {
            for(int j = 0; j < dim; j++)
                cout << a[i][j] << " ";
            cout << "\n";
        }
    }
};

int main() {
    vector<vector<double>> v = {{0.1, 0.3, 0.6},
                                {0.2, 0.1, 0.7},
                                {0.9, 0.1, 0}};
    Matrix<double> m(v);
    m.defUnity(1.0);
    m.print();
    (m ^ 100000000000).print();
    return 0;
}