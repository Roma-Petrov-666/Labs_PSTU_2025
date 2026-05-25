#include <iostream>
#include <fstream>
#include <string>

int count_total_series() {
    int total = 0;
    std::string names[4] = {"f1.txt", "f2.txt", "f3.txt", "f4.txt"};

    for (int i = 0; i < 4; i++) {
        std::ifstream f(names[i]);
        if (!f.is_open()) continue;

        int cur, temp;
        if (f >> cur) {
            total++;
            while (f >> temp) {
                if (temp < cur) total++;
                cur = temp;
            }
        }
        f.close();
    }
    return total;
}

int distribution(std::string main_path, std::string path1, std::string path2, std::string path3, std::string path4) {
    std::ofstream f1, f2, f3, f4;
    std::ifstream mainf;

    f1.open(path1); f2.open(path2); f3.open(path3); f4.open(path4);
    mainf.open(main_path);

    if (!f1.is_open() || !f2.is_open() || !f3.is_open() ||
        !f4.is_open() || !mainf.is_open()) {
        return -1;
    }

    int cur, temp;
    int series_cnt = 0;
    int write_to = 1;

    if (mainf >> cur) {
        series_cnt = 1;
        f1 << cur << ' ';

        while (mainf >> temp) {
            if (temp < cur) {
                series_cnt++;
                write_to = write_to % 4 + 1;
            }
            cur = temp;

            if (write_to == 1)      f1 << cur << ' ';
            else if (write_to == 2) f2 << cur << ' ';
            else if (write_to == 3) f3 << cur << ' ';
            else                    f4 << cur << ' ';
        }
    }

    mainf.close();
    f1.close(); f2.close(); f3.close(); f4.close();
    return series_cnt;
}

int merge(std::string in1, std::string in2, std::string in3, std::string in4, std::string out) {
    std::ifstream f1, f2, f3, f4;
    std::ofstream fout;

    f1.open(in1); f2.open(in2); f3.open(in3); f4.open(in4);
    fout.open(out);

    if (!f1.is_open() || !f2.is_open() || !f3.is_open() ||
        !f4.is_open() || !fout.is_open()) {
        return -1;
    }

    int series_out = 0;
    int val1, val2, val3, val4;

    f1 >> val1; bool have1 = !f1.fail();
    f2 >> val2; bool have2 = !f2.fail();
    f3 >> val3; bool have3 = !f3.fail();
    f4 >> val4; bool have4 = !f4.fail();

    while (have1 || have2 || have3 || have4) {
        series_out++;
        bool end1 = false, end2 = false, end3 = false, end4 = false;
        bool stop_series = false;

        while (!stop_series) {
            int chosen = 0;
            int min_val;
            bool found = false;

            if (!end1 && have1) {
				min_val = val1;
				chosen = 1;
				found = true;
			}
            if (!end2 && have2 && (!found || val2 < min_val)) {
				min_val = val2;
				chosen = 2;
				found = true;
			}
            if (!end3 && have3 && (!found || val3 < min_val)) {
				min_val = val3;
				chosen = 3;
				found = true;
			}
            if (!end4 && have4 && (!found || val4 < min_val)) {
				min_val = val4;
				chosen = 4;
				found = true;
			}

            if (!found) {
                stop_series = true;
                break;
            }

            fout << min_val << ' ';

            if (chosen == 1) {
                int temp;
                if (f1 >> temp) {
                    if (temp < val1) end1 = true;
                    val1 = temp;
                } else { have1 = false; end1 = true; }
            } else if (chosen == 2) {
                int temp;
                if (f2 >> temp) {
                    if (temp < val2) end2 = true;
                    val2 = temp;
                } else { have2 = false; end2 = true; }
            } else if (chosen == 3) {
                int temp;
                if (f3 >> temp) {
                    if (temp < val3) end3 = true;
                    val3 = temp;
                } else { have3 = false; end3 = true; }
            } else {
                int temp;
                if (f4 >> temp) {
                    if (temp < val4) end4 = true;
                    val4 = temp;
                } else { have4 = false; end4 = true; }
            }

            if ((end1 || !have1) && (end2 || !have2) &&
                (end3 || !have3) && (end4 || !have4))
                stop_series = true;
        }
    }

    f1.close(); f2.close(); f3.close(); f4.close();
    fout.close();
    return series_out;
}

void copy_file(std::string src_path, std::string dst_path) {
    std::ifstream src(src_path);
    std::ofstream dst(dst_path);
    int x;
    while (src >> x) dst << x << ' ';
    src.close();
    dst.close();
}

void external_sort(std::string output) {
    int series = count_total_series();

    if (series < 0) {
        return;
    }

    if (series == 1) {
        series = merge("f1.txt", "f2.txt", "f3.txt", "f4.txt", "merged.txt");
        copy_file("merged.txt", output);
        return;
    }

    std::string merged = "merged.txt";

    while (series > 1) {
        series = merge("f1.txt", "f2.txt", "f3.txt", "f4.txt", merged);
        if (series == 1) {
            copy_file(merged, output);
            return;
        }

        series = distribution(merged, "f1.txt", "f2.txt", "f3.txt", "f4.txt");
        if (series == 1) {
            copy_file("f1.txt", output);
            return;
        }
    }
}

int main() {
    external_sort("result.txt");

    std::ifstream res("result.txt");
    if (!res.is_open()) {
        return 1;
    }

    int num;
    while (res >> num)
        std::cout << num << " ";
    std::cout << std::endl;

    res.close();
    return 0;
}