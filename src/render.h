#ifndef RENDER_H
#define RENDER_H

#include "common.h"

extern CRender_DrawText_t CRender_DrawText;

// extern DrawBoundsText_t orig_DrawBoundsText;
extern Selection3D_RenderTool2D_t orig_Selection3D_RenderTool2D;

//void hook_DrawBoundsText(void *pRender, const float *Mins, const float *Maxs, int nFlags);
void hook_Selection3D_RenderTool2D(void *this_, void *pRender);

// TODO: dont do this
extern void *selection3d;

#endif // RENDER_H
