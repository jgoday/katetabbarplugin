/* This file is part of the KDE project

   Copyright (C) 2008 Javier Goday <jgoday @ gmail.com>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.
*/
#include "katetabsplugin.h"
#include "katetabspluginconfigpage.h"
#include "katetabbar.h"

// qt headers
#include <QLabel>
#include <QVBoxLayout>

// kde headers
#include <KConfigGroup>
#include <KDebug>
#include <KGenericFactory>
#include <KVBox>

// kate headers
#include <kate/application.h>
#include <ktexteditor/document.h>
#include <ktexteditor/view.h>


K_EXPORT_COMPONENT_FACTORY(katetabsplugin, KGenericFactory<KateTabsPlugin>("katetabsplugin"))

KateTabsPlugin::KateTabsPlugin(QObject *parent, const QStringList &parameters) :
Kate::Plugin(qobject_cast <Kate::Application *> (parent)),
    m_view(0)
{
    Q_UNUSED (parameters)
}

KateTabsPlugin::~KateTabsPlugin()
{/*
    delete m_view;*/
}

Kate::PluginView *KateTabsPlugin::createView(Kate::MainWindow *window)
{
    m_view = new KateTabsPluginView(window);

    return m_view;
}

uint KateTabsPlugin::configPages() const
{
    return 1;
}

Kate::PluginConfigPage *KateTabsPlugin::configPage(uint number, QWidget *parent , const char *name)
{
    Q_UNUSED(number)
    Q_UNUSED(name)

    KateTabsPluginConfigPage *page = new KateTabsPluginConfigPage(parent);

    connect(page, SIGNAL(applySettings()), m_view, SLOT(loadConfig()));

    return page;
}

QString KateTabsPlugin::configPageName(uint number) const
{
    Q_UNUSED(number)
    return i18n("Tabs");
}

QString KateTabsPlugin::configPageFullName(uint number) const
{
    Q_UNUSED(number)
    return i18n("Configure kate tabbar");
}

KIcon KateTabsPlugin::configPageIcon(uint number) const
{
    Q_UNUSED(number)
    return KIcon("tab-duplicate");
}

void KateTabsPlugin::loadConfig()
{
    KateTabsPluginView *view = qobject_cast <KateTabsPluginView *> (m_view);
    view->loadConfig();
}

KateTabsPluginView::KateTabsPluginView(Kate::MainWindow *window) :
    Kate::PluginView(window)
{
    KVBox *layout = qobject_cast <KVBox*> (window->centralWidget());
    m_tabbar = new KateTabBar(layout);

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

void KateTabsPluginView::readSessionConfig(KConfigBase* config, const QString& groupPrefix)
{
    Q_UNUSED(config)
    Q_UNUSED(groupPrefix)

    KConfigGroup cg(KGlobal::config(), "KateTabBarPlugin");
    m_tabbar->setShapeAsInt(cg.readEntry("tabs_shape", 0));
    insertView(cg.readEntry("tabbar_position", 0));
}

void KateTabsPluginView::writeSessionConfig(KConfigBase* config, const QString& groupPrefix)
{
    Q_UNUSED(config)
    Q_UNUSED(groupPrefix)

    KConfigGroup cg(KGlobal::config(), "KateTabBarPlugin");
    cg.writeEntry("tabs_shape", m_tabbar->shapeAsInt());
    cg.writeEntry("tabbar_position", m_tabbar->position());
}

void KateTabsPluginView::loadConfig()
{
    m_tabbar->setShapeAsInt(KConfigGroup(KGlobal::config(), "KateTabBarPlugin").readEntry("tabs_shape", 0));

    insertView(KConfigGroup(KGlobal::config(), "KateTabBarPlugin").readEntry("tabbar_position", 0));
}

void KateTabsPluginView::insertView(int position)
{
    QVBoxLayout *vlayout = qobject_cast <QVBoxLayout *> (m_tabbar->parentWidget()->layout());
    vlayout->removeWidget(m_tabbar);

    switch(position) {
        case KateTabBar::Top:
            vlayout->insertWidget(0, m_tabbar);
            break;
        case KateTabBar::Bottom:
            vlayout->insertWidget(1, m_tabbar);
            break;
    };

    m_tabbar->setPosition(position);
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

