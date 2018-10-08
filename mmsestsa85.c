//
// Created by Tu Fengzhi on 2018/9/30.
//

#include "mmsestsa85.h"

// TODO: Add MMSESTSA85
float N[HALF_WINDOW_SIZE]; // Noise Power Spectrum mean
float LambdaD;             // Noise Power Spectrum variance
int N_Count = 0;

int MMSESTSA85(float *Signal, float *OutputSignal)
{
    for (int i = 0; i < WINDOW_SIZE; i++)
    {
        OutputSignal[i] = Signal[i] * Hamming_640[i];
    }

    float Y[HALF_WINDOW_SIZE];
    float YPhase[HALF_WINDOW_SIZE];

    float complex CY[WINDOW_SIZE];
    for (int i = 0; i < WINDOW_SIZE; i++)
    {
        CY[i] = OutputSignal[i];
    }
    int result = fft(CY, WINDOW_SIZE);
    if (result != 0)
    {
        ERROR_INFO("FFT ERROR");
    }

    for (int i = 0; i < HALF_WINDOW_SIZE; i++)
    {
        YPhase[i] = atan2f(cimag(CY[i]), creal(CY[i]));
        Y[i] = sqrtf(creal(CY[i]) * creal(CY[i]) + cimag(CY[i]) * cimag(CY[i]));
    }

    //    if (N_Count < NIS)
    //    {
    //        for (int i = 0; i < HALF_WINDOW_SIZE; i++)
    //        {
    //            N[i] += Y[i];
    //        }
    //        N_Count++;
    //        // TODO: Initial silence segment: Post-Processing
    //
    //        return 1;
    //    }
    //    else if (N_Count == NIS)
    //    {
    //        for (int i = 0; i < HALF_WINDOW_SIZE; i++)
    //        {
    //            N[i] /= NIS;
    //        }
    //        N_Count++;
    //
    //        LambdaD=mean((Y(:,1:NIS)').^2)';%
    //        // TODO: Initial silence end: Post-Processing
    //
    //        return 1;
    //    }

    //
    //    PitchVad(Y, T1, SF);
    //
    //    int NoiseLength = 9;
    //    float Beta = 0.03;
    //
    //    DEBUG("SF:\n");
    //    PrintIntArray(SF, SEGMENT_NUM);
    //
    //    float YS[HALF_WINDOWS_SIZE * SEGMENT_NUM];
    //    for (int i = 0; i < SEGMENT_NUM; i++)
    //    {
    //        if (i == 0 || i == SEGMENT_NUM - 1)
    //        {
    //            for (int j = 0; j < HALF_WINDOWS_SIZE; j++)
    //            {
    //                YS[i * HALF_WINDOWS_SIZE + j] = Y[i * HALF_WINDOWS_SIZE + j];
    //            }
    //        }
    //        else
    //        {
    //            for (int j = 0; j < HALF_WINDOWS_SIZE; j++)
    //            {
    //                YS[i * HALF_WINDOWS_SIZE + j] = (Y[(i - 1) * HALF_WINDOWS_SIZE + j] + Y[i * HALF_WINDOWS_SIZE + j] + Y[(i + 1) * HALF_WINDOWS_SIZE + j]) / 3;
    //            }
    //        }
    //    }
    //
    //    float NRM[HALF_WINDOWS_SIZE];
    //    memset(NRM, 0, HALF_WINDOWS_SIZE * sizeof(float));
    //    float X[HALF_WINDOWS_SIZE * SEGMENT_NUM];
    //    for (int i = 0; i < SEGMENT_NUM; i++)
    //    {
    //        if (SF[i] == 0)
    //        {
    //            // Update N
    //            for (int j = 0; j < HALF_WINDOWS_SIZE; j++)
    //            {
    //                N[j] = (NoiseLength * N[j] + Y[i * HALF_WINDOWS_SIZE + j]) / (NoiseLength + 1);
    //            }
    //            // Obtain X & Noise Remain Maximum
    //            for (int j = 0; j < HALF_WINDOWS_SIZE; j++)
    //            {
    //                NRM[j] = NRM[j] > YS[i * HALF_WINDOWS_SIZE + j] - N[j] ? NRM[j] : YS[i * HALF_WINDOWS_SIZE + j] - N[j];
    //                X[i * HALF_WINDOWS_SIZE + j] = Beta * Y[i * HALF_WINDOWS_SIZE + j];
    //            }
    //        }
    //        else
    //        {
    //            float D[HALF_WINDOWS_SIZE];
    //            for (int j = 0; j < HALF_WINDOWS_SIZE; j++)
    //            {
    //                D[j] = YS[i * HALF_WINDOWS_SIZE + j] - N[j];
    //            }
    //            if (i != 0 && i != SEGMENT_NUM - 1)
    //            {
    //                for (int j = 0; j < SEGMENT_NUM; j++)
    //                {
    //                    if (D[j] < NRM[j])
    //                    {
    //                        D[j] = (D[j] + YS[(i - 1) * HALF_WINDOWS_SIZE + j] - N[j] + YS[(i + 1) * HALF_WINDOWS_SIZE + j] - N[j]) / 3;
    //                    }
    //                }
    //            }
    //            for (int j = 0; j < HALF_WINDOWS_SIZE; j++)
    //            {
    //                X[i * HALF_WINDOWS_SIZE + j] = D[j] > 0 ? D[j] : 0;
    //            }
    //        }
    //    }
    //
    //    memset(outData, 0, FS * sizeof(float));
    //    OverlapAdd2(X, YPhase, outData);
    //
    //    // Post-Process of outData
    //    for (int i = 0; i < FS; i ++)
    //    {
    //        printf("%f ", outData[i]);
    //        //outData[i] *= 1000000;
    //        //DEBUG("%f ", outData[i]);
    //    }
}

