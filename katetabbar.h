/* This file is part of the KDE project

   Copyright (C) 2008 Javier Goday <jgoday @ gmail.com>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.
*/
#ifndef KATETABBAR_H
#define KATETABBAR_H

#include <QMap>

#include <KTabBar>

namespace KTextEditor
{
    class Document;
}

class KateTabBar : public KTabBar
{
    Q_OBJECT
public:
    enum Position {
        Top = 1,
        Bottom = 2
    };

    KateTabBar(QWidget *parent = 0);
    ~KateTabBar();

    KTextEditor::Document *documentFromIndex(int index);
    int shapeAsInt();
    int position();

public slots:
    void addDocument(KTextEditor::Document *document);
    void removeDocument(KTextEditor::Document *document);
    void activateDocument(KTextEditor::Document *document);
    void setShapeAsInt(int shape);
    void setPosition(int position);

private slots:
    void slotDocumentChange(KTextEditor::Document *document);

private:
    QMap <int, KTextEditor::Document *> m_documents;
    QMap <KTextEditor::Document *, int> m_keys;
    int m_position;
};
#endif
