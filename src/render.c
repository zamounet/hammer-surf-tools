#include "render.h"
#include "measure.h"

CRender_DrawText_t CRender_DrawText;

//DrawBoundsText_t orig_DrawBoundsText;
Selection3D_RenderTool2D_t orig_Selection3D_RenderTool2D;

// TODO: dont do this
void *selection3d;

// void hook_DrawBoundsText(void *pRender, const float *Mins, const float *Maxs, int nFlags) {
//     // log_msg("[hook] DrawBoundsText\n");
//     orig_DrawBoundsText(pRender, Mins, Maxs, nFlags);
// }

void hook_Selection3D_RenderTool2D(void *this_, void *pRender) {
    /* log_msg("[hook] Selection3D::RenderTool2D %p %p\n", this_, pRender); */
    orig_Selection3D_RenderTool2D(this_, pRender);
    selection3d = this_;

    measure_render_2d(this_, pRender);
}
