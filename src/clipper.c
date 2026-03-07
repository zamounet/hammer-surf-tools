#include "clipper.h"
#include "hooks.h"

// TODO: move to measure.c

Clipper3D_DrawBrushExtents_t orig_Clipper3D_DrawBrushExtents;

void hook_Clipper3D_DrawBrushExtents(void *this_, void *pRender, void *pSolid, int nFlags) {
    Vec3 *ptr = (void *)this_ + CLIPPER3D_OFFSET_PLANE_NORMAL;
    Vec3 normal = (Vec3){
        fabsf(ptr->x),
        fabsf(ptr->y),
        fabsf(ptr->z)
    };

    bool surfable;
    char *str = NormalSurfString(&normal, "clipper plane ", &surfable);
    if (surfable) {
        CRender_DrawText(pRender, str, 10, 30, 2);
    }
    orig_Clipper3D_DrawBrushExtents(this_, pRender, pSolid, nFlags);
}

