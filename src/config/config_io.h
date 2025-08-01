#ifndef CONFIG_IO_H
#define CONFIG_IO_H

#include <QString>

namespace config {

class ConfigIO
{
public:
    ConfigIO();
    ConfigIO(const QString& filePath);

    const QString& getConfigFilePath() const noexcept;
    void saveConfigFile(const QString &configContent);
    QString openConfigFile();
    bool fileConfigExists() const;

private:
    // Use timestamp as saved file name
    QString generateFileName() const;
    QString getConfigsFolder() const;

    const QString m_configFilePath;
};

}

#endif // CONFIG_IO_H
