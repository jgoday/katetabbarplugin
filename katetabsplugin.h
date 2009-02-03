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
#include <kate/pluginconfigpageinterface.h>

namespace KTextEditor {
    class Document;
};
class QLabel;
class KateTabBar;

class KateTabsPlugin : public Kate::Plugin, public Kate::PluginConfigPageInterface
{
    Q_OBJECT
    Q_INTERFACES(Kate::PluginConfigPageInterface)
public:
    explicit KateTabsPlugin(QObject *parent = 0, const QStringList &parameters = QStringList());
    virtual ~KateTabsPlugin();

    Kate::PluginView *createView(Kate::MainWindow *window);

    uint configPages() const;
    Kate::PluginConfigPage *configPage(uint number = 0, QWidget *parent = 0, const char *name = 0);
    QString configPageName(uint number = 0) const;
    QString configPageFullName(uint number = 0) const;
    KIcon configPageIcon(uint number = 0) const;

    void loadConfig();

private:
    Kate::PluginView *m_view;
};

class KateTabsPluginView : public Kate::PluginView, public KXMLGUIClient
{
Q_OBJECT
public:
    KateTabsPluginView(Kate::MainWindow *window);
    ~KateTabsPluginView();

    virtual void readSessionConfig(KConfigBase* config, const QString& groupPrefix);
    virtual void writeSessionConfig(KConfigBase* config, const QString& groupPrefix);

public slots:
    void loadConfig();

private slots:
    void slotOpenDocument(int index);
    void slotActivateDocument();
    void slotCloseDocumentByIndex(int index);

private:
    void insertView(int position);

private:
    KateTabBar *m_tabbar;
};

#endif
