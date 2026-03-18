#ifndef RAMPGEN_H
#define RAMPGEN_H

#include "hammerfuncs.h"

// #define RAMPGEN_DEBUG
// #define CONVEX_DEBUG

typedef enum {
    SW,
    SE,
    NE,
    NW
} BoxCorner;

typedef enum {
    DIR_MINUS = 0,
    DIR_PLUS = 1
} AppendDirection;

// TODO: only use in rampgenui, rename to RampGenUIState
typedef struct {
    CMapSolid *ramp;
    float degrees;
    int segments;
    char curve;
    AppendDirection direction;
    float segment_width;
} RampGenCmd;

// TODO: rename to RampGenState, rename ramp_orientation to something else
typedef struct {
    Axis axis;
    AppendDirection direction;
    FaceOrientation orientation;
    char curve;
    bool convex;
    int sign; // dir * facing * axis_sign
    BoxCorner pivot;
    BoxCorner pivot_end;
    BoxCorner pivot_opposite;
    BoxCorner pivot_opposite_end;
    Angle rotate_angle;
    float degrees;
    bool flip_edge; // whether to swap pivot/pivot_end when building the cut plane
    CMapSolid **segment_list;
} RampOrientation;

void rampgen(RampGenCmd *cmd, RampOrientation *ori, bool initial, bool *generating);
void rampgen_undo();
CMapSolid *get_selected_ramp();
bool ramp_orientation(RampGenCmd *cmd, RampOrientation *out_orientation);

#endif // RAMPGEN_H
