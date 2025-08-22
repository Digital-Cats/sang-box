#pragma once

#include <QObject>
#include <QQmlApplicationEngine>
#include <QApplication>

#include <memory>

class Underhood : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool isDebug READ isDebug CONSTANT)

    using EnginePtr = std::shared_ptr<QQmlApplicationEngine>;
public:
    explicit Underhood(QApplication &app);

    void loadMainQml();
    EnginePtr getEngine();
    void hideWindowByDefault();

#ifndef NDEBUG
    void loadSrcQml();
#endif

public slots:
    void invokedReloadSrcQml();
    void reloadSrcQml();

signals:
    void engineIsLoaded();

private:
    void loadEngine();
    bool isDebug() const;

private:
    EnginePtr m_engine;
    QApplication &m_app;
};
