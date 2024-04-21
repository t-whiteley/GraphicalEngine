#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <unistd.h>

int main() {
    float dx, dy, dz, d_pitch, d_yaw;
    char invar;
    float rotation_rate = 0.2;
    float displacement_rate = 3;

    while (true) {
        // std::cout << "Type rel. coord changes: \n"; // Type a number and press enter
        // std::cin >> dx;
        // std::cin >> dy;
        // std::cin >> dz;
        // std::cin >> d_pitch;
        // std::cin >> d_yaw;

        std::cout << "Type rel. coord changes: \n"; // Type a number and press enter
        std::cin >> invar;
        std::cout << invar << std::endl;
        switch (invar) {
            case 'w': dz = displacement_rate; break;
            case 's': dz = -displacement_rate; break;
            case 'd': dx = displacement_rate; break;
            case 'a': dx = -displacement_rate; break;
            case 'u': dy = displacement_rate; break;
            case 'i': dy = -displacement_rate; break;
            case 'm': d_pitch = rotation_rate; break;
            case 'n': d_pitch = -rotation_rate; break;
            case 'k': d_yaw = rotation_rate; break;
            case 'j': d_yaw = -rotation_rate; break;
            default:  break;
        }
        usleep(20000);
    }

}