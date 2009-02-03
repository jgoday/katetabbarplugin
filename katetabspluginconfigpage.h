#ifndef KATETABSPLUGINCONFIGPAGE_H
#define KATETABSPLUGINCONFIGPAGE_H

#include <kate/pluginconfigpageinterface.h>

class QComboBox;
class KateTabsPlugin;

class KateTabsPluginConfigPage : public Kate::PluginConfigPage
{
    Q_OBJECT
public:
    KateTabsPluginConfigPage(QWidget *parent); 
    ~KateTabsPluginConfigPage();

    void apply();
    void defaults();
    void reset();

signals:
    void applySettings();

private:
    QComboBox  *m_tabbarPosition;
    QComboBox  *m_tabsShape;
};
#endif
