#ifndef TRACK_H
#define TRACK_H


extern float Err_1;
extern float Err_fro_sum;
extern float Err_fro;
extern float Err_fro_D;


float Track1PID(int16_t PosY);
float Track2PID(int16_t PosX);
float Track1PID_move(int16_t PosY);
float Track2PID_move(int16_t PosX);
float Track2PID_side(int16_t PosX);
float Track2PID_front(int16_t PosX);
float Track2PID_back(int16_t PosX);


#endif 