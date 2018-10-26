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
float X[HALF_WINDOW_SIZE];
float RemainSignal[WINDOW_SIZE - SHIFT_SIZE];

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

// Y=OverlapAdd(X,A,W,S);
// Y is the signal reconstructed signal from its spectrogram. X is a matrix with each column being the fft of a segment of signal. A is the phase angle of the spectrum which should have the same dimension as X. if it is not given the phase angle of X is used which in the case of real values is zero (assuming that its the magnitude). W is the window length of time domain segments if not given the length is assumed to be twice as long as fft window length. S is the shift length of the segmentation process ( for example in the case of non overlapping signals it is equal to W and in the case of %50 overlap is equal to W/2. if not givven W/2 is used. Y is the reconstructed time domain signal.
void OverlapAdd2(float *XNEW, float *ReconstructedSignal, float *yphase)
{
    float complex Spec[WINDOW_SIZE];
    // conj(Spec)
    for (int i = 0; i < HALF_WINDOW_SIZE; i++)
    {
        Spec[i] = XNEW[i] * cexpf(I * yphase[i]);
    }
    for (int i = 1; i < HALF_WINDOW_SIZE - 1; i++)
    {
        Spec[WINDOW_SIZE - i] = conjf(Spec[i]);
    }

    // Reconstruct the new signal
    ift(Spec, WINDOW_SIZE);
    for (int i = 0; i < WINDOW_SIZE; i++)
    {
        ReconstructedSignal[i] = crealf(Spec[i]);
    }
    for (int i = 0; i < WINDOW_SIZE - SHIFT_SIZE; i++)
    {
        ReconstructedSignal[i] += RemainSignal[i];
    }
    for (int i = SHIFT_SIZE; i < WINDOW_SIZE; i++)
    {
        RemainSignal[i - SHIFT_SIZE] = ReconstructedSignal[i];
    }
}

int MMSESTSA85(float *Signal, float *OutputSignal)
{
    N_Count++;

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

    if (N_Count <= NIS)
    {
        for (int i = 0; i < HALF_WINDOW_SIZE; i++)
        {
            N[i] += Y[i];
            LambdaD[i] += Y[i] * Y[i];
        }
        return 2; // Initial Service
    }
    else if (N_Count == NIS + 1)
    {
        for (int i = 0; i < HALF_WINDOW_SIZE; i++)
        {
            N[i] /= NIS;
            LambdaD[i] /= NIS;
        }

        SpeechFlag = 0;
        NoiseCounter = 100;
    }

    // Magnitude Spectrum Distance VAD
    SpeechFlag = VAD(Y, N, &NoiseCounter);

    // Update Noise Info
    if (N_Count > NIS && SpeechFlag == 0) // If not Speech Update Noise Parameters
    {
        for (int i = 0; i < HALF_WINDOW_SIZE; i++)
        {
            N[i] = (NOISE_LENGTH * N[i] + Y[i]) / (NOISE_LENGTH + 1) + EPSILON;
            LambdaD[i] = (NOISE_LENGTH * LambdaD[i] + Y[i] * Y[i]) / (NOISE_LENGTH + 1) + EPSILON;
        }
    }

    // Post-Processing
    float GammaNew[HALF_WINDOW_SIZE];
    float xi[HALF_WINDOW_SIZE];
    for (int i = 0; i < HALF_WINDOW_SIZE; i++)
    {
        GammaNew[i] = Y[i] * Y[i] / LambdaD[i] + EPSILON; // A Postiriori SNR
        xi[i] = ALPHA * G[i] * G[i] * Gamma[i] + (1 - ALPHA) * fmaxf(GammaNew[i] - 1, 0) + EPSILON;
    }

    memcpy(Gamma, GammaNew, HALF_WINDOW_SIZE * sizeof(float));

    float nu[HALF_WINDOW_SIZE];
    for (int i = 0; i < HALF_WINDOW_SIZE; i++)
    {
        nu[i] = Gamma[i] * xi[i] / (1 + xi[i]) + EPSILON;                                                    // A Function Used in Calculation of Gain
        G[i] = xi[i] / (1 + xi[i]) * expf(0.5F * expint_interpolation(nu[i])) + EPSILON; // Log Spectral MMSE [Ephraim 1985]
        X[i] = G[i] * Y[i];
    }

    OverlapAdd2(X, OutputSignal, YPhase);

    return SpeechFlag;
}

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
    memcpy(Left, Buffer, StepSize * sizeof(float));
    memcpy(Right, Buffer + BufferSize, StepSize * sizeof(float));
}
