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
    KateTabBar(QWidget *parent = 0);
    ~KateTabBar();

    KTextEditor::Document *documentFromIndex(int index);

public slots:
    void addDocument(KTextEditor::Document *document);
    void removeDocument(KTextEditor::Document *document);
    void activateDocument(KTextEditor::Document *document);

private slots:
    void slotDocumentChangeName(KTextEditor::Document *document);

private:
    QMap <int, KTextEditor::Document *> m_documents;
    QMap <KTextEditor::Document *, int> m_keys;
};
#endif
