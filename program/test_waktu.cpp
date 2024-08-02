#include "bits/stdc++.h"
#include "math.h"
#include "stdio.h"
#include "time.h"
#include "fstream"
#include "sys/time.h"
#include "chrono"
#include <vector>

#define DEG2RAD 0.01745329251994329576923690768489

char lut_buffer[360 * 3200 * 2];
int16_t LUT_fr2lap[1152000];
int LUT_arr[1152000];

float regress(double x)
{
    static const double terms[] = {
        6.9160619726989942e+005,
        -2.4702944302228745e+004,
        3.3769239273207108e+002,
        -2.0811507184528475e+000,
        5.2850430392945100e-003,
        -1.8747325853441007e-005,
        2.3197729279585872e-007,
        -8.1432403093594152e-010,
        -1.0497470630476182e-012,
        -9.5365340464564735e-015,
        1.8690669332287895e-016,
        -7.1692564354856969e-019,
        8.8479542465521107e-022};

    size_t csz = sizeof terms / sizeof *terms;

    double t = 1;
    float r = 0;
    for (int i = 0; i < csz; i++)
    {
        r += terms[i] * t;
        t *= x;
    }
    return r;
}

int nn_v0(float dist, float theta)
{
    while (theta < 0)
        theta += 360;
    while (theta > 360)
        theta -= 360;

    return LUT_arr[(int)(dist) * 320 + (int)(theta)];
}

float nn_v2(float dist_px, float angle_px)
{
    if (dist_px < 75)
        dist_px = 75;
    else if (dist_px > 319)
        dist_px = 319;

    if (angle_px >= 360)
        angle_px -= 360;
    else if (angle_px < 0)
        angle_px += 360;

    /* This is coordinate that just based on robot */
    float ret_buffer = LUT_fr2lap[(int)(angle_px) * 3200 + (int)(dist_px * 10)];

    return ret_buffer;
}

int main()
{
    std::ifstream lut_px2cm_fs("lut_px2cm.bin", std::ios::binary | std::ios::in);
    lut_px2cm_fs.read((char *)lut_buffer, 360 * 3200 * 2);
    lut_px2cm_fs.close();
    memcpy(LUT_fr2lap, lut_buffer, sizeof(lut_buffer));

    std::stringstream filename;
    filename << "LUT_fr2lap.csv";
    std::ifstream myFile(filename.str().c_str());
    std::string line;
    std::getline(myFile, line);

    auto st = 0U;
    auto end = line.find(",");
    uint32_t cntr = 0;
    while (end != std::string::npos)
    {
        LUT_arr[cntr] = atoi(line.substr(st, end - st).c_str());
        st = end + 1;
        end = line.find(",", st);

        cntr++;
    }

    float dist_px_test = 120;
    float angle_px_test = 90;

    // Get nano seconds elapsed since epoch

    while (1)
    {
        static uint8_t it = 0;
        auto start = std::chrono::high_resolution_clock::now();
        float dist_fld_flt = nn_v2(dist_px_test, angle_px_test);
        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = finish - start;

        auto start_2 = std::chrono::high_resolution_clock::now();
        float dist_fld_test_regress = regress(dist_px_test);
        auto finish_2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_2 = finish_2 - start_2;

        it++;

        if (it >= 20)
        {
            break;
        }
        else if (it >= 10)
        {
            std::cout << (int)it - 10 << " " << elapsed.count() * 1000000000 << " " << elapsed_2.count() * 1000000000 << "\n";
        }
    }

    return 0;
}