//void OverlapAdd2(float *XNEW, float *yphase, float *ReconstructedSignal)
//{
//    float complex Spec[WINDOW_SIZE * SEGMENT_NUM];
//    memset(Spec, 0, WINDOW_SIZE * SEGMENT_NUM * sizeof(float complex));
//    for (int i = 0; i < SEGMENT_NUM; i ++)
//    {
//        for (int j = 0; j < HALF_WINDOWS_SIZE; j ++)
//        {
//            Spec[i * WINDOW_SIZE + j] = XNEW[i * HALF_WINDOWS_SIZE + j] * cexpf(I * yphase[i * HALF_WINDOWS_SIZE + j]);
//        }
//    }
//
//    for (int i = 0; i < SEGMENT_NUM; i ++)
//    {
//        for (int j = 1; j < HALF_WINDOWS_SIZE - 1; j ++)
//        {
//            Spec[i * WINDOW_SIZE + WINDOW_SIZE - j] = conjf(Spec[i * WINDOW_SIZE + j]);
//        }
//    }
//
//    int sigLength = ((SEGMENT_NUM - 1) * FRAME_STEP_SIZE + WINDOW_SIZE);
//    DEBUG("True Output Length: %d\n", sigLength);
//
//    // Reconstruct the new signal
//    for (int i = 0; i < SEGMENT_NUM; i ++)
//    {
//        int start = i * FRAME_STEP_SIZE;
//        float complex spec[WINDOW_SIZE];
//        memcpy(spec, Spec + i * WINDOW_SIZE, WINDOW_SIZE * sizeof(float complex));
//        ift(spec, WINDOW_SIZE);
//        for (int j = start; j < start + WINDOW_SIZE; j ++)
//        {
//            ReconstructedSignal[j] += creal(spec[j - start]);
//        }
//    }
//}

//void Hamming(const int length, float *wnd)
//{
//    int i = 0;
//    for (i = 0; i < length; i++)
//        wnd[i] = 0.54F - 0.46F * cos(2.0F * PI * (float)i / (length - 1));
//}
