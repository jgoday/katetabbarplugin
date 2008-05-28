/* This file is part of the KDE project

   Copyright (C) 2008 Javier Goday <jgoday @ gmail.com>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.
*/
#include "katetabsplugin.h"
#include "katetabbar.h"

#include <QLabel>
#include <QVBoxLayout>

#include <kate/application.h>
#include <ktexteditor/document.h>
#include <ktexteditor/view.h>
#include <kdebug.h>
#include <kgenericfactory.h>

K_EXPORT_COMPONENT_FACTORY(katetabsplugin, KGenericFactory<KateTabsPlugin>("katetabsplugin"))

KateTabsPlugin::KateTabsPlugin(QObject *parent, const QStringList &parameters) :
    Kate::Plugin(qobject_cast <Kate::Application *> (parent))
{
    Q_UNUSED (parameters)
}

KateTabsPlugin::~KateTabsPlugin()
{/*
    delete m_view;*/
}

Kate::PluginView *KateTabsPlugin::createView(Kate::MainWindow *window)
{
    return new KateTabsPluginView(window);
}

KateTabsPluginView::KateTabsPluginView(Kate::MainWindow *window) :
    Kate::PluginView(window)
{
    m_tabbar = new KateTabBar(0);

    QBoxLayout *layout = qobject_cast <QBoxLayout*> (window->centralWidget()->layout());
    layout->insertWidget(0, m_tabbar);

    foreach(KTextEditor::Document* doc, Kate::application()->documentManager()->documents()) {
        m_tabbar->addDocument(doc);
    }

    connect(Kate::application()->documentManager(), SIGNAL(documentCreated(KTextEditor::Document*)),
            m_tabbar, SLOT(addDocument(KTextEditor::Document*)));
    connect(Kate::application()->documentManager(), SIGNAL(documentWillBeDeleted(KTextEditor::Document*)),
            m_tabbar, SLOT(removeDocument(KTextEditor::Document*)));
    connect(m_tabbar, SIGNAL(currentChanged(int)), SLOT(slotOpenDocument(int)));
    connect(m_tabbar, SIGNAL(closeRequest(int)), SLOT(slotCloseDocumentByIndex(int)));
    connect(mainWindow(), SIGNAL(viewChanged()), SLOT(slotActivateDocument()));
}

KateTabsPluginView::~KateTabsPluginView()
{
}

void KateTabsPluginView::slotOpenDocument(int index)
{
    mainWindow()->activateView(m_tabbar->documentFromIndex(index));
}

void KateTabsPluginView::slotActivateDocument()
{
    if (mainWindow()->activeView()) {
        m_tabbar->activateDocument(mainWindow()->activeView()->document());
    }
}

void KateTabsPluginView::slotCloseDocumentByIndex(int index)
{
    KTextEditor::Document *document = m_tabbar->documentFromIndex(index);
    Kate::application()->documentManager()->closeDocument(document);
}
