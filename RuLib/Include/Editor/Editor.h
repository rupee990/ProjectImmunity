#pragma once

#include "System/RuBaseClass.h"

enum EEditorModes
{
    MapEditor = 0,
    ImageEditor = 1
};
namespace ru
{
    class Editor : public RUClass
    {
    public:
        Editor(ru::Engine* a_engine);
        ~Editor();

        void InitializeEditor();

        void OpenEditorMode(EEditorModes mode);


        void Update();
        void RenderEditor();

    private:
        EEditorModes m_editorMode = EEditorModes::MapEditor;
    };
}