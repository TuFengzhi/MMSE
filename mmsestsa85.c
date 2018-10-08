//
// Created by Tu Fengzhi on 2018/9/30.
//

#include "mmsestsa85.h"

// TODO: Add MMSESTSA85
float N[HALF_WINDOW_SIZE];       // Noise Power Spectrum mean
float LambdaD[HALF_WINDOW_SIZE]; // Noise Power Spectrum variance
int N_Count = 0;
int NoiseCounter = 0;
float G[HALF_WINDOW_SIZE] = {[0 ... HALF_WINDOW_SIZE - 1] = 1};
float Gamma[HALF_WINDOW_SIZE] = {[0 ... HALF_WINDOW_SIZE - 1] = 1};
int SpeechFlag = 0;

float Mean(float *Data, int Length)
{
    float Sum = 0;
    for (int i = 0; i < Length; i++)
    {
        Sum += Data[i];
    }
    return Sum / Length;
}

// Spectral Distance Voice Activity Detector
// SIGNAL is the the current frames magnitude spectrum which is to labeld as noise or speech, NOISE is noise magnitude spectrum template (estimation), NOISECOUNTER is the number of imediate previous noise frames, NOISEMARGIN (default 3)is the spectral distance threshold. HANGOVER ( default 8 )is the number of noise segments after which the SPEECHFLAG is reset (goes to zero). NOISEFLAG is set to one if the the segment is labeld as noise NOISECOUNTER returns the number of previous noise segments, this value is reset (to zero) whenever a speech segment is detected. DIST is the spectral distance.

int VAD(float *Signal, float *Noise, int *NoiseCounter)
{
    int NoiseMargin = 3;
    int Hangover = 8;
    int SpeechFlag = 0;

    float SpectralDist[HALF_WINDOW_SIZE];
    for (int i = 0; i < HALF_WINDOW_SIZE; i++)
    {
        SpectralDist[i] = 20 * (log10f(Signal[i]) - log10f(Noise[i]));
        if (SpectralDist[i] < 0)
            SpectralDist[i] = 0;
    }
    float Dist = Mean(SpectralDist, HALF_WINDOW_SIZE);

    if (Dist < NoiseMargin)
        *NoiseCounter += 1;
    else
        *NoiseCounter = 0;

    if (*NoiseCounter > Hangover)
        SpeechFlag = 0;
    else
        SpeechFlag = 1;

    return SpeechFlag;
}

int MMSESTSA85(float *Signal, float *OutputSignal)
{
    for (int i = 0; i < WINDOW_SIZE; i++)
    {
        OutputSignal[i] = Signal[i] * HammingWindows[i];
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
        YPhase[i] = atan2f(cimagf(CY[i]), crealf(CY[i]));
        Y[i] = sqrtf(crealf(CY[i]) * crealf(CY[i]) + cimagf(CY[i]) * cimagf(CY[i]));
    }

    if (N_Count < NIS)
    {
        for (int i = 0; i < HALF_WINDOW_SIZE; i++)
        {
            N[i] += Y[i];
            LambdaD[i] += Y[i] * Y[i];
        }
        N_Count++;

        return 0;
    }
    else if (N_Count == NIS)
    {
        for (int i = 0; i < HALF_WINDOW_SIZE; i++)
        {
            N[i] /= NIS;
            LambdaD[i] /= NIS;
        }
        N_Count++;

        SpeechFlag = 0;
        NoiseCounter = 100;
    }

    // Magnitude Spectrum Distance VAD
    SpeechFlag = VAD(Y, N, &NoiseCounter);

    // Update Noise Info
    if (SpeechFlag == 0) // If not Speech Update Noise Parameters
    {
        for (int i = 0; i < HALF_WINDOW_SIZE; i++)
        {
            N[i] = (NOISE_LENGTH * N[i] + Y[i]) / (NOISE_LENGTH + 1);
            LambdaD[i] = (NOISE_LENGTH * LambdaD[i] + Y[i] * Y[i]) / (NOISE_LENGTH + 1);
        }
    }

    // TODO: Post-Processing

    return SpeechFlag;
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

void ReadBuffer(float *Left, float *Right, int StepSize, float *Buffer, int BufferSize)
{
    // Read Buffer to the end of ICAInput
    memcpy(Buffer, Buffer + StepSize, (BufferSize - StepSize) * sizeof(float));
    memcpy(Buffer + BufferSize, Buffer + BufferSize + StepSize, (BufferSize - StepSize) * sizeof(float));
    memcpy(Buffer + BufferSize - StepSize, Left, StepSize * sizeof(float));
    memcpy(Buffer + BufferSize * 2 - StepSize, Right, StepSize * sizeof(float));
}

void WriteBuffer(float *Buffer, int BufferSize, float *Left, float *Right, int StepSize)
{
    // Write Buffer from the end of ICAOutput
    memcpy(Left, Buffer + BufferSize - StepSize, StepSize * sizeof(float));
    memcpy(Right, Buffer + BufferSize * 2 - StepSize, StepSize * sizeof(float));
}
