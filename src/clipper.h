#ifndef CLIPPER_H
#define CLIPPER_H

#include "common.h"

extern Clipper3D_DrawBrushExtents_t orig_Clipper3D_DrawBrushExtents;

void hook_Clipper3D_DrawBrushExtents(void *this_, void *pRender, void *pSolid, int nFlags);

#endif // CLIPPER_H
