#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// Функция для умножения матриц
vector<vector<double>> multiplyMatrices(const vector<vector<double>>& A1, const vector<vector<double>>& A2) {
    int N = A1.size();
    int M = A1[0].size();
    int K = A2[0].size();

    vector<vector<double>> result(N, vector<double>(K, 0.0));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < K; j++) {
            result[i][j] = 0;
            for (int k = 0; k < M; k++) {
                result[i][j] += A1[i][k] * A2[k][j];
            }
        }
    }
    return result;
}

// Функция для возведения матрицы в степень
vector<vector<double>> powerMatrix(const vector<vector<double>>& A, int x) {
    int N = A.size();
    vector<vector<double>> result(N, vector<double>(N, 0.0));

    // Инициализация единичной матрицы
    for (int i = 0; i < N; i++) {
        result[i][i] = 1.0;
    }

    // Возведение в степень
    vector<vector<double>> base = A;
    while (x > 0) {
        if (x % 2 == 1) {
            result = multiplyMatrices(result, base);
        }
        base = multiplyMatrices(base, base);
        x /= 2;
    }
    return result;
}

// Функция для вывода матрицы
void printMatrix(const vector<vector<double>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& value : row) {
            cout << value << " ";
        }
        cout << endl;
    }
}

int main(int argc, char* argv[])
{
    bool isHuman = false;
    if (argc <= 1 || strcmp(argv[1], "false") != 0)
    {
        isHuman = true;
    }

    setlocale(LC_ALL, "Russian");
    int N, M;
    if (isHuman) {
        cout << "Введите размеры матрицы A1 (N M): ";
    }
    cin >> N >> M;

    vector<vector<double>> A1(N, vector<double>(M));

    // Ввод матрицы A1
    if (isHuman) {
        cout << "Введите элементы матрицы A1 (N строк, M чисел в каждой):" << endl;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> A1[i][j];
        }
    }
    

    while (true) {
        int command;
        if (isHuman) {
            cout << "Введите команду (0 - выход, 1 - вывод A1, 2 - A1 = A1 * A2, 3 - A1 = A1^x): ";
        }
        cin >> command;

        if (command == 0) {
            break; // Завершение программы
        }
        else if (command == 1) {
            printMatrix(A1); // Вывод матрицы A1 
        }
        else if (command == 2) {
            int K;
            if (isHuman) {
                cout << "Введите размер K для матрицы A2: ";
            }
            cin >> K;
            vector<vector<double>> A2(M, vector<double>(K));

            // Ввод матрицы A2 
            if (isHuman) {
                cout << "Введите элементы матрицы A2 (M строк, K чисел в каждой):" << endl;
            }
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < K; j++) {
                    cin >> A2[i][j];
                }
            }

            // Умножение матриц
            if (N != K) {
                cout << "NO" << endl; // Невозможно умножить
            }
            else {
                A1 = multiplyMatrices(A1, A2); // Умножение A1 на A2
                N = A1.size();
                M = A1[0].size();
            }
        }
        else if (command == 3) {           // Возведение A1 в степень x
            int x;
            if (N != M) {
                cout << "NO" << endl; // Невозможно возвести в степень
            }
            else {
                if (isHuman) {
                    cout << "Введите натуральное число x (степень): ";
                }
                cin >> x;
                A1 = powerMatrix(A1, x); // Возведение A1 в степень x
            }
        }
    }

    return 0;
}

