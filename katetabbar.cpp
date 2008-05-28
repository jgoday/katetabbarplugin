/* This file is part of the KDE project

   Copyright (C) 2008 Javier Goday <jgoday @ gmail.com>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.
*/
#include "katetabbar.h"

#include <ktexteditor/document.h>

KateTabBar::KateTabBar(QWidget *parent)
    : KTabBar(parent),
    m_documents(),
    m_keys()
{
    setCloseButtonEnabled(true);
}

KateTabBar::~KateTabBar()
{
}

KTextEditor::Document *KateTabBar::documentFromIndex(int index)
{
    return m_documents [index];
}

void KateTabBar::addDocument(KTextEditor::Document *document)
{
    int key = addTab(document->documentName());
    m_documents [key] = document;
    m_keys [document] = key;

    connect(document, SIGNAL(documentNameChanged(KTextEditor::Document *)),
                 SLOT(slotDocumentChangeName(KTextEditor::Document *)));
}

void KateTabBar::removeDocument(KTextEditor::Document *document)
{
    int key = m_keys [document];

    removeTab(key);

    m_documents.remove(key);
    m_keys.remove(document);
}

void KateTabBar::activateDocument(KTextEditor::Document *document)
{
    int key = m_keys [document];
    setCurrentIndex(key);
}

void KateTabBar::slotDocumentChangeName(KTextEditor::Document *document)
{
    int key = m_keys [document];
    setTabText(key, document->documentName());
}

#include "katetabbar.moc"