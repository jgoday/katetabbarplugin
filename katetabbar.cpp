/* This file is part of the KDE project

   Copyright (C) 2008 Javier Goday <jgoday @ gmail.com>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.
*/
#include "katetabbar.h"

#include <KIcon>
#include <KIconLoader>
#include <KIO/NetAccess>
#include <KParts/Part>
#include <KTextEditor/Document>

KateTabBar::KateTabBar(QWidget *parent)
    : KTabBar(parent),
    m_documents(),
    m_keys(),
    m_position(0)
{
    setShape(QTabBar::RoundedSouth);
    setCloseButtonEnabled(true);
}

KateTabBar::~KateTabBar()
{
}

KTextEditor::Document *KateTabBar::documentFromIndex(int index)
{
    return m_documents [index];
}

int KateTabBar::shapeAsInt()
{
    switch(shape()) {
        case QTabBar::RoundedNorth:
            return 0;
            break;
        default:
            return 1;
    };
}

int KateTabBar::position()
{
    return m_position;
}

void KateTabBar::addDocument(KTextEditor::Document *document)
{
    int key = addTab(document->documentName());
    m_documents [key] = document;
    m_keys [document] = key;

    connect(document, SIGNAL(documentNameChanged(KTextEditor::Document *)),
                SLOT(slotDocumentChange(KTextEditor::Document *)));
    connect(document, SIGNAL(modifiedChanged(KTextEditor::Document *)),
                SLOT(slotDocumentChange(KTextEditor::Document *)));
}

void KateTabBar::removeDocument(KTextEditor::Document *document)
{
    int key = m_keys [document];

    m_documents.remove(key);
    m_keys.remove(document);

    foreach(int i, m_documents.keys()) {
        if (i > key) {
            KTextEditor::Document *doc = m_documents [i];

            m_documents.remove(i);
            m_keys.remove(doc);

            m_documents [i-1] = doc;
            m_keys [doc] = i-1;
        }
    }

    removeTab(key);
}

void KateTabBar::activateDocument(KTextEditor::Document *document)
{
    int key = m_keys [document];
    setCurrentIndex(key);
}

void KateTabBar::setShapeAsInt(int shape)
{
    switch(shape) {
        case QTabBar::RoundedNorth:
            setShape(QTabBar::RoundedNorth);
            break;
        default:
            setShape(QTabBar::RoundedSouth);
            break;
    };
}

void KateTabBar::setPosition(int position)
{
    m_position = position;
}

void KateTabBar::slotDocumentChange(KTextEditor::Document *document)
{
    int key = m_keys [document];

    // sets the icon
    setTabIcon(key, KIcon(KIO::pixmapForUrl(document->url(), 0, KIconLoader::Desktop, 16)));

    if(document->isModified()) {
        setTabText(key, document->documentName() + " *");
        setTabTextColor(key, Qt::red);
    }
    else {
        setTabText(key, document->documentName());
        setTabTextColor(key, Qt::black);
    }
}

#include "katetabbar.moc"
