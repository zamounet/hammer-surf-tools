#ifndef HOOKS_H
#define HOOKS_H

#include "common.h"

typedef LRESULT (*AfxWndProc_t)(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
extern AfxWndProc_t orig_AfxWndProc;
LRESULT hook_AfxWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

typedef void (*Clipper3D_DrawBrushExtents_t)(void *this_, void *pRender, void *pSolid, int nFlags);
extern Clipper3D_DrawBrushExtents_t orig_Clipper3D_DrawBrushExtents;
void hook_Clipper3D_DrawBrushExtents(void *this_, void *pRender, void *pSolid, int nFlags);

// typedef void *(*SetFocus_t)(void *this_);
// extern SetFocus_t orig_SetFocus;
// void *hook_SetFocus(void *this_);

typedef void (*SetActiveMapDoc_t)(void *doc);
extern SetActiveMapDoc_t orig_SetActiveMapDoc;
void hook_SetActiveMapDoc(void *doc);

// typedef void (*CFaceEditSheet_ClickFace_t)(void *this_, CMapClass *pSolid, int faceIndex, int cmd, int clickMode);
// extern CFaceEditSheet_ClickFace_t orig_CFaceEditSheet_ClickFace;
// void hook_CFaceEditSheet_ClickFace(void *this_, CMapClass *pSolid, int faceIndex, int cmd, int clickMode);

typedef bool (*EnableMenuItem_t)(HMENU hMenu, UINT uIDEnableItem, UINT uEnable);
extern EnableMenuItem_t orig_EnableMenuItem;
bool hook_EnableMenuItem(HMENU hMenu, UINT uIDEnableItem, UINT uEnable);

typedef HMENU (*LoadMenuW_t)(HINSTANCE hInstance, LPCWSTR lpMenuName);
extern LoadMenuW_t orig_LoadMenuW;
HMENU hook_LoadMenuW(HINSTANCE hInstance, LPCWSTR lpMenuName);

typedef HACCEL (*LoadAcceleratorsA_t)(HINSTANCE hInstance, LPCSTR lpTableName);
extern LoadAcceleratorsA_t orig_LoadAcceleratorsA;
HACCEL hook_LoadAcceleratorsA(HINSTANCE hInstance, LPCSTR lpTableName);

typedef void (*Selection3D_RenderTool2D_t)(void *this_, void *pRender);
extern Selection3D_RenderTool2D_t orig_Selection3D_RenderTool2D;
void hook_Selection3D_RenderTool2D(void *this_, void *pRender);

CMapDoc *GetActiveMapDoc();

#endif // HOOKS_H
