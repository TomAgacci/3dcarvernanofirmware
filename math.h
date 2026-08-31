#ifndef LEGAL_MATH_H_REPLACEMENT
#define LEGAL_MATH_H_REPLACEMENT

// ------------------------------------------------------------
// Legal math.h Replacement (CC BY-NC-ND)
// Provides minimal math function prototypes.
// No copyrighted source code included.
// ------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

double sin(double);
double cos(double);
double tan(double);
double sqrt(double);
double fabs(double);
double atan2(double, double);
double pow(double, double);

int isnan(double);
int isinf(double);

#ifdef __cplusplus
}
#endif

#endif
