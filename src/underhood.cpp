#include "underhood.h"

#include <QQuickWindow>

Underhood::Underhood(QApplication &app)
    : QObject{}
    , m_engine(nullptr)
    , m_app(app)
{
    loadEngine();
}

void Underhood::loadMainQml()
{
    m_engine->loadFromModule("SangBox", "Main");
}

Underhood::EnginePtr Underhood::getEngine()
{
    return m_engine;
}

#ifndef NDEBUG
void Underhood::loadSrcQml()
{
    m_engine->load("file:/" + QLatin1String(SOURCE_ROOT) + "/src/Main.qml");
}

void Underhood::invokedReloadSrcQml()
{
    QMetaObject::invokeMethod(this, "reloadSrcQml", Qt::QueuedConnection);
}

void Underhood::reloadSrcQml()
{
    m_engine.reset();
    loadEngine();
    loadSrcQml();
}
#endif

void Underhood::loadEngine()
{
    m_engine = std::make_shared<QQmlApplicationEngine>();
    QObject::connect(
        m_engine.get(),
        &QQmlApplicationEngine::objectCreationFailed,
        &m_app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    emit engineIsLoaded();
}

bool Underhood::isDebug() const
{
#ifndef NDEBUG
    return true;
#else
    return false;
#endif
}
