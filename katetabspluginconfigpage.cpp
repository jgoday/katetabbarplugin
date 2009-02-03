#include "katetabspluginconfigpage.h"
#include "katetabbar.h"

#include <QComboBox>
#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>

#include <KGenericFactory>
#include <KConfigGroup>
#include <KDebug>
#include <KLocale>

static const int DEFAULT_POSITION = KateTabBar::Top;
static const int DEFAULT_SHAPE    = QTabBar::RoundedSouth;

KateTabsPluginConfigPage::KateTabsPluginConfigPage(QWidget *parent) : Kate::PluginConfigPage(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    KConfigGroup cg(KGlobal::config(), "KateTabBarPlugin");

    // tabs position groupbox
    QGroupBox *positionBox = new QGroupBox(i18n("Tabs position"));
    QVBoxLayout *positionBoxLayout = new QVBoxLayout();
    positionBox->setLayout(positionBoxLayout);

    // tabbar position combobox
    m_tabbarPosition = new QComboBox();
    m_tabbarPosition->addItem(i18n("Bottom"), QVariant(KateTabBar::Bottom));
    m_tabbarPosition->addItem(i18n("Top"), QVariant(KateTabBar::Top));
    m_tabbarPosition->setCurrentIndex(cg.readEntry("tabbar_position", 0));

    // tabbar position
    QHBoxLayout *box1 = new QHBoxLayout();
    box1->addWidget(new QLabel(i18n("Tabbar position")));
    box1->addWidget(m_tabbarPosition);
    positionBoxLayout->addLayout(box1);

    // tabs shape combobox
    m_tabsShape = new QComboBox();
    m_tabsShape->addItem(i18n("Rounded north"), QVariant(QTabBar::RoundedNorth));
    m_tabsShape->addItem(i18n("Rounded shouth"), QVariant(QTabBar::RoundedSouth));
    m_tabsShape->setCurrentIndex(cg.readEntry("tabs_shape", 0));

    // tabs shape
    QHBoxLayout *box2 = new QHBoxLayout();
    box2->addWidget(new QLabel(i18n("Tabs shape")));
    box2->addWidget(m_tabsShape);
    positionBoxLayout->addLayout(box2);

    mainLayout->addWidget(positionBox);
    mainLayout->addStretch(1);

    connect(m_tabbarPosition, SIGNAL(currentIndexChanged(int)), SIGNAL(changed()));
    connect(m_tabsShape, SIGNAL(currentIndexChanged(int)), SIGNAL(changed()));
}

KateTabsPluginConfigPage::~KateTabsPluginConfigPage()
{
}

void KateTabsPluginConfigPage::apply()
{
    KConfigGroup config(KGlobal::config(), "KateTabBarPlugin");
    config.writeEntry("tabbar_position", m_tabbarPosition->itemData(m_tabbarPosition->currentIndex()).toInt());
    config.writeEntry("tabs_shape", m_tabsShape->itemData(m_tabsShape->currentIndex()).toInt());
    config.sync();

    emit applySettings();
}

void KateTabsPluginConfigPage::defaults()
{
    m_tabbarPosition->setCurrentIndex(DEFAULT_POSITION);
    m_tabsShape->setCurrentIndex(DEFAULT_SHAPE);
}

void KateTabsPluginConfigPage::reset()
{
}
