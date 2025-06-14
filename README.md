# sang-box

[Russian](docs/README.ru_RU.md)

A Windows GUI client for [sing-box](https://github.com/SagerNet/sing-box).
It is developed using Qt C++ and QML with [QmlMaterial](https://github.com/hypengw/QmlMaterial) .

## Support operating systems

- Windows 10/11 x64

## How to use

1. Download compressed package file from [Release](https://github.com/Roker2/sang-box/releases).
2. Install or unzip the program.
3. Import the configuration file. 
4. Start the proxy.

### System proxy

Enable `set_system_proxy` in configuration file.

```
{
  "inbounds": [
    {
      "type": "http",
      ...
      "set_system_proxy": true
      ...
    }
}
```
### TUN mode

Set up a tun inbound. enable running with administrator privileges in the program settings.

```
{
  "inbounds": [
    {
      "type": "tun",
      ...
    }
}
```

## How to update sing-box core

Replace `sing-box.exe` in the sang-box installation directory.

## Screenshot

### Overview Tab

<div align="center">
  <img src="docs/images/en_US/overview_tab.png" alt="Overview Tab" width="500">
</div>

### Settings Tab

<div align="center">
  <img src="docs/images/en_US/settings_tab.png" alt="Settings Tab" width="500">
</div>

