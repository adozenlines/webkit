/*
 * Copyright (C) 2007 Luca Bruno <lethalman88@gmail.com>
 * Copyright (C) 2009 Holger Hans Peter Freyther
 * Copyright (C) 2010 Martin Robinson <mrobinson@webkit.org>
 * Copyright (C) 2010 Igalia S.L.
 * All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */

#ifndef PasteboardHelper_h
#define PasteboardHelper_h

#include <wtf/NeverDestroyed.h>
#include <wtf/Noncopyable.h>
#include <wtf/Vector.h>
#include <wtf/glib/GRefPtr.h>

namespace WebCore {

class DataObjectGtk;

class PasteboardHelper {
    WTF_MAKE_NONCOPYABLE(PasteboardHelper);
public:
    static PasteboardHelper& singleton();

    enum SmartPasteInclusion { IncludeSmartPaste, DoNotIncludeSmartPaste };

    GtkTargetList* targetList() const;
    GtkTargetList* targetListForDataObject(DataObjectGtk*, SmartPasteInclusion = DoNotIncludeSmartPaste);
    void fillSelectionData(GtkSelectionData*, guint, DataObjectGtk*);
    void fillDataObjectFromDropData(GtkSelectionData*, guint, DataObjectGtk*);
    Vector<GdkAtom> dropAtomsForContext(GtkWidget*, GdkDragContext*);
    void writeClipboardContents(GtkClipboard*, SmartPasteInclusion = DoNotIncludeSmartPaste, GClosure* = 0);
    void getClipboardContents(GtkClipboard*);

    enum PasteboardTargetType { TargetTypeMarkup, TargetTypeText, TargetTypeImage, TargetTypeURIList, TargetTypeNetscapeURL, TargetTypeSmartPaste, TargetTypeUnknown };
    bool clipboardContentSupportsSmartReplace(GtkClipboard*);

private:
    PasteboardHelper();
    ~PasteboardHelper() = delete;

    GRefPtr<GtkTargetList> m_targetList;

    friend class WTF::NeverDestroyed<PasteboardHelper>;
};

}

#endif // PasteboardHelper_h
