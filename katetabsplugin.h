/* This file is part of the KDE project

   Copyright (C) 2008 Javier Goday <jgoday @ gmail.com>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.
*/
#ifndef KATETABSPLUGIN_H
#define KATETABSPLUGIN_H

#include <QObject>

#include <kxmlguiclient.h>

#include <kate/documentmanager.h>
#include <kate/mainwindow.h>
#include <kate/plugin.h>

namespace KTextEditor {
    class Document;
};
class QLabel;
class KateTabBar;

class KateTabsPlugin : public Kate::Plugin
{
    Q_OBJECT
public:
    explicit KateTabsPlugin(QObject *parent = 0, const QStringList &parameters = QStringList());
    virtual ~KateTabsPlugin();

    Kate::PluginView *createView(Kate::MainWindow *window);
};

class KateTabsPluginView : public Kate::PluginView, public KXMLGUIClient
{
Q_OBJECT
public:
    KateTabsPluginView(Kate::MainWindow *window);
    ~KateTabsPluginView();

private slots:
    void slotOpenDocument(int index);
    void slotActivateDocument();
    void slotCloseDocumentByIndex(int index);

private:
    KateTabBar *m_tabbar;
};
#endif
