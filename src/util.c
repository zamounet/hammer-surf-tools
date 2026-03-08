#include "util.h"
#include "hammerfuncs.h"
#include "hooks.h"

int AfxMessageBoxF(UINT nType, const char* fmt, ...) {
    const int BUFFER_SIZE = 512;
    char buffer[BUFFER_SIZE];

    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, BUFFER_SIZE, fmt, args);
    va_end(args);

    return AfxMessageBox(buffer, nType, 0);
}

CMapClass *new_CMapEntity() {
    CMapClass *ent = ValveAlloc(CMAPENTITY_SIZE);
    CMapEntity_CMapEntity(ent);
    return ent;
}

CMapClass *new_CMapSolid() {
    CMapClass *ent = ValveAlloc(CMAPSOLID_SIZE);
    CMapSolid_CMapSolid(ent, nullptr);
    return ent;
}

RefVector *CMapDoc_GetSelection(CMapDoc *doc) {
    return &doc->m_pSelection->m_SelectionList;
}

void *GetFaceEditSheet() {
    void *wnd = GetMainWnd();
    if (!wnd) {
        return nullptr;
    }
    return *(void **)((void *)wnd + CMainFrame_m_pFaceEditSheet_Offset);
}

FaceEditSheetFaces *CFaceEditSheet_GetFaces(void *sheet) {
    return (void *)sheet + CFaceEditSheet_m_Faces_Offset;
}

static bool solid_count_cb(CMapClass *ent, void *param) {
    int *count = (int *)param;
    if (CMapClass_IsSolid(ent)) {
        (*count)++;
    }
    return true;
}

static bool get_first_solid_cb(CMapClass *ent, void *param) {
    CMapClass **out = (CMapClass **)param;
    if (CMapClass_IsSolid(ent)) {
        *out = ent;
        return false;
    }
    return true;
}

int CMapClass_SolidCount(CMapClass *ent) {
    if (CMapClass_IsSolid(ent)) {
        return 1;
    }

    int count = 0;
    CMapClass_EnumChildren(ent, solid_count_cb, &count, nullptr);
    return count;
}

CMapClass *CMapClass_FirstSolid(CMapClass *ent) {
    if (CMapClass_IsSolid(ent)) {
        return ent;
    }

    CMapClass *solid = nullptr;
    CMapClass_EnumChildren(ent, get_first_solid_cb, &solid, nullptr);
    return solid;
}
