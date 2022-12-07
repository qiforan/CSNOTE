# Ubuntu 的安装及配置

以 `Ubuntu 18.04 lts` 为例，在同一块硬盘安装双系统。

## 优盘安装系统

1. 下载 iso，选择 [ubuntu-18.04.5-desktop-amd64.iso](https://releases.ubuntu.com/18.04/ubuntu-18.04.5-desktop-amd64.iso)，也可以选择[国内镜像](https://mirrors.ustc.edu.cn/ubuntu-releases/18.04/ubuntu-18.04.5-desktop-amd64.iso)

2. 使用 [rufus](https://rufus.ie/) 制作启动盘

3. 准备合适大小的空闲分区

3. 按 `F12` 进入 `BIOS`, 注意使用笔记本自带键盘

4. 直接给 `/` 分配全部分区

5. 更新显卡驱动

## 安装中文输入法

1. 从搜狗输入法 [官网](https://pinyin.sogou.com/linux/?r=pinyin) 下载 Linux 版本的输入法

2. 安装

```shell script
cd Downloads/
sudo dpkg -i sogoupinyin*.deb
# 如果报错
sudo apt  --fix-broken install
```

3. 进入 `Language Support` 界面，在 `Keyboard input method system` 一栏中选择 `ficix`， 然后点击 `Apply System-Wide`，并重启

4. 点击右上角的键盘标志，单击 `Configure` 项，进入下面的 `Input Method` 界面后，选择 `+` 号，进入 `Add input method` 界面，取消勾选 `Only Show Current Language`，添加搜狗输入法，并移到第一位

## 美化

1. 安装 `Unity Tweak Tool`

```shell script
sudo apt-get install unity-tweak-tool
```

2. `Tweaks` 配置

* 修改窗口的按钮位置(在左边还是右边)： `Windows` --> `Placement` 
* 显示或隐藏桌面上的图标： `Desktop` --> `Show Icons`
* 修改鼠标图标：`Appearance` --> `Cursor` (推荐 `Redglass`)

去掉 `Shell` 上无法修改的叹号，运行

```shell script
sudo apt-get install gnome-shell-extensions
```

安装完成后打开 `Extensions` --> `User themes` 


3. 修改主题和图标

* Mcmojave 主题 
* Numix 图标 

下载 [主题](https://www.opendesktop.org/s/Gnome/p/1275087)，解压到 `~/.themes/`，在 `Tweaks`  --> `Appearance` --> `Applications` 中选择主题

修改图标的方式是类似的(存放到 `~/.icons/`)，这里提供另一种方式安装 `numix` 图标

```shell script
sudo add-apt-repository ppa:numix/ppa
sudo apt-get update
sudo apt-get install numix-gtk-theme numix-icon-theme-circle
```

4. 安装 `Dash to Dock` 插件，并放置到底部


## clash

### 安装 clash

1. 下载对应的 clash 版本 [下载地址](https://github.com/Dreamacro/clash/releases)

2. 解压 clash

3. 将解压出的文件重命名成 clash

4. 将 clash 移动到 `/usr/bin/` 目录下

5. 赋予 clash 可执行权限

```bash
sudo chmod +x /usr/bin/clash
```

6. 检查 clash 是否安装成功

```bash
clash -v
```

### 修改配置

默认配置目录是 `$HOME/.config/clash`

配置文件的名称是 `config.yml`

如果要使用其他目录，可以使用 `-d` 控制配置目录

### systemd 服务脚本

在 `/lib/systemd/system/` 目录下创建 `clash@.service` 文件

```bash
sudo vim /lib/systemd/system/clash@.service
```

写入以下内容(不用修改)并保存:

```bash
[Unit]
Description=A rule based proxy in Go for %i.
After=network.target

[Service]
Type=simple
User=%i
Restart=on-abort
ExecStart=/usr/bin/clash

[Install]
WantedBy=multi-user.target
```

```bash
# 重新加载 systemd 模块
systemctl daemon-reload

# 启动 clash 服务
# user 表示的是当前用户名
systemctl start clash@user

# 设置开机自启
systemctl enable clash@user
```

## 问题

1. 双系统时间不同步

两种解决方法:

1.在 Ubuntu 中把计算机硬件时间改成系统显示的时间，即禁用 Ubuntu 的 UTC

>在 Ubuntu 16.04 版本以前，关闭 UTC 的方法是编辑 `/etc/default/rcS`，将 `UTC=yes` 改成 `UTC=no`
>但在 Ubuntu 16.04 使用 systemd 启动之后，时间改成了由 timedatectl 来管理，所以更改方法是
>`timedatectl set-local-rtc 1 --adjust-system-clock`
>执行后重启 Ubuntu

2.让 Windows 把硬件时间当作 UTC

>在命令行中输入下面命令
>`Reg add HKLM\SYSTEM\CurrentControlSet\Control\TimeZoneInformation /v RealTimeIsUniversal /t REG_DWORD /d 1`

倾向于第一种。

