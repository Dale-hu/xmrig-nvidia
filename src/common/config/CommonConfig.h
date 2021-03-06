/* XMRig
 * Copyright 2014      imonero <https://github.com/global-blockchain>
 * Copyright 2016-2017 XMRig       <admin@imonero.org>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __COMMONCONFIG_H__
#define __COMMONCONFIG_H__


#include <vector>


#include "common/interfaces/IConfig.h"
#include "common/net/Pool.h"
#include "common/utils/c_str.h"
#include "common/xmrig.h"


namespace xmrig {


class CommonConfig : public IConfig
{
public:
    CommonConfig();
    ~CommonConfig();

    inline bool isApiIPv6() const                  { return m_apiIPv6; }
    inline bool isApiRestricted() const            { return m_apiRestricted; }
    inline bool isBackground() const               { return m_background; }
    inline bool isColors() const                   { return m_colors; }
    inline bool isDryRun() const                   { return m_dryRun; }
    inline bool isSyslog() const                   { return m_syslog; }
    inline const char *apiToken() const            { return m_apiToken.data(); }
    inline const char *apiWorkerId() const         { return m_apiWorkerId.data(); }
    inline const char *logFile() const             { return m_logFile.data(); }
    inline const char *userAgent() const           { return m_userAgent.data(); }
    inline const std::vector<Pool> &pools() const  { return m_activePools; }
    inline int apiPort() const                     { return m_apiPort; }
    inline int donateLevel() const                 { return m_donateLevel; }
    inline int printTime() const                   { return m_printTime; }
    inline int retries() const                     { return m_retries; }
    inline int retryPause() const                  { return m_retryPause; }
    inline void setColors(bool colors)             { m_colors = colors; }

    inline bool isWatch() const override               { return m_watch && !m_fileName.isNull(); }
    inline const Algorithm &algorithm() const override { return m_algorithm; }
    inline const char *fileName() const override       { return m_fileName.data(); }

    bool save() override;

protected:
    enum State {
        NoneState,
        ReadyState,
        ErrorState
    };

    bool finalize() override;
    bool parseBoolean(int key, bool enable) override;
    bool parseString(int key, const char *arg) override;
    bool parseUint64(int key, uint64_t arg) override;
    void setFileName(const char *fileName) override;

    Algorithm m_algorithm;
    bool m_adjusted;
    bool m_apiIPv6;
    bool m_apiRestricted;
    bool m_background;
    bool m_colors;
    bool m_dryRun;
    bool m_syslog;
    bool m_watch;
    int m_apiPort;
    int m_donateLevel;
    int m_printTime;
    int m_retries;
    int m_retryPause;
    State m_state;
    std::vector<Pool> m_activePools;
    std::vector<Pool> m_pools;
    xmrig::c_str m_apiToken;
    xmrig::c_str m_apiWorkerId;
    xmrig::c_str m_fileName;
    xmrig::c_str m_logFile;
    xmrig::c_str m_userAgent;

private:
    bool parseInt(int key, int arg);
};


} /* namespace xmrig */

#endif /* __COMMONCONFIG_H__ */
